/*
 * stringType.h
 *
 *  Created on: 9.9.2011
 *      Author: Adam Juraszek
 */

#ifndef STRINGTYPE_H_
#define STRINGTYPE_H_

#include "simpleType.h"

class StringType: public SimpleType {
public:
	StringType(QString name) :
			SimpleType(name, NULL) {
	}
	virtual ~StringType() {
	}
	virtual QString getDataType();
	virtual QString generateControl(QString inputString);
	virtual QString generateSetter(QString inputString, QString outputVariable);
};

#endif /* STRINGTYPE_H_ */
