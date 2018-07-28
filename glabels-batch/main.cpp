/*  main.cpp
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

#include "model/FileUtil.h"
#include "model/Db.h"
#include "model/Model.h"
#include "model/PageRenderer.h"
#include "model/Settings.h"
#include "model/Version.h"
#include "model/XmlLabelParser.h"

#include "barcode/Backends.h"
#include "merge/Factory.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QLibraryInfo>
#include <QLocale>
#include <QPrinter>
#include <QPrinterInfo>
#include <QTranslator>
#include <QtDebug>


int main( int argc, char **argv )
{
	QGuiApplication app( argc, argv );

	QCoreApplication::setOrganizationName( "glabels.org" );
	QCoreApplication::setOrganizationDomain( "glabels.org" );
	QCoreApplication::setApplicationName( "glabels-batch-qt" );
	QCoreApplication::setApplicationVersion( glabels::model::Version::STRING );

	//
	// Setup translators
	//
	QLocale locale = QLocale::system();
	QString qtTranslationsDir = QLibraryInfo::location( QLibraryInfo::TranslationsPath );
	QString myTranslationsDir = glabels::model::FileUtil::translationsDir().canonicalPath();
	
	QTranslator qtTranslator;
	if ( qtTranslator.load( locale, "qt", "_", qtTranslationsDir ) )
	{
		app.installTranslator(&qtTranslator);
	}

	QTranslator glabelsTranslator;
	if ( glabelsTranslator.load( locale, "glabels", "_", myTranslationsDir ) )
	{
		app.installTranslator(&glabelsTranslator);
	}

	QTranslator templatesTranslator;
	if ( templatesTranslator.load( locale, "templates", "_", myTranslationsDir ) )
	{
		app.installTranslator(&templatesTranslator);
	}


	//
	// Parse command line
	//
	const QList<QCommandLineOption> options = {
		{{"p","printer"},
		 QString( QCoreApplication::translate( "main", "Send output to <printer>. (Default=\"%1\")") ).arg( QPrinterInfo::defaultPrinterName() ),
		 QCoreApplication::translate( "main", "printer" ),
		 QPrinterInfo::defaultPrinterName() },
		
		{{"o","output"},
		 QCoreApplication::translate( "main", "Set output filename to <filename>. (Default=\"output.pdf\")" ),
		 QCoreApplication::translate( "main", "filename" ),
		 "output.pdf" },
		
		{{"s","sheets"},
		 QCoreApplication::translate( "main", "Set number of sheets to <n>. (Default=1)" ),
		 "n", "1" },

		{{"c","copies"},
		 QCoreApplication::translate( "main", "Set number of copies to <n>. (Default=1)" ),
		 "n", "1" },
		
		{{"f","first"},
		 QCoreApplication::translate( "main", "Set starting label on 1st page to <n>. (Default=1)" ),
		 "n", "1" },

		{{"l","outlines"},
		 QCoreApplication::translate( "main", "Print label outlines." ) },
		
		{{"m","crop-marks"},
		 QCoreApplication::translate( "main", "Print crop marks." ) },
		
		{{"r","reverse"},
		 QCoreApplication::translate( "main", "Print in reverse (mirror image)." ) }
	};


	QCommandLineParser parser;
	parser.setApplicationDescription( QCoreApplication::translate( "main", "gLabels Label Designer (Batch Front-end)" ) );
	parser.addOptions( options );
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addPositionalArgument( "file",
	                              QCoreApplication::translate( "main", "gLabels project file to print." ),
	                              "file" );
	parser.process( app );
	

	//
	// Initialize subsystems
	//
	glabels::model::Settings::init();
	glabels::model::Db::init();
	glabels::merge::Factory::init();
	glabels::barcode::Backends::init();

	
	if ( parser.positionalArguments().size() == 1 )
	{
		QString filename = parser.positionalArguments().constFirst();

		glabels::model::Model *model = glabels::model::XmlLabelParser::readFile( filename );
		if ( model )
		{
			QPrinter printer( QPrinter::HighResolution );
			printer.setColorMode( QPrinter::Color );
			if ( parser.isSet("printer") )
			{
				qDebug() << "Batch mode.  printer =" << parser.value("printer");
				printer.setPrinterName( parser.value("printer") );
			}
			else if ( parser.isSet("output") )
			{
				qDebug() << "Batch mode.  output =" << parser.value("output");
				printer.setOutputFileName( parser.value("output") );
			}
			else
			{
				qDebug() << "Batch mode.  printer =" << QPrinterInfo::defaultPrinterName();
			}

			glabels::model::PageRenderer renderer( model );
			renderer.setNCopies( 1 );
			renderer.setStartLabel( parser.value( "first" ).toInt() - 1 );
			renderer.setPrintOutlines( parser.isSet( "outlines" ) );
			renderer.setPrintCropMarks( parser.isSet( "crop-marks" ) );
			renderer.setPrintReverse( parser.isSet( "reverse" ) );
			renderer.print( &printer );
		}
	}
	else
	{
		if ( parser.positionalArguments().size() == 0 )
		{
			qWarning() << "Error: missing glabels project file.";
		}
		else
		{
			qWarning() << "Error: batch mode supports only one glabels project file.";
		}
		return -1;
	}
		
	return 0;
}
