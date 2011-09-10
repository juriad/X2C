/*
 * attributeUse.cpp
 *
 *  Created on: 28.8.2011
 *      Author: Adam Juraszek
 */

#include "attributeUse.h"
#include "utils.h"
#include "simpleType.h"

void AttributeUse::generate(QString &className, QString &ehprivate,
		QString &ehpublic, QString &ehinclude, QString &ecpp,
		QString &eccinclude) {
	Attribute *a = getAttribute();
	SimpleType *st = a->getSimpleType();
	QString dt = st->getDataType();
	QString name = unqualify(a->getName());
	ehpublic.append("bool " + methodName(name, "has") + "() {\n");
	ehpublic.append("  return " + varName(name, "has", "Value") + ";\n");
	ehpublic.append("}\n");
	ehpublic.append(
			"bool " + methodName(name, "canBe", "Set") + "(QString input);\n");
	ehpublic.append(dt + " " + methodName(name, "get") + "() {\n");
	ehpublic.append("  return " + varName(name, QString(), "Value") + ";\n");
	ehpublic.append("}\n");

	ehprivate.append(dt + " " + varName(name, QString(), "Value") + ";\n");
	ehprivate.append("bool " + varName(name, "has", "Value") + ";\n");
	ehprivate.append("void " + methodName(name, "set") + "(QString string);\n");
	ehprivate.append("void " + methodName(name, "init") + "();\n");

	ecpp.append(
			"void " + className + "::" + methodName(name, "set")
					+ "(QString string) {\n");
	ecpp.append(
			"  "
					+ st->generateSetter("string",
							varName(name, QString(), "Value")) + "\n");
	ecpp.append("  " + varName(name, "has", "Value") + " = true;\n");
	ecpp.append("}\n");

	ecpp.append(
			"void " + className + "::" + methodName(name, "init") + "(){\n");
	ecpp.append(
			"  " + st->generateInit(varName(name, QString(), "Value")) + "\n");
	ecpp.append("}\n");

	ecpp.append(
			"bool " + className + "::" + methodName(name, "canBe", "Set")
					+ "(QString input) {\n");
	ecpp.append("  bool ok;\n");
	ecpp.append("  " + st->generateControl("input") + "\n");
	ecpp.append("  return ok;\n");
	ecpp.append("}\n");
}
