/*
 * elementUse.cpp
 *
 *  Created on: 30.8.2011
 *      Author: Adam Juraszek
 */

#include "elementUse.h"
#include "utils.h"

void ElementUse::generate(QString &className, QString &ehprivate,
		QString &ehpublic, QString &ehinclude, QString &ecpp,
		QString &eccinclude) {
	Element *e = getElement();

	eccinclude.append("#include \"" + e->getClassName() + ".h\"\n");
	ehinclude.append("#include \"" + e->getClassName() + ".h\"\n");

	ehpublic.append(
			"inline QList<" + e->getClassName() + "*> "
					+ methodName(e->getName(), "get", "List") + "() {\n");
	ehpublic.append(
			"  return " + varName(e->getName(), QString(), "List") + ";\n");
	ehpublic.append("}\n");
	ehprivate.append(
			"QList<" + e->getClassName() + "*> "
					+ varName(e->getName(), QString(), "List") + ";\n");
	ehprivate.append(
			"void " + methodName(e->getName(), "add") + "(" + e->getClassName()
					+ " * ele);\n");
	ecpp.append(
			"void " + className + "::" + methodName(e->getName(), "add") + "("
					+ e->getClassName() + " * ele) {\n");
	ecpp.append(
			"  " + varName(e->getName(), QString(), "List")
					+ ".append(ele);\n");
	ecpp.append("  qDebug() << \"" + e->getClassName() + "\";\n");
	ecpp.append("}\n");

	ehprivate.append("void " + methodName(e->getName(), "init") + "();\n");
	ecpp.append(
			"void " + className + "::" + methodName(e->getName(), "init")
					+ "(){\n");
	ecpp.append(
			"  qDebug() << \"" + className + "\"<<\"" + e->getName()
					+ "\" <<\"init\";\n");
	ecpp.append(
			"  " + varName(e->getName(), QString(), "List") + " = QList<"
					+ e->getClassName() + "*>();\n");
	ecpp.append("}\n");

}
