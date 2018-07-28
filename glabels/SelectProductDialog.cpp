/*  SelectProductDialog.cpp
 *
 *  Copyright (C) 2013-2016  Jim Evins <evins@snaught.com>
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

#include "SelectProductDialog.h"

#include "NotebookUtil.h"
#include "TemplatePickerItem.h"

#include "model/Db.h"
#include "model/Settings.h"

#include <QtDebug>


namespace glabels
{
	
	///
	/// Constructor
	///
	SelectProductDialog::SelectProductDialog( QWidget *parent )
		: QDialog(parent), mCanceled(false)
	{
		setupUi( this );

		pageSizeIsoCheck->setChecked( model::Settings::searchIsoPaperSizes() );
		pageSizeUsCheck->setChecked( model::Settings::searchUsPaperSizes() );
		pageSizeOtherCheck->setChecked( model::Settings::searchOtherPaperSizes() );

		allCategoriesRadio->setChecked( model::Settings::searchAllCategories() );
		selectedCategoriesRadio->setChecked( !model::Settings::searchAllCategories() );

		categoriesCheckContainer->setEnabled( !model::Settings::searchAllCategories() );
		mCategoryIdList = model::Settings::searchCategoryList();
	
		QList<model::Category*> categories = model::Db::categories();
		foreach ( model::Category *category, categories )
		{
			QCheckBox* check = new QCheckBox( category->name() );
			check->setChecked( mCategoryIdList.contains( category->id() ) );
			categoriesLayout->addWidget( check );

			mCheckList.append( check );
			mCheckToCategoryMap[check] = category->id();

			connect( check, SIGNAL(clicked()), this, SLOT(onCategoryCheckClicked()) );
		}

		NotebookUtil::establishSize( modeNotebook );

		QList<model::Template*> tmplates = model::Db::templates();
		templatePicker->setTemplates( tmplates );

		if ( model::Settings::recentTemplateList().count() > 0 )
		{
			modeNotebook->setCurrentIndex(1);
		}

		onModeTabChanged();
	}

	
	///
	/// Get selected template
	///
	const model::Template* SelectProductDialog::tmplate() const
	{
		if ( !mCanceled )
		{
			return templatePicker->selectedTemplate();
		}
		else
		{
			return nullptr;
		}
	}


	///
	/// Mode Notebook Tab Changed Slot
	///
	void SelectProductDialog::onModeTabChanged()
	{
		switch (modeNotebook->currentIndex())
		{
		case 0:
			// Search Tab
			templatePicker->applyFilter( searchEntry->text(),
			                             pageSizeIsoCheck->isChecked(),
			                             pageSizeUsCheck->isChecked(),
			                             pageSizeOtherCheck->isChecked(),
			                             allCategoriesRadio->isChecked(),
			                             mCategoryIdList );
			break;
		case 1:
			// Recent Tab
			templatePicker->applyFilter( model::Settings::recentTemplateList() );
			break;
		default:
			qDebug() << "onModeTabChanged(): unknown tab!";
		}
	}


	///
	/// Search Entry Text Changed Slot
	///
	void SelectProductDialog::onSearchEntryTextChanged()
	{
		templatePicker->applyFilter( searchEntry->text(),
		                             pageSizeIsoCheck->isChecked(),
		                             pageSizeUsCheck->isChecked(),
		                             pageSizeOtherCheck->isChecked(),
		                             allCategoriesRadio->isChecked(),
		                             mCategoryIdList );
	}


	///
	/// Page Size Check Clicked Slot
	///
	void SelectProductDialog::onPageSizeCheckClicked()
	{
		model::Settings::setSearchIsoPaperSizes( pageSizeIsoCheck->isChecked() );
		model::Settings::setSearchUsPaperSizes( pageSizeUsCheck->isChecked() );
		model::Settings::setSearchOtherPaperSizes( pageSizeOtherCheck->isChecked() );

		templatePicker->applyFilter( searchEntry->text(),
		                             pageSizeIsoCheck->isChecked(),
		                             pageSizeUsCheck->isChecked(),
		                             pageSizeOtherCheck->isChecked(),
		                             allCategoriesRadio->isChecked(),
		                             mCategoryIdList );
	}


	///
	/// Category Radio Clicked Slot
	///
	void SelectProductDialog::onCategoryRadioClicked()
	{
		categoriesCheckContainer->setEnabled( selectedCategoriesRadio->isChecked() );
		loadCategoryList();

		templatePicker->applyFilter( searchEntry->text(),
		                             pageSizeIsoCheck->isChecked(),
		                             pageSizeUsCheck->isChecked(),
		                             pageSizeOtherCheck->isChecked(),
		                             allCategoriesRadio->isChecked(),
		                             mCategoryIdList );

		model::Settings::setSearchAllCategories( allCategoriesRadio->isChecked() );
	}


	///
	/// Category Check Clicked Slot
	///
	void SelectProductDialog::onCategoryCheckClicked()
	{
		loadCategoryList();

		templatePicker->applyFilter( searchEntry->text(),
		                             pageSizeIsoCheck->isChecked(),
		                             pageSizeUsCheck->isChecked(),
		                             pageSizeOtherCheck->isChecked(),
		                             allCategoriesRadio->isChecked(),
		                             mCategoryIdList );


		model::Settings::setSearchCategoryList( mCategoryIdList );
	}


	///
	/// Template Picker Selection Changed Slot
	///
	void SelectProductDialog::onTemplatePickerSelectionChanged()
	{
		// Delay close.  This should make the selection more apparent to the user.
		mTimer.start( 125, this );
	}


	///
	/// Cancel Button Clicked Slot
	///
	void SelectProductDialog::onCancelButtonClicked()
	{
		mCanceled = true;
		close();
	}


	///
	/// Cancel Button Clicked Slot
	///
	void SelectProductDialog::timerEvent( QTimerEvent *event )
	{
		mTimer.stop();
		close();
	}


	///
	/// Load category list
	///
	void SelectProductDialog::loadCategoryList()
	{
		mCategoryIdList.clear();

		foreach( QCheckBox* check, mCheckList )
		{
			if ( check->isChecked() )
			{
				mCategoryIdList.append( mCheckToCategoryMap[check] );
			}
		}
	}

} // namespace glabels
