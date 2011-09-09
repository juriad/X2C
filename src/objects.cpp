/*
 * objects.cpp
 *
 *  Created on: 24.8.2011
 *      Author: Adam Juraszek
 */

#include "objects.h"
#include "utils.h"
#include "simpleType.h"
#include "listType.h"
#include "unionType.h"
#include "complexType.h"

#include "attributeUse.h"
#include "elementUse.h"

#include "stringType.h"

QHash<QString, Type*> types;
QHash<QString, Attribute*> attrs;
QHash<QString, Element*> eles;

QHash<QString, Type*> &getTypes() {
	return types;
}

QHash<QString, Attribute*> &getAttrs() {
	return attrs;
}

QHash<QString, Element*> &getEles() {
	return eles;
}

void addAttributes(QDomElement &parent, Type *type) {
	QList<QDomElement> as = getElements(parent, longer("attribute", false));
	for (int i = 0; i < as.size(); i++) {
		QDomElement ae = as.at(i);
		Attribute *a = attrs.value(ae.attribute("ref"));
		AttributeUse *au = new AttributeUse(a);
		if (ae.hasAttribute("default")) {
			au->setDefault(ae.attribute("default"));
		} else if (ae.hasAttribute("fixed")) {
			au->setDefault(ae.attribute("fixed"));
		}
		type->addAtribute(au);
	}
}

void addElements(QDomElement &parent, ComplexType *type) {
	QList<QDomElement> es = getAllElements(parent);
	for (int i = 0; i < es.size(); i++) {
		QDomElement ee = es.at(i);
		if (ee.localName() == "element") {
			Element *e = eles.value(ee.attribute("ref"));
			ElementUse *eu = new ElementUse(e);
			if (ee.hasAttribute("default")) {
				eu->setDefault(ee.attribute("default"));
			} else if (ee.hasAttribute("fixed")) {
				eu->setDefault(ee.attribute("fixed"));
			}
			type->addElement(eu);
		} else {
			addElements(ee, type);
		}
	}
}

void prepareBuildInTypes() {
	QString name;
	name = longer("string", false);
	types.insert(name, new StringType("string"));
	name = longer("normalized string", false);
	types.insert(name, new StringType("normalized string"));
	name = longer("token", false);
	types.insert(name, new StringType("token"));

	/*name = longer("anyURI", false);
	types.insert(name, new SimpleType(name));
	name = longer("nonNegativeInteger", false);
	types.insert(name, new SimpleType(name));*/
}

bool simpleTypeRestriction(QDomElement simpleType, QDomElement restriction) {
	qDebug() << "restriction";
	if (restriction.hasAttribute(QString("base"))) {
		QString base = restriction.attribute(QString("base"));
		Type *baseType = types.value(base, NULL);
		if (baseType == NULL) {
			return false;
		} else {
			SimpleType *sType = (SimpleType*) baseType;
			QString name = longer(simpleType.attribute("name"), true);
			if (sType->isSimpleValue()) {
				types.insert(name, new SimpleType(name, sType));
			} else if (sType->isList()) {
				types.insert(name, new ListType(name, (ListType*) sType));
			} else if (sType->isSimpleValue()) {
				types.insert(name, new UnionType(name, (UnionType*) sType));
			} else {
				qDebug("unknown type of restriction base");
			}
			// NOTODO restriction on value
		}
	} else {
		qDebug()
				<< QString(
						"unsupported union type (memberTypes not specified)");
	}
	return true;
}

bool simpleTypeList(QDomElement simpleType, QDomElement list) {
	qDebug() << "list";
	if (list.hasAttribute(QString("itemType"))) {
		QString item = list.attribute(QString("itemType"));
		Type *itemType = types.value(item, NULL);
		if (itemType == NULL) {
			return false;
		} else {
			QString name = longer(simpleType.attribute("name"), true);
			// NOTODO restriction on value
			types.insert(name, new ListType(name, (SimpleType*) itemType));
		}
	} else {
		qDebug() << QString("unsupported list type (itemType not specified)");
	}
	return true;
}

bool simpleTypeUnion(QDomElement simpleType, QDomElement uunion) {
	qDebug() << "union";
	if (uunion.hasAttribute(QString("memberTypes"))) {
		QString members = uunion.attribute(QString("memberTypes"));
		QStringList ms = members.simplified().split(" ");

		QList<SimpleType*> stypes;
		for (int i = 0; i < ms.size(); i++) {
			SimpleType *type = (SimpleType*) types.value(ms.at(i));
			if (type == NULL) {
				return false;
			} else {
				stypes.append(type);
			}
		}
		QString name = longer(simpleType.attribute("name"), true);
		// NOTODO restriction on value
		types.insert(name, new UnionType(name, stypes));
	} else {
		qDebug()
				<< QString(
						"unsupported restriction method (base not specified)");
	}
	return true;
}

bool simpleType(QDomElement simpleType) {
	QString name = simpleType.attribute("name");
	qDebug() << "simpleType" << name << "start";

	QList<QDomElement> es = getAllElements(simpleType);
	for (int i = 0; i < es.size(); i++) {
		QDomElement e = es.at(i);
		if (e.localName() == "restriction") {
			if (!simpleTypeRestriction(simpleType, e)) {
				return false;
			}
		} else if (e.localName() == "list") {
			if (!simpleTypeList(simpleType, e)) {
				return false;
			}
		} else if (e.localName() == "union") {
			if (!simpleTypeUnion(simpleType, e)) {
				return false;
			}
		} else if (e.localName() == "annotation") {
			continue;
		} else {
			qDebug()
					<< QString("unsupported subelement %1 of simpleType").arg(
							e.localName());
		}
	}
	return true;
}

bool simpleContentRestriction(QDomElement complexType,
		QDomElement restriction) {
	qDebug() << "restriction";
	if (restriction.hasAttribute(QString("base"))) {
		QString base = restriction.attribute(QString("base"));
		Type *baseType = types.value(base, NULL);
		if (baseType == NULL) {
			qDebug() << "waiting for base" << base;
			return false;
		} else {
			QString name = longer(complexType.attribute("name"), true);
			SimpleType *st = new SimpleType(name,
					(SimpleType*) types.find(base).value());
			// NOTODO restriction on value
			addAttributes(restriction, st);
			types.insert(name, st);
		}
	} else {
		qDebug()
				<< QString(
						"unsupported restriction method (base not specified)");
	}
	return true;
}

bool simpleContentExtension(QDomElement complexType, QDomElement extension) {
	qDebug() << "extension";
	if (extension.hasAttribute(QString("base"))) {
		QString base = extension.attribute(QString("base"));
		Type *baseType = types.value(base, NULL);
		if (baseType == NULL) {
			qDebug() << "waiting for base" << base;
			return false;
		} else {
			QString name = longer(complexType.attribute("name"), true);
			SimpleType *st = new SimpleType(name,
					(SimpleType*) types.find(base).value());
			addAttributes(extension, st);

			types.insert(name, st);
		}
	} else {
		qDebug()
				<< QString("unsupported extension method (base not specified)");
	}
	return true;
}

bool simpleContent(QDomElement complexType, QDomElement simpleContent) {
	qDebug() << "simpleContent";
	QList<QDomElement> es = getAllElements(simpleContent);
	for (int i = 0; i < es.size(); i++) {
		QDomElement e = es.at(i);
		if (e.localName() == "restriction") {
			return simpleContentRestriction(complexType, e);
		} else if (e.localName() == "extension") {
			return simpleContentExtension(complexType, e);
		} else if (e.localName() == "annotation") {
			continue;
		} else {
			qDebug() << QString("unsupported subelement %1").arg(e.localName());
		}
	}
	return true;
}

bool complexContentRestriction(QDomElement complexType,
		QDomElement restriction) {
	qDebug() << "restriction";
	if (restriction.hasAttribute(QString("base"))) {
		QString base = restriction.attribute(QString("base"));
		Type *baseType = types.value(base, NULL);
		if (baseType == NULL) {
			return false;
		} else {
			QString name = longer(complexType.attribute("name"), true);
			ComplexType *ct = new ComplexType(name,
					(ComplexType*) types.find(base).value());
			addAttributes(restriction, ct);
			// NOTODO restriction on elements on complexContent
			types.insert(name, ct);
		}
	} else {
		qDebug()
				<< QString(
						"unsupported restriction method (base not specified)");
	}
	return true;
}

bool complexContentExtension(QDomElement complexType, QDomElement extension) {
	qDebug() << "extension";
	if (extension.hasAttribute(QString("base"))) {
		QString base = extension.attribute(QString("base"));
		Type *baseType = types.value(base, NULL);
		if (baseType == NULL) {
			return false;
		} else {
			QString name = longer(complexType.attribute("name"), true);
			ComplexType *ct = new ComplexType(name,
					(ComplexType*) types.find(base).value());
			QList<QDomElement> es = getAllElements(extension);
			for (int i = 0; i < es.size(); i++) {
				QDomElement e = es.at(i);
				if (e.localName() == "all" || e.localName() == "choice"
						|| e.localName() == "sequence") {
					addElements(e, ct);
				}
			}
			addAttributes(extension, ct);
			types.insert(name, ct);
		}
	} else {
		qDebug()
				<< QString("unsupported extension method (base not specified)");
	}
	return true;
}

bool complexContent(QDomElement complexType, QDomElement simpleContent) {
	qDebug() << "complexContent";
	QList<QDomElement> es = getAllElements(simpleContent);
	for (int i = 0; i < es.size(); i++) {
		QDomElement e = es.at(i);
		if (e.localName() == "restriction") {
			return complexContentRestriction(complexType, e);
		} else if (e.localName() == "extension") {
			return complexContentExtension(complexType, e);
		} else if (e.localName() == "annotation") {
			continue;
		} else {
			qDebug() << QString("unsupported subelement %1").arg(e.localName());
		}
	}
	return true;
}

bool complexType(QDomElement complexType) {
	QString name = complexType.attribute("name");
	qDebug() << "complexType" << name << "start";
	bool contentProcessed = false;
	QList<QDomElement> es = getAllElements(complexType);
	ComplexType *ct;
	for (int i = 0; i < es.size(); i++) {
		QDomElement e = es.at(i);
		if (e.localName() == "simpleContent") {
			if (!simpleContent(complexType, e)) {
				return false;
			}
			contentProcessed = true;
		} else if (e.localName() == "complexContent") {
			if (!complexContent(complexType, e)) {
				return false;
			}
			contentProcessed = true;
		} else if (e.localName() == "all" || e.localName() == "choice"
				|| e.localName() == "sequence") {
			QString name = longer(complexType.attribute("name"), true);
			ct = new ComplexType(name, NULL);
			addElements(e, ct);
			types.insert(name, ct);
			contentProcessed = true;
		} else if (e.localName() == "annotation") {
			continue;
		} else if (e.localName() == "attribute") {
			continue; // processed later
		} else if (e.localName() == "group"
				|| e.localName() == "attributeGroup") {
			qDebug() << "should have already been replaced!";
		} else {
			qDebug() << QString("unsupported subelement %1").arg(e.localName());
		}
	}
	if (!contentProcessed) {
		qDebug() << "!contentProcessed";
		QString name = longer(complexType.attribute("name"), true);
		ct = new ComplexType(name, NULL);
		types.insert(name, ct);
	}
	addAttributes(complexType, ct);
	return true;
}

void makeEmptyAttributes(QDomElement root) {
	QList<QDomElement> as = getElements(root, longer("attribute", false));
	for (int i = 0; i < as.size(); i++) {
		QDomElement a = as.at(i);
		Attribute *attr = new Attribute(longer(a.attribute("name"), true));
		if (a.hasAttribute("default")) {
			attr->setDefault(a.attribute("default"));
		} else if (a.hasAttribute("fixed")) {
			attr->setDefault(a.attribute("fixed"));
		}
		attrs.insert(attr->getName(), attr);
	}
}

void makeAttributeBowels(QDomElement root) {
	QList<QDomElement> as = getElements(root, longer("attribute", false));
	for (int i = 0; i < as.size(); i++) {
		QDomElement a = as.at(i);
		Attribute *attr = attrs.value(longer(a.attribute("name"), true));
		attr->setSimpleType((SimpleType*) types.value(a.attribute("type")));
	}
}

void makeEmptyElements(QDomElement root) {
	QList<QDomElement> es = getElements(root, longer("element", false));
	for (int i = 0; i < es.size(); i++) {
		QDomElement e = es.at(i);
		Element *ele = new Element(longer(e.attribute("name"), true));

		if (e.hasAttribute("default")) {
			ele->setDefault(e.attribute("default"));
		} else if (e.hasAttribute("fixed")) {
			ele->setDefault(e.attribute("fixed"));
		}
		eles.insert(ele->getName(), ele);
	}
}

void makeElementBowels(QDomElement root) {
	QList<QDomElement> es = getElements(root, longer("element", false));
	for (int i = 0; i < es.size(); i++) {
		QDomElement e = es.at(i);
		Element *ele = eles.value(longer(e.attribute("name"), true));
		qDebug() << e.attribute("name") << e.attribute("type");
		qDebug() << types.value(e.attribute("type"));
		ele->setType(types.value(e.attribute("type")));
	}
}
