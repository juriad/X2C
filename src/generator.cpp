/*
 * generator.cpp
 *
 *  Created on: 1.9.2011
 *      Author: Adam Juraszek
 */

#include <QtCore/QtCore>
#include "generator.h"
#include "objects.h"

static void generateClass(Element* ele) {
	ele->generate();
}

void generateClasses() {
	QHash<QString, Element*> elements = getElements();
	for (int i = 0; i < elements.size(); i++) {
		generateClass(elements.values().at(i));
	}
}
