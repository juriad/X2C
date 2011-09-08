#include "SimpleElementCustomInner.h"

void SimpleElementCustomInner::setValue(QString string) {
  valueValue = string;
}
void SimpleElementCustomInner::initValue(){
  qDebug() << "SimpleElementCustomInner"<<"value" <<"init";
  valueValue = QString();
}
SimpleElementCustomInner * SimpleElementCustomInner::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  SimpleElementCustomInner *simpleElementCustomInner = new SimpleElementCustomInner();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      simpleElementCustomInner->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    simpleElementCustomInner->setAttribute(a);
  }
  simpleElementCustomInner->setValue(element.text());
  return simpleElementCustomInner;
}
void SimpleElementCustomInner::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
}
void SimpleElementCustomInner::setAttribute( QDomAttr &attr) {
  if(attr.localName().compare("Value", Qt::CaseInsensitive)==0) {
    setValue(attr.value());
    return;
  }
}
QDomDocument * SimpleElementCustomInner::loadXmlDocument(QFile & file) {
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
SimpleElementCustomInner  * SimpleElementCustomInner::fromFile(QFile & file) {
  QDomDocument *doc = SimpleElementCustomInner::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return SimpleElementCustomInner::fromElement(root);
}
