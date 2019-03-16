/*  VariablesView.cpp
 *
 *  Copyright (C) 2016  Jim Evins <evins@snaught.com>
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

#include "VariablesView.h"

#include "EditVariableDialog.h"

#include <QTableWidgetItem>
#include <QtDebug>


namespace
{
	enum ICol {
		I_COL_NAME      = 0,
		I_COL_TYPE      = 1,
		I_COL_VALUE     = 2,
		I_COL_INCREMENT = 3,
		I_COL_STEP_SIZE = 4
	};
}


namespace glabels
{

	///
	/// Constructor
	///
	VariablesView::VariablesView( QWidget *parent )
		: QWidget(parent), mModel(nullptr), mUndoRedoModel(nullptr)
	{
		setupUi( this );

		titleLabel->setText( QString( "<span style='font-size:18pt;'>%1</span>" ).arg( tr("Variables") ) );
	}


	///
	/// Destructor
	///
	VariablesView::~VariablesView()
	{
		// empty
	}


	///
	/// Set Model
	///
	void VariablesView::setModel( model::Model* model, UndoRedoModel* undoRedoModel )
	{
		mModel = model;
		mUndoRedoModel = undoRedoModel;

		updateControls();
		loadTable();
		
		connect( mModel, SIGNAL(variablesChanged()), this, SLOT(onVariablesChanged()) );
	}


	///
	/// table Selection Changed
	///
	void VariablesView::onTableSelectionChanged()
	{
		updateControls();
	}


	///
	/// addButton Clicked
	///
	void VariablesView::onAddButtonClicked()
	{
		EditVariableDialog dialog( this );

		model::Variable v( model::Variable::Type::NUMERIC,
		                   "x",
		                   "0",
		                   model::Variable::Increment::NEVER,
		                   "0" );
		dialog.setVariable( v );

		if ( dialog.exec() == QDialog::Accepted )
		{
			mModel->variables()->addVariable( dialog.variable() );
			selectVariable( dialog.variable().name() );
		}
	}


	///
	/// editButton Clicked
	///
	void VariablesView::onEditButtonClicked()
	{
		int iRow = table->selectedItems()[0]->row();
		QString name = table->item( iRow, I_COL_NAME )->text();
		
		if ( mModel->variables()->hasVariable( name ) )
		{
			model::Variable v = mModel->variables()->value( name );
		
			EditVariableDialog dialog( this );
			dialog.setVariable( v );

			if ( dialog.exec() == QDialog::Accepted )
			{
				mModel->variables()->replaceVariable( name, dialog.variable() );
				selectVariable( dialog.variable().name() );
			}
		}
	}


	///
	/// deleteButton Clicked
	///
	void VariablesView::onDeleteButtonClicked()
	{
		int iRow = table->selectedItems()[0]->row();
		
		QString name = table->item( iRow, I_COL_NAME )->text();
		mModel->variables()->deleteVariable( name );
	}


	///
	/// Variables Changed
	///
	void VariablesView::onVariablesChanged()
	{
		// Reload table from variables
		loadTable();
	}


	///
	/// update controls
	///
	void VariablesView::updateControls()
	{
		bool hasSelection = !table->selectedItems().isEmpty();

		editButton->setEnabled( hasSelection );
		deleteButton->setEnabled( hasSelection );
	}


	///
	/// load table from variables
	///
	void VariablesView::loadTable()
	{
		table->clearContents();
		table->setRowCount( mModel->variables()->size() );

		int iRow = 0;
		for( const auto& v : *mModel->variables() )
		{
			auto* typeItem = new QTableWidgetItem( model::Variable::typeToI18nString(v.type()) );
			typeItem->setFlags( typeItem->flags() ^ Qt::ItemIsEditable );
			table->setItem( iRow, I_COL_TYPE, typeItem );
			
			auto* nameItem = new QTableWidgetItem( v.name() );
			nameItem->setFlags( nameItem->flags() ^ Qt::ItemIsEditable );
			table->setItem( iRow, I_COL_NAME, nameItem );
			
			auto* valueItem = new QTableWidgetItem( v.value() );
			valueItem->setFlags( valueItem->flags() ^ Qt::ItemIsEditable );
			table->setItem( iRow, I_COL_VALUE, valueItem );
			
			auto* incrementItem = new QTableWidgetItem( model::Variable::incrementToI18nString(v.increment()) );
			incrementItem->setFlags( incrementItem->flags() ^ Qt::ItemIsEditable );
			table->setItem( iRow, I_COL_INCREMENT, incrementItem );
			
			auto* stepSizeItem = new QTableWidgetItem( v.stepSize() );
			stepSizeItem->setFlags( stepSizeItem->flags() ^ Qt::ItemIsEditable );
			table->setItem( iRow, I_COL_STEP_SIZE, stepSizeItem );

			table->showRow( iRow );
			iRow++;
		}
	}


	void VariablesView::selectVariable( const QString& name )
	{
		int iRow = 0;
		for( const auto& v : *mModel->variables() )
		{
			if ( v.name() == name )
			{
				qDebug() << "Selecting row " << iRow;
				table->setCurrentCell( iRow, 0,
				                       (QItemSelectionModel::Select|QItemSelectionModel::Rows) );
				break;
			}

			iRow++;
		}
	}


} // namespace glabels
