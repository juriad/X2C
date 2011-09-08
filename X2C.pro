TEMPLATE = app
TARGET = X2C
QT += core
QT += xml
QT -= qui
HEADERS += src/generator.h \
    src/element.h \
    src/elementUse.h \
    src/attributeUse.h \
    src/unionType.h \
    src/listType.h \
    src/objects.h \
    src/utils.h \
    src/normalizer.h \
    src/complexType.h \
    src/simpleType.h \
    src/attribute.h \
    src/type.h \
    src/settings.h
SOURCES += \
    src/generator.cpp \
    src/elementUse.cpp \
    src/element.cpp \
    src/attributeUse.cpp \
    src/unionType.cpp \
    src/listType.cpp \
    src/objects.cpp \
    src/normalizer.cpp \
    src/utils.cpp \
    src/complexType.cpp \
    src/simpleType.cpp \
    src/type.cpp \
    src/attribute.cpp \
    src/settings.cpp \
    src/main.cpp
FORMS += 
RESOURCES += 
