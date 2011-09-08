/*
 * listType.cpp
 *
 *  Created on: 24.8.2011
 *      Author: Adam Juraszek
 */

#include "listType.h"

bool ListType::isSimpleValue() {
	return false;
}
bool ListType::isList() {
	return true;
}
bool ListType::isUnion() {
	return false;
}

