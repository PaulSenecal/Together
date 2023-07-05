QT       += core gui
QT += sql
QT += widgets
QT += network
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatpage/chatpage.cpp \
    chatpage/clientsocket.cpp \
    loginpage/loginpage.cpp \
    main.cpp \
    registerpage/registerwindow.cpp \
    settingpage/settingwindow.cpp

HEADERS += \
    chatpage/chatpage.h \
    chatpage/clientsocket.h \
    loginpage/loginpage.h \
    registerpage/registerwindow.h \
    settingpage/settingwindow.h

FORMS += \
    chatpage/chatpage.ui \
    loginpage/loginpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    rsc/images/chat/addFile.svg \
    rsc/images/chat/addFriend.svg \
    rsc/images/chat/bell.svg \
    rsc/images/chat/camera.svg \
    rsc/images/chat/chatBull.svg \
    rsc/images/chat/completChatBule.svg \
    rsc/images/chat/logoTogether.svg \
    rsc/images/chat/my.svg \
    rsc/images/chat/phone.svg \
    rsc/images/chat/send.svg \
    rsc/images/chat/settingDote.svg \
    rsc/images/chat/settingWile.svg \
    rsc/images/chat/smile.svg \
    rsc/images/chat/verticalSeparator.svg \
    rsc/images/chat/vocalMessage.svg \
    rsc/images/log/back.jpg \
    rsc/images/log/back.png \
    rsc/images/log/back.svg \
    rsc/images/log/fb.svg \
    rsc/images/log/git.svg \
    rsc/images/log/google.svg
