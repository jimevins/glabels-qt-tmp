/*  PropertiesView.h
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

#ifndef PropertiesView_h
#define PropertiesView_h


#include "ui_PropertiesView.h"

#include "model/Model.h"
#include "model/Units.h"


namespace glabels
{

	// Forward references
	class UndoRedoModel;
	

	///
	/// Properties View Widget
	///
	class PropertiesView : public QWidget, public Ui_PropertiesView
	{
		Q_OBJECT


		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	public:
		PropertiesView( QWidget *parent = nullptr );
		~PropertiesView() override;


		/////////////////////////////////
		// Public methods
		/////////////////////////////////
		void setModel( model::Model* model, UndoRedoModel* undoRedoModel );


		/////////////////////////////////
		// Slots
		/////////////////////////////////
	private slots:
		void onSettingsChanged();
		void onLabelSizeChanged();
		void onOrientationActivated();
		void onChangeProductButtonClicked();


		/////////////////////////////////
		// Private Data
		/////////////////////////////////
	private:
		model::Model*      mModel;
		UndoRedoModel*     mUndoRedoModel;
		model::Units       mUnits;
		int                mOldOrientationIndex;
	};

}


#endif // PropertiesView_h
