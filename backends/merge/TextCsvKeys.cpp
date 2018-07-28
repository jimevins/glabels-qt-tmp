/*  Merge/TextCsvKeys.cpp
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

#include "TextCsvKeys.h"


namespace glabels
{
	namespace merge
	{

		static const QString ID = "Text/Comma/Line1Keys";
	
	
		///
		/// Constructor
		///
		TextCsvKeys::TextCsvKeys() : Text(',',true)
		{
			mId = ID;
		}


		///
		/// Constructor
		///
		TextCsvKeys::TextCsvKeys( const TextCsvKeys* merge ) : Text( merge )
		{
		}


		///
		/// Clone
		///
		TextCsvKeys* TextCsvKeys::clone() const
		{
			return new TextCsvKeys( this );
		}


		///
		/// Get ID
		///
		QString TextCsvKeys::id()
		{
			return ID;
		}


		///
		/// Create
		///
		Merge* TextCsvKeys::create()
		{
			return new TextCsvKeys();
		}

	} // namespace merge
} // namespace glabels
