#ifndef SimpleInnerAttributeInnerInner_H_
#define SimpleInnerAttributeInnerInner_H_
#include <QtCore/QtCore>
#include <QDomDocument>

class SimpleInnerAttributeInnerInner {
public:
SimpleInnerAttributeInnerInner() {
  initInnerAttribute4();
  initValue();
}
static SimpleInnerAttributeInnerInner* fromFile( QFile &file);
static SimpleInnerAttributeInnerInner* fromElement( QDomElement &element);
static QDomDocument * loadXmlDocument(QFile & file);
bool hasInnerAttribute4() {
  return hasInnerAttribute4Value;
}
QString getInnerAttribute4() {
  return innerAttribute4Value;
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
QString innerAttribute4Value;
bool hasInnerAttribute4Value;
void setInnerAttribute4(QString string);
void initInnerAttribute4();
QString valueValue;
bool hasValueValue;
void setValue(QString string);
void initValue();

};
#endif