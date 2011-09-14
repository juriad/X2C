/*
 * listType.cpp
 *
 *  Created on: 24.8.2011
 *      Author: Adam Juraszek
 */

#include "listType.h"
#include "utils.h"

bool ListType::isSimpleValue() {
	return false;
}
bool ListType::isList() {
	return true;
}
bool ListType::isUnion() {
	return false;
}

QString ListType::getDataType() {
	return "QList<" + getItem()->getDataType() + ">";
}

QString ListType::generateSetter(QString inputString, QString outputVariable) {
	// variable ok is redefined inside
	QString control = "  bool outerOk;\n";
	// make list variable safe
	control.append("  " + toDataType(inputString, "list_", "&outerOk") + "\n");
	control.append("  if(!outerOk) {\n");
	control.append("    return;\n");
	control.append("  }\n");
	control.append("  " + outputVariable + " = list_;");
	return control;
}

QString ListType::generateControl(QString inputString) {
	// variable ok is redefined inside
	QString control = "  bool outerOk;\n";
	// make list variable safe
	control.append(
			"  "
					+ toDataType(inputString, "list_", "&outerOk").replace(
							"return", "return false") + "\n");
	control.append("  ok = outerOk;");
	return control;
}

/*
 * input is previously defined string variable
 * output is dt variable
 * error is previously defined bool* variable -- rather positive
 */
QString ListType::toDataType(QString input, QString output, QString error) {
	QString setter =
			"QString normalized = " + input
					+ ".replace(QChar(9), QChar(32)).replace(QChar(10), QChar(32)).replace(QChar(13), QChar(32));\n";
	setter.append("  QString trimmed = normalized.trimmed();\n");
	setter.append(
			"  QStringList parts = trimmed.split(\" \", QString::SkipEmptyParts);\n");
	setter.append(
			"  " + getDataType() + " " + output + " = " + getDataType()
					+ "();\n");
	setter.append("  *(" + error + ") = !trimmed.isEmpty();\n");
	setter.append("  for(int i = 0; i < parts.size(); i++) {\n");
	setter.append("    bool ok;");
	setter.append("    " + getItem()->generateControl("parts.at(i)") + "\n");
	setter.append("    if(ok) {\n");
	setter.append("      " + getItem()->getDataType() + " item;\n");
	setter.append(
			"      " + getItem()->generateSetter("parts.at(i)", "item") + "\n");
	setter.append("      " + output + ".append(item);\n");
	setter.append("    } else {\n");
	setter.append("      *(" + error + ") = false;\n");
	setter.append("      break;\n");
	setter.append("    }\n");
	setter.append("  }\n");
	return setter;
}

QString ListType::generateInit(QString varName) {
	return varName + " = " + getDataType() + "();";
}
