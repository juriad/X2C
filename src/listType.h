/*
 * listType.h
 *
 *  Created on: 24.8.2011
 *      Author: Adam Juraszek
 */

#ifndef LISTTYPE_H_
#define LISTTYPE_H_

#include "simpleType.h"
#include <QtCore/QtCore>

class ListType: public SimpleType {
public:
	ListType(QString name, SimpleType *item) :
			SimpleType(name, NULL) {
		ListType::item = item;
	}
	ListType(QString name, ListType *base) :
			SimpleType(name, base) {
		ListType::item = base->getItem();
	}
	virtual ~ListType() {
	}
	SimpleType *getItem() {
		return item;
	}
	virtual bool isSimpleValue();
	virtual bool isList();
	virtual bool isUnion();
	virtual QString getDataType();
	virtual QString generateControl(QString inputString);
	virtual QString generateSetter(QString inputString, QString outputVariable);
	virtual QString generateInit(QString varName);
private:
	QString toDt(QString input, QString output, QString error);
	SimpleType *item;
};

#endif /* LISTTYPE_H_ */
