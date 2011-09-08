#include <QtDebug>
#include <QDomDocument>
#include <QtCore/QtCore>

#include "simpleType.h"
#include "complexType.h"
#include "settings.h"
#include "objects.h"
#include "utils.h"
#include "generator.h"

class Type;

QDomDocument * loadXmlDocument(QFile * file) {

	if (!file->exists()) {
		qDebug() << "doesn't exist";
		return NULL;
	}

	QString errorStr;
	int errorLine;
	int errorColumn;

	QDomDocument *doc = new QDomDocument;
	if (!doc->setContent(file, true, &errorStr, &errorLine, &errorColumn)) {
		qDebug()
				<< QString("Error > %1 < in file %2 on line %3, column %4").arg(
						errorStr).arg(file->fileName()).arg(errorLine).arg(
						errorColumn);
		delete doc;
		doc = NULL;
	}
	return doc;
}

void printNode(QDomNode n, int tab) {
	QString t = "  ";
	QString tt;
	QString s;
	for (int i = 0; i < tab; i++) {
		tt.append(t);
	}
	if (n.isElement()) {
		QDomElement e = n.toElement();
		s = QString("e- %1, value: %2; %3 : %4").arg(e.nodeName()).arg(
				e.text() == "" ? "empty" : e.text()).arg(e.prefix()).arg(
				e.localName());
		qDebug() << tt.append(s);
		QDomNamedNodeMap as = e.attributes();
		for (int i = 0; i < as.count(); i++) {
			printNode(as.item(i), tab + 1);
		}
	} else if (n.isAttr()) {
		QDomAttr a = n.toAttr();
		s = QString("a- %1, value: %2; %3 : %4").arg(a.nodeName()).arg(
				a.nodeValue()).arg(a.prefix()).arg(a.localName());
		qDebug() << tt.append(s);
	}
}

void iterateOverDocument(QDomNode n, int tab) {
	printNode(n, tab);
	//QDomNodeList es = n.childNodes();
	QDomElement e = n.toElement();
	QList<QDomElement> es = getAllElements(e);
	for (int i = 0; i < es.count(); i++) {
		iterateOverDocument(es.at(i), tab + 1);
	}
}

void makeGlobalTypes(QDomElement root) {
	QQueue<QDomElement> waitPoints;

	QList<QDomElement> ss = getElements(root, longer("simpleType", false));
	for (int i = 0; i < ss.size(); i++) {
		QDomElement s = ss.at(i);
		waitPoints.enqueue(s);
		qDebug() << "queued s";
	}

	while (waitPoints.size() > 0) {
		QDomElement s = waitPoints.dequeue();
		if (!simpleType(s)) {
			waitPoints.enqueue(s);
		}
	}

	QList<QDomElement> cs = getElements(root, longer("complexType", false));
	for (int i = 0; i < cs.size(); i++) {
		QDomElement c = cs.at(i);
		waitPoints.enqueue(c);
		qDebug() << "queued c";
	}
	while (waitPoints.size() > 0) {
		QDomElement c = waitPoints.dequeue();
		if (!complexType(c)) {
			waitPoints.enqueue(c);
		}
	}
}

void printTypes() {
	qDebug() << "types";
	QList<Type*> vs = getTypes().values();
	for (int i = 0; i < vs.size(); i++) {
		Type* t = vs.at(i);
		QString s = t->getName();
		s.append(t->hasSimpleContent() ? " *" : " #");
		s.append(" " + QString::number((t->getAttributes()->size())));
		qDebug() << s;
	}
}

void printAttrs() {
	qDebug() << "attrs";
	QList<Attribute*> vs = getAttrs().values();
	for (int i = 0; i < vs.size(); i++) {
		Attribute* t = vs.at(i);
		QString s = t->getName();
		qDebug() << s;
	}
}

void printEles() {
	qDebug() << "elements";
	QList<Element*> vs = getEles().values();
	for (int i = 0; i < vs.size(); i++) {
		Element* t = vs.at(i);
		QString s = t->getName();
		qDebug() << s;
	}
}

#include "normalizer.h"

int main(int argc, char *argv[]) {
	QCoreApplication(argc, argv);

	Settings::settings()->setSchemaPrefix(QString());
	Settings::settings()->setUserPrefix("tns");
	Settings::settings()->setDir(
			new QDir(QDir::current().currentPath() + "/gen"));

	prepareBuildInTypes();

	QFile *in = new QFile(argv[1]);
	QDomDocument *doc = loadXmlDocument(in);
	if (doc == NULL) {
		qDebug() << QString("error");
	} else {
		globalizeAndName(*doc);
		QDomElement root = doc->documentElement();
		iterateOverDocument(root, 0);

		makeEmptyAttributes(root);
		makeEmptyElements(root);
		makeGlobalTypes(root);
		makeAttributeBowels(root);
		makeElementBowels(root);
		printTypes();
		printAttrs();
		printEles();
		generateClasses();
		delete doc;
	}
	return EXIT_SUCCESS;
}
