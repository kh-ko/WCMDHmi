QT += quick widgets charts virtualkeyboard sql

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        source/helper/databasehelper.cpp \
        source/helper/languagehelper.cpp \
        source/helper/localsetting.cpp \
        source/logger/nsdebug.cpp \
        source/main.cpp \
        source/qmlmodel/wcmd/introscenemodel.cpp \
        source/qmlmodel/wcmd/main_scene/mainviewmodel.cpp \
        source/qmlmodel/wcmd/main_scene/panelbackupmodel.cpp \
        source/qmlmodel/wcmd/main_scene/paneldebuggingmodel.cpp \
        source/qmlmodel/wcmd/main_scene/panelwcsettinginhomemodel.cpp \
        source/qmlmodel/wcmd/mainscenemodel.cpp \
        source/qmlmodel/wcmd/menu_scene/checkup/panelmdcheckupmodel.cpp \
        source/qmlmodel/wcmd/menu_scene/devicesetting/paneldevicesettingmodel.cpp \
        source/qmlmodel/wcmd/menu_scene/etcsetting/paneletcsettingmodel.cpp \
        source/qmlmodel/wcmd/menu_scene/graph/metaldetectorgraphmodel.cpp \
        source/qmlmodel/wcmd/menu_scene/graph/panelmdgraphmodel.cpp \
        source/qmlmodel/wcmd/menu_scene/graph/panelwcgraphmodel.cpp \
        source/qmlmodel/wcmd/menu_scene/information/panelinformationmodel.cpp \
        source/qmlmodel/wcmd/menu_scene/loggingdata/loggingdatamodel.cpp \
        source/qmlmodel/wcmd/menu_scene/productsetting/panelproductsettingmodel.cpp \
        source/qmlmodel/wcmd/menu_scene/productsetting/productsettingitemmodel.cpp \
        source/service/dsp/dspinterface.cpp \
        source/service/dsp/dsppacketbuilder.cpp \
        source/service/dsp/dspservice.cpp \
        source/service/dsp/myalloc.cpp \
        source/service/dsp/sendpacketqueue.cpp \
        source/service/dspmanager.cpp \
        source/service/wcmdservice.cpp \
        source/util/etcutil.cpp \
        source/util/mouseeventspy.cpp

RESOURCES += qml/qml.qrc

TRANSLATIONS += Lang_ko_KR.ts
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
target.path = /home/pi/apps/$${TARGET}
INSTALLS += target

HEADERS += \
    source/globaldef/EnumDefine.h \
    source/globaldef/GlobalDefine.h \
    source/helper/databasehelper.h \
    source/helper/languagehelper.h \
    source/helper/localsetting.h \
    source/logger/nsdebug.h \
    source/model/Information.h \
    source/model/databasebackupstate.h \
    source/model/deviceconnectionInfo.h \
    source/model/deviceinfo.h \
    source/model/devicesetting.h \
    source/model/devicestatus.h \
    source/model/event.h \
    source/model/eventinfo.h \
    source/model/metaldetectorgraphdata.h \
    source/model/productsetting.h \
    source/model/productstatus.h \
    source/model/wccaribrationinfo.h \
    source/model/weightcheckergraphdata.h \
    source/qmlmodel/wcmd/introscenemodel.h \
    source/qmlmodel/wcmd/main_scene/FactoryResetViewModel.h \
    source/qmlmodel/wcmd/main_scene/mainviewmodel.h \
    source/qmlmodel/wcmd/main_scene/panelbackupmodel.h \
    source/qmlmodel/wcmd/main_scene/paneldebuggingmodel.h \
    source/qmlmodel/wcmd/main_scene/panelwcsettinginhomemodel.h \
    source/qmlmodel/wcmd/mainmodel.h \
    source/qmlmodel/wcmd/mainscenemodel.h \
    source/qmlmodel/wcmd/menu_scene/checkup/panelmdcheckupmodel.h \
    source/qmlmodel/wcmd/menu_scene/checkup/panelwcdynamiccalibraionmodel.h \
    source/qmlmodel/wcmd/menu_scene/checkup/panelwcstaticcaribrationmodel.h \
    source/qmlmodel/wcmd/menu_scene/clocksetting/panelclocksettingmodel.h \
    source/qmlmodel/wcmd/menu_scene/devicesetting/paneldevicesettingmodel.h \
    source/qmlmodel/wcmd/menu_scene/etcsetting/paneletcsettingmodel.h \
    source/qmlmodel/wcmd/menu_scene/graph/metaldetectorgraphmodel.h \
    source/qmlmodel/wcmd/menu_scene/graph/panelmdgraphmodel.h \
    source/qmlmodel/wcmd/menu_scene/graph/panelwcgraphmodel.h \
    source/qmlmodel/wcmd/menu_scene/information/panelinformationmodel.h \
    source/qmlmodel/wcmd/menu_scene/loggingdata/loggingdatamodel.h \
    source/qmlmodel/wcmd/menu_scene/productsetting/panelproductsettingmodel.h \
    source/qmlmodel/wcmd/menu_scene/productsetting/productsettingitemmodel.h \
    source/service/dsp/dspinterface.h \
    source/service/dsp/dsppacketbuilder.h \
    source/service/dsp/dspservice.h \
    source/service/dsp/myalloc.h \
    source/service/dsp/sendpacketqueue.h \
    source/service/dspmanager.h \
    source/service/wcmdservice.h \
    source/util/etcutil.h \
    source/util/mouseeventspy.h

DISTFILES +=
