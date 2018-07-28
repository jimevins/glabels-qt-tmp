/*  FrameCd.cpp
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

#include "FrameCd.h"

#include "Constants.h"
#include "StrUtil.h"

#include <QtDebug>


namespace glabels
{
	namespace model
	{

		FrameCd::FrameCd( const Distance& r1,
		                  const Distance& r2,
		                  const Distance& w,
		                  const Distance& h,
		                  const Distance& waste,
		                  const QString&  id )
			: Frame(id), mR1(r1), mR2(r2), mW(w), mH(h), mWaste(waste)
		{
			Distance wReal = (mW == 0) ? 2*mR1 : mW;
			Distance hReal = (mH == 0) ? 2*mR1 : mH;

			//
			// Create path
			//
			{
				/*
				 * Construct outer subpath (may be clipped if it's a business card CD)
				 */
				QPainterPath outerPath;
				outerPath.addEllipse( (wReal/2 - r1).pt(), (hReal/2 - r1).pt(), 2*r1.pt(), 2*r1.pt() );

				QPainterPath clipPath;
				clipPath.addRect( 0, 0, wReal.pt(), hReal.pt() );

				mPath.addPath( outerPath & clipPath );
				mPath.closeSubpath();

				/*
				 * Add inner subpath
				 */
				mPath.addEllipse( (wReal/2 - r2).pt(), (hReal/2 - r2).pt(), 2*r2.pt(), 2*r2.pt() );
			}

			//
			// Create clip path
			//
			{
				Distance r1Clip = mR1 + mWaste;
				Distance r2Clip = mR2 - mWaste;
				Distance wClip = (mW == 0) ? 2*r1Clip : mW + 2*mWaste;
				Distance hClip = (mH == 0) ? 2*r1Clip : mH + 2*mWaste;

				/*
				 * Construct outer subpath (may be clipped if it's a business card CD)
				 */
				QPainterPath outerPath;
				outerPath.addEllipse( (wReal/2 - r1Clip).pt(), (hReal/2 - r1Clip).pt(), 2*r1Clip.pt(), 2*r1Clip.pt() );

				QPainterPath clipPath;
				clipPath.addRect( -mWaste.pt(), -mWaste.pt(), wClip.pt(), hClip.pt() );

				mClipPath.addPath( outerPath & clipPath );
				mClipPath.closeSubpath();

				/*
				 * Add inner subpath
				 */
				mClipPath.addEllipse( (wReal/2 - r2Clip).pt(), (hReal/2 - r2Clip).pt(), 2*r2Clip.pt(), 2*r2Clip.pt() );
			}
		}


		FrameCd::FrameCd( const FrameCd& other )
			: Frame(other),
			  mR1(other.mR1), mR2(other.mR2), mW(other.mW), mH(other.mH), mWaste(other.mWaste),
			  mPath(other.mPath)
		{
			// empty
		}

	
		Frame* FrameCd::dup() const
		{
			return new FrameCd( *this );
		}
	

		Distance FrameCd::w() const
		{
			return (mW == 0) ? 2*mR1 : mW;
		}

	
		Distance FrameCd::h() const
		{
			return (mH == 0) ? 2*mR1 : mH;
		}


		Distance FrameCd::r1() const
		{
			return mR1;
		}

	
		Distance FrameCd::r2() const
		{
			return mR2;
		}

	
		Distance FrameCd::waste() const
		{
			return mWaste;
		}
	

		QString FrameCd::sizeDescription( const Units& units ) const
		{
			if ( units.toEnum() == Units::IN )
			{
				QString dStr = StrUtil::formatFraction( 2 * mR1.in() );

				return QString().sprintf( "%s %s %s",
				                          qPrintable(dStr),
				                          qPrintable(units.toTrName()),
				                          qPrintable(tr("diameter")) );
			}
			else
			{
				return QString().sprintf( "%.5g %s %s",
				                          2 * mR1.inUnits(units),
				                          qPrintable(units.toTrName()),
				                          qPrintable(tr("diameter")) );
			}
		}


		bool FrameCd::isSimilarTo( Frame* other ) const
		{
			if ( auto *otherCd = dynamic_cast<FrameCd*>(other) )
			{
				if ( (fabs( mW  - otherCd->mW )  <= EPSILON) &&
				     (fabs( mH  - otherCd->mH )  <= EPSILON) &&
				     (fabs( mR1 - otherCd->mR1 ) <= EPSILON) &&
				     (fabs( mR2 - otherCd->mR2 ) <= EPSILON) )
				{
					return true;
				}
			}
			return false;
		}


		const QPainterPath& FrameCd::path() const
		{
			return mPath;
		}
	

		const QPainterPath& FrameCd::clipPath() const
		{
			return mClipPath;
		}
	

		QPainterPath FrameCd::marginPath( const Distance& size ) const
		{
			Distance wReal = (mW == 0) ? 2*mR1 : mW;
			Distance hReal = (mH == 0) ? 2*mR1 : mH;

			Distance r1 = mR1 - size;
			Distance r2 = mR2 + size;

			QPainterPath path;

			/*
			 * Construct outer subpath (may be clipped if it's a business card CD)
			 */
			QPainterPath outerPath;
			outerPath.addEllipse( (wReal/2 - r1).pt(), (hReal/2 - r1).pt(), 2*r1.pt(), 2*r1.pt() );

			QPainterPath clipPath;
			clipPath.addRect( size.pt(), size.pt(), (wReal-2*size).pt(), (hReal-2*size).pt() );

			path.addPath( outerPath & clipPath );
			path.closeSubpath();

			/*
			 * Add inner subpath
			 */
			path.addEllipse( (wReal/2 - r2).pt(), (hReal/2 - r2).pt(), 2*r2.pt(), 2*r2.pt() );

			return path;
		}

	}
}
