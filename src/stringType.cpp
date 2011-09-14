/*
 * stringType.cpp
 *
 *  Created on: 9.9.2011
 *      Author: Adam Juraszek
 */

#include "stringType.h"

QString StringType::getDataType() {
	return "QString";
}

QString StringType::generateSetter(QString inputString,
		QString outputVariable) {
	QString setter = "  if(" + inputString
			+ (getName() == "token" ? ".trimmed()" : "") + ".isEmpty()) {\n";
	setter.append("    return;\n");
	setter.append("  }\n");
	if (getName() == "string") {
		setter.append("  " + outputVariable + " = " + inputString + ";");
	} else if (getName() == "normalizedString") {
		setter.append(
				"  QString normalized = " + inputString
						+ ".replace(QChar(9), QChar(32)).replace(QChar(10), QChar(32)).replace(QChar(13), QChar(32));\n");
		setter.append("  " + outputVariable + " = normalized;");
		return setter;
	} else {
		// token
		setter.append(
				"  QString normalized = " + inputString
						+ ".replace(QChar(9), QChar(32)).replace(QChar(10), QChar(32)).replace(QChar(13), QChar(32));\n");
		setter.append("  QString trimmed = normalized.trimmed();\n");
		setter.append(
				"  QString collapsed = trimmed.split(\" \", QString::SkipEmptyParts).join(\" \");\n");
		setter.append("  " + outputVariable + " = collapsed;");
		return setter;
	}
	return setter;
}

QString StringType::generateControl(QString inputString) {
	return "ok = !" + inputString + (getName() == "token" ? ".trimmed()" : "")
			+ ".isEmpty();";
}

QString StringType::generateInit(QString varName) {
	return varName + " = " + getDataType() + "();";
}
