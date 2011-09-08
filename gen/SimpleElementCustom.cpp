#include "SimpleElementCustom.h"

void SimpleElementCustom::setValue(QString string) {
  valueValue = string;
}
void SimpleElementCustom::initValue(){
  qDebug() << "SimpleElementCustom"<<"value" <<"init";
  valueValue = QString();
}
SimpleElementCustom * SimpleElementCustom::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  SimpleElementCustom *simpleElementCustom = new SimpleElementCustom();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      simpleElementCustom->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    simpleElementCustom->setAttribute(a);
  }
  simpleElementCustom->setValue(element.text());
  return simpleElementCustom;
}
void SimpleElementCustom::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
}
void SimpleElementCustom::setAttribute( QDomAttr &attr) {
  if(attr.localName().compare("Value", Qt::CaseInsensitive)==0) {
    setValue(attr.value());
    return;
  }
}
QDomDocument * SimpleElementCustom::loadXmlDocument(QFile & file) {
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
SimpleElementCustom  * SimpleElementCustom::fromFile(QFile & file) {
  QDomDocument *doc = SimpleElementCustom::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return SimpleElementCustom::fromElement(root);
}
