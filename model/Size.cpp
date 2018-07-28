/*  Size.cpp
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

#include "Size.h"


namespace glabels
{
	namespace model
	{

		///
		/// Constructor
		///
		Size::Size() : mW(0), mH(0)
		{
			// empty
		}


		///
		/// Constructor
		///
		Size::Size( const Distance& w, const Distance& h ) : mW(w), mH(h)
		{
			// empty
		}


		///
		/// Get w
		///
		Distance Size::w() const
		{
			return mW;
		}


		///
		/// Set w
		///
		void Size::setW( const Distance& value )
		{
			mW = value;
		}


		///
		/// Get h
		///
		Distance Size::h() const
		{
			return mH;
		}


		///
		/// Set h
		///
		void Size::setH( const Distance& value )
		{
			mH = value;
		}


		///
		/// Convert to a QSizeF
		///
		QSizeF Size::qSizeF() const
		{
			QSizeF s;

			s.setWidth( mW.pt() );
			s.setHeight( mH.pt() );

			return s;
		}

	}
}
