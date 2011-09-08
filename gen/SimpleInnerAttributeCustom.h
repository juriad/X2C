#ifndef SimpleInnerAttributeCustom_H_
#define SimpleInnerAttributeCustom_H_
#include <QtCore/QtCore>
#include <QDomDocument>

class SimpleInnerAttributeCustom {
public:
SimpleInnerAttributeCustom() {
  initInnerAttribute2();
  initValue();
}
static SimpleInnerAttributeCustom* fromFile( QFile &file);
static SimpleInnerAttributeCustom* fromElement( QDomElement &element);
static QDomDocument * loadXmlDocument(QFile & file);
bool hasInnerAttribute2() {
  return hasInnerAttribute2Value;
}
QString getInnerAttribute2() {
  return innerAttribute2Value;
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
QString innerAttribute2Value;
bool hasInnerAttribute2Value;
void setInnerAttribute2(QString string);
void initInnerAttribute2();
QString valueValue;
bool hasValueValue;
void setValue(QString string);
void initValue();

};
#endif