#ifndef SimpleElementCustomInner_H_
#define SimpleElementCustomInner_H_
#include <QtCore/QtCore>
#include <QDomDocument>

class SimpleElementCustomInner {
public:
SimpleElementCustomInner() {
  initValue();
}
static SimpleElementCustomInner* fromFile( QFile &file);
static SimpleElementCustomInner* fromElement( QDomElement &element);
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