/*  Preview.h
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

#ifndef Preview_h
#define Preview_h


#include "model/Distance.h"
#include "model/Model.h"
#include "model/PageRenderer.h"

#include <QGraphicsView>
#include <QGraphicsScene>


namespace glabels
{
	
	///
	///  Preview Widget
	///
	class Preview : public QGraphicsView
	{
		Q_OBJECT


		/////////////////////////////////
		// Life Cycle
		/////////////////////////////////
	public:
		Preview( QWidget *parent = nullptr );


		/////////////////////////////////
		// Renderer
		/////////////////////////////////
	public:
		void setRenderer( const model::PageRenderer* renderer );
	private slots:
		void onRendererChanged();


		/////////////////////////////////////
		// Event handlers
		/////////////////////////////////////
	protected:
		void resizeEvent( QResizeEvent* event ) override;

		
		/////////////////////////////////
		// Internal Methods
		/////////////////////////////////
	private:
		void clearScene();
		void drawPaper( const model::Distance& pw, const model::Distance& ph );
		void drawLabels();
		void drawLabel( const model::Distance& x, const model::Distance& y, const QPainterPath& path );
		
		void drawPreviewOverlay();


		/////////////////////////////////
		// Private Data
		/////////////////////////////////
	private:
		const model::Model*        mModel;
		const model::PageRenderer* mRenderer;    
		QGraphicsScene*            mScene;

	};

}


#endif // Preview_h
