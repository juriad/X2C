#include "Anon30.h"
#include "Anon29.h"

void Anon30::addAnon29(Anon29 * ele) {
  anon29List.append(ele);
  qDebug() << "Anon29";
}
void Anon30::initAnon29(){
  qDebug() << "Anon30"<<"tns:anon29" <<"init";
  anon29List = QList<Anon29*>();
}
Anon30 * Anon30::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  Anon30 *anon30 = new Anon30();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      anon30->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    anon30->setAttribute(a);
  }
  return anon30;
}
void Anon30::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
  if(element.localName().compare("Anon29", Qt::CaseInsensitive)==0) {
    Anon29 *cn = Anon29::fromElement(element);
    addAnon29(cn);
    return;
  }
}
void Anon30::setAttribute( QDomAttr &attr) {
}
QDomDocument * Anon30::loadXmlDocument(QFile & file) {
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
Anon30  * Anon30::fromFile(QFile & file) {
  QDomDocument *doc = Anon30::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return Anon30::fromElement(root);
}
