/*
 * elementUse.h
 *
 *  Created on: 28.8.2011
 *      Author: Adam Juraszek
 */

#ifndef ELEMENTUSE_H_
#define ELEMENTUSE_H_

#include "element.h"

class ElementUse {
public:
	ElementUse(Element *ele) {
		ElementUse::ele = ele;
		if (ele->hasDefault()) {
			setDefault(ele->getDefault());
		} else {
			setNoDefault();
		}
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
	Element *getElement() {
		return ele;
	}
	void generate(QString &className, QString &ehprivate, QString &ehpublic,
			QString &ehinclude, QString &ecpp, QString &eccinclude);
private:
	Element *ele;
	QString df;
	int dfState;
};

#endif /* ELEMENTUSE_H_ */
