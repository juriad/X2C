#include "Anon27.h"

void Anon27::setValue(QString string) {
  valueValue = string;
}
void Anon27::initValue(){
  qDebug() << "Anon27"<<"value" <<"init";
  valueValue = QString();
}
Anon27 * Anon27::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  Anon27 *anon27 = new Anon27();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      anon27->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    anon27->setAttribute(a);
  }
  anon27->setValue(element.text());
  return anon27;
}
void Anon27::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
}
void Anon27::setAttribute( QDomAttr &attr) {
  if(attr.localName().compare("Value", Qt::CaseInsensitive)==0) {
    setValue(attr.value());
    return;
  }
}
QDomDocument * Anon27::loadXmlDocument(QFile & file) {
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
Anon27  * Anon27::fromFile(QFile & file) {
  QDomDocument *doc = Anon27::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return Anon27::fromElement(root);
}
