#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCursor>
#include <QtQuickControls2/QQuickStyle>
#include "source/globaldef/GlobalDefine.h"
#include "source/logger/nsdebug.h"
#include "source/qmlmodel/wcmd/mainmodel.h"
#include "source/qmlmodel/wcmd/introscenemodel.h"
#include "source/qmlmodel/wcmd/mainscenemodel.h"
#include "source/qmlmodel/wcmd/main_scene/mainviewmodel.h"
#include "source/qmlmodel/wcmd/menu_scene/graph/metaldetectorgraphmodel.h"
#include "source/qmlmodel/wcmd/menu_scene/graph/panelmdgraphmodel.h"
#include "source/qmlmodel/wcmd/menu_scene/graph/panelwcgraphmodel.h"
#include "source/qmlmodel/wcmd/menu_scene/productsetting/panelproductsettingmodel.h"
#include "source/qmlmodel/wcmd/menu_scene/productsetting/productsettingitemmodel.h"
#include "source/qmlmodel/wcmd/menu_scene/loggingdata/loggingdatamodel.h"
#include "source/qmlmodel/wcmd/menu_scene/devicesetting/paneldevicesettingmodel.h"
#include "source/qmlmodel/wcmd/menu_scene/information/panelinformationmodel.h"
#include "source/qmlmodel/wcmd/menu_scene/etcsetting/paneletcsettingmodel.h"
#include "source/qmlmodel/wcmd/main_scene/panelbackupmodel.h"
#include "source/qmlmodel/wcmd/main_scene/paneldebuggingmodel.h"
#include "source/qmlmodel/wcmd/main_scene/FactoryResetViewModel.h"
#include "source/qmlmodel/wcmd/menu_scene/checkup/panelmdcheckupmodel.h"
#include "source/qmlmodel/wcmd/menu_scene/checkup/panelwcstaticcaribrationmodel.h"
#include "source/qmlmodel/wcmd/menu_scene/clocksetting/panelclocksettingmodel.h"
#include "source/qmlmodel/wcmd/menu_scene/checkup/panelwcdynamiccalibraionmodel.h"
#include "source/qmlmodel/wcmd/main_scene/panelwcsettinginhomemodel.h"
#include "source/service/coreservice.h"
#include "source/util/mouseeventspy.h"

int main(int argc, char *argv[])
{
    int resultExec = 0;

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

#if defined(Q_OS_WIN)
    //QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
#else
    QGuiApplication::setOverrideCursor(Qt::BlankCursor);
#endif

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/ui/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterUncreatableType<EnumDefine>("EnumDefine", 1, 0, "EnumDefine", "");


    qRegisterMetaType<DspInfoDto>();
    qRegisterMetaType<DspConnectionDto>();
    qRegisterMetaType<DspSettingDto>();
    qRegisterMetaType<DspStatusDto>();
    qRegisterMetaType<EventDto>();
    qRegisterMetaType<MetalGraphDto>();
    qRegisterMetaType<ProductSettingDto>();
    qRegisterMetaType<WeightGraphDto>();

    qmlRegisterType<MainModel>("MainModel", 1, 0, "MainModel");
    qmlRegisterType<IntroSceneModel>("IntroSceneModel", 1, 0, "IntroSceneModel");
    qmlRegisterType<MainSceneModel>("MainSceneModel", 1, 0, "MainSceneModel");
    qmlRegisterType<MainViewModel>("MainViewModel", 1, 0, "MainViewModel");
    qmlRegisterType<MetalDetectorGraphModel>("MetalDetectorGraphModel", 1, 0, "MetalDetectorGraphModel");
    qmlRegisterType<PanelMDGraphModel>("PanelMDGraphModel", 1, 0, "PanelMDGraphModel");
    qmlRegisterType<PanelWCGraphModel>("PanelWCGraphModel", 1, 0, "PanelWCGraphModel");
    qmlRegisterType<PanelProductSettingModel>("PanelProductSettingModel", 1, 0, "PanelProductSettingModel");
    qmlRegisterType<ProductSettingItemModel>("ProductSettingItemModel", 1, 0, "ProductSettingItemModel");
    qmlRegisterType<LoggingDataModel>("LoggingDataModel", 1, 0, "LoggingDataModel");
    qmlRegisterType<PanelDeviceSettingModel>("PanelDeviceSettingModel", 1, 0, "PanelDeviceSettingModel");
    qmlRegisterType<PanelInformationModel>("PanelInformationModel", 1, 0, "PanelInformationModel");
    qmlRegisterType<PanelEtcSettingModel>("PanelEtcSettingModel", 1, 0, "PanelEtcSettingModel");
    qmlRegisterType<PanelBackupModel>("PanelBackupModel", 1, 0, "PanelBackupModel");
    qmlRegisterType<PanelDebuggingModel>("PanelDebuggingModel", 1, 0, "PanelDebuggingModel");
    qmlRegisterType<FactoryResetViewModel>("FactoryResetViewModel", 1, 0, "FactoryResetViewModel");
    qmlRegisterType<PanelMDCheckupModel>("PanelMDCheckupModel", 1, 0, "PanelMDCheckupModel");
    qmlRegisterType<PanelWCStaticCaribrationModel>("PanelWCStaticCaribrationModel", 1, 0, "PanelWCStaticCaribrationModel");
    qmlRegisterType<PanelClockSettingModel>("PanelClockSettingModel", 1, 0, "PanelClockSettingModel");
    qmlRegisterType<PanelWCDynamicCalibrationModel>("PanelWCDynamicCalibrationModel", 1, 0, "PanelWCDynamicCalibrationModel");
    qmlRegisterType<PanelWCSettingInHomeModel>("PanelWCSettingInHomeModel", 1, 0, "PanelWCSettingInHomeModel");

    qmlRegisterSingletonType<MouseEventSpy>("MouseEventSpy", 1, 0, "MouseEventSpy", MouseEventSpy::singletonProvider);
    qmlRegisterSingletonType(QUrl("qrc:/uiengine/ViewManager.qml"), "ViewManager", 1, 0, "ViewManager");
    qmlRegisterSingletonType(QUrl("qrc:/uiengine/FontManager.qml"), "FontManager", 1, 0, "FontManager");

    NSDebug::startService();

    qInstallMessageHandler(NSDebug::debugMessageHandler);

    engine.load(url);
    resultExec = app.exec();

    qInstallMessageHandler(nullptr);
    NSDebug::stopService();

    return resultExec;
}
