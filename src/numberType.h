/*
 * stringType.h
 *
 *  Created on: 9.9.2011
 *      Author: Adam Juraszek
 */

#ifndef NUMBERTYPE_H_
#define NUMBERTYPE_H_

#include "simpleType.h"

class NumberType: public SimpleType {
public:
	NumberType(QString name) :
			SimpleType(name, NULL) {
	}
	virtual ~NumberType() {
	}
	virtual QString getDataType();
	virtual QString generateControl(QString inputString);
	virtual QString generateSetter(QString inputString, QString outputVariable);
	virtual QString generateInit(QString varName);
private:
	QString toDataType(QString input, QString output, QString error);
};

#endif /* NUMBERTYPE_H_ */
