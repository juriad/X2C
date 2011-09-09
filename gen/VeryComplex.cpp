#include "VeryComplex.h"
#include "Anon30.h"
#include "SimpleElement.h"
#include "SimpleElementCustom.h"

void VeryComplex::addAnon30(Anon30 * ele) {
  anon30List.append(ele);
  qDebug() << "Anon30";
}
void VeryComplex::initAnon30(){
  qDebug() << "VeryComplex"<<"Anon30" <<"init";
  anon30List = QList<Anon30*>();
}
void VeryComplex::addSimpleElement(SimpleElement * ele) {
  simpleElementList.append(ele);
  qDebug() << "SimpleElement";
}
void VeryComplex::initSimpleElement(){
  qDebug() << "VeryComplex"<<"SimpleElement" <<"init";
  simpleElementList = QList<SimpleElement*>();
}
void VeryComplex::addSimpleElementCustom(SimpleElementCustom * ele) {
  simpleElementCustomList.append(ele);
  qDebug() << "SimpleElementCustom";
}
void VeryComplex::initSimpleElementCustom(){
  qDebug() << "VeryComplex"<<"SimpleElementCustom" <<"init";
  simpleElementCustomList = QList<SimpleElementCustom*>();
}
VeryComplex * VeryComplex::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  VeryComplex *veryComplex = new VeryComplex();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      veryComplex->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    veryComplex->setAttribute(a);
  }
  return veryComplex;
}
void VeryComplex::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
  if(element.localName().compare("Anon30", Qt::CaseInsensitive)==0) {
    Anon30 *cn = Anon30::fromElement(element);
    addAnon30(cn);
    return;
  }
  if(element.localName().compare("SimpleElement", Qt::CaseInsensitive)==0) {
    SimpleElement *cn = SimpleElement::fromElement(element);
    addSimpleElement(cn);
    return;
  }
  if(element.localName().compare("SimpleElementCustom", Qt::CaseInsensitive)==0) {
    SimpleElementCustom *cn = SimpleElementCustom::fromElement(element);
    addSimpleElementCustom(cn);
    return;
  }
}
void VeryComplex::setAttribute( QDomAttr &attr) {
}
QDomDocument * VeryComplex::loadXmlDocument(QFile & file) {
  if (!file.exists()) {
    qDebug() << "doesn't exist";
    return NULL;
  }
  QString errorStr;
  int errorLine;
  int errorColumn;
  QDomDocument *doc = new QDomDocument;
  if (!doc->setContent(&file, true, &errorStr, &errorLine, &errorColumn)) {
    qDebug()<< QString("Error > %1 < in file %2 on line %3, column %4").arg(
      errorStr).arg(file.fileName()).arg(errorLine).arg(errorColumn);
    delete doc;
    doc = NULL;
  }
  return doc;
}
VeryComplex  * VeryComplex::fromFile(QFile & file) {
  QDomDocument *doc = VeryComplex::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return VeryComplex::fromElement(root);
}
