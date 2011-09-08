#ifndef Loop_H_
#define Loop_H_
#include <QtCore/QtCore>
#include <QDomDocument>
#include "Loop.h"

class Loop {
public:
Loop() {
  initLoop();
}
static Loop* fromFile( QFile &file);
static Loop* fromElement( QDomElement &element);
static QDomDocument * loadXmlDocument(QFile & file);
inline QList<Loop*> getLoopList() {
  return loopList;
}

private:
void addSubElement( QDomElement &element);
void setAttribute( QDomAttr &attr);
QList<Loop*> loopList;
void addLoop(Loop * ele);
void initLoop();

};
#endif