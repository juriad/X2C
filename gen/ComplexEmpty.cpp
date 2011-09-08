#include "ComplexEmpty.h"

ComplexEmpty * ComplexEmpty::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  ComplexEmpty *complexEmpty = new ComplexEmpty();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      complexEmpty->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    complexEmpty->setAttribute(a);
  }
  return complexEmpty;
}
void ComplexEmpty::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
}
void ComplexEmpty::setAttribute( QDomAttr &attr) {
}
QDomDocument * ComplexEmpty::loadXmlDocument(QFile & file) {
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
ComplexEmpty  * ComplexEmpty::fromFile(QFile & file) {
  QDomDocument *doc = ComplexEmpty::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return ComplexEmpty::fromElement(root);
}
