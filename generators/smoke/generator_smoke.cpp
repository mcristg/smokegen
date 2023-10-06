/*
    Generator for the SMOKE sources
    Copyright (C) 2009 Arno Rehn <arno@arnorehn.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QHash>
#include <QSet>
#include <QString>
#include <QtDebug>

#include <QXmlStreamReader>
#include <QRegularExpression>

#include <iostream>

#include <type.h>

#include "globals.h"
#include "../../options.h"

QDir Options::outputDir = QDir::current();
QList<QFileInfo> Options::headerList;
QStringList Options::classList;

int Options::parts = 20;
QString Options::module = "qt";
QStringList Options::parentModules;
QDir Options::libDir;
QStringList Options::scalarTypes;
QStringList Options::voidpTypes;

QStringList Options::moduleNamespaces;
QStringList Options::excludeIncFiles;
QStringList Options::needOpNew;
QStringList Options::doubleConditions;
QStringList Options::tripleConditions;
QStringList Options::OverridesFinalFunctions;

bool Options::qtMode = false;
QList<QRegularExpression> Options::excludeExpressions;
QList<QRegularExpression> Options::includeFunctionNames;
QList<QRegularExpression> Options::includeFunctionSignatures;

static void showUsage()
{
    std::cout <<
    "Usage: generator -g smoke [smoke generator options] [other generator options] -- <headers>" << std::endl <<
    "    -m <module name> (default: 'qt')" << std::endl <<
    "    -p <parts> (default: 20)" << std::endl <<
    "    -pm <comma-seperated list of parent modules>" << std::endl <<
    "    -st <comma-seperated list of types that should be munged to scalars>" << std::endl <<
    "    -vt <comma-seperated list of types that should be mapped to Smoke::t_voidp>" << std::endl <<
    "    -L <directory containing parent libs> (parent smoke libs can be located in a <modulename> subdirectory>)" << std::endl;
}

static void XmlStreamparse_smokeConfig(QFileInfo &smokeConfig)
{
  if (smokeConfig.exists()) {
    QFile file(smokeConfig.filePath());
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader reader(&file);

    while(!reader.atEnd() && !reader.hasError()) {
      // Read next element.
      QXmlStreamReader::TokenType token = reader.readNext();
      const auto tag = reader.name();
      // If token is just StartDocument, we'll go to next.
      if (token == QXmlStreamReader::StartDocument) {
	continue;
      }
      // If token is StartElement, we'll see if we can read it.
      if (token == QXmlStreamReader::StartElement) {
	if (tag.toString() == "outputDir") {
	  Options::outputDir = QDir(reader.readElementText());
	} else if (tag.toString() == "moduleName") {
	  Options::module = reader.readElementText();
	} else if (tag.toString() == "parts") {
	  Options::parts = reader.readElementText().toInt();
	} else if (tag.toString() == "parentModules") {
	  while (reader.readNextStartElement()) {
	    if (reader.name().toString() == "module") {
	      Options::parentModules << reader.readElementText();
	    }
	  }	    
	} else if (tag.toString() == "scalarTypes") {
	  while (reader.readNextStartElement()) {
	    if (reader.name().toString() == "typeName") {
	      Options::scalarTypes << reader.readElementText();
	    }
	  }
	} else if (tag.toString() == "voidpTypes") {
	  while (reader.readNextStartElement()) {
	    if (reader.name().toString() == "typeName") {
	      Options::voidpTypes << reader.readElementText();
	    }
	  }
	} else if (tag.toString() == "classList") {
	  while (reader.readNextStartElement()) {
	    if (reader.name().toString() == "class") {
	      Options::classList << reader.readElementText();
	    }
	  }
	} else if (tag.toString() == "exclude") {
	  while (reader.readNextStartElement()) {
	    if (reader.name().toString() == "signature") {
	      Options::excludeExpressions << QRegularExpression(reader.readElementText());
	    }
	  }
	} else if (tag.toString() == "functions") {
	  while (reader.readNextStartElement()) {
	    if (reader.name().toString() == "name") {
	      Options::includeFunctionNames << QRegularExpression(reader.readElementText());
	    } else if (reader.name().toString() == "signature") {
	      Options::includeFunctionSignatures << QRegularExpression(reader.readElementText());
	    }
	  }
	} else if (tag.toString() == "moduleNamespaces") {
	  while (reader.readNextStartElement()) {
	    if (reader.name().toString() == "namespace") {
	      Options::moduleNamespaces << reader.readElementText();
	    }
	  }
	} else if (tag.toString() == "excludeIncFiles") {
	  while (reader.readNextStartElement()) {
	    if (reader.name().toString() == "excludeIncFile") {
	      Options::excludeIncFiles << reader.readElementText();
	    }
	  }
	} else if (tag.toString() == "needOpNew") {
	  while (reader.readNextStartElement()) {
	    if (reader.name().toString() == "class") {
	      Options::needOpNew << reader.readElementText();
	    }
	  }
	} else if (tag.toString() == "doubleConditions") {
	  while (reader.readNextStartElement()) {
	    if (reader.name().toString() == "doubleCondition") {
	      Options::doubleConditions << reader.readElementText();
	    }
	  }
	} else if (tag.toString() == "tripleConditions") {
	  while (reader.readNextStartElement()) {
	    if (reader.name().toString() == "tripleCondition") {
	      Options::tripleConditions << reader.readElementText();
	    }
	  }
	} else if (tag.toString() == "OverridesFinalFunctions") {
	  while (reader.readNextStartElement()) {
	    if (reader.name().toString() == "name") {
	      Options::OverridesFinalFunctions << reader.readElementText();
	    }
	  }  
	}
      }
    }
    // Error handling.
    if (reader.hasError()) {
      qDebug() << reader.errorString();
    }
    reader.clear();
    file.close();
  } else {
    qWarning() << "Couldn't find config file" << smokeConfig.filePath();
  }
}

extern "C" Q_DECL_EXPORT
int generate()
{
    Options::headerList = ParserOptions::headerList;
    
    QFileInfo smokeConfig;
    
    const QStringList& args = QCoreApplication::arguments();
    for (int i = 0; i < args.count(); i++) {
        if (  (args[i] == "-m" || args[i] == "-p" || args[i] == "-pm" || args[i] == "-o" ||
               args[i] == "-st" || args[i] == "-vt" || args[i] == "-smokeconfig" || args[i] == "-L")
            && i + 1 >= args.count())
        {
            qCritical() << "generator_smoke: not enough parameters for option" << args[i];
            return EXIT_FAILURE;
        } else if (args[i] == "-m") {
            Options::module = args[++i];
        } else if (args[i] == "-p") {
            bool ok = false;
            Options::parts = args[++i].toInt(&ok);
            if (!ok) {
                qCritical() << "generator_smoke: couldn't parse argument for option" << args[i - 1];
                return EXIT_FAILURE;
            }
        } else if (args[i] == "-pm") {
            Options::parentModules = args[++i].split(',');
        } else if (args[i] == "-st") {
            Options::scalarTypes = args[++i].split(',');
        } else if (args[i] == "-vt") {
            Options::voidpTypes = args[++i].split(',');
        } else if (args[i] == "-smokeconfig") {
            smokeConfig = QFileInfo(args[++i]);
        } else if (args[i] == "-o") {
            Options::outputDir = QDir(args[++i]);
        } else if (args[i] == "-L") {
            Options::libDir = QDir(args[++i]);
        } else if (args[i] == "-h" || args[i] == "--help") {
            showUsage();
            return EXIT_SUCCESS;
        }
    }

    XmlStreamparse_smokeConfig(smokeConfig);
    
    if (!Options::outputDir.exists()) {
        qWarning() << "output directoy" << Options::outputDir.path() << "doesn't exist; creating it...";
        QDir::current().mkpath(Options::outputDir.path());
    }
    
    Options::qtMode = ParserOptions::qtMode;

    Options::voidpTypes << "long long" << "long long int" << "unsigned long long" << "unsigned long long int" <<
        "nullptr_t" << "std::nullptr_t" << "char16_t" << "char32_t";
    Options::scalarTypes << "long long" << "long long int" << "unsigned long long" << "unsigned long long int" <<
        "nullptr_t" << "std::nullptr_t" << "char16_t" << "char32_t";
    
    // Fill the type map. It maps some long integral types to shorter forms as used in SMOKE.
    Util::typeMap["long int"] = "long";
    Util::typeMap["short int"] = "short";
    Util::typeMap["long double"] = "double";
    Util::typeMap["wchar_t"] = "int";   // correct?

    if (sizeof(unsigned int) == sizeof(size_t)) {
        Util::typeMap["size_t"] = "uint";
    } else if (sizeof(unsigned long) == sizeof(size_t)) {
        Util::typeMap["size_t"] = "ulong";
    }

    qDebug() << "Generating SMOKE sources...";
    
    SmokeDataFile smokeData;
    smokeData.write();
    SmokeClassFiles classFiles(&smokeData);
    classFiles.write();
    
    qDebug() << "Done.";
    
    return EXIT_SUCCESS;
}
