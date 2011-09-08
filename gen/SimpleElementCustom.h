#ifndef SimpleElementCustom_H_
#define SimpleElementCustom_H_
#include <QtCore/QtCore>
#include <QDomDocument>

class SimpleElementCustom {
public:
SimpleElementCustom() {
  initValue();
}
static SimpleElementCustom* fromFile( QFile &file);
static SimpleElementCustom* fromElement( QDomElement &element);
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