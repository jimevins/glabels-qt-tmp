/*  XmlTemplateParser.h
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

#ifndef model_XmlTemplateParser_h
#define model_XmlTemplateParser_h


#include "Template.h"

#include <QDomElement>
#include <QString>


namespace glabels
{
	namespace model
	{

		class XmlTemplateParser
		{
		public:
			XmlTemplateParser() = default;

			bool readFile( const QString &fileName, bool isUserDefined = false );
			Template *parseTemplateNode( const QDomElement &node, bool isUserDefined = false );

		private:
			void parseRootNode( const QDomElement &node, bool isUserDefined );
			void parseMetaNode( const QDomElement &node, Template *tmplate );
			void parseLabelRectangleNode( const QDomElement &node, Template *tmplate );
			void parseLabelEllipseNode( const QDomElement &node, Template *tmplate );
			void parseLabelRoundNode( const QDomElement &node, Template *tmplate );
			void parseLabelCdNode( const QDomElement &node, Template *tmplate );
			void parseLabelNodeCommon( const QDomElement &node, Frame *frame );
			void parseLayoutNode( const QDomElement &node, Frame *frame );
			void parseMarkupMarginNode( const QDomElement &node, Frame *frame );
			void parseMarkupLineNode( const QDomElement &node, Frame *frame );
			void parseMarkupCircleNode( const QDomElement &node, Frame *frame );
			void parseMarkupRectNode( const QDomElement &node, Frame *frame );
			void parseMarkupEllipseNode( const QDomElement &node, Frame *frame );

		};

	}
}


#endif // model_XmlTemplateParser_h
