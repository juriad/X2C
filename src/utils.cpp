/*
 * utils.cpp
 *
 *  Created on: 22.8.2011
 *      Author: Adam Juraszek
 */

#include <QtCore/QtCore>
#include "utils.h"
#include "settings.h"

QList<QDomElement> getAllElements(QDomElement &parent) {
	QDomNodeList l = parent.childNodes();
	QList<QDomElement> children;
	for (int i = 0; i < l.size(); i++) {
		children.append(l.at(i).toElement());
	}
	return children;
}

QList<QDomElement> getElements(QDomElement parent, QString tagName) {
	QDomNodeList l = parent.childNodes();
	QList<QDomElement> children;
	for (int i = 0; i < l.size(); i++) {
		if (l.at(i).isElement()) {
			if (l.at(i).toElement().tagName() == tagName) {
				children.append(l.at(i).toElement());
			}
		}
	}
	return children;
}

QDomElement getElement(QDomElement parent, QString tagName) {
	QDomNodeList l = parent.childNodes();
	for (int i = 0; i < l.size(); i++) {
		if (l.at(i).isElement()) {
			if (l.at(i).toElement().tagName() == tagName) {
				return l.at(i).toElement();
			}
		}
	}
	return QDomElement();
}

bool hasElement(QDomElement parent, QString tagName) {
	QDomNodeList l = parent.childNodes();
	for (int i = 0; i < l.size(); i++) {
		if (l.at(i).isElement()) {
			if (l.at(i).toElement().tagName() == tagName) {
				return true;
			}
		}
	}
	return false;
}

QString longer(QString userName, bool user) {
	QString prefix;
	if (user) {
		prefix = Settings::settings()->getUserPrefix();
	} else {
		prefix = Settings::settings()->getSchemaPrefix();
	}
	if (prefix != "") {
		userName = prefix + ":" + userName;
	}
	return userName;
}

QString unqualify(QString name) {
	int index = name.lastIndexOf(":");
	if (index < 0) {
		return name;
	}
	return name.mid(index + 1);
}

QString makeFirstUpper(QString name) {
	return name.left(1).toUpper() + name.right(name.size() - 1);
}

QString makeFirstLower(QString name) {
	return name.left(1).toLower() + name.right(name.size() - 1);
}

QString methodName(QString name, QString prefix, QString sufix) {
	return prefix + makeFirstUpper(unqualify(name)) + makeFirstUpper(sufix);
}

QString className(QString name) {
	return makeFirstUpper(unqualify(name));
}

QString varName(QString name, QString prefix, QString sufix) {
	if (prefix.size() > 0) {
		return prefix + makeFirstUpper(unqualify(name)) + makeFirstUpper(sufix);
	} else {
		return makeFirstLower(unqualify(name)) + makeFirstUpper(sufix);
	}
}
