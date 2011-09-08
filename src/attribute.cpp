/*
 * attribute.cpp
 *
 *  Created on: 21.8.2011
 *      Author: Adam Juraszek
 */

#include "attribute.h"

Attribute::Attribute(QString name) {
	Attribute::name = name;
	Attribute::base = NULL;
	Attribute::type = NULL;
	setNoDefault();
}
