#ifndef SimpleInnerAttributeInner_H_
#define SimpleInnerAttributeInner_H_
#include <QtCore/QtCore>
#include <QDomDocument>

class SimpleInnerAttributeInner {
public:
SimpleInnerAttributeInner() {
  initInnerAttribute3();
  initValue();
}
static SimpleInnerAttributeInner* fromFile( QFile &file);
static SimpleInnerAttributeInner* fromElement( QDomElement &element);
static QDomDocument * loadXmlDocument(QFile & file);
bool hasInnerAttribute3() {
  return hasInnerAttribute3Value;
}
QString getInnerAttribute3() {
  return innerAttribute3Value;
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
QString innerAttribute3Value;
bool hasInnerAttribute3Value;
void setInnerAttribute3(QString string);
void initInnerAttribute3();
QString valueValue;
bool hasValueValue;
void setValue(QString string);
void initValue();

};
#endif