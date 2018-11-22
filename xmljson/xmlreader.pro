TEMPLATE = app
TARGET = xmlreader
DEPENDPATH += .
INCLUDEPATH += .
QT = core

# Input
HEADERS += \
    playerinforeader.h \
    playerinfo.h \
    playerinfowriter.h \
    playerinfojson.h

DISTFILES += \
    playerinfo.xml \
    playerinfowr.xml

SOURCES += \
    playerinforeader.cpp \
    main.cpp \
    playerinfowriter.cpp \
    playerinfojson.cpp
