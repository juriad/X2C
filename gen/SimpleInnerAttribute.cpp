#include "SimpleInnerAttribute.h"

void SimpleInnerAttribute::setInnerAttribute1(QString string) {
  innerAttribute1Value = string;
}
void SimpleInnerAttribute::initInnerAttribute1(){
  qDebug() << "SimpleInnerAttribute"<<"innerAttribute1" <<"init";
  innerAttribute1Value = QString();
}
void SimpleInnerAttribute::setValue(QString string) {
  valueValue = string;
}
void SimpleInnerAttribute::initValue(){
  qDebug() << "SimpleInnerAttribute"<<"value" <<"init";
  valueValue = QString();
}
SimpleInnerAttribute * SimpleInnerAttribute::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  SimpleInnerAttribute *simpleInnerAttribute = new SimpleInnerAttribute();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      simpleInnerAttribute->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    simpleInnerAttribute->setAttribute(a);
  }
  simpleInnerAttribute->setValue(element.text());
  return simpleInnerAttribute;
}
void SimpleInnerAttribute::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
}
void SimpleInnerAttribute::setAttribute( QDomAttr &attr) {
  if(attr.localName().compare("InnerAttribute1", Qt::CaseInsensitive)==0) {
    setInnerAttribute1(attr.value());
    return;
  }
  if(attr.localName().compare("Value", Qt::CaseInsensitive)==0) {
    setValue(attr.value());
    return;
  }
}
QDomDocument * SimpleInnerAttribute::loadXmlDocument(QFile & file) {
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
SimpleInnerAttribute  * SimpleInnerAttribute::fromFile(QFile & file) {
  QDomDocument *doc = SimpleInnerAttribute::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return SimpleInnerAttribute::fromElement(root);
}
