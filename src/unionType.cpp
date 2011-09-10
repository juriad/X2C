/*
 * unionType.cpp
 *
 *  Created on: 24.8.2011
 *      Author: Adam Juraszek
 */

#include "unionType.h"

bool UnionType::isSimpleValue() {
	return false;
}

bool UnionType::isList() {
	return true;
}

bool UnionType::isUnion() {
	return false;
}

QString UnionType::getDataType() {
	qDebug() << "unimplemented";
	return QString();
}

QString UnionType::generateControl(QString inputString) {
	qDebug() << "unimplemented";
	return QString();
}

QString UnionType::generateSetter(QString inputString, QString outputVariable) {
	qDebug() << "unimplemented";
	return QString();
}

QString UnionType::generateInit(QString varName) {
	qDebug() << "unimplemented";
	return QString();
}
