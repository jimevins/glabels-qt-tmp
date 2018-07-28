/*  Style.cpp
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

#include "Style.h"


namespace glabels
{
	namespace barcode
	{
	
		///
		/// Default Constructor
		///
		Style::Style ()
			: mId( "" ),
			  mBackendId( "" ),
			  mName( "" ),
			  mCanText( false ),
			  mTextOptional( false ),
			  mCanChecksum( false ),
			  mChecksumOptional( false ),
			  mDefaultDigits( "" ),
			  mCanFreeform( false ),
			  mPreferedN( 0 )
		{
			// empty
		}


		///
		/// Constructor From Data
		///
		Style::Style ( const QString& id,
		               const QString& backendId,
		               const QString& name,
		               bool           canText,
		               bool           textOptional,
		               bool           canChecksum,
		               bool           checksumOptional,
		               const QString& defaultDigits,
		               bool           canFreeform,
		               int            preferedN )
			: mId( id ),
			  mBackendId( backendId ),
			  mName( name ),
			  mCanText( canText ),
			mTextOptional( textOptional ),
			mCanChecksum( canChecksum ),
			mChecksumOptional( checksumOptional ),
			mDefaultDigits( defaultDigits ),
			mCanFreeform( canFreeform ),
			mPreferedN( preferedN )
		{
			// empty
		}


		///
		/// ID Property Getter
		///
		const QString& Style::id() const
		{
			return mId;
		}


		///
		/// Full ID Property Getter
		///
		QString Style::fullId() const
		{
			if ( mBackendId == "" )
			{
				return mId;
			}
			else
			{
				return mBackendId + "::" + mId;
			}
		}


		///
		/// Backend ID Property Getter
		///
		const QString& Style::backendId() const
		{
			return mBackendId;
		}


		///
		/// Name Property Getter
		///
		const QString& Style::name() const
		{
			return mName;
		}


		///
		/// Can Text Property Getter
		///
		bool Style::canText() const
		{
			return mCanText;
		}


		///
		/// Text Optional Property Getter
		///
		bool Style::textOptional() const
		{
			return mTextOptional;
		}


		///
		/// Can Checksum Property Getter
		///
		bool Style::canChecksum() const
		{
			return mCanChecksum;
		}


		///
		/// Checksum Optional Property Getter
		///
		bool Style::checksumOptional() const
		{
			return mChecksumOptional;
		}


		///
		/// Default Digits Property Getter
		///
		const QString& Style::defaultDigits() const
		{
			return mDefaultDigits;
		}


		///
		/// Can Freeform Property Getter
		///
		bool Style::canFreeform() const
		{
			return mCanFreeform;
		}


		///
		/// Prefered N Property Getter
		///
		int Style::preferedN() const
		{
			return mPreferedN;
		}


		///
		/// Generate Example Digits
		///
		QString Style::exampleDigits( int n ) const
		{
			if ( mCanFreeform )
			{
				return QString( qMax( n, 1 ), QChar('0') );
			}
			else
			{
				return mDefaultDigits;
			}
		}


		///
		/// "Not equals" operator
		///
		bool Style::operator!=( const Style& other ) const
		{
			return mId != other.mId;
		}
	
	} // namespace barcode
} // namespace glabels
