QT += quick widgets charts virtualkeyboard sql serialbus

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
        source/logger/nsdebug.cpp \
        source/main.cpp \
        source/service/remoteconsole/monitoringservice.cpp \
        source/service/remoteconsole/syncclient.cpp \
        source/service/remoteconsole/syncserverservice.cpp \
        source/thread/historybackupthread.cpp \
        source/util/etcutil.cpp \
        source/util/fileloaderthreadex.cpp \
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
    source/globaldef/qmlenumdef.h \
    source/logger/nsdebug.h \
    source/qmlmodel/wcmd/introscenemodel.h \
    source/qmlmodel/wcmd/main_scene/FactoryResetViewModel.h \
    source/qmlmodel/wcmd/main_scene/mainviewmodel.h \
    source/qmlmodel/wcmd/main_scene/panelbackupmodel.h \
    source/qmlmodel/wcmd/main_scene/paneldebuggingmodel.h \
    source/qmlmodel/wcmd/main_scene/panelfullmdmodel.h \
    source/qmlmodel/wcmd/main_scene/panelgroupsettinginhomemodel.h \
    source/qmlmodel/wcmd/main_scene/panelpdselectmodel.h \
    source/qmlmodel/wcmd/main_scene/panelwcsettinginhomemodel.h \
    source/qmlmodel/wcmd/mainmodel.h \
    source/qmlmodel/wcmd/mainscenemodel.h \
    source/qmlmodel/wcmd/menu_scene/checkup/panelmdcheckupmodel.h \
    source/qmlmodel/wcmd/menu_scene/checkup/panelwcdynamiccalibraionmodel.h \
    source/qmlmodel/wcmd/menu_scene/checkup/panelwcstaticcaribrationmodel.h \
    source/qmlmodel/wcmd/menu_scene/clocksetting/panelclocksettingmodel.h \
    source/qmlmodel/wcmd/menu_scene/devicesetting/paneldevicesettingmodel.h \
    source/qmlmodel/wcmd/menu_scene/graph/metaldetectorgraphmodel.h \
    source/qmlmodel/wcmd/menu_scene/graph/panelmdgraphmodel.h \
    source/qmlmodel/wcmd/menu_scene/graph/panelwcgraphmodel.h \
    source/qmlmodel/wcmd/menu_scene/information/panelinformationmodel.h \
    source/qmlmodel/wcmd/menu_scene/loggingdata/loggingdatamodel.h \
    source/qmlmodel/wcmd/menu_scene/maxerrorsetting/panelmaxerrorsettingmodel.h \
    source/qmlmodel/wcmd/menu_scene/productsetting/panelproductsettingmodel.h \
    source/qmlmodel/wcmd/menu_scene/productsetting/productsettingitemmodel.h \
    source/service/coreservice.h \
    source/service/def/builddef.h \
    source/service/def/datetimeform.h \
    source/service/def/filedef.h \
    source/service/defaultsetting/defaultsettingsprovider.h \
    source/service/dsp/dspdatastore.h \
    source/service/dsp/dspdatastorestruct.h \
    source/service/dsp/dspmaster.h \
    source/service/dsp/dspsendqueue.h \
    source/service/dsp/dspsendqueueitem.h \
    source/service/dsp/dspsprovider.h \
    source/service/dsp/packet/dsppacket.h \
    source/service/dsp/packet/dsppacketstruct.h \
    source/service/dto/devsettingdto.h \
    source/service/dto/dspconninfodto.h \
    source/service/dto/dspdevsettingdto.h \
    source/service/dto/dspeventdto.h \
    source/service/dto/dspinfodto.h \
    source/service/dto/dspmdgdto.h \
    source/service/dto/dsppdsettingdto.h \
    source/service/dto/dspstatusdto.h \
    source/service/dto/dspwcgdto.h \
    source/service/dto/enum/enumdef.h \
    source/service/dto/eventdto.h \
    source/service/dto/hmisettingdto.h \
    source/service/dto/informationdto.h \
    source/service/dto/pdbasesettingdto.h \
    source/service/dto/pdsettingdto.h \
    source/service/dto/pdstatsdto.h \
    source/service/dto/securitydto.h \
    source/service/dto/trendsitemdto.h \
    source/service/dto/trendsoptiondto.h \
    source/service/eventhistory/dailyeventhismanager.h \
    source/service/eventhistory/dailypdhismanager.h \
    source/service/eventhistory/dailypdstatsmanager.h \
    source/service/eventhistory/eventhissprovider.h \
    source/service/includesvcdto.h \
    source/service/localsetting/languagehelper.h \
    source/service/localsetting/localsettingsprovider.h \
    source/service/productsetting/productsprovider.h \
    source/service/remoteconsole/deviceinfobrodcaster.h \
    source/service/remoteconsole/dto/devicesocketdto.h \
    source/service/remoteconsole/dto/enum/remoteenumdef.h \
    source/service/remoteconsole/dto/modbusdatastore.h \
    source/service/remoteconsole/monitoringservice.h \
    source/service/remoteconsole/syncclient.h \
    source/service/remoteconsole/syncserverservice.h \
    source/service/remoteconsole/tcpmodbusslave.h \
    source/service/timer/timersprovider.h \
    source/service/util/byteswap.h \
    source/service/util/exceptionutil.h \
    source/service/util/filecopylocal.h \
    source/service/util/filefolderreader.h \
    source/service/util/filereaderex.h \
    source/service/util/filewriterex.h \
    source/service/util/sproviderconnectutil.h \
    source/service/work/TrendsManager.h \
    source/service/work/worksprovider.h \
    source/thread/historybackupthread.h \
    source/util/etcutil.h \
    source/util/fileloaderthreadex.h \
    source/util/mouseeventspy.h

DISTFILES +=
