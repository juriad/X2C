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

/*QString ListType::getDataType() {
	return "QList<" + getItem()->getDataType() + ">";
}

QString generateSetter(QString inputString, QString outputVariable) {
	// TODO generateSetter for list
	return "";
}

QString generateControl(QString inputString) {
	// TODO generateControl for list
	return "return true;";
}*/
