/*
 * utils.h
 *
 *  Created on: 22.8.2011
 *      Author: Adam Juraszek
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <QtCore/QtCore>
#include <QDomDocument>

QList<QDomElement> getAllElements(QDomElement &parent);

QList<QDomElement> getElements(QDomElement parent, QString tagName);

QDomElement getElement(QDomElement parent, QString tagName);

QString longer(QString userName, bool user);

bool hasElement(QDomElement parent, QString tagName);

QString unqualify(QString name);

QString makeFirstUpper(QString name);

QString makeFirstLower(QString name);

QString methodName(QString name, QString prefix, QString sufix = QString());

QString className(QString name);

QString varName(QString name, QString prefix = QString(), QString sufix =
		QString());

#endif /* UTILS_H_ */
