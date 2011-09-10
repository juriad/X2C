/*
 * booleanType.h
 *
 *  Created on: 9.9.2011
 *      Author: Adam Juraszek
 */

#ifndef BOOLEANTYPE_H_
#define BOOLEANTYPE_H_

#include "simpleType.h"

class BooleanType: public SimpleType {
public:
	BooleanType() :
			SimpleType("boolean", NULL) {
	}
	virtual ~BooleanType() {
	}
	virtual QString getDataType();
	virtual QString generateControl(QString inputString);
	virtual QString generateSetter(QString inputString, QString outputVariable);
	virtual QString generateInit(QString varName);
};

#endif /* BOOLEANTYPE_H_ */
