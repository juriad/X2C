#include "SimpleInnerAttributeInner.h"

void SimpleInnerAttributeInner::setInnerAttribute3(QString string) {
  innerAttribute3Value = string;
}
void SimpleInnerAttributeInner::initInnerAttribute3(){
  qDebug() << "SimpleInnerAttributeInner"<<"innerAttribute3" <<"init";
  innerAttribute3Value = QString();
}
void SimpleInnerAttributeInner::setValue(QString string) {
  valueValue = string;
}
void SimpleInnerAttributeInner::initValue(){
  qDebug() << "SimpleInnerAttributeInner"<<"value" <<"init";
  valueValue = QString();
}
SimpleInnerAttributeInner * SimpleInnerAttributeInner::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  SimpleInnerAttributeInner *simpleInnerAttributeInner = new SimpleInnerAttributeInner();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      simpleInnerAttributeInner->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    simpleInnerAttributeInner->setAttribute(a);
  }
  simpleInnerAttributeInner->setValue(element.text());
  return simpleInnerAttributeInner;
}
void SimpleInnerAttributeInner::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
}
void SimpleInnerAttributeInner::setAttribute( QDomAttr &attr) {
  if(attr.localName().compare("InnerAttribute3", Qt::CaseInsensitive)==0) {
    setInnerAttribute3(attr.value());
    return;
  }
  if(attr.localName().compare("Value", Qt::CaseInsensitive)==0) {
    setValue(attr.value());
    return;
  }
}
QDomDocument * SimpleInnerAttributeInner::loadXmlDocument(QFile & file) {
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
SimpleInnerAttributeInner  * SimpleInnerAttributeInner::fromFile(QFile & file) {
  QDomDocument *doc = SimpleInnerAttributeInner::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return SimpleInnerAttributeInner::fromElement(root);
}
