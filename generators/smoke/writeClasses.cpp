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
#include <QFile>
#include <QMap>
#include <QSet>
#include <QTextStream>

#include <type.h>

#include "globals.h"
#include "../../options.h"

SmokeClassFiles::SmokeClassFiles(SmokeDataFile *data)
    : m_smokeData(data)
{
    // Smokegen does not correctly detect some namespaces in Qt3D.  
    Util::missingNamespace.insert("QSceneChange", "Qt3DCore::");
    Util::missingNamespace.insert("QSkeletonLoader", "Qt3DCore::");
    Util::missingNamespace.insert("QAspectEngine", "Qt3DCore::");
    Util::missingNamespace.insert("QNode", "Qt3DCore::");
    Util::missingNamespace.insert("QGeometryView", "Qt3DCore::");

    Util::missingNamespace.insert("QWheelEvent", "Qt3DInput::");
    Util::missingNamespace.insert("QMouseDevice", "Qt3DInput::");
    Util::missingNamespace.insert("QMouseEvent", "Qt3DInput::");
    Util::missingNamespace.insert("QAxisAccumulator", "Qt3DInput::");
    
    Util::missingNamespace.insert("QAbstractTexture", "Qt3DRender::");
    Util::missingNamespace.insert("QRenderTargetOutput", "Qt3DRender::");
    Util::missingNamespace.insert("QCameraLens", "Qt3DRender::");
    Util::missingNamespace.insert("QTextureWrapMode", "Qt3DRender::");
    Util::missingNamespace.insert("QBlitFramebuffer", "Qt3DRender::");
    Util::missingNamespace.insert("QAttribute", "Qt3DRender::");
    Util::missingNamespace.insert("QPickEvent", "Qt3DRender::");
    Util::missingNamespace.insert("QPointSize", "Qt3DRender::");
    Util::missingNamespace.insert("QSubtreeEnabler", "Qt3DRender::");
    Util::missingNamespace.insert("QShaderProgram", "Qt3DRender::");
    Util::missingNamespace.insert("QBlendEquationArguments", "Qt3DRender::");
    Util::missingNamespace.insert("QLevelOfDetail", "Qt3DRender::");
    Util::missingNamespace.insert("QPickingSettings", "Qt3DRender::");
    Util::missingNamespace.insert("QComputeCommand", "Qt3DRender::");
    Util::missingNamespace.insert("QMesh", "Qt3DRender::");
    Util::missingNamespace.insert("QCamera", "Qt3DRender::");
    Util::missingNamespace.insert("QAbstractLight", "Qt3DRender::");
    Util::missingNamespace.insert("QBuffer", "Qt3DRender::");
    Util::missingNamespace.insert("QStencilOperationArguments", "Qt3DRender::");
    Util::missingNamespace.insert("QSceneLoader", "Qt3DRender::");
    Util::missingNamespace.insert("QRasterMode", "Qt3DRender::");
    Util::missingNamespace.insert("QSortPolicy", "Qt3DRender::");
    Util::missingNamespace.insert("QRenderCapabilities", "Qt3DRender::");
    Util::missingNamespace.insert("QDepthTest", "Qt3DRender::");
    Util::missingNamespace.insert("QSetFence", "Qt3DRender::");
    Util::missingNamespace.insert("QAbstractRayCaster", "Qt3DRender::");
    Util::missingNamespace.insert("QGraphicsApiFilter", "Qt3DRender::");
    Util::missingNamespace.insert("QShaderImage", "Qt3DRender::");
    Util::missingNamespace.insert("QBlendEquation", "Qt3DRender::");
    Util::missingNamespace.insert("QClearBuffers", "Qt3DRender::");
    Util::missingNamespace.insert("QAlphaTest", "Qt3DRender::");
    Util::missingNamespace.insert("QFrontFace", "Qt3DRender::");
    Util::missingNamespace.insert("QLayerFilter", "Qt3DRender::");
    Util::missingNamespace.insert("QStencilTestArguments", "Qt3DRender::");
    Util::missingNamespace.insert("QRenderSettings", "Qt3DRender::");
    Util::missingNamespace.insert("QRayCasterHit", "Qt3DRender::");
    Util::missingNamespace.insert("QTextureImage", "Qt3DRender::");
    Util::missingNamespace.insert("QGeometryRenderer", "Qt3DRender::");
    Util::missingNamespace.insert("QWaitFence", "Qt3DRender::");
    Util::missingNamespace.insert("QCullFace", "Qt3DRender::");
    Util::missingNamespace.insert("QMemoryBarrier", "Qt3DRender::");
    
    Util::missingNamespace.insert("QVector<QRenderTargetOutput::AttachmentPoint>",
				  "QVector<Qt3DRender::QRenderTargetOutput::AttachmentPoint>");
    Util::missingNamespace.insert("const QVector<QRenderTargetOutput::AttachmentPoint>&",
				  "const QVector<Qt3DRender::QRenderTargetOutput::AttachmentPoint>&");
    
    Util::missingNamespace.insert("QFlags<QAnimationCallback::Flag>", "QFlags<Qt3DAnimation::QAnimationCallback::Flag>");
    Util::missingNamespace.insert("(QFlags<QAnimationCallback::Flag>)Qt3DAnimation::QAnimationCallback::QAnimationCallback::OnOwningThread",
				  "(QFlags<Qt3DAnimation::QAnimationCallback::Flag>)Qt3DAnimation::QAnimationCallback::QAnimationCallback::OnOwningThread");
     
    Util::missingNamespace.insert("QAnimationClipLoader", "Qt3DAnimation::");
    Util::missingNamespace.insert("QAbstractClipAnimator", "Qt3DAnimation::");
    Util::missingNamespace.insert("QMorphingAnimation", "Qt3DAnimation::");
    Util::missingNamespace.insert("QKeyframeAnimation", "Qt3DAnimation::");    
    Util::missingNamespace.insert("QAnimationCallback", "Qt3DAnimation::");
    Util::missingNamespace.insert("QAbstractAnimation", "Qt3DAnimation::");

    // Error overrides a 'final' function 
    Util::OverridesFinalFunction.append("axisCount");
    Util::OverridesFinalFunction.append("buttonCount");
    Util::OverridesFinalFunction.append("axisNames");
    Util::OverridesFinalFunction.append("buttonNames");
    Util::OverridesFinalFunction.append("axisIdentifier");
    Util::OverridesFinalFunction.append("buttonIdentifier");
}

bool SmokeClassFiles::HaveNamespaceQt3D(const QString& param,QString& Namespace)
{  
    if (Util::missingNamespace.contains(param)) {
      Namespace = Util::missingNamespace.value(param);
      return true;
    }

    QStringList list1 = param.split("::", Qt::SkipEmptyParts);
    //check class name collision in the different modules with Qt3D
    if ((!Options::module.contains("animation") && list1.at(0) == "QAbstractAnimation")  ||
	(Options::module.contains("multimedia") && list1.at(0) == "QCamera"))
      return false;
    if (Options::module.contains("animation") && list1.at(0) == "QAbstractAnimation")
      if ((list1.at(1) == "State") || (list1.at(1) == "Direction"))
	return false;
    if (Util::missingNamespace.contains(list1.at(0))) {
      // Problems in Qt6 with Q3D namespace, collide Q3DCore and Qt3DRender.
      if (Options::module.contains("3dcore"))
	if (list1.at(0) == "QBuffer" || list1.at(0) == "QAttribute"){
	  Namespace = "Qt3DCore::" + param;
	  return true;
	}
      Namespace = Util::missingNamespace.value(list1.at(0)) + param;
      return true;
    }
    return false;
}

void SmokeClassFiles::write()
{
    write(m_smokeData->includedClasses);
}

void SmokeClassFiles::write(const QList<QString>& keys)
{
    qDebug("writing out x_*.cpp [%s]", qPrintable(Options::module));
    
    // how many classes go in one file
    int count = keys.count() / Options::parts;
    int count2 = count;
    
    for (int i = 0; i < Options::parts; i++) {
        QSet<QString> includes;
        QString classCode;
        QTextStream classOut(&classCode);
        
        // write the class code to a QString so we can later prepend the #includes
        if (i == Options::parts - 1) count2 = -1;
        foreach (const QString& str, keys.mid(count * i, count2)) {
            const Class* klass = &classes[str];
            includes.insert(klass->fileName());
            writeClass(classOut, klass, str, includes);
        }
        
        // create the file
        QFile file(Options::outputDir.filePath("x_" + QString::number(i + 1) + ".cpp"));
        file.open(QFile::ReadWrite | QFile::Truncate);

        QTextStream fileOut(&file);
	
        // write out the header
        fileOut << "//Auto-generated by " << QCoreApplication::arguments()[0] << ". DO NOT EDIT.\n";

        // Adjustment by Open CASCADE, foreware inclusion of _smoke.h file, smokegen sometimes does not 
        // include the files in the correct order, so manually include them in _smoke.h
        fileOut << "\n#include <smoke.h>\n#include <" << Options::module << "_smoke.h>\n";	

#ifdef WIN32
	    fileOut << "\n#include <windows.h>\n";
#endif
	//Missing qrenderapi.h
        if (Options::module.contains("3drender"))
	   fileOut << "#include <qrenderapi.h>\n";
        // ... and the #includes
        QList<QString> sortedIncludes = includes.values();
        std::sort(sortedIncludes.begin(), sortedIncludes.end());
        for (QString& str : sortedIncludes) {
            if (str.isEmpty())
                continue;
            if (str.startsWith("/builtins/"))
                str.remove(0, 10);
            //Avoid error : redefinition by inclusion of qsharedpointer_impl.h
            if (!str.contains("qsharedpointer_impl.h"))
	      //ignore .lxx files (Open CASCADE)
	      if (!str.contains(".lxx"))
		fileOut << "#include <" << str << ">\n";
        }

        fileOut << "\nclass __internal_SmokeClass {};\n";

        fileOut << "\nnamespace __smoke" << Options::module << " {\n\n";

        // now the class code
        fileOut << classCode;
        
        fileOut << "\n}\n";
        
        file.close();
    }
}

QString SmokeClassFiles::generateMethodBody(const QString& indent, const QString& className, const QString& smokeClassName, const Method& meth,
                                            int index, bool dynamicDispatch, QSet<QString>& includes,
                                            bool privateDestructor)
{
    QString methodBody;
    QTextStream out(&methodBody);
    QString Namespace;
    bool cond = false;

    out << indent;

    if (meth.isConstructor()) {
        out << smokeClassName << "* xret = new " << smokeClassName << "(";
    } else {
        const Function* func = Util::globalFunctionMap[&meth];
        if (func)
           includes.insert(func->fileName());
       
        addIncludesForType(includes, meth.type());

        if (meth.type()->isFunctionPointer() || meth.type()->isArray())
            out << meth.type()->toString("xret") << " = ";
        else if (meth.type() != Type::Void) {
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))       
          // Dirty hack, stupidy compiler error (::QByteArray name() const). Qt 5.15.2
          // error : must use 'class' tag to refer to type 'QByteArray' in this scope 
          if (meth.name().contains("name") &&  meth.type()->toString().contains("QByteArray"))
             out << "class QByteArray" << " xret = ";
          else        
#endif
            //look for classes with Qt3D's namespace
	    if (HaveNamespaceQt3D(meth.type()->toString(),Namespace)) {
	        out << Namespace << " xret = ";
	    } else
	        out << meth.type()->toString() << " xret = ";
        }
	
        if (!(meth.flags() & Method::Static)) {
            QString objName = privateDestructor ? "obj" : "this";
            if (meth.isConst()) {
	        if (Util::OverridesFinalFunction.contains(meth.name()))
                    out << "((" << (privateDestructor ? className : smokeClassName) << QString("*)%1)->").arg(objName);
		else out << "((const " << (privateDestructor ? className : smokeClassName) << QString("*)%1)->").arg(objName);
            } else {
                out << QString("%1->").arg(objName);
            }
        }
        if (!dynamicDispatch && !func) {
            // dynamic dispatch not wanted, call with 'this->Foo::method()'
            out << className << "::";
        } else if (func) {
          if (!func->nameSpace().isEmpty())
             if (!meth.name().contains("qt_getEnumName")  && !meth.name().contains("qt_getEnumMetaObject"))
                 out << func->nameSpace() << "::";
        }
        out << meth.name() << "(";
    }

    for (int j = 0; j < meth.parameters().count(); j++) {
        const Parameter& param = meth.parameters()[j];

        addIncludesForType(includes, param.type());

        if (j > 0) out << ",";

        QString field = Util::stackItemField(param.type());
        QString typeName = param.type()->toString();
	//look for classes with Qt3D's namespace
	cond = HaveNamespaceQt3D(param.type()->toString(),Namespace);
	if (cond)
	   typeName = Namespace;
	else if (param.type()->name().contains("QWebEngineCallback"))
             {
                typeName = "void (*)(const QVariant)";
             }
             else {
	       if (param.type()->isArray()) {
		 Type t = *param.type();
		 t.setPointerDepth(t.pointerDepth() + 1);
		 t.setIsRef(false);
		 typeName = t.toString();
		 out << '*';
	       }
	       else if (field == "s_class" && (param.type()->pointerDepth() == 0 || param.type()->isRef()) && !param.type()->isFunctionPointer()) {
		 // references and classes are passed in s_class
		 typeName.append('*');
		 out << '*';
	       }
	       // Erroneous cast.
	       if (typeName.contains("&(*)") && meth.name().contains("Init"))
	         typeName.replace("&", "");
	       // casting to a reference doesn't make sense in this case
	       if (param.type()->isRef() && !param.type()->isFunctionPointer()) {
		 //Multiples '&' example "const std::function<void (const QWebEngineFindTextResult &)>&"
		 int pos = typeName.lastIndexOf('&');
		 typeName.replace(pos,1, ' ');
	       }	  
             }
             out << "(" << typeName << ")" << "x[" << j + 1 << "]." << field;
    } 

    // if the method has any other default parameters, append them here as values
    if (!meth.remainingDefaultValues().isEmpty()) {
	QStringList  defaultParams = QStringList(meth.remainingDefaultValues());
	QString substituted;
	//Avoid error : reference to type 'const ClassName' cannot bind to an initializer list
	for (int i = 0; i < defaultParams.size(); ++i) {
	     substituted = defaultParams.at(i);
	     //look for classes with Qt3D's namespace
	     if (Util::missingNamespace.contains(substituted)) { 
                 Namespace = Util::missingNamespace.value(substituted);
		 defaultParams.replaceInStrings(substituted,Namespace);
	     } else if (substituted.contains("{}"))
	                defaultParams.replaceInStrings(substituted,"{}");
        }
        if (meth.parameters().count() > 0)
            out << "," ;
        out << defaultParams.join(",");
    }

    out << ");\n";
    if (meth.type() != Type::Void) {
        auto field = Util::stackItemField(meth.type());
        if (field == "s_enum")
            out << indent << "x[0]." << field << " = static_cast<long>(" << Util::assignmentString(meth.type(), "xret") << ");\n";
        else
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))                
          // Dirty hack, stupidy compiler error (::QByteArray name() const). Qt 5.15.2
          // error : must use 'class' tag to refer to type 'QByteArray' in this scope 
          if (meth.name().contains("name") &&  meth.type()->toString().contains("QByteArray"))
              out <<  indent << "x[0]." << field << " = " << "(void*)new class QByteArray(xret);\n";
          else
#endif
	  out << indent << "x[0]." << field << " = " << Util::assignmentString(meth.type(), "xret") << ";\n";
    } else {
        out << indent << "(void)x; // noop (for compiler warning)\n";
    }

    //out << "        qDebug(\"End of " << meth.toString() << "\");\n";
    return methodBody;
}

void SmokeClassFiles::generateMethod(QTextStream& out, const QString& className, const QString& smokeClassName,
                                     const Method& meth, int index, QSet<QString>& includes,
                                     bool privateDestructor)
{
    out << "    ";
    if ((meth.flags() & Method::Static) || meth.isConstructor() || privateDestructor)
        out << "static ";
    out << QString("void x_%1(%2Smoke::Stack x) {\n").arg(index)
        .arg((!(meth.flags() & Method::Static) && privateDestructor) ? (className + "* obj, ") : "");
    out << "        // " << meth.toString() << "\n";

    bool dynamicDispatch = ((meth.flags() & Method::PureVirtual) || (meth.flags() & Method::DynamicDispatch));

    if (dynamicDispatch || !Util::virtualMethodsForClass(meth.getClass()).contains(&meth)) {
        // This is either already flagged as dynamic dispatch or just a normal method. We can generate a normal method call for it.

        out << generateMethodBody("        ",   // indent
                                  className, smokeClassName, meth, index, dynamicDispatch, includes, privateDestructor);
    } else {
        // This is a virtual method. To know whether we should call with dynamic dispatch, we need a bit of RTTI magic.
        includes.insert("typeinfo");
        out << "        if (dynamic_cast<__internal_SmokeClass*>(static_cast<" << className << "*>(this))) {\n";   
        out << generateMethodBody("            ",   // indent
                                  className, smokeClassName, meth, index, false, includes, privateDestructor);
        out << "        } else {\n";
        out << generateMethodBody("            ",   // indent
                                  className, smokeClassName, meth, index, true, includes, privateDestructor);
        out << "        }\n";
    }

    out << "    }\n";
    
    // If the constructor was generated from another one with default parameteres, we don't need to explicitly create
    // it here again. The x_* call will append the default parameters at the end and thus choose the right constructor.
    if (meth.isConstructor() && meth.remainingDefaultValues().isEmpty()) {
        out << "    explicit " << smokeClassName << '(';
        QStringList x_list;
        for (int i = 0; i < meth.parameters().count(); i++) {
            if (i > 0) out << ", ";
            out << meth.parameters()[i].type()->toString() << " x" << QString::number(i + 1);
            x_list << "x" + QString::number(i + 1);
        }
        out << ") : " << meth.getClass()->name() << '(' << x_list.join(", ") << ") {}\n";
    }
}

void SmokeClassFiles::generateGetAccessor(QTextStream& out, const QString& className, const Field& field,
                                          const Type* type, int index)
{
    out << "    ";
    QString fieldName;
    if (field.flags() & Field::Static) {
        out << "static ";
    } else {
        fieldName = "this->";
    }
    fieldName += className + "::" + field.name();
    out << "void x_" << index << "(Smoke::Stack x) {\n"
        << "        // " << field.toString() << "\n"
        << "        x[0].";
    if (Util::stackItemField(type).contains("s_enum"))
        out << "s_enum" <<  " = static_cast<long>("
            << Util::assignmentString(type, fieldName) << ");\n"  << "    }\n";
    else out << Util::stackItemField(type) << " = "
             << Util::assignmentString(type, fieldName) << ";\n" << "    }\n";
}

void SmokeClassFiles::generateSetAccessor(QTextStream& out, const QString& className, const Field& field,
                                          const Type* type, int index)
{
    out << "    ";
    QString fieldName;
    if (field.flags() & Field::Static) {
        out << "static ";
    } else {
        fieldName = "this->";
    }
    fieldName += className + "::" + field.name();
    out << "void x_" << index << "(Smoke::Stack x) {\n"
        << "        // " << field.toString() << "=\n";
    QString unionField = Util::stackItemField(type);
    QString cast = type->toString();
    cast.replace("&", "");
    // C++ haven't first class arrays.
    if (cast.contains("[") && (unionField == "s_class" && type->pointerDepth() == 0)) {
      QStringList list1 = cast.split("[", Qt::SkipEmptyParts);
      QStringList list2 = list1.at(1).split("]", Qt::SkipEmptyParts);
      int siz = list2.at(0).toInt();
      out << "        " << "std::memcpy(" << fieldName << ", x[1].s_class, " << siz
          << "*sizeof(" <<  list1.at(0) << "));\n";
    } else {
      out << "        " << fieldName << " = ";
      if (unionField == "s_class" && type->pointerDepth() == 0) {
	out << '*';
	cast += '*';
      }
      out << '(' << cast << ')' << "x[1]." << unionField << ";\n";
    }
    out << "    }\n";
}

void SmokeClassFiles::generateEnumMemberCall(QTextStream& out, const QString& className, const QString& member, int index)
{
    out << "    static void x_" << index << "(Smoke::Stack x) {\n"
        << "        x[0].s_enum = static_cast<long>(";
    
    if (!className.isEmpty())
        out  << className << "::";

    out << member << ");\n"
        << "    }\n";  
}

void SmokeClassFiles::generateVirtualMethod(QTextStream& out, const Method& meth, QSet<QString>& includes)
{
    QString x_params, x_list;
    QString type = meth.type()->toString();
    addIncludesForType(includes, meth.type());
    
    out << "    virtual " << type << " " << meth.name() << "(";
    for (int i = 0; i < meth.parameters().count(); i++) {
        if (i > 0) { out << ", "; x_list.append(", "); }
        const Parameter& param = meth.parameters()[i];
        
        addIncludesForType(includes, param.type());
         
        out << param.type()->toString() << " x" << i + 1;
        x_params += QString("        x[%1].%2 = %3;\n")
            .arg(QString::number(i + 1)).arg(Util::stackItemField(param.type()))
            .arg(Util::assignmentString(param.type(), "x" + QString::number(i + 1)));
        x_list += "x" + QString::number(i + 1);
    }
    out << ") ";
    if (meth.isConst())
        if (!Util::OverridesFinalFunction.contains(meth.name()))
            out << "const ";
    if (meth.hasExceptionSpec()) {
        out << "throw(";
        for (int i = 0; i < meth.exceptionTypes().count(); i++) {
            if (i > 0) out << ", ";
            out << meth.exceptionTypes()[i].toString();
        }
        out << ") ";
    }
    out << "{\n";
    out << QString("        Smoke::StackItem x[%1];\n").arg(meth.parameters().count() + 1);
    out << x_params;
    
    if (meth.flags() & Method::PureVirtual) {
        out << QString("        this->_binding->callMethod(%1, (void*)this, x, true /*pure virtual*/);\n").arg(m_smokeData->methodIdx[&meth]);
        if (meth.type() != Type::Void) {
            QString field = Util::stackItemField(meth.type());
            if (meth.type()->pointerDepth() == 0 && field == "s_class") {
                QString tmpType = type;
                if (meth.type()->isRef()) tmpType.replace('&', "");
                tmpType.append('*');
                out << "        " << tmpType << " xptr = (" << tmpType << ")x[0].s_class;\n";
                out << "        " << type << " xret(*xptr);\n";
                out << "        delete xptr;\n";
                out << "        return xret;\n";
            } else {
                out << QString("        return (%1)x[0].%2;\n").arg(type, Util::stackItemField(meth.type()));
            }
        }
    } else {
        out << QString("        if (this->_binding->callMethod(%1, (void*)this, x)) ").arg(m_smokeData->methodIdx[&meth]);
        if (meth.type() == Type::Void) {
            out << "return;\n";
        } else {
            QString field = Util::stackItemField(meth.type());
            if (meth.type()->pointerDepth() == 0 && field == "s_class") {
                QString tmpType = type;
                if (meth.type()->isRef()) tmpType.replace('&', "");
                tmpType.append('*');
                out << "{\n";
                out << "            " << tmpType << " xptr = (" << tmpType << ")x[0].s_class;\n";
                out << "            " << type << " xret(*xptr);\n";
                out << "            delete xptr;\n";
                out << "            return xret;\n";
                out << "        }\n";
            } else {
                out << QString("return (%1)x[0].%2;\n").arg(type, Util::stackItemField(meth.type()));
            }
        }
        out << "        ";
        if (meth.type() != Type::Void)
            out << "return ";
        out << QString("this->%1::%2(%3);\n").arg(meth.getClass()->toString()).arg(meth.name()).arg(x_list);
    }
    out << "    }\n";
}

void SmokeClassFiles::writeClass(QTextStream& out, const Class* klass, const QString& className, QSet<QString>& includes)
{
    // Find the destructor.  If the destructor is private, then we can't
    // subclass from this class.  All calls in the x_Class must be static, and
    // the class won't inherit from anything.
    const Method *destructor = Util::findDestructor(klass);
    bool privateDestructor = destructor ? (destructor->access() == Access_private) : false;

    const QString underscoreName = QString(className).replace("::", "__");
    const QString smokeClassName = "x_" + underscoreName;

    QString switchCode;
    QTextStream switchOut(&switchCode);

    out << QString("class %1").arg(smokeClassName);
    if (!klass->isNameSpace()) {
        if (!privateDestructor) {
            out << QString(" : public %1").arg(className);
            if (Util::hasClassVirtualDestructor(klass) && Util::hasClassPublicDestructor(klass)) {
                out << ", public __internal_SmokeClass";
            }
        }
    }
    out << " {\n";
    if (Util::canClassBeInstanciated(klass)) {
        out << "    SmokeBinding* _binding;\n";
        out << "public:\n";
        out << "    void x_0(Smoke::Stack x) {\n";
        out << "        // set the smoke binding\n";
        out << "        _binding = (SmokeBinding*)x[1].s_class;\n";
        out << "    }\n";
        
        switchOut << "        case 0: xself->x_0(args);\tbreak;\n";
    } else {
        out << "public:\n";
    }
    
    int xcall_index = 1;

    foreach (const Method& meth, klass->methods()) {
        if (&meth == destructor)
            continue;

        if (meth.access() == Access_private)
            continue;

        QString obj;
        if ((meth.flags() & Method::Static) || meth.isConstructor() || privateDestructor)
            obj = smokeClassName + "::";
        else
            obj = "xself->";

        switchOut << "        case " << xcall_index << ": "
                  << obj
                  << "x_" << xcall_index << QString("(%1args);\tbreak;\n")
                     .arg((!(meth.flags() & Method::Static) && privateDestructor) ? "xself, " : "");
        if (Util::fieldAccessors.contains(&meth)) {
            // accessor method?
            const Field* field = Util::fieldAccessors[&meth];
            if (meth.name().startsWith("set")) {
                generateSetAccessor(out, className, *field, meth.parameters()[0].type(), xcall_index);
            } else {
                generateGetAccessor(out, className, *field, meth.type(), xcall_index);
            }
        } else {
            generateMethod(out, className, smokeClassName, meth, xcall_index, includes, privateDestructor);
        }
        xcall_index++;
    }

    QString enumCode;
    QTextStream enumOut(&enumCode);
    const Enum* e = 0;
    bool enumFound = false;
    foreach (const BasicTypeDeclaration* decl, klass->children()) {
        if (!(e = dynamic_cast<const Enum*>(decl)))
            continue;
        if (e->access() == Access_private)
            continue;
        
        foreach (const EnumMember& member, e->members()) {
            switchOut << "        case " << xcall_index << ": " << smokeClassName <<  "::x_" << xcall_index << "(args);\tbreak;\n";
            if (e->parent())
                generateEnumMemberCall(out, className, member.name(), xcall_index++);
            else
                generateEnumMemberCall(out, e->nameSpace(), member.name(), xcall_index++);
        }
        
        // only generate the xenum_call if the enum has a valid name
        if (e->name().isEmpty())
            continue;
        
        enumFound = true;
        
        // xenum_operation method code
        QString enumString = e->toString();
        enumOut << "        case " << m_smokeData->typeIndex[&types[enumString]] << ": //" << enumString << '\n';
        enumOut << "            switch(xop) {\n";
        enumOut << "                case Smoke::EnumNew:\n";
        enumOut << "                    xdata = (void*)new " << enumString << ";\n";
        enumOut << "                    break;\n";
        enumOut << "                case Smoke::EnumDelete:\n";
        enumOut << "                    delete (" << enumString << "*)xdata;\n";
        enumOut << "                    break;\n";
        enumOut << "                case Smoke::EnumFromLong:\n";
        enumOut << "                    *(" << enumString << "*)xdata = (" << enumString << ")xvalue;\n";
        enumOut << "                    break;\n";
        enumOut << "                case Smoke::EnumToLong:\n";
        enumOut << "                    xvalue = (long)*(" << enumString << "*)xdata;\n";
        enumOut << "                    break;\n";
        enumOut << "            }\n";
        enumOut << "            break;\n";
    }
    
    foreach (const Method* meth, Util::virtualMethodsForClass(klass)) {
        generateVirtualMethod(out, *meth, includes);
    }
    
    // this class contains enums, write out an xenum_operation method
    if (enumFound) {
        out << "    static void xenum_operation(Smoke::EnumOperation xop, Smoke::Index xtype, void *&xdata, long &xvalue) {\n";
        out << "        switch(xtype) {\n";
        out << enumCode;
        out << "        }\n";
        out << "    }\n";
    }
    
    // destructor
    // if the class can't be instanstiated, a callback when it's deleted is unnecessary
    if (Util::canClassBeInstanciated(klass)) {
        out << "    ~" << smokeClassName << "() ";
        if (destructor && destructor->hasExceptionSpec()) {
            out << "throw(";
            for (int i = 0; i < destructor->exceptionTypes().count(); i++) {
                if (i > 0) out << ", ";
                out << destructor->exceptionTypes()[i].toString();
            }
            out << ") ";
        }
        out << QString("{ this->_binding->deleted(%1, (void*)this); }\n").arg(m_smokeData->classIndex[className]);
    }
    out << "};\n";
    
    if (enumFound) {
        out << "void xenum_" << underscoreName << "(Smoke::EnumOperation xop, Smoke::Index xtype, void *&xdata, long &xvalue) {\n";
        out << "    " << smokeClassName << "::xenum_operation(xop, xtype, xdata, xvalue);\n";
        out << "}\n";
    }
    
    // xcall_class function
    out << "void xcall_" << underscoreName << "(Smoke::Index xi, void *obj, Smoke::Stack args) {\n";
    if (privateDestructor)
        out << "    " << className << " *xself = (" << className << "*)obj;\n";
    else
        out << "    " << smokeClassName << " *xself = (" << smokeClassName << "*)obj;\n";
    out << "    switch(xi) {\n";
    out << switchCode;
    if (Util::hasClassPublicDestructor(klass))
        out << "        case " << xcall_index << ": delete (" << className << "*)xself;\tbreak;\n";
    out << "    }\n";
    out << "}\n";
}

void SmokeClassFiles::addIncludesForType(QSet< QString >& includes, const Type* type) {
    if (type->getClass()) {
        includes.insert(type->getClass()->fileName());
    }

    for (int i = 0; i < type->templateArguments().size(); i++) {
        addIncludesForType(includes, &type->templateArguments()[i]);
    }
}
