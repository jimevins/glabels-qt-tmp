/*  MainWindow.cpp
 *
 *  Copyright (C) 2014  Jim Evins <evins@snaught.com>
 *
 *  This file is part of gLabels-qt.
 *
 *  gLabels-qt is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  gLabels-qt is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with gLabels-qt.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MainWindow.h"

#include <QSettings>
#include <QStatusBar>
#include <QFrame>
#include <QAction>
#include <QCloseEvent>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QLabel>
#include <QDebug>

#include "libglabels/Db.h"
#include "View.h"
#include "ObjectEditor.h"
#include "LabelModel.h"
#include "LabelModelBoxObject.h"
#include "Icons.h"
#include "File.h"
#include "Help.h"


namespace glabels
{

	///
	/// Static window list
	///
	QList<MainWindow*> MainWindow::smWindowList;


	///
	/// Constructor
	///
	MainWindow::MainWindow()
	{
		mView = new View();
		mObjectEditor = new ObjectEditor();

		createActions();
		createMenus();
		createToolBars();
		createStatusBar();

		QWidget* editorPage = createEditorPage();
		
		setCentralWidget( editorPage );
		mModel = 0;

		setDocVerbsEnabled( false );
		setPasteVerbsEnabled( false );
		setTitle();

		readSettings();

		smWindowList.push_back( this );
	}


	///
	/// Destructor
	///
	MainWindow::~MainWindow()
	{
		smWindowList.removeOne( this );
	}


	///
	/// Get model accessor
	///
	LabelModel* MainWindow::model() const
	{
		return mModel;
	}


	///
	/// Set model accessor
	///
	void MainWindow::setModel( LabelModel *label )
	{
		mModel = label;
		mView->setModel( mModel );

		setDocVerbsEnabled( true );
		setSelectionVerbsEnabled( false );
		setMultiSelectionVerbsEnabled( false );
		setTitle();

		connect( mModel, SIGNAL(nameChanged()), this, SLOT(onNameChanged()) );
		connect( mModel, SIGNAL(modifiedChanged()), this, SLOT(onModifiedChanged()) );
		connect( mModel, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()) );
		connect( mModel, SIGNAL(changed()), this, SLOT(onLabelChanged()) );
	}


	///
	/// Is window empty?
	///
	bool MainWindow::isEmpty() const
	{
		return mModel == 0;
	}

	///
	/// Get window list
	///
	QList<MainWindow*> MainWindow::windowList()
	{
		return smWindowList;
	}


	///
	/// Close Event Handler
	///
	void MainWindow::closeEvent( QCloseEvent *event )
	{
		writeSettings();
		event->accept();
	}


	///
	/// Create Actions
	///
	void MainWindow::createActions()
	{
		/* File actions */
		fileNewAction = new QAction( tr("&New..."), this );
		fileNewAction->setIcon( QIcon::fromTheme( "document-new", Icons::Fallback::FileNew() ) );
		fileNewAction->setShortcut( QKeySequence::New );
		fileNewAction->setStatusTip( tr("Create a new file") );
		connect( fileNewAction, SIGNAL(triggered()), this, SLOT(fileNew()) );

		fileOpenAction = new QAction( tr("&Open..."), this );
		fileOpenAction->setIcon( QIcon::fromTheme( "document-open", Icons::Fallback::FileOpen() ) );
		fileOpenAction->setShortcut( QKeySequence::Open );
		fileOpenAction->setStatusTip( tr("Open a file") );
		connect( fileOpenAction, SIGNAL(triggered()), this, SLOT(fileOpen()) );

		fileSaveAction = new QAction( tr("&Save"), this );
		fileSaveAction->setIcon( QIcon::fromTheme( "document-save", Icons::Fallback::FileSave() ) );
		fileSaveAction->setShortcut( QKeySequence::Save );
		fileSaveAction->setStatusTip( tr("Save current file") );
		connect( fileSaveAction, SIGNAL(triggered()), this, SLOT(fileSave()) );

		fileSaveAsAction = new QAction( tr("Save &As..."), this );
		fileSaveAsAction->setIcon( QIcon::fromTheme( "document-save-as", Icons::Fallback::FileSaveAs() ) );
		fileSaveAsAction->setShortcut( QKeySequence::SaveAs );
		fileSaveAsAction->setStatusTip( tr("Save current file to a different name") );
		connect( fileSaveAsAction, SIGNAL(triggered()), this, SLOT(fileSaveAs()) );

		filePrintAction = new QAction( tr("&Print..."), this );
		filePrintAction->setIcon( QIcon::fromTheme( "document-print", Icons::Fallback::FilePrint() ) );
		filePrintAction->setShortcut( QKeySequence::Print );
		filePrintAction->setStatusTip( tr("Print the current file") );
		connect( filePrintAction, SIGNAL(triggered()), this, SLOT(filePrint()) );

		filePropertiesAction = new QAction( tr("Properties..."), this );
		filePropertiesAction->setIcon( QIcon::fromTheme( "document-properties" ) );
		filePropertiesAction->setStatusTip( tr("Modify document properties") );
		connect( filePropertiesAction, SIGNAL(triggered()), this, SLOT(fileProperties()) );

		fileTemplateDesignerAction = new QAction( tr("Template &Designer..."), this );
		fileTemplateDesignerAction->setStatusTip( tr("Create custom templates") );
		connect( fileTemplateDesignerAction, SIGNAL(triggered()), this, SLOT(fileTemplateDesigner()) );

		fileCloseAction = new QAction( tr("&Close"), this );
		fileCloseAction->setIcon( QIcon::fromTheme( "window-close" ) );
		fileCloseAction->setShortcut( QKeySequence::Close );
		fileCloseAction->setStatusTip( tr("Close the current window") );
		connect( fileCloseAction, SIGNAL(triggered()), this, SLOT(fileClose()) );

		fileExitAction = new QAction( tr("E&xit"), this );
		fileExitAction->setIcon( QIcon::fromTheme( "application-exit" ) );
		fileExitAction->setShortcut( QKeySequence::Quit );
		fileExitAction->setStatusTip( tr("Exit glabels") );
		connect( fileExitAction, SIGNAL(triggered()), this, SLOT(fileExit()) );


		/* Edit actions */
		editUndoAction = new QAction( tr("Undo"), this );
		editUndoAction->setIcon( QIcon::fromTheme( "edit-undo" ) );
		editUndoAction->setShortcut( QKeySequence::Undo );
		editUndoAction->setStatusTip( tr("Undo") );
		connect( editUndoAction, SIGNAL(triggered()), this, SLOT(editUndo()) );

		editRedoAction = new QAction( tr("Redo"), this );
		editRedoAction->setIcon( QIcon::fromTheme( "edit-redo" ) );
		editRedoAction->setShortcut( QKeySequence::Redo );
		editRedoAction->setStatusTip( tr("Redo") );
		connect( editRedoAction, SIGNAL(triggered()), this, SLOT(editRedo()) );

		editCutAction = new QAction( tr("Cut"), this );
		editCutAction->setIcon( QIcon::fromTheme( "edit-cut", Icons::Fallback::EditCut() ) );
		editCutAction->setShortcut( QKeySequence::Cut );
		editCutAction->setStatusTip( tr("Cut the selection") );
		connect( editCutAction, SIGNAL(triggered()), this, SLOT(editCut()) );

		editCopyAction = new QAction( tr("&Copy"), this );
		editCopyAction->setIcon( QIcon::fromTheme( "edit-copy", Icons::Fallback::EditCopy() ) );
		editCopyAction->setShortcut( QKeySequence::Copy );
		editCopyAction->setStatusTip( tr("Copy the selection") );
		connect( editCopyAction, SIGNAL(triggered()), this, SLOT(editCopy()) );

		editPasteAction = new QAction( tr("&Paste"), this );
		editPasteAction->setIcon( QIcon::fromTheme( "edit-paste", Icons::Fallback::EditPaste() ) );
		editPasteAction->setShortcut( QKeySequence::Paste );
		editPasteAction->setStatusTip( tr("Paste the clipboard") );
		connect( editPasteAction, SIGNAL(triggered()), this, SLOT(editPaste()) );

		editDeleteAction = new QAction( tr("&Delete"), this );
		editDeleteAction->setIcon( QIcon::fromTheme( "edit-delete" ) );
		editDeleteAction->setShortcut( QKeySequence::Delete );
		editDeleteAction->setStatusTip( tr("Delete the selected objects") );
		connect( editDeleteAction, SIGNAL(triggered()), this, SLOT(editDelete()) );

		editSelectAllAction = new QAction( tr("Select &All"), this );
		editSelectAllAction->setIcon( QIcon::fromTheme( "edit-select-all" ) );
		editSelectAllAction->setShortcut( QKeySequence::SelectAll );
		editSelectAllAction->setStatusTip( tr("Select all objects") );
		connect( editSelectAllAction, SIGNAL(triggered()), this, SLOT(editSelectAll()) );

		editUnSelectAllAction = new QAction( tr("Un-select All"), this );
		editUnSelectAllAction->setIcon( QIcon::fromTheme( "edit-unselect-all" ) );
		editUnSelectAllAction->setStatusTip( tr("Remove all selections") );
		connect( editUnSelectAllAction, SIGNAL(triggered()), this, SLOT(editUnSelectAll()) );

		editPreferencesAction = new QAction( tr("Preferences"), this );
		editPreferencesAction->setIcon( QIcon::fromTheme( "edit-preferences" ) );
		editPreferencesAction->setShortcut( QKeySequence::Preferences );
		editPreferencesAction->setStatusTip( tr("Configure the application") );
		connect( editPreferencesAction, SIGNAL(triggered()), this, SLOT(editPreferences()) );


		/* View actions */
		viewFileToolBarAction = new QAction( tr("File"), this );
		viewFileToolBarAction->setCheckable( true );
		viewFileToolBarAction->setStatusTip( tr("Change visibility of file toolbar in current window") );
		connect( viewFileToolBarAction, SIGNAL(toggled(bool)), this, SLOT(viewFileToolBar(bool)) );

		viewEditorToolBarAction = new QAction( tr("Editor"), this );
		viewEditorToolBarAction->setCheckable( true );
		viewEditorToolBarAction->setStatusTip( tr("Change visibility of editor toolbar in current window") );
		connect( viewEditorToolBarAction, SIGNAL(toggled(bool)), this, SLOT(viewEditorToolBar(bool)) );


		viewGridAction = new QAction( tr("Grid"), this );
		viewGridAction->setCheckable( true );
		viewGridAction->setStatusTip( tr("Change visibility of the grid in current window") );
		connect( viewGridAction, SIGNAL(toggled(bool)), this, SLOT(viewGrid(bool)) );

		viewMarkupAction = new QAction( tr("Markup"), this );
		viewMarkupAction->setCheckable( true );
		viewMarkupAction->setStatusTip( tr("Change visibility of markup lines in current window") );
		connect( viewMarkupAction, SIGNAL(toggled(bool)), this, SLOT(viewMarkup(bool)) );

		viewZoomInAction = new QAction( tr("Zoom &In"), this );
		viewZoomInAction->setIcon( QIcon::fromTheme( "zoom-in", Icons::Fallback::ZoomIn() ) );
		viewZoomInAction->setShortcut( QKeySequence::ZoomIn );
		viewZoomInAction->setStatusTip( tr("Increase magnification") );
		connect( viewZoomInAction, SIGNAL(triggered()), this, SLOT(viewZoomIn()) );

		viewZoomOutAction = new QAction( tr("Zoom &Out"), this );
		viewZoomOutAction->setIcon( QIcon::fromTheme( "zoom-out", Icons::Fallback::ZoomOut() ) );
		viewZoomOutAction->setShortcut( QKeySequence::ZoomOut );
		viewZoomOutAction->setStatusTip( tr("Decrease magnification") );
		connect( viewZoomOutAction, SIGNAL(triggered()), this, SLOT(viewZoomOut()) );

		viewZoom1To1Action = new QAction( tr("Zoom &1 to 1"), this );
		viewZoom1To1Action->setIcon( QIcon::fromTheme( "zoom-original", Icons::Fallback::ZoomOriginal() ) );
		viewZoom1To1Action->setStatusTip( tr("Restore scale to 100%") );
		connect( viewZoom1To1Action, SIGNAL(triggered()), this, SLOT(viewZoom1To1()) );

		viewZoomToFitAction = new QAction( tr("Zoom to &Fit"), this );
		viewZoomToFitAction->setIcon( QIcon::fromTheme( "zoom-fit-best", Icons::Fallback::ZoomBestFit() ) );
		viewZoomToFitAction->setStatusTip( tr("Set scale to fit window") );
		connect( viewZoomToFitAction, SIGNAL(triggered()), this, SLOT(viewZoomToFit()) );


		/* Object actions */
		objectsArrowModeAction = new QAction( tr("Select Mode"), this );
		objectsArrowModeAction->setIcon( Icons::Arrow() );
		objectsArrowModeAction->setStatusTip( tr("Select, move and modify objects") );
		connect( objectsArrowModeAction, SIGNAL(triggered()), this, SLOT(objectsArrowMode()) );

		objectsCreateTextAction = new QAction( tr("Text"), this );
		objectsCreateTextAction->setIcon( Icons::Text() );
		objectsCreateTextAction->setStatusTip( tr("Create text object") );
		connect( objectsCreateTextAction, SIGNAL(triggered()), this, SLOT(objectsCreateText()) );

		objectsCreateBoxAction = new QAction( tr("Box"), this );
		objectsCreateBoxAction->setIcon( Icons::Box() );
		objectsCreateBoxAction->setStatusTip( tr("Create box object") );
		connect( objectsCreateBoxAction, SIGNAL(triggered()), this, SLOT(objectsCreateBox()) );

		objectsCreateLineAction = new QAction( tr("Line"), this );
		objectsCreateLineAction->setIcon( Icons::Line() );
		objectsCreateLineAction->setStatusTip( tr("Create line object") );
		connect( objectsCreateLineAction, SIGNAL(triggered()), this, SLOT(objectsCreateLine()) );

		objectsCreateEllipseAction = new QAction( tr("Ellipse"), this );
		objectsCreateEllipseAction->setIcon( Icons::Ellipse() );
		objectsCreateEllipseAction->setStatusTip( tr("Create ellipse/circle object") );
		connect( objectsCreateEllipseAction, SIGNAL(triggered()), this, SLOT(objectsCreateEllipse()) );

		objectsCreateImageAction = new QAction( tr("Image"), this );
		objectsCreateImageAction->setIcon( Icons::Image() );
		objectsCreateImageAction->setStatusTip( tr("Create image object") );
		connect( objectsCreateImageAction, SIGNAL(triggered()), this, SLOT(objectsCreateImage()) );

		objectsCreateBarcodeAction = new QAction( tr("Barcode"), this );
		objectsCreateBarcodeAction->setIcon( Icons::Barcode() );
		objectsCreateBarcodeAction->setStatusTip( tr("Create barcode object") );
		connect( objectsCreateBarcodeAction, SIGNAL(triggered()), this, SLOT(objectsCreateBarcode()) );

		objectsOrderRaiseAction = new QAction( tr("Bring To Front"), this );
		objectsOrderRaiseAction->setIcon( Icons::OrderTop() );
		objectsOrderRaiseAction->setStatusTip( tr("Raise selection to top") );
		connect( objectsOrderRaiseAction, SIGNAL(triggered()), this, SLOT(objectsOrderRaise()) );

		objectsOrderLowerAction = new QAction( tr("Send To Back"), this );
		objectsOrderLowerAction->setIcon( Icons::OrderBottom() );
		objectsOrderLowerAction->setStatusTip( tr("Lower selection to bottom") );
		connect( objectsOrderLowerAction, SIGNAL(triggered()), this, SLOT(objectsOrderLower()) );

		objectsXformRotateLeftAction = new QAction( tr("Rotate Left"), this );
		objectsXformRotateLeftAction->setIcon( Icons::RotateLeft() );
		objectsXformRotateLeftAction->setStatusTip( tr("Rotate object(s) 90 degrees counter-clockwise") );
		connect( objectsXformRotateLeftAction, SIGNAL(triggered()), this, SLOT(objectsXformRotateLeft()) );

		objectsXformRotateRightAction = new QAction( tr("Rotate Right"), this );
		objectsXformRotateRightAction->setIcon( Icons::RotateRight() );
		objectsXformRotateRightAction->setStatusTip( tr("Rotate object(s) 90 degrees clockwise") );
		connect( objectsXformRotateRightAction, SIGNAL(triggered()), this, SLOT(objectsXformRotateRight()) );

		objectsXformFlipHorizAction = new QAction( tr("Flip Horizontally"), this );
		objectsXformFlipHorizAction->setIcon( Icons::FlipHoriz() );
		objectsXformFlipHorizAction->setStatusTip( tr("Flip object(s) horizontally") );
		connect( objectsXformFlipHorizAction, SIGNAL(triggered()), this, SLOT(objectsXformFlipHoriz()) );

		objectsXformFlipVertAction = new QAction( tr("Flip Vertically"), this );
		objectsXformFlipVertAction->setIcon( Icons::FlipVert() );
		objectsXformFlipVertAction->setStatusTip( tr("Flip object(s) vertically") );
		connect( objectsXformFlipVertAction, SIGNAL(triggered()), this, SLOT(objectsXformFlipVert()) );

		objectsAlignLeftAction = new QAction( tr("Align Left"), this );
		objectsAlignLeftAction->setIcon( Icons::AlignLeft() );
		objectsAlignLeftAction->setStatusTip( tr("Align objects to left edges") );
		connect( objectsAlignLeftAction, SIGNAL(triggered()), this, SLOT(objectsAlignLeft()) );

		objectsAlignHCenterAction = new QAction( tr("Align Center"), this );
		objectsAlignHCenterAction->setIcon( Icons::AlignHCenter() );
		objectsAlignHCenterAction->setStatusTip( tr("Align objects to horizontal centers") );
		connect( objectsAlignHCenterAction, SIGNAL(triggered()), this, SLOT(objectsAlignHCenter()) );

		objectsAlignRightAction = new QAction( tr("Align Right"), this );
		objectsAlignRightAction->setIcon( Icons::AlignRight() );
		objectsAlignRightAction->setStatusTip( tr("Align objects to right edges") );
		connect( objectsAlignRightAction, SIGNAL(triggered()), this, SLOT(objectsAlignRight()) );

		objectsAlignTopAction = new QAction( tr("Align Top"), this );
		objectsAlignTopAction->setIcon( Icons::AlignTop() );
		objectsAlignTopAction->setStatusTip( tr("Align objects to top edges") );
		connect( objectsAlignTopAction, SIGNAL(triggered()), this, SLOT(objectsAlignTop()) );

		objectsAlignVCenterAction = new QAction( tr("Align Middle"), this );
		objectsAlignVCenterAction->setIcon( Icons::AlignVCenter() );
		objectsAlignVCenterAction->setStatusTip( tr("Align objects to vertical centers") );
		connect( objectsAlignVCenterAction, SIGNAL(triggered()), this, SLOT(objectsAlignVCenter()) );

		objectsAlignBottomAction = new QAction( tr("Align Bottom"), this );
		objectsAlignBottomAction->setIcon( Icons::AlignBottom() );
		objectsAlignBottomAction->setStatusTip( tr("Align objects to bottom edges") );
		connect( objectsAlignBottomAction, SIGNAL(triggered()), this, SLOT(objectsAlignBottom()) );

		objectsCenterHorizAction = new QAction( tr("Center Horizontally"), this );
		objectsCenterHorizAction->setIcon( Icons::CenterHoriz() );
		objectsCenterHorizAction->setStatusTip( tr("Horizontally center objects in label") );
		connect( objectsCenterHorizAction, SIGNAL(triggered()), this, SLOT(objectsCenterHoriz()) );

		objectsCenterVertAction = new QAction( tr("Center Vertically"), this );
		objectsCenterVertAction->setIcon( Icons::CenterVert() );
		objectsCenterVertAction->setStatusTip( tr("Vertically center objects in label") );
		connect( objectsCenterVertAction, SIGNAL(triggered()), this, SLOT(objectsCenterVert()) );

		objectsMergePropertiesAction = new QAction( tr("Merge Properties..."), this );
		objectsMergePropertiesAction->setIcon( Icons::Merge() );
		objectsMergePropertiesAction->setStatusTip( tr("Edit merge properties") );
		connect( objectsMergePropertiesAction, SIGNAL(triggered()), this, SLOT(objectsMergeProperties()) );


		/* Help actions */
		helpContentsAction = new QAction( tr("&Contents..."), this );
		helpContentsAction->setIcon( QIcon::fromTheme( "help-contents" ) );
		helpContentsAction->setShortcut( QKeySequence::HelpContents );
		helpContentsAction->setStatusTip( tr("Open gLabels manual") );
		connect( helpContentsAction, SIGNAL(triggered()), this, SLOT(helpContents()) );

		helpAboutAction = new QAction( tr("&About..."), this );
		helpAboutAction->setIcon( QIcon::fromTheme( "help-about" ) );
		helpAboutAction->setStatusTip( tr("About gLabels") );
		connect( helpAboutAction, SIGNAL(triggered()), this, SLOT(helpAbout()) );
	}


	///
	/// Create Menus
	///
	void MainWindow::createMenus()
	{
		fileMenu = menuBar()->addMenu( tr("&File") );
		fileMenu->addAction( fileNewAction );
		fileMenu->addAction( fileOpenAction );
		fileMenu->addAction( fileSaveAction );
		fileMenu->addAction( fileSaveAsAction );
		fileMenu->addSeparator();
		fileMenu->addAction( filePrintAction );
		fileMenu->addSeparator();
		fileMenu->addAction( filePropertiesAction );
		fileMenu->addAction( fileTemplateDesignerAction );
		fileMenu->addSeparator();
		fileMenu->addAction( fileCloseAction );
		fileMenu->addAction( fileExitAction );

		editMenu = menuBar()->addMenu( tr("&Edit") );
		editMenu->addAction( editUndoAction );
		editMenu->addAction( editRedoAction );
		editMenu->addSeparator();
		editMenu->addAction( editCutAction );
		editMenu->addAction( editCopyAction );
		editMenu->addAction( editPasteAction );
		editMenu->addAction( editDeleteAction );
		editMenu->addSeparator();
		editMenu->addAction( editSelectAllAction );
		editMenu->addAction( editUnSelectAllAction );
		editMenu->addSeparator();
		editMenu->addAction( editPreferencesAction );

		viewMenu = menuBar()->addMenu( tr("&View") );
		viewToolBarsMenu = viewMenu->addMenu( tr("Toolbars") );
		viewToolBarsMenu->addAction( viewFileToolBarAction );
		viewToolBarsMenu->addAction( viewEditorToolBarAction );
		viewMenu->addSeparator();
		viewMenu->addAction( viewGridAction );
		viewMenu->addAction( viewMarkupAction );
		viewMenu->addSeparator();
		viewMenu->addAction( viewZoomInAction );
		viewMenu->addAction( viewZoomOutAction );
		viewMenu->addAction( viewZoom1To1Action );
		viewMenu->addAction( viewZoomToFitAction );

		objectsMenu = menuBar()->addMenu( tr("&Objects") );
		objectsMenu->addAction( objectsArrowModeAction );
		objectsCreateMenu = objectsMenu->addMenu( tr("&Create") );
		objectsCreateMenu->addAction( objectsCreateTextAction );
		objectsCreateMenu->addAction( objectsCreateBoxAction );
		objectsCreateMenu->addAction( objectsCreateLineAction );
		objectsCreateMenu->addAction( objectsCreateEllipseAction );
		objectsCreateMenu->addAction( objectsCreateImageAction );
		objectsCreateMenu->addAction( objectsCreateBarcodeAction );
		objectsMenu->addSeparator();
		objectsOrderMenu = objectsMenu->addMenu( tr("&Order") );
		objectsOrderMenu->addAction( objectsOrderRaiseAction );
		objectsOrderMenu->addAction( objectsOrderLowerAction );
		objectsXformMenu = objectsMenu->addMenu( tr("&Rotate/Flip") );
		objectsXformMenu->addAction( objectsXformRotateLeftAction );
		objectsXformMenu->addAction( objectsXformRotateRightAction );
		objectsXformMenu->addAction( objectsXformFlipHorizAction );
		objectsXformMenu->addAction( objectsXformFlipVertAction );
		objectsAlignMenu = objectsMenu->addMenu( tr("&Alignment") );
		objectsAlignMenu->addAction( objectsAlignLeftAction );
		objectsAlignMenu->addAction( objectsAlignHCenterAction );
		objectsAlignMenu->addAction( objectsAlignRightAction );
		objectsAlignMenu->addSeparator();
		objectsAlignMenu->addAction( objectsAlignTopAction );
		objectsAlignMenu->addAction( objectsAlignVCenterAction );
		objectsAlignMenu->addAction( objectsAlignBottomAction );
		objectsCenterMenu = objectsMenu->addMenu( tr("Center") );
		objectsCenterMenu->addAction( objectsCenterHorizAction );
		objectsCenterMenu->addAction( objectsCenterVertAction );
		objectsMenu->addSeparator();
		objectsMenu->addAction( objectsMergePropertiesAction );

		helpMenu = menuBar()->addMenu( tr("&Help") );
		helpMenu->addAction( helpContentsAction );
		helpMenu->addAction( helpAboutAction );
	}


	///
	/// Create Tool Bars
	///
	void MainWindow::createToolBars()
	{
		fileToolBar = addToolBar( tr("&File") );
		fileToolBar->addAction( fileNewAction );
		fileToolBar->addAction( fileOpenAction );
		fileToolBar->addAction( fileSaveAction );
		fileToolBar->addSeparator();
		fileToolBar->addAction( filePrintAction );

		editorToolBar = new QToolBar( tr("&Editor") );
		editorToolBar->addAction( objectsArrowModeAction );
		editorToolBar->addSeparator();
		editorToolBar->addAction( objectsCreateTextAction );
		editorToolBar->addAction( objectsCreateBoxAction );
		editorToolBar->addAction( objectsCreateLineAction );
		editorToolBar->addAction( objectsCreateEllipseAction );
		editorToolBar->addAction( objectsCreateImageAction );
		editorToolBar->addAction( objectsCreateBarcodeAction );
		editorToolBar->addSeparator();
		editorToolBar->addAction( editCutAction );
		editorToolBar->addAction( editCopyAction );
		editorToolBar->addAction( editPasteAction );
		editorToolBar->addSeparator();
		editorToolBar->addAction( viewZoomInAction );
		editorToolBar->addAction( viewZoomOutAction );
		editorToolBar->addAction( viewZoom1To1Action );
		editorToolBar->addAction( viewZoomToFitAction );
	}


	///
	/// Create Status Bar
	///
	void MainWindow::createStatusBar()
	{
		zoomInfoLabel = new QLabel( " 999% " );
		zoomInfoLabel->setAlignment( Qt::AlignHCenter );
		zoomInfoLabel->setMinimumSize( zoomInfoLabel->sizeHint() );
		zoomInfoLabel->setFrameStyle( QFrame::Panel | QFrame::Sunken );

		cursorInfoLabel = new QLabel;
		cursorInfoLabel->setIndent( 3 );
		cursorInfoLabel->setFrameStyle( QFrame::Panel | QFrame::Sunken );

		statusBar()->addWidget( zoomInfoLabel );
		statusBar()->addWidget( cursorInfoLabel, 1 );

		onZoomChanged();
		onPointerExit();

		connect( mView, SIGNAL(zoomChanged()), this, SLOT(onZoomChanged()) );
		connect( mView, SIGNAL(pointerMoved(double, double)),
			 this, SLOT(onPointerMoved(double, double)) );
		connect( mView, SIGNAL(pointerExited()), this, SLOT(onPointerExit()) );
	}


	///
	/// Create Editor Page
	///
	QWidget* MainWindow::createEditorPage()
	{
		QWidget* page = new QWidget;

		QVBoxLayout* editorVLayout = new QVBoxLayout;
		editorVLayout->addWidget( editorToolBar );
		editorVLayout->addWidget( mView );

		QHBoxLayout* editorHLayout = new QHBoxLayout;
		editorHLayout->addLayout( editorVLayout );
		editorHLayout->addWidget( mObjectEditor );

		page->setLayout( editorHLayout );

		return page;
	}


	///
	/// Set enabled state of actions associated with a document.
	///
	void MainWindow::setDocVerbsEnabled( bool enabled )
	{
		filePropertiesAction->setEnabled( enabled );
		fileSaveAction->setEnabled( enabled );
		fileSaveAsAction->setEnabled( enabled );
		filePrintAction->setEnabled( enabled );
		editUndoAction->setEnabled( enabled );
		editRedoAction->setEnabled( enabled );
		editCutAction->setEnabled( enabled );
		editCopyAction->setEnabled( enabled );
		editPasteAction->setEnabled( enabled );
		editDeleteAction->setEnabled( enabled );
		editSelectAllAction->setEnabled( enabled );
		editUnSelectAllAction->setEnabled( enabled );
		viewZoomInAction->setEnabled( enabled );
		viewZoomOutAction->setEnabled( enabled );
		viewZoom1To1Action->setEnabled( enabled );
		viewZoomToFitAction->setEnabled( enabled );
		viewGridAction->setEnabled( enabled );
		viewMarkupAction->setEnabled( enabled );
		objectsArrowModeAction->setEnabled( enabled );
		objectsCreateMenu->setEnabled( enabled );
		objectsCreateTextAction->setEnabled( enabled );
		objectsCreateLineAction->setEnabled( enabled );
		objectsCreateBoxAction->setEnabled( enabled );
		objectsCreateEllipseAction->setEnabled( enabled );
		objectsCreateImageAction->setEnabled( enabled );
		objectsCreateBarcodeAction->setEnabled( enabled );
		objectsOrderMenu->setEnabled( enabled );
		objectsOrderRaiseAction->setEnabled( enabled );
		objectsOrderLowerAction->setEnabled( enabled );
		objectsXformMenu->setEnabled( enabled );
		objectsXformRotateLeftAction->setEnabled( enabled );
		objectsXformRotateRightAction->setEnabled( enabled );
		objectsXformFlipHorizAction->setEnabled( enabled );
		objectsXformFlipVertAction->setEnabled( enabled );
		objectsAlignMenu->setEnabled( enabled );
		objectsAlignLeftAction->setEnabled( enabled );
		objectsAlignRightAction->setEnabled( enabled );
		objectsAlignHCenterAction->setEnabled( enabled );
		objectsAlignTopAction->setEnabled( enabled );
		objectsAlignBottomAction->setEnabled( enabled );
		objectsAlignVCenterAction->setEnabled( enabled );
		objectsCenterMenu->setEnabled( enabled );
		objectsCenterHorizAction->setEnabled( enabled );
		objectsCenterVertAction->setEnabled( enabled );
		objectsMergePropertiesAction->setEnabled( enabled );
	}


	///
	/// Set enabled state of actions associated with a document being modified since last save.
	///
	void MainWindow::setDocModifiedVerbsEnabled( bool enabled )
	{
		fileSaveAction->setEnabled( enabled );
	}


	///
	/// Set enabled state of actions associated with data being available on clipboard.
	///
	void MainWindow::setPasteVerbsEnabled( bool enabled )
	{
		editPasteAction->setEnabled( enabled );
	}


	///
	/// Set enabled state of actions associated with a non-empty selection.
	///
	void MainWindow::setSelectionVerbsEnabled( bool enabled )
	{
		editCutAction->setEnabled( enabled );
		editCopyAction->setEnabled( enabled );
		editDeleteAction->setEnabled( enabled );
		editUnSelectAllAction->setEnabled( enabled );
		objectsOrderMenu->setEnabled( enabled );
		objectsOrderRaiseAction->setEnabled( enabled );
		objectsOrderLowerAction->setEnabled( enabled );
		objectsXformMenu->setEnabled( enabled );
		objectsXformRotateLeftAction->setEnabled( enabled );
		objectsXformRotateRightAction->setEnabled( enabled );
		objectsXformFlipHorizAction->setEnabled( enabled );
		objectsXformFlipVertAction->setEnabled( enabled );
		objectsCenterMenu->setEnabled( enabled );
		objectsCenterHorizAction->setEnabled( enabled );
		objectsCenterVertAction->setEnabled( enabled );
	}


	///
	/// Set enabled state of actions associated with a non-atomic selection.
	///
	void MainWindow::setMultiSelectionVerbsEnabled( bool enabled )
	{
		objectsAlignMenu->setEnabled( enabled );
		objectsAlignLeftAction->setEnabled( enabled );
		objectsAlignRightAction->setEnabled( enabled );
		objectsAlignHCenterAction->setEnabled( enabled );
		objectsAlignTopAction->setEnabled( enabled );
		objectsAlignBottomAction->setEnabled( enabled );
		objectsAlignVCenterAction->setEnabled( enabled );
	}


	///
	/// Set window title
	///
	void MainWindow::setTitle()
	{
		if ( mModel == 0 )
		{
			setWindowTitle( "gLabels" );
		}
		else
		{
			if ( mModel->isModified() )
			{
				setWindowTitle( mModel->shortName() + " " + tr("(modified)")
						+ " - gLabels" );
			}
			else
			{
				setWindowTitle( mModel->shortName() + " - gLabels" );
			}
		}
	}


	///
	/// Read MainWindow Settings
	///
	void MainWindow::readSettings()
	{
		QSettings settings;

		settings.beginGroup( "MainWindow" );
		bool showFileToolBar    = settings.value( "showFileToolBar",    true ).toBool();
		bool showEditorToolBar  = settings.value( "showEditToolBar",    true ).toBool();
		bool showGrid           = settings.value( "showGrid",           true ).toBool();
		bool showMarkup         = settings.value( "showMarkup",         true ).toBool();
		settings.endGroup();

		viewFileToolBarAction   ->setChecked( showFileToolBar );
		viewEditorToolBarAction ->setChecked( showEditorToolBar );
		viewGridAction          ->setChecked( showGrid );
		viewMarkupAction        ->setChecked( showMarkup );

		fileToolBar   ->setVisible(       showFileToolBar );
		editorToolBar ->setVisible(       showEditorToolBar );
		mView         ->setGridVisible(   showGrid );
		mView         ->setMarkupVisible( showMarkup );
	}


	///
	/// Write MainWindow Settings
	///
	void MainWindow::writeSettings()
	{
		QSettings settings;

		settings.beginGroup( "MainWindow" );
		settings.setValue( "showFileToolBar",    viewFileToolBarAction->isChecked() );
		settings.setValue( "showEditorToolBar",  viewEditorToolBarAction->isChecked() );
		settings.setValue( "showGrid",           viewGridAction->isChecked() );
		settings.setValue( "showMarkup",         viewMarkupAction->isChecked() );
		settings.endGroup();
	}


	///
	/// File->New Action
	///
	void MainWindow::fileNew()
	{
		File::newLabel( this );
	}


	///
	/// File->Open Action
	///
	void MainWindow::fileOpen()
	{
		File::open( this );
	}


	///
	/// File->Save Action
	///
	void MainWindow::fileSave()
	{
		File::save( this );
	}


	///
	/// File->Save As Action
	///
	void MainWindow::fileSaveAs()
	{
		File::saveAs( this );
	}


	///
	/// File->Print Action
	///
	void MainWindow::filePrint()
	{
		File::print( this );
	}


	///
	/// File->Properties Action
	///
	void MainWindow::fileProperties()
	{
		qDebug() << "ACTION: file->Properties";
	}


	///
	/// File->Template Designer Action
	///
	void MainWindow::fileTemplateDesigner()
	{
		qDebug() << "ACTION: file->Template Designer";
	}


	///
	/// File->Close Action
	///
	void MainWindow::fileClose()
	{
		File::close( this );
	}


	///
	/// File->Exit Action
	///
	void MainWindow::fileExit()
	{
		File::exit();
	}


	///
	/// Edit->Undo Action
	///
	void MainWindow::editUndo()
	{
		qDebug() << "ACTION: edit->Undo";
	}


	///
	/// Edit->Redo Action
	///
	void MainWindow::editRedo()
	{
		qDebug() << "ACTION: edit->Redo";
	}


	///
	/// Edit->Cut Action
	///
	void MainWindow::editCut()
	{
		qDebug() << "ACTION: edit->Cut";
	}


	///
	/// Edit->Copy Action
	///
	void MainWindow::editCopy()
	{
		qDebug() << "ACTION: edit->Copy";
	}


	///
	/// Edit->Paste Action
	///
	void MainWindow::editPaste()
	{
		qDebug() << "ACTION: edit->Paste";
	}


	///
	/// Edit->Delete Action
	///
	void MainWindow::editDelete()
	{
		mModel->deleteSelection();
	}


	///
	/// Edit->Select All Action
	///
	void MainWindow::editSelectAll()
	{
		mModel->selectAll();
	}


	///
	/// Edit->Unselect All Action
	///
	void MainWindow::editUnSelectAll()
	{
		mModel->unselectAll();
	}


	///
	/// Edit->Preferences Action
	///
	void MainWindow::editPreferences()
	{
		qDebug() << "ACTION: edit->Preferences";
	}


	///
	/// View->File Tool Bar Toggle Action
	///
	void MainWindow::viewFileToolBar( bool state )
	{
		fileToolBar->setVisible( state );
	}


	///
	/// View->Objects Tool Bar Toggle Action
	///
	void MainWindow::viewEditorToolBar( bool state )
	{
		editorToolBar->setVisible( state );
	}


	///
	/// View->Grid Toggle Action
	///
	void MainWindow::viewGrid( bool state )
	{
		mView->setGridVisible( state );
	}


	///
	/// View->Markup Toggle Action
	///
	void MainWindow::viewMarkup( bool state )
	{
		mView->setMarkupVisible( state );
	}


	///
	/// View->Zoom In Action
	///
	void MainWindow::viewZoomIn()
	{
		mView->zoomIn();
	}


	///
	/// View->Zoom Out Action
	///
	void MainWindow::viewZoomOut()
	{
		mView->zoomOut();
	}


	///
	/// View->Zoom 1:1 Action
	///
	void MainWindow::viewZoom1To1()
	{
		mView->zoom1To1();
	}


	///
	/// View->Zoom To Fit Action
	///
	void MainWindow::viewZoomToFit()
	{
		mView->zoomToFit();
	}


	///
	/// Objects->Arrow Mode Action
	///
	void MainWindow::objectsArrowMode()
	{
		mView->arrowMode();
	}


	///
	/// Objects->Create Text Mode Action
	///
	void MainWindow::objectsCreateText()
	{
		qDebug() << "ACTION: objects->Create->Text";
	}


	///
	/// Objects->Create Box Mode Action
	///
	void MainWindow::objectsCreateBox()
	{
		mView->createBoxMode();
	}


	///
	/// Objects->Create Line Mode Action
	///
	void MainWindow::objectsCreateLine()
	{
		qDebug() << "ACTION: objects->Create->Line";
	}


	///
	/// Objects->Create Ellipse Mode Action
	///
	void MainWindow::objectsCreateEllipse()
	{
		qDebug() << "ACTION: objects->Create->Ellipse";
	}


	///
	/// Objects->Create Image Mode Action
	///
	void MainWindow::objectsCreateImage()
	{
		qDebug() << "ACTION: objects->Create->Image";
	}


	///
	/// Objects->Create Barcode Mode Action
	///
	void MainWindow::objectsCreateBarcode()
	{
		qDebug() << "ACTION: objects->Create->Barcode";
	}


	///
	/// Objects->Order->Bring To Front Action
	///
	void MainWindow::objectsOrderRaise()
	{
		qDebug() << "ACTION: objects->Order->Bring to front";
	}


	///
	/// Objects->Order->Send To Back Action
	///
	void MainWindow::objectsOrderLower()
	{
		qDebug() << "ACTION: objects->Order->Send to back";
	}


	///
	/// Objects->Rotate/Flip->Rotate Left Action
	///
	void MainWindow::objectsXformRotateLeft()
	{
		qDebug() << "ACTION: objects->Rotate/Flip->Rotate Left";
	}


	///
	/// Objects->Rotate/Flip->Rotate Right Action
	///
	void MainWindow::objectsXformRotateRight()
	{
		qDebug() << "ACTION: objects->Rotate/Flip->Rotate Right";
	}


	///
	/// Objects->Rotate/Flip->Flip Horizontally Action
	///
	void MainWindow::objectsXformFlipHoriz()
	{
		qDebug() << "ACTION: objects->Rotate/Flip->Flip Horizontally";
	}


	///
	/// Objects->Rotate/Flip->Flip Vertically Action
	///
	void MainWindow::objectsXformFlipVert()
	{
		qDebug() << "ACTION: objects->Rotate/Flip->Flip Vertically";
	}


	///
	/// Objects->Align->Left Action
	///
	void MainWindow::objectsAlignLeft()
	{
		qDebug() << "ACTION: objects->Align->Left";
	}


	///
	/// Objects->Align->Center Horizontally Action
	///
	void MainWindow::objectsAlignHCenter()
	{
		qDebug() << "ACTION: objects->Align->Center Horizontally";
	}


	///
	/// Objects->Align->Right Action
	///
	void MainWindow::objectsAlignRight()
	{
		qDebug() << "ACTION: objects->Align->Right";
	}


	///
	/// Objects->Align->Top Action
	///
	void MainWindow::objectsAlignTop()
	{
		qDebug() << "ACTION: objects->Align->Top";
	}


	///
	/// Objects->Align->Center Vertically Action
	///
	void MainWindow::objectsAlignVCenter()
	{
		qDebug() << "ACTION: objects->Align->Center Vertically";
	}


	///
	/// Objects->Align->Bottom Action
	///
	void MainWindow::objectsAlignBottom()
	{
		qDebug() << "ACTION: objects->Align->Bottom";
	}


	///
	/// Objects->Center->Horizontally Action
	///
	void MainWindow::objectsCenterHoriz()
	{
		qDebug() << "ACTION: objects->Center->Horizontally";
	}


	///
	/// Objects->Center->Vertically Action
	///
	void MainWindow::objectsCenterVert()
	{
		qDebug() << "ACTION: objects->Center->Vertically";
	}


	///
	/// Objects->Merge Properties Action
	///
	void MainWindow::objectsMergeProperties()
	{
		qDebug() << "ACTION: objects->Merge Properties...";
	}


	///
	/// Help->Contents Action
	///
	void MainWindow::helpContents()
	{
		Help::displayContents( this );
	}


	///
	/// Help->About Action
	///
	void MainWindow::helpAbout()
	{
		Help::displayAbout( this );
	}


	///
	/// Zoom changed: update Zoom Information in Status Bar
	///
	void MainWindow::onZoomChanged()
	{
		zoomInfoLabel->setText( QString( " %1% " ).arg(100*mView->zoom(), 0, 'f', 0) );

		viewZoomInAction->setEnabled( !mView->isZoomMax() );
		viewZoomOutAction->setEnabled( !mView->isZoomMin() );
	}


	///
	/// Pointer moved: update Cursor Information in Status Bar
	///
	void MainWindow::onPointerMoved( double x, double y )
	{
		/* TODO: convert x,y to locale units and set precision accordingly. */
		cursorInfoLabel->setText( QString( "%1, %2" ).arg(x).arg(y) );
	}


	///
	/// Pointer exited view: update Zoom Information in Status Bar (Clears information)
	///
	void MainWindow::onPointerExit()
	{
		cursorInfoLabel->setText( "" );
	}


	///
	/// Name changed handler
	///
	void MainWindow::onNameChanged()
	{
		setTitle();
	}


	///
	/// Modified changed handler
	///
	void MainWindow::onModifiedChanged()
	{
		setTitle();
		setDocModifiedVerbsEnabled( mModel->isModified() );
	}


	///
	/// Selection changed handler
	///
	void MainWindow::onSelectionChanged()
	{
		setSelectionVerbsEnabled( !mModel->isSelectionEmpty() );
		setMultiSelectionVerbsEnabled( !mModel->isSelectionAtomic() );
	}


	///
	/// Label changed handler
	///
	void MainWindow::onLabelChanged()
	{
		/* @TODO: update undo/redo verbs. */
	}


}
