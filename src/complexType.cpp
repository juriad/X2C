/*
 * complexType.cpp
 *
 *  Created on: 21.8.2011
 *      Author: Adam Juraszek
 */

#include "complexType.h"

bool ComplexType::hasComplexContent() {
	return true;
}

bool ComplexType::hasSimpleContent() {
	return false;
}
