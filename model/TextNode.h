/*  TextNode.h
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

#ifndef model_TextNode_h
#define model_TextNode_h


#include "merge/Record.h"

#include <QString>


namespace glabels
{
	namespace model
	{

		///
		/// Text Node Type
		///
		struct TextNode
		{

			/////////////////////////////////
			// Life Cycle
			/////////////////////////////////
		public:
			TextNode();

			TextNode( bool isField, const QString &data );


			/////////////////////////////////
			// Operators
			/////////////////////////////////
		public:
			bool operator==( const TextNode& other );

			bool operator!=( const TextNode& other );


			/////////////////////////////////
			// Properties
			/////////////////////////////////
		public:
			//
			// is field? Property
			//
			bool isField() const;
			void setField( bool isField );

			//
			// Data Property
			//
			const QString& data() const;
			void setData( const QString& data );


			/////////////////////////////////
			// Misc. Methods
			/////////////////////////////////
			QString text( merge::Record* record ) const;
			bool isEmptyField( merge::Record* record ) const;


			/////////////////////////////////
			// Private Data
			/////////////////////////////////
		private:

			bool    mIsField;
			QString mData;

		};

	}
}


#endif // model_TextNode_h
