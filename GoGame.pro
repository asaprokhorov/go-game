TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

win32{
    LIBS += -lws2_32
}

SOURCES += \
    socket.cpp \
    server.cpp \
    client.cpp \
    main.cpp \
    serversocket.cpp \
    clientsocket.cpp \
    gamefield.cpp

HEADERS += \
    socket.h \
    server.h \
    client.h \
    serversocket.h \
    clientsocket.h \
    gamefield.h

