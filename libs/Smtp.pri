# qtsmtpclient.pri
HEADERS += \
    SmtpClient.h \
    MimeMessage.h \
    MimeText.h \
    EmailAddress.h \
    MimeAttachment.h \
    MimeHtml.h # Add all relevant .h files

SOURCES += \
    SmtpClient.cpp \
    MimeMessage.cpp \
    MimeText.cpp \
    EmailAddress.cpp \
    MimeAttachment.cpp \
    MimeHtml.cpp # Add all relevant .cpp files

# REQUIRED: Add SSL support
QT += network # QTcpSocket
QT += core
QT += gui
QT += Ssl # For QSslSocket

# Optional: If the library defines specific includes for itself (less common for this type)
# INCLUDEPATH += $$PWD
