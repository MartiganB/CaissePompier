QT       += core gui
QT       += sql
QT       += multimedia



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    $$PWD/NfcLibrary/NdefLibrary/inc \
    $$PWD/NfcLibrary/NdefLibrary/src \
    $$PWD/NfcLibrary/NxpNci/inc \
    $$PWD/NfcLibrary/NxpNci/src \
    $$PWD/NfcLibrary/inc \
    $$PWD/NfcLibrary/src \
    $$PWD/NfcTask/inc \
    $$PWD/NfcTask/src \
    $$PWD/TML/inc \
    $$PWD/TML/src

LIBS += -lsetupapi

SOURCES += \
    NfcLibrary/NdefLibrary/src/P2P_NDEF.c \
    NfcLibrary/NdefLibrary/src/RW_NDEF.c \
    NfcLibrary/NdefLibrary/src/RW_NDEF_MIFARE.c \
    NfcLibrary/NdefLibrary/src/RW_NDEF_T1T.c \
    NfcLibrary/NdefLibrary/src/RW_NDEF_T2T.c \
    NfcLibrary/NdefLibrary/src/RW_NDEF_T3T.c \
    NfcLibrary/NdefLibrary/src/RW_NDEF_T4T.c \
    NfcLibrary/NdefLibrary/src/RW_NDEF_T5T.c \
    NfcLibrary/NdefLibrary/src/T4T_NDEF_emu.c \
    NfcLibrary/NxpNci/src/NxpNci.c \
    NfcTask/src/ndef_helper.c \
    NfcTask/src/nfc_task.c \
    TML/src/framework_Allocator.c \
    TML/src/framework_Container.c \
    TML/src/framework_Map.c \
    TML/src/framework_Parcel.c \
    TML/src/framework_Timer.c \
    TML/src/framework_mutex.c \
    TML/src/framework_thread.c \
    TML/src/hid.c \
    TML/src/lpcusbsio.c \
    TML/src/tml.c \
    TML/src/tml_hid.c \
    addstock.cpp \
    addusr.cpp \
    connexion.cpp \
    delstock.cpp \
    delusr.cpp \
    gestionmenu.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    menustock.cpp \
    modstock.cpp \
    modusr.cpp \
    nfcmanager.cpp

HEADERS += \
    NfcLibrary/NdefLibrary/inc/P2P_NDEF.h \
    NfcLibrary/NdefLibrary/inc/RW_NDEF.h \
    NfcLibrary/NdefLibrary/inc/RW_NDEF_MIFARE.h \
    NfcLibrary/NdefLibrary/inc/RW_NDEF_T1T.h \
    NfcLibrary/NdefLibrary/inc/RW_NDEF_T2T.h \
    NfcLibrary/NdefLibrary/inc/RW_NDEF_T3T.h \
    NfcLibrary/NdefLibrary/inc/RW_NDEF_T4T.h \
    NfcLibrary/NdefLibrary/inc/RW_NDEF_T5T.h \
    NfcLibrary/NdefLibrary/inc/T4T_NDEF_emu.h \
    NfcLibrary/NxpNci/inc/NxpNci.h \
    NfcLibrary/inc/Nfc.h \
    NfcLibrary/inc/Nfc_settings.h \
    NfcTask/inc/ndef_helper.h \
    NfcTask/inc/nfc_task.h \
    TML/inc/framework_Allocator.h \
    TML/inc/framework_Container.h \
    TML/inc/framework_Interface.h \
    TML/inc/framework_Map.h \
    TML/inc/framework_Parcel.h \
    TML/inc/framework_Timer.h \
    TML/inc/framework_windows.h \
    TML/inc/hidapi.h \
    TML/inc/lpcusbsio.h \
    TML/inc/lpcusbsio_i2c.h \
    TML/inc/tml.h \
    TML/inc/tml_hid.h \
    TML/inc/tool.h \
    addstock.h \
    addusr.h \
    connexion.h \
    delstock.h \
    delusr.h \
    gestionmenu.h \
    mainwindow.h \
    menu.h \
    menustock.h \
    modstock.h \
    modusr.h \
    nfcmanager.h

FORMS += \
    addstock.ui \
    addusr.ui \
    connexion.ui \
    delstock.ui \
    delusr.ui \
    gestionmenu.ui \
    mainwindow.ui \
    menu.ui \
    menustock.ui \
    modstock.ui \
    modusr.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
