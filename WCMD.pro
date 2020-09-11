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
        source/helper/languagehelper.cpp \
        source/logger/nsdebug.cpp \
        source/main.cpp \
        source/service/coreservice.cpp \
        source/service/dspconnectioninfoservice.cpp \
        source/service/eventservice.cpp \
        source/service/localsettingservice.cpp \
        source/service/productsettingservice.cpp \
        source/thread/dsp/dspcommunitythread.cpp \
        source/thread/dsp/dspinterface.cpp \
        source/thread/dsp/dsppacketbuilder.cpp \
        source/thread/dsp/sendpacketqueue.cpp \
        source/thread/historybackupthread.cpp \
        source/util/etcutil.cpp \
        source/util/eventchecker.cpp \
        source/util/fileloaderthread.cpp \
        source/util/filewriter.cpp \
        source/util/mouseeventspy.cpp \
        source/util/myalloc.cpp

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
    source/helper/languagehelper.h \
    source/logger/nsdebug.h \
    source/model/dspconnectionmodel.h \
    source/model/dspsettingmodel.h \
    source/model/dspstatusmodel.h \
    source/model/eventmodel.h \
    source/model/guisettingmodel.h \
    source/model/hmisettingmodel.h \
    source/model/informationmodel.h \
    source/model/lasterrormodel.h \
    source/model/procsettingmodel.h \
    source/model/productsettingmodel.h \
    source/model/productstatusmodel.h \
    source/model/securitysettingmodel.h \
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
    source/service/coreservice.h \
    source/service/dspconnectioninfoservice.h \
    source/service/eventservice.h \
    source/service/localsettingservice.h \
    source/service/productsettingservice.h \
    source/thread/dsp/dspcommunitythread.h \
    source/thread/dsp/dspinterface.h \
    source/thread/dsp/dsppacketbuilder.h \
    source/thread/dsp/dto/dspaddressdto.h \
    source/thread/dsp/dto/dspconnectiondto.h \
    source/thread/dsp/dto/dspinfodto.h \
    source/thread/dsp/dto/dspsettingdto.h \
    source/thread/dsp/dto/dspstatusdto.h \
    source/thread/dsp/dto/eventdto.h \
    source/thread/dsp/dto/metalgraphdto.h \
    source/thread/dsp/dto/productsettingdto.h \
    source/thread/dsp/dto/weightgraphdto.h \
    source/thread/dsp/sendpacketqueue.h \
    source/thread/historybackupthread.h \
    source/util/etcutil.h \
    source/util/eventchecker.h \
    source/util/fileloaderthread.h \
    source/util/filewriter.h \
    source/util/mouseeventspy.h \
    source/util/myalloc.h

DISTFILES +=
