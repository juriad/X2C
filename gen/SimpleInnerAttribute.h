#ifndef SimpleInnerAttribute_H_
#define SimpleInnerAttribute_H_
#include <QtCore/QtCore>
#include <QDomDocument>

class SimpleInnerAttribute {
public:
SimpleInnerAttribute() {
  initInnerAttribute1();
  initValue();
}
static SimpleInnerAttribute* fromFile( QFile &file);
static SimpleInnerAttribute* fromElement( QDomElement &element);
static QDomDocument * loadXmlDocument(QFile & file);
bool hasInnerAttribute1() {
  return hasInnerAttribute1Value;
}
QString getInnerAttribute1() {
  return innerAttribute1Value;
}
bool hasValue() {
  return hasValueValue;
}
QString getValue() {
  return valueValue;
}

private:
void addSubElement( QDomElement &element);
void setAttribute( QDomAttr &attr);
QString innerAttribute1Value;
bool hasInnerAttribute1Value;
void setInnerAttribute1(QString string);
void initInnerAttribute1();
QString valueValue;
bool hasValueValue;
void setValue(QString string);
void initValue();

};
#endif