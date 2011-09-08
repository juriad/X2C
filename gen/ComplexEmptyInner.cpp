#include "ComplexEmptyInner.h"

ComplexEmptyInner * ComplexEmptyInner::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  ComplexEmptyInner *complexEmptyInner = new ComplexEmptyInner();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      complexEmptyInner->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    complexEmptyInner->setAttribute(a);
  }
  return complexEmptyInner;
}
void ComplexEmptyInner::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
}
void ComplexEmptyInner::setAttribute( QDomAttr &attr) {
}
QDomDocument * ComplexEmptyInner::loadXmlDocument(QFile & file) {
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
ComplexEmptyInner  * ComplexEmptyInner::fromFile(QFile & file) {
  QDomDocument *doc = ComplexEmptyInner::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return ComplexEmptyInner::fromElement(root);
}
