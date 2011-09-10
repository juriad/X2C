/*
 * simpleType.cpp
 *
 *  Created on: 21.8.2011
 *      Author: Adam Juraszek
 */

#include "simpleType.h"

bool SimpleType::isSimpleValue() {
	return true;
}
bool SimpleType::isList() {
	return false;
}
bool SimpleType::isUnion() {
	return false;
}
QString SimpleType::getDataType() {
	qDebug() << getName();
	if (getBase() != NULL) {
		qDebug() << getBase()->getName();
		return ((SimpleType*) getBase())->getDataType();
	} else {
		qDebug() << "falling back to " << "QString";
		return "QString";
	}
}
// save (can be set (true)), (cannot be set (false)) to previously defined variable ok
QString SimpleType::generateControl(QString inputString) {
	return ((SimpleType*) getBase())->generateControl(inputString);
}
QString SimpleType::generateSetter(QString inputString,
		QString outputVariable) {
	return ((SimpleType*) getBase())->generateSetter(inputString,
			outputVariable);
}

QString SimpleType::generateInit(QString varName) {
	return ((SimpleType*) getBase())->generateInit(varName);
}
