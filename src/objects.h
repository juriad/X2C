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

QHash<QString, Element*> &getElements();

bool simpleType(QDomElement simpleType);

bool complexType(QDomElement complexType);

void makeEmptyAttributes(QDomElement root);

void makeAttributeBowels(QDomElement root);

void makeEmptyElements(QDomElement root);

void makeElementBowels(QDomElement root);

#endif /* OBJECTS_H_ */
