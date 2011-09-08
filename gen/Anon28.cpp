#include "Anon28.h"

void Anon28::setValue(QString string) {
  valueValue = string;
}
void Anon28::initValue(){
  qDebug() << "Anon28"<<"value" <<"init";
  valueValue = QString();
}
Anon28 * Anon28::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  Anon28 *anon28 = new Anon28();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      anon28->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    anon28->setAttribute(a);
  }
  anon28->setValue(element.text());
  return anon28;
}
void Anon28::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
}
void Anon28::setAttribute( QDomAttr &attr) {
  if(attr.localName().compare("Value", Qt::CaseInsensitive)==0) {
    setValue(attr.value());
    return;
  }
}
QDomDocument * Anon28::loadXmlDocument(QFile & file) {
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
Anon28  * Anon28::fromFile(QFile & file) {
  QDomDocument *doc = Anon28::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return Anon28::fromElement(root);
}
