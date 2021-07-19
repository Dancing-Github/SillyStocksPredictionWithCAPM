QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CandleSeries.cpp \
    CandlestickSet.cpp \
    Capm.cpp \
    SQLiteDB.cpp \
    dialogk.cpp \
    form.cpp \
    main.cpp \
    mymainwindow.cpp \
    spider.cpp

HEADERS += \
    CandleSeries.h \
    CandlestickSet.h \
    Capm.h \
    SQLiteDB.h \
    dialogk.h \
    form.h \
    mymainwindow.h \
    spider.h \
    sqlite3.h

FORMS += \
    dialogk.ui \
    form.ui \
    mymainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc


unix|win32: LIBS += -L$$PWD/./ -lsqlite3

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
