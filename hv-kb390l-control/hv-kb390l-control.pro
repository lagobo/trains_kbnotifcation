###############################################################################
#
#      HV-390L control utility
#
###############################################################################
lessThan(QT_MAJOR_VERSION, 5) \
    | equals(QT_MAJOR_VERSION, 5) : lessThan(QT_MINOR_VERSION, 2) \
        : error (QT 5.2 or newer is required)

isEmpty(PREFIX): PREFIX   = /usr
DEFINES += PREFIX=$$PREFIX
CONFIG  += c++11
QT      += core

include (libqhid/libqhid.pri)

TEMPLATE = app
TARGET   = hv-kb390l-control
VERSION  = 1.0

DEFINES += PRODUCT_NAME=\\\"$$TARGET\\\" \
    PRODUCT_VERSION=\\\"$$VERSION\\\"

SOURCES += \
    hv-kb390l-control.cpp \
    src/kb390l.cpp

HEADERS  += \
    src/kb390l.h

FORMS    +=

RESOURCES +=

# MacOS specific
ICON =
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9

# Windows specific
RC_ICONS =

# Linux specific
target.path=./bin

INSTALLS +=
