#include "SimpleElementCustomForward.h"

void SimpleElementCustomForward::setValue(QString string) {
  valueValue = string;
}
void SimpleElementCustomForward::initValue(){
  qDebug() << "SimpleElementCustomForward"<<"value" <<"init";
  valueValue = QString();
}
SimpleElementCustomForward * SimpleElementCustomForward::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  SimpleElementCustomForward *simpleElementCustomForward = new SimpleElementCustomForward();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      simpleElementCustomForward->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    simpleElementCustomForward->setAttribute(a);
  }
  simpleElementCustomForward->setValue(element.text());
  return simpleElementCustomForward;
}
void SimpleElementCustomForward::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
}
void SimpleElementCustomForward::setAttribute( QDomAttr &attr) {
  if(attr.localName().compare("Value", Qt::CaseInsensitive)==0) {
    setValue(attr.value());
    return;
  }
}
QDomDocument * SimpleElementCustomForward::loadXmlDocument(QFile & file) {
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
SimpleElementCustomForward  * SimpleElementCustomForward::fromFile(QFile & file) {
  QDomDocument *doc = SimpleElementCustomForward::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return SimpleElementCustomForward::fromElement(root);
}
