#ifndef SimpleElementCustomForward_H_
#define SimpleElementCustomForward_H_
#include <QtCore/QtCore>
#include <QDomDocument>

class SimpleElementCustomForward {
public:
SimpleElementCustomForward() {
  initValue();
}
static SimpleElementCustomForward* fromFile( QFile &file);
static SimpleElementCustomForward* fromElement( QDomElement &element);
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