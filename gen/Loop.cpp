#include "Loop.h"
#include "Loop.h"

void Loop::addLoop(Loop * ele) {
  loopList.append(ele);
  qDebug() << "Loop";
}
void Loop::initLoop(){
  qDebug() << "Loop"<<"tns:loop" <<"init";
  loopList = QList<Loop*>();
}
Loop * Loop::fromElement(QDomElement &element) {
  qDebug() << element.localName() <<"fromElement";
  Loop *loop = new Loop();
  QDomNodeList list = element.childNodes();
  for (int i = 0; i < list.size(); i++) {
    if (list.at(i).isElement()) {
      QDomElement e = list.at(i).toElement();
      loop->addSubElement(e);
    }
  }
  QDomNamedNodeMap attrs = element.attributes();
  for(int i = 0; i<attrs.size(); i++) {
    QDomAttr a = attrs.item(i).toAttr();
    loop->setAttribute(a);
  }
  return loop;
}
void Loop::addSubElement( QDomElement &element) {
  qDebug() << element.localName() <<"subElement";
  if(element.localName().compare("Loop", Qt::CaseInsensitive)==0) {
    Loop *cn = Loop::fromElement(element);
    addLoop(cn);
    return;
  }
}
void Loop::setAttribute( QDomAttr &attr) {
}
QDomDocument * Loop::loadXmlDocument(QFile & file) {
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
Loop  * Loop::fromFile(QFile & file) {
  QDomDocument *doc = Loop::loadXmlDocument(file);
  QDomElement root = doc->documentElement();
  return Loop::fromElement(root);
}
