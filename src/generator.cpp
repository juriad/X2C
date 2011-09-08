/*
 * generator.cpp
 *
 *  Created on: 1.9.2011
 *      Author: Adam Juraszek
 */

#include "generator.h"

#include "objects.h"
#include <QtCore/QtCore>

static void generateClass(Element* ele) {
	ele->generate();
}

void generateClasses() {
	QHash<QString, Element*> elements = getEles();
	for (int i = 0; i < elements.size(); i++) {
		generateClass(elements.values().at(i));
	}
}
