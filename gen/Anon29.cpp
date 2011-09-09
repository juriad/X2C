#include "Anon29.h"
#include "Anon27.h"
#include "Anon28.h"

void Anon29::addAnon27(Anon27 * ele) {
  anon27List.append(ele);
  qDebug() << "Anon27";
}
void Anon29::initAnon27(){
  qDebug() << "Anon29"<<"Anon27" <<"init";
  anon27List = QList<Anon27*>();
}
void Anon29::addAnon28(Anon28 * ele) {
  anon28List.append(ele);
  qDebug() << "Anon28";
}
void Anon29::initAnon28(){
  qDebug() << "Anon29"<<"Anon28" <<"init";
  anon28List = QList<Anon28*>();
}
Anon29 * Anon29::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  Anon29 *anon29 = new Anon29();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      anon29->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    anon29->setAttribute(a);
  }
  return anon29;
}
void Anon29::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
  if(element.localName().compare("Anon27", Qt::CaseInsensitive)==0) {
    Anon27 *cn = Anon27::fromElement(element);
    addAnon27(cn);
    return;
  }
  if(element.localName().compare("Anon28", Qt::CaseInsensitive)==0) {
    Anon28 *cn = Anon28::fromElement(element);
    addAnon28(cn);
    return;
  }
}
void Anon29::setAttribute( QDomAttr &attr) {
}
QDomDocument * Anon29::loadXmlDocument(QFile & file) {
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
Anon29  * Anon29::fromFile(QFile & file) {
  QDomDocument *doc = Anon29::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return Anon29::fromElement(root);
}
