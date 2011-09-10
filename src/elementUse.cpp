/*
 * elementUse.cpp
 *
 *  Created on: 30.8.2011
 *      Author: Adam Juraszek
 */

#include "elementUse.h"
#include "utils.h"

void ElementUse::generate(QString &cName, QString &ehprivate,
		QString &ehpublic, QString &ehinclude, QString &ecpp,
		QString &eccinclude) {
	Element *e = getElement();
	QString name = className(e->getName());

	eccinclude.append("#include \"" + name + ".h\"\n");
	ehinclude.append("#include \"" + name + ".h\"\n");

	// model variable
	ehprivate.append(
			"QList<" + name + "*> "
					+ varName(name, QString(), "List") + ";\n");

	// get ### List
	ehpublic.append(
			"QList<" + name + "*> " + methodName(name, "get", "List")
					+ "() {\n");
	ehpublic.append("  return " + varName(name, QString(), "List") + ";\n");
	ehpublic.append("}\n");

	// add ###
	ehprivate.append(
			"void " + methodName(name, "add") + "(" + name + " * ele);\n");
	ecpp.append(
			"void " + cName + "::" + methodName(name, "add") + "(" + name
					+ " * ele) {\n");
	ecpp.append("  " + varName(name, QString(), "List") + ".append(ele);\n");
	ecpp.append("}\n");

	// init ###
	ehprivate.append("void " + methodName(name, "init") + "();\n");
	ecpp.append(
			"void " + cName + "::" + methodName(name, "init") + "() {\n");
	ecpp.append(
			"  " + varName(name, QString(), "List") + " = QList<" + name
					+ "*>();\n");
	ecpp.append("}\n");

}
