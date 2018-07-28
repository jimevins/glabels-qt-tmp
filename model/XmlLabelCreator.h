/*  XmlLabelCreator.h
 *
 *  Copyright (C) 2014  Jim Evins <evins@snaught.com>
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

#ifndef model_XmlLabelCreator_h
#define model_XmlLabelCreator_h


#include <QObject>
#include <QDomElement>


namespace glabels
{
	namespace model
	{

		// Forward references
		class Model;
		class ModelObject;
		class ModelBoxObject;
		class ModelEllipseObject;
		class ModelLineObject;
		class ModelImageObject;
		class ModelBarcodeObject;
		class ModelTextObject;


		///
		/// XmlLabelCreator
		///
		class XmlLabelCreator : public QObject
		{
			Q_OBJECT

		public:
			static void writeFile( const Model* label, const QString& fileName );
			static void writeBuffer( const Model* label, QByteArray& buffer );
			static void serializeObjects( const QList<ModelObject*>& objects, QByteArray& buffer );

		private:
			static void createDoc( QDomDocument& doc, const Model* label );
			static void createRootNode( const Model* label );
			static void createObjectsNode( QDomElement &parent, const QList<ModelObject*>& objects, bool rotate );
			static void createObjectBoxNode( QDomElement &parent, const ModelBoxObject* object );
			static void createObjectEllipseNode( QDomElement &parent, const ModelEllipseObject* object );
			static void createObjectLineNode( QDomElement &parent, const ModelLineObject* object );
			static void createObjectImageNode( QDomElement &parent, const ModelImageObject* object );
			static void createObjectBarcodeNode( QDomElement &parent, const ModelBarcodeObject* object );
			static void createObjectTextNode( QDomElement &parent, const ModelTextObject* object );
			static void createPNode( QDomElement &parent, const QString& blockText );
			static void createPositionAttrs( QDomElement &node, const ModelObject* object );
			static void createSizeAttrs( QDomElement &node, const ModelObject* object );
			static void createLineAttrs( QDomElement &node, const ModelObject* object );
			static void createFillAttrs( QDomElement &node, const ModelObject* object );
			static void createAffineAttrs( QDomElement &node, const ModelObject* object );
			static void createShadowAttrs( QDomElement &node, const ModelObject* object );
			static void createMergeNode( QDomElement &parent, const Model* label );
			static void createDataNode( QDomElement &parent, const QList<ModelObject*>& objects );
			static void createPngFileNode( QDomElement &parent, const QString& name, const QImage& image );
			static void createSvgFileNode( QDomElement &parent, const QString& name, const QByteArray& svg );

		};

	}
}


#endif // model_XmlLabelCreator_h
