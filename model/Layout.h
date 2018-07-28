/*  Layout.h
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

#ifndef model_Layout_h
#define model_Layout_h


#include "Distance.h"


namespace glabels
{
	namespace model
	{

		class Layout
		{
		
		public:
			Layout( int             nx,
			        int             ny,
			        const Distance& x0,
			        const Distance& y0,
			        const Distance& dx,
			        const Distance& dy );

			Layout( const Layout &other );

			int nx() const;
			int ny() const;

			Distance x0() const;
			Distance y0() const;

			Distance dx() const;
			Distance dy() const;

			bool isSimilarTo( const Layout *other );

			Layout* dup() const;


		private:
			int      mNx;
			int      mNy;
			Distance mX0;
			Distance mY0;
			Distance mDx;
			Distance mDy;
		
		};

	}
}


#endif // model_Layout_h
