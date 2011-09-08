/*
 * objects.h
 *
 *  Created on: 24.8.2011
 *      Author: Adam Juraszek
 */

#ifndef OBJECTS_H_
#define OBJECTS_H_
#include <QDomDocument>
#include <QtCore/QtCore>
#include "element.h"

class Type;
class Attribute;

void prepareBuildInTypes();

QHash<QString, Type*> &getTypes();

QHash<QString, Attribute*> &getAttrs();

QHash<QString, Element*> &getEles();

bool simpleTypeRestriction(QDomElement simpleType, QDomElement restriction);

bool simpleTypeList(QDomElement simpleType, QDomElement restriction);

bool simpleTypeUnion(QDomElement simpleType, QDomElement restriction);

bool simpleType(QDomElement simpleType);

bool simpleContentRestriction(QDomElement complexType, QDomElement restriction);

bool simpleContentExtension(QDomElement complexType, QDomElement extension);

bool simpleContent(QDomElement complexType, QDomElement simpleContent);

bool complexContentRestriction(QDomElement complexType,
		QDomElement restriction);

bool complexContentExtension(QDomElement complexType, QDomElement extension);

bool complexContent(QDomElement complexType, QDomElement simpleContent);

bool complexType(QDomElement complexType);

void makeEmptyAttributes(QDomElement root);

void makeAttributeBowels(QDomElement root);

void makeEmptyElements(QDomElement root);

void makeElementBowels(QDomElement root);

#endif /* OBJECTS_H_ */
