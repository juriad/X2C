/*
 * element.h
 *
 *  Created on: 29.8.2011
 *      Author: Adam Juraszek
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <QtCore/QtCore>

class Type;

class Element {
public:
	Element(QString name);
	~Element();
	QString getName() {
		return name;
	}
	void setType(Type *type) {
		Element::type = type;
	}
	void setBase(Element *base) {
		Element::base = base;
	}
	Element *getBase() {
		return base;
	}
	QString getDefault() {
		if (dfState == 1) {
			return df;
		}
		return QString();
	}
	void setNoDefault() {
		dfState = 0;
		df = QString();
	}
	bool hasDefault() {
		return dfState == 1;
	}
	void setDefault(QString def) {
		dfState = 1;
		df = def;
	}
	Type *getType() {
		return type;
	}
	void generate();
private:
	QString name;
	Element *base;
	QString df;
	int dfState;
	Type *type;
};

#endif /* ELEMENT_H_ */
