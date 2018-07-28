/*  Merge/Record.h
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

#ifndef merge_Record_h
#define merge_Record_h


#include <QString>
#include <QMap>


namespace glabels
{
	namespace merge
	{

		///
		/// Merge Record
		///
		class Record : public QMap<QString,QString>
		{

			/////////////////////////////////
			// Life Cycle
			/////////////////////////////////
		public:
			Record();
			Record( const Record* record );


			/////////////////////////////////
			// Object duplication
			/////////////////////////////////
			Record* clone() const;


			/////////////////////////////////
			// Properties
			/////////////////////////////////
		public:
			bool isSelected() const;
			void setSelected( bool value );


			/////////////////////////////////
			// Private data
			/////////////////////////////////
		private:
			bool                  mSelected;

		};

	}
}


#endif // merge_Record_h
