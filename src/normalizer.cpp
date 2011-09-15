/*
 * normalizer.cpp
 *
 *  Created on: 22.8.2011
 *      Author: Adam Juraszek
 */

#include <QtCore/QtCore>
#include <QDomDocument>
#include "normalizer.h"
#include "utils.h"
#include "settings.h"

static void typeType(QDomElement &root, QDomElement type) {
	static int number = 0;
	qDebug() << "type type" << number;
	QString name = QString("anon:anon%1").arg(number++);
	type.setAttributeNS(QString(), "name", name);
	QDomElement parent = type.parentNode().toElement();
	if (parent.localName() == "list") {
		type.parentNode().toElement().setAttributeNS(QString(), "itemType",
				longer(name, true));
	} else if (parent.localName() == "attribute"
			|| parent.localName() == "element") {
		type.parentNode().toElement().setAttributeNS(QString(), "type",
				longer(name, true));
	} else if (parent.localName() == "union") {
		QDomElement parent = type.parentNode().toElement();
		QString attr;
		if (parent.hasAttribute("memberTypes")) {
			attr =
					type.parentNode().toElement().attribute("memberTypes").append(
							" ");
			parent.removeAttribute("memberTypes");
		} else {
			attr = QString();
		}
		type.parentNode().toElement().setAttributeNS(QString(), "memberTypes",
				attr + longer(name, true));
	} else {
		qDebug() << "unsupported parent of type";
	}
	root.appendChild(type);
}

static void refAttribute(QDomElement &root, QDomElement &attr) {
	QDomElement a = attr.cloneNode(true).toElement();
	a.removeAttribute("name");
	a.removeAttribute("type");
	QList<QDomElement> sl = getAllElements(a);
	for (int i = 0; i < sl.size(); i++) {
		a.removeChild(sl.at(i));
	}
	a.setAttributeNS(QString(), "ref", longer(attr.attribute("name"), true));
	attr.parentNode().appendChild(a);
	root.appendChild(attr);
}

static void refElement(QDomElement &root, QDomElement &ele) {
	QDomElement e = ele.cloneNode(true).toElement();
	e.removeAttribute("default");
	e.removeAttribute("fixed");
	e.removeAttribute("form");
	e.removeAttribute("block");
	e.removeAttribute("name");
	e.removeAttribute("type");
	ele.removeAttribute("maxOccurs");
	ele.removeAttribute("minOccurs");
	QList<QDomElement> sl = getAllElements(e);
	for (int i = 0; i < sl.size(); i++) {
		e.removeChild(sl.at(i));
	}
	e.setAttributeNS(QString(), "ref", longer(ele.attribute("name"), true));
	ele.parentNode().appendChild(e);
	root.appendChild(ele);
}

/*
 * iterates through tree and each local definition moves to root
 */
static void iterate(QDomElement &root, QDomElement &parent) {
	QList<QDomElement> es = getAllElements(parent);
	for (int i = 0; i < es.size(); i++) {
		QDomElement e = es.at(i);
		iterate(root, e);
		qDebug() << e.tagName() << e.attribute("name", "--");
		if (e.localName() == "element" && e.hasAttribute("name")
				&& parent != root) {
			refElement(root, e);
		} else if (e.localName() == "attribute" && e.hasAttribute("name")
				&& parent != root) {
			refAttribute(root, e);
		} else if ((e.localName() == "simpleType"
				|| e.localName() == "complexType") && !e.hasAttribute("name")) {
			typeType(root, e);
		}
	}
}

/*
static bool unrefAGs(QDomElement &parent,
		QHash<QString, QDomElement*> &flatAttrs) {
	QList<QDomElement> as = getElements(parent,
			longer("attributeGroup", false));
	bool gg = true;
	for (int i = 0; i < as.size(); i++) {
		QDomElement ag = as.at(i);
		if (!ag.hasAttribute("ref")) {
			continue;
		}

		if (flatAttrs.contains(ag.attribute("ref"))) {
			QDomElement *aga = flatAttrs.value(ag.attribute("ref"));
			QList<QDomElement> agas = getAllElements(*aga);
			for (int i = 0; i < agas.size(); i++) {
				QDomElement a = agas.at(i);
				if (a.localName() == "attribute"
						|| a.localName() == "attributeGroup") {
					parent.insertBefore(a, ag);
				}
			}
			parent.removeChild(ag);
		} else {
			gg = false;
		}
	}
	return gg;
}

static bool unrefGroups(QDomElement &parent,
		QHash<QString, QDomElement*> &flatGroups) {
	QList<QDomElement> gs = getElements(parent, longer("group", false));
	bool gg = true;
	for (int i = 0; i < gs.size(); i++) {
		QDomElement g = gs.at(i);
		if (!g.hasAttribute("ref")) {
			continue;
		}

		if (flatGroups.contains(g.attribute("ref"))) {
			qDebug() << "unreffing";
			QDomElement *ggroup = flatGroups.value(g.attribute("ref"));
			QList<QDomElement> ggroups = getAllElements(*ggroup);
			for (int i = 0; i < ggroups.size(); i++) {
				qDebug() << "inner";
				QDomElement ge = ggroups.at(i);
				if (ge.localName() == "all" || ge.localName() == "choice"
						|| ge.localName() == "sequence") {
					qDebug() << "pre replaced";
					parent.replaceChild(ge, g);
					qDebug() <<"replaced";
				}
			}
		} else {
			gg = false;
		}
	}
	return gg;
}

static bool iterateGroups(QDomElement &parent,
		QHash<QString, QDomElement*> flatGroups
		, QHash<QString, QDomElement*> &flatAttrs) {
	bool gg = true;
	if (!unrefGroups(parent, flatGroups)) {
		gg = false;
	}
	qDebug() << "after unrefGroups";

	unrefAGs(parent, flatAttrs);
	qDebug() << "after unrefAGs";

	QList<QDomElement> es = getAllElements(parent);
	for (int i = 0; i < es.size(); i++) {
		QDomElement e = es.at(i);
		qDebug() << "processing child" << e.localName() << e.attribute("name");
		if (!iterateGroups(e, flatGroups, flatAttrs)) {
			gg = false;
		}
	}
	qDebug() << "before return";
	return gg;
}

static void groups(QDomElement &root) {
	qDebug("attrGroups");
	QQueue<QDomElement> as = QQueue<QDomElement>();
	QList<QDomElement> aas = getElements(root, "attributeGroup");
	for (int i = 0; i < aas.size(); i++) {
		as.enqueue(aas.at(i));
	}

	QHash<QString, QDomElement*> flatAGs;
	while (as.size() > 0) {
		QDomElement g = as.dequeue();
		if (unrefAGs(g, flatAGs)) {
			flatAGs.insert(longer(g.attribute("name"), true), &g);
		} else {
			as.enqueue(g);
		}
	}

	qDebug("groups");
	QQueue<QDomElement> es = QQueue<QDomElement>();
	QList<QDomElement> ees = getElements(root, "group");
	for (int i = 0; i < ees.size(); i++) {
		es.enqueue(ees.at(i));
		qDebug() << "init enqueue" << ees.at(i).attribute("name");
	}
	QHash<QString, QDomElement*> flatGroups;

	while (es.size() > 0) {
		QDomElement g = es.dequeue();
		qDebug() << "dequeue" << g.localName() << g.attribute("name");
		if (iterateGroups(g, flatGroups, flatAGs)) {
			flatGroups.insert(longer(g.attribute("name"), true), &g);
			qDebug() << "completed";
		} else {
			es.enqueue(g);
			qDebug() << "requeued";
		}
	}

	qDebug("iterateGroups free");
	QList<QDomElement> cs = getElements(root, "complexType");
	for (int i = 0; i < ees.size(); i++) {
		QDomElement c = cs.at(i);
		iterateGroups(c, flatGroups, flatAGs);
	}
}*/

/*
 * restrictions are not supported
 * everything restricted can be assigned to unrestricted variable
 */
static void removeRestrictionInners(QDomElement e) {
	QList<QDomElement> es = getAllElements(e);

	for (int i = 0; i < es.size(); i++) {
		if (e.localName() == "restriction") {
			e.removeChild(es.at(i));
		} else {
			removeRestrictionInners(es.at(i));
		}
	}
}

void globalizeAndName(QDomDocument & doc) {
	QDomElement e = doc.documentElement();
	removeRestrictionInners(e);
	iterate(e, e);
	//groups(e);
	qDebug("globalized");
}

