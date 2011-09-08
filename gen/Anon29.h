#ifndef Anon29_H_
#define Anon29_H_
#include <QtCore/QtCore>
#include <QDomDocument>
#include "Anon27.h"
#include "Anon28.h"

class Anon29 {
public:
Anon29() {
  initAnon27();
  initAnon28();
}
static Anon29* fromFile( QFile &file);
static Anon29* fromElement( QDomElement &element);
static QDomDocument * loadXmlDocument(QFile & file);
inline QList<Anon27*> getAnon27List() {
  return anon27List;
}
inline QList<Anon28*> getAnon28List() {
  return anon28List;
}

private:
void addSubElement( QDomElement &element);
void setAttribute( QDomAttr &attr);
QList<Anon27*> anon27List;
void addAnon27(Anon27 * ele);
void initAnon27();
QList<Anon28*> anon28List;
void addAnon28(Anon28 * ele);
void initAnon28();

};
#endif