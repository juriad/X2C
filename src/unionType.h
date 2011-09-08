/*
 * unionType.h
 *
 *  Created on: 24.8.2011
 *      Author: Adam Juraszek
 */

#ifndef UNIONTYPE_H_
#define UNIONTYPE_H_

#include "unionType.h"
#include <QtCore/QtCore>
#include "simpleType.h"

class UnionType: public SimpleType {
public:
	UnionType(QString name, QList<SimpleType*> members) :
			SimpleType(name, NULL) {
		UnionType::members = members;
	}
	UnionType(QString name, UnionType *base) :
			SimpleType(name, base) {
		UnionType::members = base->getMembers();
	}
	virtual ~UnionType() {
	}
	QList<SimpleType*> getMembers() {
		return members;
	}
	virtual bool isSimpleValue();
	virtual bool isList();
	virtual bool isUnion();
private:
	QList<SimpleType*> members;
};

#endif /* UNIONTYPE_H_ */
