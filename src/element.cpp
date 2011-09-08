/*
 * element.cpp
 *
 *  Created on: 29.8.2011
 *      Author: Adam Juraszek
 */

#include "element.h"
#include "utils.h"
#include "attributeUse.h"
#include "type.h"
#include "simpleType.h"
#include "complexType.h"
#include "settings.h"

Element::Element(QString name) {
	Element::name = name;
	Element::base = NULL;
	Element::type = NULL;
	setNoDefault();
}

QString Element::getClassName() {
	return makeFirstUpper(unqualify(getName()));
}

static void saveToFile(QString file, QString &string) {
	QFile f(file);
	qDebug() << f.fileName();
	f.open(QFile::WriteOnly);
	f.write(string.toAscii());
	f.close();
}

void Element::generate() {
	QString eh = QString();
	QString ehprivate = QString();
	QString ehpublic = QString();
	QString ehinclude = QString();
	QString ecppinclude = QString();
	QString ecpp = QString();

	Type *t = this->getType();

	if (t->hasSimpleContent()) {
		SimpleType *st = (SimpleType*) t;
		Attribute *a = new Attribute("value");
		a->setSimpleType(st);
		AttributeUse *au = new AttributeUse(a);
		t->addAtribute(au);
	}

	// get all elements and attributes to generates
	QHash<QString, AttributeUse*> attributes = QHash<QString, AttributeUse*>();
	QHash<QString, ElementUse*> elements = QHash<QString, ElementUse*>();

	Type *tt = t;
	do {
		QList<AttributeUse*> *aus = tt->getAttributes();
		QList<ElementUse*> *eus;
		if (tt->hasComplexContent()) {
			eus = ((ComplexType*) tt)->getElements();
			for (int i = 0; i < eus->size(); i++) {
				ElementUse *eu = eus->at(i);
				QString name = eu->getElement()->getName();
				if (!elements.contains(name)) {
					elements.insert(name, eu);
				} else {
					qDebug() << "element overridden";
				}
			}
		}
		for (int i = 0; i < aus->size(); i++) {
			AttributeUse *au = aus->at(i);
			QString name = au->getAttribute()->getName();
			qDebug() << name;
			if (!attributes.contains(name)) {
				attributes.insert(name, au);
			} else {
				qDebug() << "attribute overridden";
			}
		}
		tt = tt->getBase();
	} while (tt != NULL);

	QString cname = getClassName();

	// generate attributes
	QList<AttributeUse*> attributesValues = attributes.values();
	for (int i = 0; i < attributesValues.size(); i++) {
		AttributeUse *au = attributesValues.at(i);
		au->generate(cname, ehprivate, ehpublic, ehinclude, ecpp, ecppinclude);
	}

	// generate elements
	QList<ElementUse*> elementsValues = elements.values();
	for (int i = 0; i < elementsValues.size(); i++) {
		ElementUse *eu = elementsValues.at(i);
		eu->generate(cname, ehprivate, ehpublic, ehinclude, ecpp, ecppinclude);
	}

	QList<QString> elementsNames = elements.keys();
	QList<QString> attributesNames = attributes.keys();

	// concatenate .h
	eh.append("#ifndef " + cname + "_H_\n");
	eh.append("#define " + cname + "_H_\n");
	eh.append("#include <QtCore/QtCore>\n");
	eh.append("#include <QDomDocument>\n");
	eh.append(ehinclude);
	eh.append("\n");

	eh.append("class " + cname + " {\n");

	eh.append("public:\n");
	eh.append(cname + "() {\n");
	for (int i = 0; i < elementsNames.size(); i++) {
		eh.append("  " + methodName(elementsNames.at(i), "init") + "();\n");
	}
	for (int i = 0; i < attributesNames.size(); i++) {
		eh.append("  " + methodName(attributesNames.at(i), "init") + "();\n");
	}
	eh.append("}\n");
	eh.append("static " + cname + "* fromFile( QFile &file);\n");
	eh.append("static " + cname + "* fromElement( QDomElement &element);\n");
	eh.append("static QDomDocument * loadXmlDocument(QFile & file);\n");
	eh.append(ehpublic);
	eh.append("\n");

	eh.append("private:\n");
	eh.append("void addSubElement( QDomElement &element);\n");
	eh.append("void setAttribute( QDomAttr &attr);\n");
	eh.append(ehprivate);
	eh.append("\n");

	eh.append("};\n");
	eh.append("#endif");

	// concatenate .cpp
	ecppinclude.prepend("#include \"" + cname + ".h\"\n");
	ecppinclude.append("\n");

	ecpp.prepend(ecppinclude);
	ecpp.append(
			cname + " * " + cname + "::fromElement(QDomElement &element) {\n");
	ecpp.append("  qDebug() << element.localName() <<\"fromElement\";\n");
	ecpp.append(
			"  " + cname + " *" + varName(cname) + " = new " + cname + "();\n");
	ecpp.append("  QDomNodeList list = element.childNodes();\n");
	ecpp.append("  for (int i = 0; i < list.size(); i++) {\n");
	ecpp.append("    if (list.at(i).isElement()) {\n");
	ecpp.append("      QDomElement e = list.at(i).toElement();\n");
	ecpp.append("      " + varName(cname) + "->addSubElement(e);\n");
	ecpp.append("    }\n");
	ecpp.append("  }\n");
	ecpp.append("  QDomNamedNodeMap attrs = element.attributes();\n");
	ecpp.append("  for(int i = 0; i<attrs.size(); i++) {\n");
	ecpp.append("    QDomAttr a = attrs.item(i).toAttr();\n");
	ecpp.append("    " + varName(cname) + "->setAttribute(a);\n");
	ecpp.append("  }\n");
	if (t->hasSimpleContent()) {
		ecpp.append("  " + varName(cname) + "->setValue(element.text());\n");
	}
	ecpp.append("  return " + varName(cname) + ";\n");
	ecpp.append("}\n");
	ecpp.append("void " + cname + "::addSubElement( QDomElement &element) {\n");
	ecpp.append("  qDebug() << element.localName() <<\"subElement\";\n");
	for (int i = 0; i < elementsNames.size(); i++) {
		QString cn = className(elementsNames.at(i));
		ecpp.append(
				"  if(element.localName().compare(\"" + cn
						+ "\", Qt::CaseInsensitive)==0) {\n");
		ecpp.append("    " + cn + " *cn = " + cn + "::fromElement(element);\n");
		ecpp.append("    " + methodName(cn, "add") + "(cn);\n");
		ecpp.append("    return;\n");
		ecpp.append("  }\n");
	}
	ecpp.append("}\n");
	ecpp.append("void " + cname + "::setAttribute( QDomAttr &attr) {\n");

	for (int i = 0; i < attributesNames.size(); i++) {
		QString an = className(attributesNames.at(i));
		ecpp.append(
				"  if(attr.localName().compare(\"" + an
						+ "\", Qt::CaseInsensitive)==0) {\n");
		ecpp.append("    " + methodName(an, "set") + "(attr.value());\n");
		ecpp.append("    return;\n");
		ecpp.append("  }\n");
	}
	ecpp.append("}\n");

	ecpp.append(
			"QDomDocument * " + cname + "::loadXmlDocument(QFile & file) {\n");
	ecpp.append("  if (!file.exists()) {\n");
	ecpp.append("    qDebug() << \"doesn't exist\";\n");
	ecpp.append("    return NULL;\n");
	ecpp.append("  }\n");
	ecpp.append("  QString errorStr;\n");
	ecpp.append("  int errorLine;\n");
	ecpp.append("  int errorColumn;\n");
	ecpp.append("  QDomDocument *doc = new QDomDocument;\n");
	ecpp.append(
			"  if (!doc->setContent(&file, true, &errorStr, &errorLine, &errorColumn)) {\n");
	ecpp.append(
			"    qDebug()<< QString(\"Error > %1 < in file %2 on line %3, column %4\").arg(\n");
	ecpp.append(
			"      errorStr).arg(file.fileName()).arg(errorLine).arg(errorColumn);\n");
	ecpp.append("    delete doc;\n");
	ecpp.append("    doc = NULL;\n");
	ecpp.append("  }\n");
	ecpp.append("  return doc;\n");
	ecpp.append("}\n");
	ecpp.append(cname + "  * " + cname + "::fromFile(QFile & file) {\n");
	ecpp.append(
			"  QDomDocument *doc = " + cname + "::loadXmlDocument(file);\n");
	ecpp.append("  QDomElement root = doc->documentElement();\n");
	ecpp.append("  return " + cname + "::fromElement(root);\n");
	ecpp.append("}\n");

	QDir *d = Settings::settings()->getDir();
	saveToFile(d->filePath(cname + ".h"), eh);
	saveToFile(d->filePath(cname + ".cpp"), ecpp);
}
