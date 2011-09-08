#ifndef Anon30_H_
#define Anon30_H_
#include <QtCore/QtCore>
#include <QDomDocument>
#include "Anon29.h"

class Anon30 {
public:
Anon30() {
  initAnon29();
}
static Anon30* fromFile( QFile &file);
static Anon30* fromElement( QDomElement &element);
static QDomDocument * loadXmlDocument(QFile & file);
inline QList<Anon29*> getAnon29List() {
  return anon29List;
}

private:
void addSubElement( QDomElement &element);
void setAttribute( QDomAttr &attr);
QList<Anon29*> anon29List;
void addAnon29(Anon29 * ele);
void initAnon29();

};
#endif