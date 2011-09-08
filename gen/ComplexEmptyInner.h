#ifndef ComplexEmptyInner_H_
#define ComplexEmptyInner_H_
#include <QtCore/QtCore>
#include <QDomDocument>

class ComplexEmptyInner {
public:
ComplexEmptyInner() {
}
static ComplexEmptyInner* fromFile( QFile &file);
static ComplexEmptyInner* fromElement( QDomElement &element);
static QDomDocument * loadXmlDocument(QFile & file);

private:
void addSubElement( QDomElement &element);
void setAttribute( QDomAttr &attr);

};
#endif