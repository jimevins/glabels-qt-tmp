/*  Merge/TextSemicolon.cpp
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

#include "TextSemicolon.h"


namespace glabels
{
	namespace merge
	{

		static const QString ID = "Text/Semicolon";


		///
		/// Constructor
		///
		TextSemicolon::TextSemicolon() : Text(';',false)
		{
			mId = ID;
		}


		///
		/// Constructor
		///
		TextSemicolon::TextSemicolon( const TextSemicolon* merge ) : Text( merge )
		{
		}


		///
		/// Clone
		///
		TextSemicolon* TextSemicolon::clone() const
		{
			return new TextSemicolon( this );
		}


		///
		/// Get ID
		///
		QString TextSemicolon::id()
		{
			return ID;
		}


		///
		/// Create
		///
		Merge* TextSemicolon::create()
		{
			return new TextSemicolon();
		}

	} // namespace merge
} // namespace glabels
