/*  TemplatePicker.h
 *
 *  Copyright (C) 2013  Jim Evins <evins@snaught.com>
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

#ifndef TemplatePicker_h
#define TemplatePicker_h


#include "model/Template.h"

#include <QList>
#include <QListWidget>


namespace glabels
{

	///
	/// Template Picker Widget
	///
	class TemplatePicker : public QListWidget
	{
		Q_OBJECT


		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	public:
		TemplatePicker( QWidget *parent = nullptr );


		/////////////////////////////////
		// Properties
		/////////////////////////////////
	public:
		void setTemplates( const QList <model::Template*> &tmplates );


		/////////////////////////////////
		// Methods
		/////////////////////////////////
		void applyFilter( const QString& searchString,
		                  bool isoMask, bool usMask, bool otherMask,
		                  bool anyCategory, const QStringList& categoryIds );

		void applyFilter( const QStringList& names );

		const model::Template *selectedTemplate();

	};

}


#endif // TemplatePicker_h
