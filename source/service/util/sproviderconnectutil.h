#ifndef SPROVIDERCONNECTUTIL_H
#define SPROVIDERCONNECTUTIL_H

#define ENABLE_SLOT_CORE_START connect(CoreService::getInstance(), SIGNAL(signalEventStarted()), this, SLOT(onStartedCoreService()))
#define ENABLE_SLOT_CORE_STOP  connect(CoreService::getInstance(), SIGNAL(signalEventStopped()), this, SLOT(onStoppedCoreService()))

#define ENABLE_SLOT_DSP_START                     connect(DspSProvider::getInstance(), SIGNAL(signalEventStarted()                                            ), this, SLOT(onStartedDspSProvider()                             ))
#define ENABLE_SLOT_DSP_STOP                      connect(DspSProvider::getInstance(), SIGNAL(signalEventStopped()                                            ), this, SLOT(onStoppedDspSProvider()                             ))
#define ENABLE_SLOT_DSP_CHANGED_ISCONNECT         connect(DspSProvider::getInstance(), SIGNAL(signalEventChangedIsConnect(quint64, bool)                      ), this, SLOT(onChangedDspIsConnect(quint64, bool)                ))
#define ENABLE_SLOT_DSP_COMPLETED_FR              connect(DspSProvider::getInstance(), SIGNAL(signalEventCompletedFactoryReset(bool)                          ), this, SLOT(onCompletedDspFR(bool)                              ))
#define ENABLE_SLOT_DSP_CHANGED_REMOTE_DEVSETTING connect(DspSProvider::getInstance(), SIGNAL(signalEventChangedRemoteDeviceSetting(quint64, DspDevSettingDto)), this, SLOT(onChangedRemoteDevSetting(quint64, DspDevSettingDto)))
#define ENABLE_SLOT_DSP_CHANGED_REMOTE_PDSETTING  connect(DspSProvider::getInstance(), SIGNAL(signalEventChangedRemoteProductSetting(quint64, DspPDSettingDto)), this, SLOT(onChangedRemotePDSetting(quint64, DspPDSettingDto)  ))
#define ENABLE_SLOT_DSP_CHANGED_DSP_STATUS        connect(DspSProvider::getInstance(), SIGNAL(signalEventChangedDeviceStatus(quint64, DspStatusDto)           ), this, SLOT(onChangedDspStatus(quint64, DspStatusDto)           ))
#define ENABLE_SLOT_DSP_CHANGED_DSP_INFO          connect(DspSProvider::getInstance(), SIGNAL(signalEventChangedDeviceInfo(quint64, DspInfoDto)               ), this, SLOT(onChangedDspInfo(quint64, DspInfoDto)               ))
#define ENABLE_SLOT_DSP_ADDED_EVENT               connect(DspSProvider::getInstance(), SIGNAL(signalEventAddedEvent(quint64, DspEventDto)                     ), this, SLOT(onAddedDspEvent(quint64, DspEventDto)               ))
#define ENABLE_SLOT_DSP_CHANGED_REF_VLOTAGE       connect(DspSProvider::getInstance(), SIGNAL(signalEventChangedRefVoltage(quint64, qint32)                   ), this, SLOT(onChangedRefVoltage(quint64, qint32)                ))
#define ENABLE_SLOT_DSP_ADDED_WCG                 connect(DspSProvider::getInstance(), SIGNAL(signalEventAddedWeightCheckerGraph(quint64, DspWCGDto)          ), this, SLOT(onAddedWCG(quint64, DspWCGDto)                      ))
#define ENABLE_SLOT_DSP_ADDED_MDG                 connect(DspSProvider::getInstance(), SIGNAL(signalEventAddedMetalDetectorGraph(quint64, DspMDGDto)          ), this, SLOT(onAddedMDG(quint64, DspMDGDto)                      ))

#define ENABLE_SLOT_LSETTING_START                  connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventStarted()                             ), this, SLOT(onStartedLocalSettingSProvider()        ))
#define ENABLE_SLOT_LSETTING_STOP                   connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventStopped()                             ), this, SLOT(onStoppedLocalSettingSProvider()        ))
#define ENABLE_SLOT_LSETTING_CHANGED_ISDETAIL       connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedIsDetail(bool)                 ), this, SLOT(onChangedGuiIsDetail(bool)              ))
#define ENABLE_SLOT_LSETTING_CHANGED_VIEWMODE       connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedViewMode(int)                  ), this, SLOT(onChangedViewMode(int)                  ))
#define ENABLE_SLOT_LSETTING_CHANGED_PDSORTMODE     connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedPDSortMode(int)                ), this, SLOT(onChangedPDSortMode(int)                ))
#define ENABLE_SLOT_LSETTING_CHANGED_TR_OPTION      connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedTROption(TrendsOptionDto)      ), this, SLOT(onChangedTROption(TrendsOptionDto)      ))
#define ENABLE_SLOT_LSETTING_CHANGED_INFO           connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedInformation(InformationDto)    ), this, SLOT(onChangedInformation(InformationDto)    ))
#define ENABLE_SLOT_LSETTING_CHANGED_BACKUP_DATE    connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedBackupLastDate(QDate)          ), this, SLOT(onChangedBackupLastDate(QDate)          ))
#define ENABLE_SLOT_LSETTING_CHANGED_DEV_SETTING    connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedDevSetting(DevSettingDto)      ), this, SLOT(onChangedDevSetting(DevSettingDto)      ))
#define ENABLE_SLOT_LSETTING_CHANGED_HMI_SETTING    connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedHMISetting(HMISettingDto)      ), this, SLOT(onChangedHMISetting(HMISettingDto)      ))
#define ENABLE_SLOT_LSETTING_CHANGED_PDBASE_SETTING connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedPdBaseSetting(PdBaseSettingDto)), this, SLOT(onChangedPdBaseSetting(PdBaseSettingDto)))
#define ENABLE_SLOT_LSETTING_CHANGED_MAX_ERROR      connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedMaxError(quint32)              ), this, SLOT(onChangedMaxError(quint32)              ))

#define ENABLE_SLOT_PDSETTING_START                connect(ProductSProvider::getInstance(), SIGNAL(signalEventStarted()                         ), this, SLOT(onStartedProductSProvider()         ))
#define ENABLE_SLOT_PDSETTING_STOP                 connect(ProductSProvider::getInstance(), SIGNAL(signalEventStopped()                         ), this, SLOT(onStoppedProductSProvider()         ))
#define ENABLE_SLOT_PDSETTING_ADD_PD               connect(ProductSProvider::getInstance(), SIGNAL(signalEventAddedPDSetting(PDSettingDto)      ), this, SLOT(onAddedPDSetting(PDSettingDto)      ))
#define ENABLE_SLOT_PDSETTING_CHANGED_PD           connect(ProductSProvider::getInstance(), SIGNAL(signalEventChangedPDSetting(PDSettingDto)    ), this, SLOT(onChangedPDSetting(PDSettingDto)    ))
#define ENABLE_SLOT_PDSETTING_REMOVED_PD           connect(ProductSProvider::getInstance(), SIGNAL(signalEventRemovedPDSetting(quint64)         ), this, SLOT(onRemovedPDSetting(quint64)         ))
#define ENABLE_SLOT_PDSETTING_CHANGED_CURR_PD      connect(ProductSProvider::getInstance(), SIGNAL(signalEventChangedCurrPDSetting(PDSettingDto)), this, SLOT(onChangedCurrPDSetting(PDSettingDto)))

#define ENABLE_SLOT_WORK_START           connect(WorkSProvider::getInstance(), SIGNAL(signalEventStarted()                 ), this, SLOT(onStartedWorkSProvider()    ))
#define ENABLE_SLOT_WORK_STOP            connect(WorkSProvider::getInstance(), SIGNAL(signalEventStopped()                 ), this, SLOT(onStoppedWorkSProvider()    ))
#define ENABLE_SLOT_WORK_CHANGED_STATS   connect(WorkSProvider::getInstance(), SIGNAL(signalEventChangedPDStats(PDStatsDto)), this, SLOT(onChangedPDStats(PDStatsDto)))
#define ENABLE_SLOT_WORK_CHANGED_LASTERR connect(WorkSProvider::getInstance(), SIGNAL(signalEventChangedLastErr(EventDto  )), this, SLOT(onChangedLastErr(EventDto  )))

#define ENABLE_SLOT_EVENTHIS_START           connect(EventHistorySProvider::getInstance(), SIGNAL(signalEventStarted()                  ), this, SLOT(onStartedEventHisSProvider()    ))
#define ENABLE_SLOT_EVENTHIS_STOP            connect(EventHistorySProvider::getInstance(), SIGNAL(signalEventStopped()                  ), this, SLOT(onStoppedEventHisProvider()     ))
#define ENABLE_SLOT_EVENTHIS_ADDED_EVENT     connect(EventHistorySProvider::getInstance(), SIGNAL(siganlEventAddedEventHistory(EventDto)), this, SLOT(onAddedEventHistory(EventDto)   ))

#define ENABLE_SLOT_TIMER_START connect(TimerSProvider::getInstance(), SIGNAL(signalEventStarted()     ), this, SLOT(onStartedTimerSProvider()))
#define ENABLE_SLOT_TIMER_STOP  connect(TimerSProvider::getInstance(), SIGNAL(signalEventStopped()     ), this, SLOT(onStoppedTimerSProvider()))
#define ENABLE_SLOT_TIMER_TICK  connect(TimerSProvider::getInstance(), SIGNAL(signalTimeTick(QDateTime)), this, SLOT(onTimeTick(QDateTime)    ))

#endif // SPROVIDERCONNECTUTIL_H
