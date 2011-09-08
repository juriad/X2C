#include "SimpleInnerAttributeInnerInner.h"

void SimpleInnerAttributeInnerInner::setInnerAttribute4(QString string) {
  innerAttribute4Value = string;
}
void SimpleInnerAttributeInnerInner::initInnerAttribute4(){
  qDebug() << "SimpleInnerAttributeInnerInner"<<"innerAttribute4" <<"init";
  innerAttribute4Value = QString();
}
void SimpleInnerAttributeInnerInner::setValue(QString string) {
  valueValue = string;
}
void SimpleInnerAttributeInnerInner::initValue(){
  qDebug() << "SimpleInnerAttributeInnerInner"<<"value" <<"init";
  valueValue = QString();
}
SimpleInnerAttributeInnerInner * SimpleInnerAttributeInnerInner::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  SimpleInnerAttributeInnerInner *simpleInnerAttributeInnerInner = new SimpleInnerAttributeInnerInner();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      simpleInnerAttributeInnerInner->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    simpleInnerAttributeInnerInner->setAttribute(a);
  }
  simpleInnerAttributeInnerInner->setValue(element.text());
  return simpleInnerAttributeInnerInner;
}
void SimpleInnerAttributeInnerInner::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
}
void SimpleInnerAttributeInnerInner::setAttribute( QDomAttr &attr) {
  if(attr.localName().compare("InnerAttribute4", Qt::CaseInsensitive)==0) {
    setInnerAttribute4(attr.value());
    return;
  }
  if(attr.localName().compare("Value", Qt::CaseInsensitive)==0) {
    setValue(attr.value());
    return;
  }
}
QDomDocument * SimpleInnerAttributeInnerInner::loadXmlDocument(QFile & file) {
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
SimpleInnerAttributeInnerInner  * SimpleInnerAttributeInnerInner::fromFile(QFile & file) {
  QDomDocument *doc = SimpleInnerAttributeInnerInner::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return SimpleInnerAttributeInnerInner::fromElement(root);
}
