/*  Db.h
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

#ifndef model_Db_h
#define model_Db_h


#include "Category.h"
#include "Paper.h"
#include "Template.h"
#include "Vendor.h"

#include <QCoreApplication>
#include <QDir>
#include <QList>
#include <QString>


namespace glabels
{
	namespace model
	{

		class Db
		{
			Q_DECLARE_TR_FUNCTIONS(Db)

		private:
			Db();

		
		public:
			static void init();
			static Db* instance();


			static const QList<Paper*>& papers();
			static const QStringList& paperIds();
			static const QStringList& paperNames();

			static const QList<Category*>& categories();
			static const QStringList& categoryIds();
			static const QStringList& categoryNames();

			static const QList<Vendor*>& vendors();
			static const QStringList& vendorNames();

			static const QList<Template*>& templates();


			static void registerPaper( Paper *paper );
			static const Paper *lookupPaperFromName( const QString& name );
			static const Paper *lookupPaperFromId( const QString& id );
			static QString lookupPaperIdFromName( const QString& name );
			static QString lookupPaperNameFromId( const QString& id );
			static bool isPaperIdKnown( const QString& id );
			static bool isPaperIdOther( const QString& id );

			static void registerCategory( Category *category );
			static const Category *lookupCategoryFromName( const QString& name );
			static const Category *lookupCategoryFromId( const QString& id );
			static QString lookupCategoryIdFromName( const QString& name );
			static QString lookupCategoryNameFromId( const QString& id );
			static bool isCategoryIdKnown( const QString& id );

			static void registerVendor( Vendor *vendor );
			static const Vendor *lookupVendorFromName( const QString& name );
			static QString lookupVendorUrlFromName( const QString& name );
			static bool isVendorNameKnown( const QString& id );

			static void registerTemplate( Template *tmplate );
			static const Template *lookupTemplateFromName( const QString& name );
			static const Template *lookupTemplateFromBrandPart( const QString& brand,
			                                                    const QString& part );
			static bool isTemplateKnown( const QString& brand, const QString& part );
			static bool isSystemTemplateKnown( const QString& brand, const QString& part );
			static QStringList getNameListOfSimilarTemplates( const QString& name );

			static QString userTemplateFilename( const QString& brand, const QString& part );
			static void registerUserTemplate( Template *tmplate );
			static void deleteUserTemplateByBrandPart( const QString& brand,
			                                           const QString& part );

			static void printKnownPapers();
			static void printKnownCategories();
			static void printKnownVendors();
			static void printKnownTemplates();


		private:
			static QDir systemTemplatesDir();

			static void readPapers();
			static void readPapersFromDir( const QDir& dir );

			static void readCategories();
			static void readCategoriesFromDir( const QDir& dir );

			static void readVendors();
			static void readVendorsFromDir( const QDir& dir );

			static void readTemplates();
			static void readTemplatesFromDir( const QDir& dir, bool isUserDefined );


		private:
			static QList<Paper*>    mPapers;
			static QStringList      mPaperIds;
			static QStringList      mPaperNames;

			static QList<Category*> mCategories;
			static QStringList      mCategoryIds;
			static QStringList      mCategoryNames;

			static QList<Vendor*>   mVendors;
			static QStringList      mVendorNames;

			static QList<Template*> mTemplates;

			static QString          mPaperNameOther;

		};

	}
}


#endif // model_Db_h
