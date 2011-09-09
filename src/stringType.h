/*
 * stringType.h
 *
 *  Created on: 9.9.2011
 *      Author: Adam Juraszek
 */

#ifndef STRINGTYPE_H_
#define STRINGTYPE_H_

#include "simpleType.h"

class StringType: public SimpleType {
public:
	StringType(QString name) :
			SimpleType(name, NULL) {
	}
	virtual ~StringType() {
	}
	virtual QString getDataType() {
		qDebug() << "dataType" << "string";
		return "QString";
	}
	virtual QString generateControl(QString inputString) {
		return "return true";
	}
	virtual QString generateSetter(QString inputString,
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
};

#endif /* STRINGTYPE_H_ */
