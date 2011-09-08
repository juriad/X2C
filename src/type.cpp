/*
 * type.cpp
 *
 *  Created on: 21.8.2011
 *      Author: Adam Juraszek
 */

#include "type.h"

Type::Type(QString name, Type *base, bool simple) {
	Type::name = name;
	Type::base = base;
	Type::simple = simple;
	Type::attributes = new QList<AttributeUse*>();
}

QString Type::generate() {
	return QString();
}
