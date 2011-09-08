#include "SimpleElement.h"

void SimpleElement::setValue(QString string) {
  valueValue = string;
}
void SimpleElement::initValue(){
  qDebug() << "SimpleElement"<<"value" <<"init";
  valueValue = QString();
}
SimpleElement * SimpleElement::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  SimpleElement *simpleElement = new SimpleElement();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      simpleElement->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    simpleElement->setAttribute(a);
  }
  simpleElement->setValue(element.text());
  return simpleElement;
}
void SimpleElement::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
}
void SimpleElement::setAttribute( QDomAttr &attr) {
  if(attr.localName().compare("Value", Qt::CaseInsensitive)==0) {
    setValue(attr.value());
    return;
  }
}
QDomDocument * SimpleElement::loadXmlDocument(QFile & file) {
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
SimpleElement  * SimpleElement::fromFile(QFile & file) {
  QDomDocument *doc = SimpleElement::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return SimpleElement::fromElement(root);
}
