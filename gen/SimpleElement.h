#ifndef SimpleElement_H_
#define SimpleElement_H_
#include <QtCore/QtCore>
#include <QDomDocument>

class SimpleElement {
public:
SimpleElement() {
  initValue();
}
static SimpleElement* fromFile( QFile &file);
static SimpleElement* fromElement( QDomElement &element);
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