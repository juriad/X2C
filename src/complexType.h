/*
 * complexType.h
 *
 *  Created on: 21.8.2011
 *      Author: Adam Juraszek
 */

#ifndef COMPLEXTYPE_H_
#define COMPLEXTYPE_H_

#include "type.h"

#include "elementUse.h"

class ComplexType: public Type {
public:
	ComplexType(QString name, ComplexType *base = NULL) :
			Type(name, base, false) {
		elements = new QList<ElementUse*>();
	}
	void addElement(ElementUse *element) {
		elements->append(element);
	}
	QList<ElementUse*> *getElements() {
		return elements;
	}
	virtual ~ComplexType() {
	}
	virtual bool hasSimpleContent();
	virtual bool hasComplexContent();
private:
	QList<ElementUse*> *elements;
};

#endif /* COMPLEXTYPE_H_ */
