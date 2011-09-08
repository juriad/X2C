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
