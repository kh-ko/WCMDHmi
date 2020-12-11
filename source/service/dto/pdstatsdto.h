#ifndef PDSTATSDTO_H
#define PDSTATSDTO_H

#include <QObject>

class PDStatsDto
{
public:
    quint64    mSeq                = 0;
    quint16    mNum                = 0;
    QString    mName               = "";
    int        mWCOCnt             = 0;
    int        mWCOWCnt            = 0;
    int        mWCNorCnt           = 0;
    int        mWCUCnt             = 0;
    int        mWCUWCnt            = 0;
    int        mWCEtcCnt           = 0;
    int        mWCMDCnt            = 0;
    int        mMDPassCnt          = 0;
    int        mMDFailCnt          = 0;
    int        mWCTradeCnt         = 0;
    int        mWCTotalCnt         = 0;
    int        mMDTotalCnt         = 0;
    quint64    mWCTradeTotalWeight = 0;

    PDStatsDto(){}
    PDStatsDto(const PDStatsDto& copy) :
        mSeq               (copy.mSeq               ),
        mNum               (copy.mNum               ),
        mName              (copy.mName              ),
        mWCOCnt            (copy.mWCOCnt            ),
        mWCOWCnt           (copy.mWCOWCnt           ),
        mWCNorCnt          (copy.mWCNorCnt          ),
        mWCUCnt            (copy.mWCUCnt            ),
        mWCUWCnt           (copy.mWCUWCnt           ),
        mWCEtcCnt          (copy.mWCEtcCnt          ),
        mWCMDCnt           (copy.mWCMDCnt           ),
        mMDPassCnt         (copy.mMDPassCnt         ),
        mMDFailCnt         (copy.mMDFailCnt         ),
        mWCTradeCnt        (copy.mWCTradeCnt        ),
        mWCTotalCnt        (copy.mWCTotalCnt        ),
        mMDTotalCnt        (copy.mMDTotalCnt        ),
        mWCTradeTotalWeight(copy.mWCTradeTotalWeight){}
    ~PDStatsDto(){}

    PDStatsDto& operator=(const PDStatsDto& other)
    {
        mSeq                = other.mSeq               ;
        mNum                = other.mNum               ;
        mName               = other.mName              ;
        mWCOCnt             = other.mWCOCnt            ;
        mWCOWCnt            = other.mWCOWCnt           ;
        mWCNorCnt           = other.mWCNorCnt          ;
        mWCUCnt             = other.mWCUCnt            ;
        mWCUWCnt            = other.mWCUWCnt           ;
        mWCEtcCnt           = other.mWCEtcCnt          ;
        mWCMDCnt            = other.mWCMDCnt           ;
        mMDPassCnt          = other.mMDPassCnt         ;
        mMDFailCnt          = other.mMDFailCnt         ;
        mWCTradeCnt         = other.mWCTradeCnt        ;
        mWCTotalCnt         = other.mWCTotalCnt        ;
        mMDTotalCnt         = other.mMDTotalCnt        ;
        mWCTradeTotalWeight = other.mWCTradeTotalWeight;

        return *this;
    }

    bool setValue(QString value)
    {
        int findFieldCnt = 0;

        QStringList fieldList = value.split(",");

        foreach(QString field ,fieldList)
        {
            if(field.contains(":") == false)
                continue;

            int splitIdx  = field.indexOf(":");
            QString key   = field.left(splitIdx);
            QString value = field.mid(splitIdx+1);

            if     (key == "ProdcutSettingSeq"){findFieldCnt++; mSeq       = value.toULongLong();}
            else if(key == "ProductNo"        ){findFieldCnt++; mNum       = value.toUInt()     ;}
            else if(key == "ProductName"      ){findFieldCnt++; mName      = value;              }
            else if(key == "O"                ){findFieldCnt++; mWCOCnt    = value.toUInt();     }
            else if(key == "OW"               ){findFieldCnt++; mWCOWCnt   = value.toUInt();     }
            else if(key == "N"                ){findFieldCnt++; mWCNorCnt  = value.toUInt();     }
            else if(key == "U"                ){findFieldCnt++; mWCUCnt    = value.toUInt();     }
            else if(key == "UW"               ){findFieldCnt++; mWCUWCnt   = value.toUInt();     }
            else if(key == "ETC"              ){findFieldCnt++; mWCEtcCnt  = value.toUInt();     }
            else if(key == "WC MD F"          ){findFieldCnt++; mWCMDCnt   = value.toUInt();     }
            else if(key == "MD F"             ){findFieldCnt++; mMDFailCnt = value.toUInt();     }
            else if(key == "MD P"             ){findFieldCnt++; mMDPassCnt = value.toUInt();     }
        }

        mWCTotalCnt = mWCOCnt + mWCOWCnt + mWCNorCnt + mWCUCnt + mWCUWCnt + mWCEtcCnt + mWCMDCnt;
        mMDTotalCnt = mMDPassCnt + mMDFailCnt;

        return findFieldCnt == 0 ? false : true;
    }

    QString toString()
    {
        return QString("ProdcutSettingSeq:%1,ProductName:%2,ProductNo:%3,U:%4,UW:%5,N:%6,OW:%7,O:%8,ETC:%9,WC MD F:%10,MD F:%11,MD P:%12")
                    .arg(mSeq      )
                    .arg(mName     )
                    .arg(mNum      )
                    .arg(mWCUCnt   )
                    .arg(mWCUWCnt  )
                    .arg(mWCNorCnt )
                    .arg(mWCOWCnt  )
                    .arg(mWCOCnt   )
                    .arg(mWCEtcCnt )
                    .arg(mWCMDCnt  )
                    .arg(mMDFailCnt)
                    .arg(mMDPassCnt);
    }

    void clearValue()
    {
        mWCOCnt             = 0;
        mWCOWCnt            = 0;
        mWCNorCnt           = 0;
        mWCUCnt             = 0;
        mWCUWCnt            = 0;
        mWCEtcCnt           = 0;
        mWCMDCnt            = 0;
        mMDPassCnt          = 0;
        mMDFailCnt          = 0;
        mWCTradeCnt         = 0;
        mWCTotalCnt         = 0;
        mMDTotalCnt         = 0;
        mWCTradeTotalWeight = 0;
    }

    void reset()
    {
        mSeq  = 0;
        mNum  = 0;
        mName = "";
        clearValue();
    }
};

Q_DECLARE_METATYPE(PDStatsDto);
#endif // PDSTATSDTO_H
