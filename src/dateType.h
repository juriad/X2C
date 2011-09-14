/*
 * dateType.h
 *
 *  Created on: 9.9.2011
 *      Author: Adam Juraszek
 */

#ifndef DATETYPE_H_
#define DATETYPE_H_

#include "simpleType.h"

class DateType: public SimpleType {
public:
	DateType(QString name) :
			SimpleType(name, NULL) {
	}
	virtual ~DateType() {
	}
	virtual QString getDataType();
	virtual QString generateControl(QString inputString);
	virtual QString generateSetter(QString inputString, QString outputVariable);
	virtual QString generateInit(QString varName);
	virtual QString normalize(QString inputString, QString outputVariable);
protected:
	static QString format;
};

#endif /* DateTYPE_H_ */
