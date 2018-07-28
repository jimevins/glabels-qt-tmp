/*  Merge/TextTsvKeys.cpp
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

#include "TextTsvKeys.h"


namespace glabels
{
	namespace merge
	{

		static const QString ID = "Text/Tab/Line1Keys";


		///
		/// Constructor
		///
		TextTsvKeys::TextTsvKeys() : Text('\t',true)
		{
			mId = ID;
		}


		///
		/// Constructor
		///
		TextTsvKeys::TextTsvKeys( const TextTsvKeys* merge ) : Text( merge )
		{
		}


		///
		/// Clone
		///
		TextTsvKeys* TextTsvKeys::clone() const
		{
			return new TextTsvKeys( this );
		}


		///
		/// Get ID
		///
		QString TextTsvKeys::id()
		{
			return ID;
		}


		///
		/// Create
		///
		Merge* TextTsvKeys::create()
		{
			return new TextTsvKeys();
		}

	} // namespace merge
} // namespace glabels
