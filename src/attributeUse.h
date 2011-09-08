/*
 * attributeUse.h
 *
 *  Created on: 28.8.2011
 *      Author: Adam Juraszek
 */

#ifndef ATTRIBUTEUSE_H_
#define ATTRIBUTEUSE_H_
#include <QtCore/QtCore>

#include "attribute.h"

class AttributeUse {
public:
	AttributeUse(Attribute *attr) {
		AttributeUse::attr = attr;
		if (attr->hasDefault()) {
			setDefault(attr->getDefault());
		} else {
			setNoDefault();
		}
	}
	Attribute *getAttribute() {
		return attr;
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
	void generate(QString &className, QString &ehprivate, QString &ehpublic, QString &ehinclude,
			QString &ecpp, QString &eccinclude);
private:
	Attribute *attr;
	QString df;
	int dfState;
};

#endif /* ATTRIBUTEUSE_H_ */
