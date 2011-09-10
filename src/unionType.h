/*
 * unionType.h
 *
 *  Created on: 24.8.2011
 *      Author: Adam Juraszek
 */

#ifndef UNIONTYPE_H_
#define UNIONTYPE_H_

#include <QtCore/QtCore>
#include "unionType.h"
#include "simpleType.h"

/*
 * is not supported in generated class
 * only placeholder
 */
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
	virtual QString getDataType();
	virtual QString generateControl(QString inputString);
	virtual QString generateSetter(QString inputString, QString outputVariable);
	virtual QString generateInit(QString varName);
private:
	QList<SimpleType*> members;
};

#endif /* UNIONTYPE_H_ */
