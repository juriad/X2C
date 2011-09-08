#ifndef ComplexEmpty_H_
#define ComplexEmpty_H_
#include <QtCore/QtCore>
#include <QDomDocument>

class ComplexEmpty {
public:
ComplexEmpty() {
}
static ComplexEmpty* fromFile( QFile &file);
static ComplexEmpty* fromElement( QDomElement &element);
static QDomDocument * loadXmlDocument(QFile & file);

private:
void addSubElement( QDomElement &element);
void setAttribute( QDomAttr &attr);

};
#endif