/*
 * type.h
 *
 *  Created on: 21.8.2011
 *      Author: Adam Juraszek
 */

#ifndef TYPE_H_
#define TYPE_H_

#include <QtCore/QtCore>
#include "attribute.h"

class AttributeUse;

class Type {
public:
	Type(QString name, Type *base, bool simple);
	virtual ~Type() {
	}
	QList<AttributeUse*> *getAttributes() {
		qDebug() << attributes->size();
		return attributes;
	}
	void addAtribute(AttributeUse *attribute) {
		attributes->append(attribute);
	}
	QString getName() {
		return name;
	}
	virtual bool hasSimpleContent() {
		return simple;
	}
	virtual bool hasComplexContent() {
		return !simple;
	}
	Type *getBase() {
		return base;
	}
	virtual QString generate();
private:
	QList<AttributeUse*> *attributes;
	QString name;
	bool simple;
protected:
	Type *base;
};

#endif /* TYPE_H_ */
