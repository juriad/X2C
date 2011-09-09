/*
 * stringType.cpp
 *
 *  Created on: 9.9.2011
 *      Author: Adam Juraszek
 */

#include "stringType.h"

QString StringType::getDataType() {
	qDebug() << "dataType" << "string";
	return "QString";
}
QString StringType::generateSetter(QString inputString,
		QString outputVariable) {
	if (getName() == "string") {
		return outputVariable + " = " + inputString + ";";
	} else if (getName() == "normalized string") {
		QString setter =
				"QString normalized = " + inputString
						+ ".replace(QChar(9), QChar(32)).replace(QChar(10), QChar(32)).replace(QChar(13), QChar(32));";
		return outputVariable + " = normalized;";
	} else {
		QString setter =
				"QString normalized = " + inputString
						+ ".replace(QChar(9), QChar(32)).replace(QChar(10), QChar(32)).replace(QChar(13), QChar(32));\n";
		setter.append("QString trimmed = normalized.trimmed();\n");
		setter.append("bool space = false;\n");
		setter.append("for(int i = trimmed.size()-1; i>0; i--) {\n");
		setter.append("if(trimmed.at(i)==QChar(32)) {\n");
		setter.append("if(space) {\n");
		setter.append("trimmed.remove(i);\n");
		setter.append("} else {\n");
		setter.append("space = true;\n");
		setter.append("}\n");
		setter.append("} else {\n");
		setter.append("space = false;\n");
		setter.append("}\n");
		setter.append("}\n");
		return outputVariable + " = trimmed;";
	}
}

QString StringType::generateControl(QString inputString) {
	return "return true";
}

