#-------------------------------------------------
#
# Project created by Attila Perger
#
#-------------------------------------------------

QT       += core network

TARGET = QtSMTPClient

# Build as an application
#TEMPLATE = app

# Build as a library
TEMPLATE = lib
unix:VERSION = 1.1
DEFINES += SMTP_BUILD
win32:CONFIG += dll

CONFIG(debug, debug|release) {
        DESTDIR = Debug
} else {
        DESTDIR = Release
}
OBJECTS_DIR = $$DESTDIR/obj
MOC_DIR = $$DESTDIR/moc

include(QtSMTPClient.pri)

OTHER_FILES += \
    LICENSE \
    README.md

FORMS +=
