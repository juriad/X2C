#ifndef ComplexEmptyForward_H_
#define ComplexEmptyForward_H_
#include <QtCore/QtCore>
#include <QDomDocument>

class ComplexEmptyForward {
public:
ComplexEmptyForward() {
}
static ComplexEmptyForward* fromFile( QFile &file);
static ComplexEmptyForward* fromElement( QDomElement &element);
static QDomDocument * loadXmlDocument(QFile & file);

private:
void addSubElement( QDomElement &element);
void setAttribute( QDomAttr &attr);

};
#endif