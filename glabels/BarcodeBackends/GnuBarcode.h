/*  GnuBarcode.h
 *
 *  Copyright (C) 2017  Jim Evins <evins@snaught.com>
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

#ifndef barcode_GnuBarcode_h
#define barcode_GnuBarcode_h

#if HAVE_GNU_BARCODE

#include "glbarcode/Barcode1dBase.h"


namespace glabels
{
	namespace GnuBarcode
	{

		/**
		 * GnuBarcode::Base base class for all GNU Barcodes
		 *
		 * Implements glbarcode::Barcode1dBase.
		 */
		class Base : public glbarcode::Barcode1dBase
		{
		protected:
			int flags;
			
			bool isAscii( const std::string& data ) const;
			
			bool isNumericLengthValid( const std::string& data,
			                           unsigned int       nMin,
			                           unsigned int       nMax ) const;

			bool isNumericLength1Valid( const std::string& data,
			                            unsigned int       nMin,
			                            unsigned int       nMax ) const;

			bool isNumericLength2Valid( const std::string& data,
			                            unsigned int       nMin,
			                            unsigned int       nMax ) const;
			
			void vectorize( const std::string& encodedData,
			                const std::string& displayText,
			                const std::string& cookedData,
			                double&            w,
			                double&            h ) override;
		};


		/**
		 * EAN Barcode (Any)
		 */
		class Ean : public Base
		{
		public:
			static Barcode* create();
			
		protected:
			bool validate( const std::string& rawData ) override;
			std::string encode( const std::string& cookedData ) override;
		};

	}
}


#endif // HAVE_GNU_BARCODE

#endif // barcode_GnuBarcode_h
