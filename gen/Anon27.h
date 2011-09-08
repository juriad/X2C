#ifndef Anon27_H_
#define Anon27_H_
#include <QtCore/QtCore>
#include <QDomDocument>

class Anon27 {
public:
Anon27() {
  initValue();
}
static Anon27* fromFile( QFile &file);
static Anon27* fromElement( QDomElement &element);
static QDomDocument * loadXmlDocument(QFile & file);
bool hasValue() {
  return hasValueValue;
}
QString getValue() {
  return valueValue;
}

private:
void addSubElement( QDomElement &element);
void setAttribute( QDomAttr &attr);
QString valueValue;
bool hasValueValue;
void setValue(QString string);
void initValue();

};
#endif