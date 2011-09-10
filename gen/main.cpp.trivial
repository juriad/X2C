#include <QtCore/QtCore>
#include "VeryComplex.h"

int main(int argc, char* argv[]) {
	QFile file("/home/adam/programming/workspace/X2C/trivial.xml");
	VeryComplex *c = VeryComplex::fromFile(file);
	qDebug() <<"read";
	QList<Anon30*> anon30s = c->getAnon30List();
	for (int i = 0; i < anon30s.size(); i++) {
		QList<Anon29*> anon29s = anon30s.at(i)->getAnon29List();
		for (int j = 0; j < anon29s.size(); j++) {
			QList<Anon28*> anon28s = anon29s.at(i)->getAnon28List();
			for (int k = 0; k < anon28s.size(); k++) {
				qDebug() << anon28s.at(k)->getValue() << "anon28";
			}
			QList<Anon27*> anon27s = anon29s.at(i)->getAnon27List();
			for (int k = 0; k < anon27s.size(); k++) {
				qDebug() << anon27s.at(k)->getValue() << "anon27";
			}
		}
	}
	QList<SimpleElementCustom*> simpleElementCustoms =
			c->getSimpleElementCustomList();
	for (int i = 0; i < simpleElementCustoms.size(); i++) {
		qDebug() << simpleElementCustoms.at(i)->getValue()
				<< "simpleElementCustom";
	}
	QList<SimpleElement*> simpleElements = c->getSimpleElementList();
	for (int i = 0; i < simpleElements.size(); i++) {
		qDebug() << simpleElements.at(i)->getValue() << "simpleElement";
	}

	return EXIT_SUCCESS;
}
