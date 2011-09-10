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
	if (getName() == "string") {
		return outputVariable + " = " + inputString + ";";
	} else if (getName() == "normalizedString") {
		QString setter =
				"QString normalized = " + inputString
						+ ".replace(QChar(9), QChar(32)).replace(QChar(10), QChar(32)).replace(QChar(13), QChar(32));";
		return outputVariable + " = normalized;";
	} else {
		// token
		QString setter =
				"QString normalized = " + inputString
						+ ".replace(QChar(9), QChar(32)).replace(QChar(10), QChar(32)).replace(QChar(13), QChar(32));\n";
		setter.append("QString trimmed = normalized.trimmed();\n");
		setter.append(
				"QString collapsed = trimmed.split(\" \", QString::SkipEmptyParts).join(" ");\n");
		return outputVariable + " = collapsed;";
	}
}

QString StringType::generateControl(QString inputString) {
	return "ok = true";
}

QString StringType::generateInit(QString varName) {
	return varName + " = " + getDataType() + "();";
}
