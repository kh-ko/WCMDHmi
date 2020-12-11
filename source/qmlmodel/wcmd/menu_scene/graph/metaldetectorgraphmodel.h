#ifndef METALDETECTORGRAPHMODEL_H
#define METALDETECTORGRAPHMODEL_H

#include <QObject>
#include <QtMath>
#include <QDebug>

class MetalDetectorGraphModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool     isVisible         READ      getIsVisible            NOTIFY      signalEventChangedIsVisible         )
    Q_PROPERTY(bool     isRawGraphOn      READ      getIsRawGraphOn         NOTIFY      signalEventChangedIsRawGraphOn      )
    Q_PROPERTY(int      range             READ      getRange                NOTIFY      signalEventChangedRange             )
    Q_PROPERTY(quint16  senstivity        READ      getSenstivity           NOTIFY      signalEventChangedSenstivity        )
    Q_PROPERTY(bool     isDetect          READ      getIsDetect             NOTIFY      signalEventChangedIsDetect          )
    Q_PROPERTY(int      min               READ      getMin                  NOTIFY      signalEventChangedMin               )
    Q_PROPERTY(int      max               READ      getMax                  NOTIFY      signalEventChangedMax               )
    Q_PROPERTY(int      lineInterval      READ      getLineInterval         NOTIFY      signalEventChangedLineInterval      )
    Q_PROPERTY(int      pointCnt          READ      getPointCnt             NOTIFY      signalEventChangedPointCnt          )

public:
    qint16 *  mRawPoints        = nullptr;
    qint16 *  mFilterPoints     = nullptr;
    int       mStartIdx         = 0;
    int       mPointBuffWidth   = 0;

    bool      mIsVisible        = false;
    bool      mIsRawGraphOn     = false;
    int       mRange            = 1;
    quint16   mSenstivity       = 1;
    bool      mIsDetect         = false;
    int       mMin              = 0;
    int       mMax              = 0;
    int       mLineInterval     = 0;
    int       mPointCnt         = 0;

    bool      getIsVisible          (){ return mIsVisible           ;}
    bool      getIsRawGraphOn       (){ return mIsRawGraphOn        ;}
    int       getRange              (){ return mRange               ;}
    quint16   getSenstivity         (){ return mSenstivity          ;}
    bool      getIsDetect           (){ return mIsDetect            ;}
    int       getMin                (){ return mMin                 ;}
    int       getMax                (){ return mMax                 ;}
    int       getLineInterval       (){ return mLineInterval        ;}
    int       getPointCnt           (){ return mPointCnt            ;}

    void      setIsVisible          (bool    value){ if( value == mIsVisible        ) return; mIsVisible        = value; emit signalEventChangedIsVisible       (value);}
    void      setIsRawGraphOn       (bool    value){ if( value == mIsRawGraphOn     ) return; mIsRawGraphOn     = value; emit signalEventChangedIsRawGraphOn    (value);}
    void      setRange              (int     value){ if( value == mRange            ) return; mRange            = value; emit signalEventChangedRange           (value); setLineInterval(value / 6);}
    void      setSenstivity         (quint16 value){ if( value == mSenstivity       ) return; mSenstivity       = value; emit signalEventChangedSenstivity      (value);}
    void      setIsDetect           (bool    value){ if( value == mIsDetect         ) return; mIsDetect         = value; emit signalEventChangedIsDetect        (value);}
    void      setMin                (int     value){ if( value == mMin              ) return; mMin              = value; emit signalEventChangedMin             (value);}
    void      setMax                (int     value){ if( value == mMax              ) return; mMax              = value; emit signalEventChangedMax             (value);}
    void      setLineInterval       (int     value){ if( value == mLineInterval     ) return; mLineInterval     = value; emit signalEventChangedLineInterval    (value);}
    void      setPointCnt           (int     value){ if( value == mPointCnt         ) return; mPointCnt         = value; emit signalEventChangedPointCnt        (value);}

    explicit MetalDetectorGraphModel(QObject *parent = nullptr):QObject(parent){}
    ~MetalDetectorGraphModel()
    {
        if(mRawPoints != nullptr)
            free(mRawPoints);

        if(mFilterPoints != nullptr)
            free(mFilterPoints);
    }

signals:
    void signalEventChangedIsVisible        (bool    value);
    void signalEventChangedIsRawGraphOn     (bool    value);
    void signalEventChangedRange            (int     value);
    void signalEventChangedSenstivity       (quint16 value);
    void signalEventChangedIsDetect         (bool    value);
    void signalEventChangedMin              (int     value);
    void signalEventChangedMax              (int     value);
    void signalEventChangedLineInterval     (int     value);
    void signalEventChangedPointCnt         (int     value);

    void signalEventChangedGraph            (             );

public slots:
    Q_INVOKABLE void onCommandSetGraphWidth   (int width)
    {
        if(mRawPoints != nullptr)
            free(mRawPoints);

        if(mFilterPoints != nullptr)
            free(mFilterPoints);

        if(width < 1)
            return;

        mRawPoints    = (qint16 *)malloc(sizeof(quint16) * width);
        mFilterPoints = (qint16 *)malloc(sizeof(quint16) * width);
        mPointBuffWidth = width;
        mStartIdx = 0;
        setPointCnt(0);
    }

    Q_INVOKABLE qint16 onCommandGetRawPointValue   (int idx)
    {
        if(mPointBuffWidth < idx - 1)
            return 0;

        return mRawPoints[(mStartIdx + idx)%mPointBuffWidth];
    }

    Q_INVOKABLE qint16 onCommandGetFilterPointValue   (int idx)
    {
        if(mPointBuffWidth < idx - 1)
            return 0;

        return mFilterPoints[(mStartIdx + idx)%mPointBuffWidth];
    }

public :
    void addPoints(int pointCnt, qint16 * points)
    {
        int min = 0, max = 0;
        bool isDetect = false;

        if(mPointBuffWidth < 10)
            return;

        int endIdx = (mStartIdx + mPointCnt) % mPointBuffWidth;

        for(int i = 0; i < pointCnt; i ++)
        {
            mRawPoints   [endIdx] = points[i * 2];
            mFilterPoints[endIdx] = points[i * 2 + 1];
            endIdx = (endIdx + 1) % mPointBuffWidth;

        }

        mPointCnt = mPointCnt + pointCnt;

        if(mPointCnt > mPointBuffWidth)
        {
            mPointCnt = mPointBuffWidth;
            mStartIdx = endIdx;
        }

        for(int i = 0; i < mPointCnt; i ++)
        {
            if(mFilterPoints[i] > mSenstivity || (mFilterPoints[i] < mSenstivity * -1))
                isDetect = true;

            if(min > mFilterPoints[i])
                min = mFilterPoints[i];

            if(max < mFilterPoints[i])
                max = mFilterPoints[i];
        }

        setIsDetect(isDetect);
        setMax(max);
        setMin(min);

        emit signalEventChangedGraph();
    }
};

#endif // METALDETECTORGRAPHMODEL_H
