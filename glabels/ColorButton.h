/*  ColorButton.h
 *
 *  Copyright (C) 2014-2016  Jim Evins <evins@snaught.com>
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

#ifndef ColorButton_h
#define ColorButton_h


#include "ColorPaletteDialog.h"

#include "model/ColorNode.h"

#include <QPushButton>


namespace glabels
{
	
	///
	/// Color Button
	///
	class ColorButton : public QPushButton
	{
		Q_OBJECT


		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	public:
		ColorButton( QWidget* parent = nullptr );


		/////////////////////////////////
		// Signals
		/////////////////////////////////
	signals:
		void colorChanged();


		/////////////////////////////////
		// Public Methods
		/////////////////////////////////
	public:
		void   init( const QString& defaultLabel, const QColor& defaultColor, const QColor& color );
		void   setColorNode( model::ColorNode colorNode );
		void   setColor( QColor color );
		void   setToDefault();
		model::ColorNode colorNode();
		void   setKeys( const QList<QString> keyList );
		void   clearKeys();


		/////////////////////////////////
		// Slots
		/////////////////////////////////
	private slots:
		void onButtonToggled( bool checked );
		void onPaletteDialogAccepted();
		void onPaletteDialogRejected();
		void onPaletteDialogChanged( model::ColorNode colorNode, bool isDefault );


		/////////////////////////////////
		// Private Methods
		/////////////////////////////////
	private:


		/////////////////////////////////
		// Private Members
		/////////////////////////////////
	private:
		QColor              mDefaultColor;
		bool                mIsDefault;
		model::ColorNode    mColorNode;

		ColorPaletteDialog* mDialog;
	};

}


#endif // ColorButton_h
