#-------------------------------------------------
#
# Project created by Attila Perger
#
#-------------------------------------------------

QT       += core network

INCLUDEPATH += $$PWD/src

SOURCES += \
    $$PWD/src/emailaddress.cpp \
    $$PWD/src/mimeattachment.cpp \
    $$PWD/src/mimefile.cpp \
    $$PWD/src/mimehtml.cpp \
    $$PWD/src/mimeinlinefile.cpp \
    $$PWD/src/mimemessage.cpp \
    $$PWD/src/mimepart.cpp \
    $$PWD/src/mimetext.cpp \
    $$PWD/src/smtpclient.cpp \
    $$PWD/src/quotedprintable.cpp \
    $$PWD/src/mimemultipart.cpp \
    $$PWD/src/mimecontentformatter.cpp \

HEADERS  += \
    $$PWD/src/emailaddress.h \
    $$PWD/src/mimeattachment.h \
    $$PWD/src/mimefile.h \
    $$PWD/src/mimehtml.h \
    $$PWD/src/mimeinlinefile.h \
    $$PWD/src/mimemessage.h \
    $$PWD/src/mimepart.h \
    $$PWD/src/mimetext.h \
    $$PWD/src/smtpclient.h \
    $$PWD/src/SmtpMime \
    $$PWD/src/quotedprintable.h \
    $$PWD/src/mimemultipart.h \
    $$PWD/src/mimecontentformatter.h \
    $$PWD/src/smtpexports.h
