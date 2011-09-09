/*
 * simpleType.h
 *
 *  Created on: 21.8.2011
 *      Author: Adam Juraszek
 */

#ifndef SIMPLETYPE_H_
#define SIMPLETYPE_H_

#include "type.h"

class SimpleType: public Type {
public:
	SimpleType(QString name, SimpleType *base = NULL) :
			Type(name, base, true) {
	}
	virtual ~SimpleType() {
	}
	virtual bool isSimpleValue();
	virtual bool isList();
	virtual bool isUnion();
	virtual QString getDataType();
	virtual QString generateControl(QString inputString);
	virtual QString generateSetter(QString inputString, QString outputVariable);
};

#endif /* SIMPLETYPE_H_ */
