QT          += core gui
# Qt network are required
# for checking the WIFI and MAC hardware address :)
QT          += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    Main/AnalysisPolicyHandler/ \
    Main/CommandExecutor/ \
    Main/JLUClientTrayIcon/ \
    Main/LoggerChecker/ \
    Main/NetworkAuthInfoCollector/ \
    Main/StateChecker/ \
    Main/UiLoader/ \
    Ui/LoggerWindow/ \
    Ui/MainWindow/ \
    Ui/UserCreator/ \
    Ui/HelpWindow


SOURCES += \
    Info/about/AboutInfo.cpp \
    Info/help/HelpInfo.cpp \
    Main/AnalysisPolicyHandler/AnalysisPolicyHandler.cpp \
    Main/CommandExecutor/CommandExecutor.cpp \
    Main/JLUClientTrayIcon/JLUClientTrayIcon.cpp \
    Main/LoggerChecker/LoginChecker.cpp \
    Main/NetworkAuthInfoCollector/NetworkAuthInfoCollector.cpp \
    Main/StateChecker/StateChecker.cpp \
    Main/UiLoader/UiLoader.cpp \
    Ui/HelpWindow/HelpWindow.cpp \
    Ui/LoggerWindow/LoggerWindow.cpp \
    Ui/MainWindow/CCJLUClientMainWindow.cpp \
    Ui/UserCreator/UserCreatorDialog.cpp \
    main.cpp

HEADERS += \
    ConstParams.h \
    Info/about/AboutInfo.h \
    Info/help/HelpInfo.h \
    Main/AnalysisPolicyHandler/AnalysisPolicyHandler.h \
    Main/CommandExecutor/CommandExecutor.h \
    Main/JLUClientTrayIcon/JLUClientTrayIcon.h \
    Main/LoggerChecker/LoginChecker.h \
    Main/NetworkAuthInfoCollector/NetworkAuthInfoCollector.h \
    Main/StateChecker/StateChecker.h \
    Main/UiLoader/UiLoader.h \
    Ui/HelpWindow/HelpWindow.h \
    Ui/LoggerWindow/LoggerWindow.h \
    Ui/MainWindow/CCJLUClientMainWindow.h \
    Ui/UserCreator/UserCreatorDialog.h


FORMS += \
    Ui/HelpWindow/HelpWindow.ui \
    Ui/LoggerWindow/LoggerWindow.ui \
    Ui/MainWindow/CCJLUClientMainWindow.ui \
    Ui/UserCreator/UserCreatorDialog.ui

DEFINES +=  __MAJOR_VERSION=1       \
            __MINOR_VERISON=0       \
            __NAME=\\\"CCJLUDrClient\\\"

DEFINES += CLEAR_LOG_IF_REACH_LIMITATION

contains(DEFINES, CLEAR_LOG_IF_REACH_LIMITATION){
    DEFINES += __CLEAR_LIMITATION=200
}



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    documentation_resources.qrc \
    stylesheets/light/lightstyle.qrc \
    stylesheets/mainui_related.qrc

DISTFILES +=
