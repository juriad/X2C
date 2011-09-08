#include "SimpleInnerAttributeCustom.h"

void SimpleInnerAttributeCustom::setInnerAttribute2(QString string) {
  innerAttribute2Value = string;
}
void SimpleInnerAttributeCustom::initInnerAttribute2(){
  qDebug() << "SimpleInnerAttributeCustom"<<"innerAttribute2" <<"init";
  innerAttribute2Value = QString();
}
void SimpleInnerAttributeCustom::setValue(QString string) {
  valueValue = string;
}
void SimpleInnerAttributeCustom::initValue(){
  qDebug() << "SimpleInnerAttributeCustom"<<"value" <<"init";
  valueValue = QString();
}
SimpleInnerAttributeCustom * SimpleInnerAttributeCustom::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  SimpleInnerAttributeCustom *simpleInnerAttributeCustom = new SimpleInnerAttributeCustom();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      simpleInnerAttributeCustom->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    simpleInnerAttributeCustom->setAttribute(a);
  }
  simpleInnerAttributeCustom->setValue(element.text());
  return simpleInnerAttributeCustom;
}
void SimpleInnerAttributeCustom::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
}
void SimpleInnerAttributeCustom::setAttribute( QDomAttr &attr) {
  if(attr.localName().compare("InnerAttribute2", Qt::CaseInsensitive)==0) {
    setInnerAttribute2(attr.value());
    return;
  }
  if(attr.localName().compare("Value", Qt::CaseInsensitive)==0) {
    setValue(attr.value());
    return;
  }
}
QDomDocument * SimpleInnerAttributeCustom::loadXmlDocument(QFile & file) {
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
SimpleInnerAttributeCustom  * SimpleInnerAttributeCustom::fromFile(QFile & file) {
  QDomDocument *doc = SimpleInnerAttributeCustom::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return SimpleInnerAttributeCustom::fromElement(root);
}
