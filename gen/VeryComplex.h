#ifndef VeryComplex_H_
#define VeryComplex_H_
#include <QtCore/QtCore>
#include <QDomDocument>
#include "Anon30.h"
#include "SimpleElement.h"
#include "SimpleElementCustom.h"

class VeryComplex {
public:
VeryComplex() {
  initAnon30();
  initSimpleElement();
  initSimpleElementCustom();
}
static VeryComplex* fromFile( QFile &file);
static VeryComplex* fromElement( QDomElement &element);
static QDomDocument * loadXmlDocument(QFile & file);
inline QList<Anon30*> getAnon30List() {
  return anon30List;
}
inline QList<SimpleElement*> getSimpleElementList() {
  return simpleElementList;
}
inline QList<SimpleElementCustom*> getSimpleElementCustomList() {
  return simpleElementCustomList;
}

private:
void addSubElement( QDomElement &element);
void setAttribute( QDomAttr &attr);
QList<Anon30*> anon30List;
void addAnon30(Anon30 * ele);
void initAnon30();
QList<SimpleElement*> simpleElementList;
void addSimpleElement(SimpleElement * ele);
void initSimpleElement();
QList<SimpleElementCustom*> simpleElementCustomList;
void addSimpleElementCustom(SimpleElementCustom * ele);
void initSimpleElementCustom();

};
#endif