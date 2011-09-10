/*
 * booleanType.cpp
 *
 *  Created on: 9.9.2011
 *      Author: Adam Juraszek
 */

#include "booleanType.h"

QString BooleanType::getDataType() {
	return "bool";
}
QString BooleanType::generateSetter(QString inputString,
		QString outputVariable) {
	QString setter = "  QString b = " + inputString + ".trimmed();\n";
	setter.append(
			"  if(b.startsWith(\"t\") || b.startsWith(\"y\") || b.startsWith(\"1\")) {\n");
	setter.append("  " + outputVariable + " = true;\n");
	setter.append("  } else {\n");
	setter.append("  " + outputVariable + " = false;\n");
	setter.append("  }");
	return setter;
}

QString BooleanType::generateControl(QString inputString) {
	return "  ok = true;";
}

QString BooleanType::generateInit(QString varName) {
	return "  " + varName + " = false;";
}
