/*
 * attribute.h
 *
 *  Created on: 21.8.2011
 *      Author: Adam Juraszek
 */

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include <QtCore/QtCore>

class SimpleType;

class Attribute {
public:
	Attribute(QString name);
	~Attribute();
	QString getName() {
		return name;
	}
	void setSimpleType(SimpleType *type) {
		Attribute::type = type;
	}
	void setBase(Attribute *base) {
		Attribute::base = base;
	}
	Attribute *getBase() {
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
	SimpleType *getSimpleType() {
		return type;
	}
private:
	QString name;
	Attribute *base;
	QString df;
	int dfState;
	SimpleType *type;
};

#endif /* ATTRIBUTE_H_ */
