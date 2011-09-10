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

	// data model, ends with underscore
	ehprivate.append(dt + " " + varName(name, QString(), "Value") + ";\n");
	ehprivate.append("bool " + varName(name, "has", "Value") + ";\n");

	// has ###, returns true also if default exists
	ehpublic.append("bool " + methodName(name, "has") + "() {\n");
	ehpublic.append("  return " + varName(name, "has", "Value") + ";\n");
	ehpublic.append("}\n");

	// is ### Valid, returns true if input can be set
	ehpublic.append(
			"bool " + methodName(name, "is", "Valid") + "(QString input);\n");
	ecpp.append(
			"bool " + className + "::" + methodName(name, "is", "Valid")
					+ "(QString input) {\n");
	ecpp.append("  bool ok;\n");
	// inserts control which expects string variable input and bool ok
	ecpp.append("  " + st->generateControl("input") + "\n");
	ecpp.append("  return ok;\n");
	ecpp.append("}\n");

	// get ###, returns default if exists or value if set
	ehpublic.append(dt + " " + methodName(name, "get") + "() {\n");
	ehpublic.append("  return " + varName(name, QString(), "Value") + ";\n");
	ehpublic.append("}\n");

	// set ###, doesn't do tests
	ehprivate.append("void " + methodName(name, "set") + "(QString input);\n");
	ecpp.append(
			"void " + className + "::" + methodName(name, "set")
					+ "(QString input) {\n");
	// inserts setting mechanism, expects string variable input and model variable
	ecpp.append(
			"  " + st->generateSetter("input", varName(name, QString(), "Value"))
					+ "\n");
	ecpp.append("  " + varName(name, "has", "Value") + " = true;\n");
	ecpp.append("}\n");

	// default value handling, defaults in attribute are copied to attributeUse
	QString df;
	bool hasDf = false;
	if (hasDefault()) {
		hasDf = true;
		df = getDefault();
	}

	// init ###, sets default if exists
	ehprivate.append("void " + methodName(name, "init") + "();\n");
	ecpp.append(
			"void " + className + "::" + methodName(name, "init") + "() {\n");
	// inserts initializer of model
	ecpp.append("  " + st->generateInit(varName(name, QString(), "Value")) + "\n");
	if (hasDf) {
		ecpp.append("  " + methodName(name, "set") + "(" + df + ");\n");
	}
	ecpp.append("}\n");

}
