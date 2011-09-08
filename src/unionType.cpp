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

