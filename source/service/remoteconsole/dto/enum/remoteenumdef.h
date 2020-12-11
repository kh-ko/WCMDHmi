#ifndef REMOTEENUMDEF_H
#define REMOTEENUMDEF_H
#include <QObject>

class RemoteEnumDef: public QObject{
    Q_OBJECT
    Q_ENUMS(eRSyncErrType)

public:
    enum eRSyncErrType{
        RSYNC_ERR_NONE            = 0,
        RSYNC_ERR_CANCLE          = 1,
        RSYNC_ERR_NETWORK         = 2,
        RSYNC_ERR_FILE_INFO       = 3,
        RSYNC_ERR_ALREADY_SYNCING = 4,
        RSYNC_ERR_CLOSE           = 5
    };

    enum eRFuncCode{
        RFUNC_CODE_INFO                  = 1,
        RFUNC_CODE_RSYNC                 = 2,
        RFUNC_CODE_RSYNC_INIT            = 3,
        RFUNC_CODE_RSYNC_ALREADY_SYNCING = 4,
        RFUNC_CODE_RSYNC_FILE_INFO       = 5,
        RFUNC_CODE_RSYNC_FILE_CONTENT    = 6,
        RFUNC_CODE_RSYNC_COMPLETE        = 7,
        RFUNC_CODE_MONITOR_STATUS        = 8
    };
};
#endif // REMOTEENUMDEF_H
