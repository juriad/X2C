#ifndef Anon28_H_
#define Anon28_H_
#include <QtCore/QtCore>
#include <QDomDocument>

class Anon28 {
public:
Anon28() {
  initValue();
}
static Anon28* fromFile( QFile &file);
static Anon28* fromElement( QDomElement &element);
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