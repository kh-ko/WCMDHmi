#ifndef LANGUAGEHELPER_H
#define LANGUAGEHELPER_H

#include <QObject>
#include <QApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QTranslator>
#include <QDebug>

#include "source/service/includesvcdto.h"
#include "source/service/util/exceptionutil.h"

class LanguageHelper : public QObject
{
    Q_OBJECT
public:
    EnumDef::eLang mLang      = EnumDef::LANG_ENG;

    explicit LanguageHelper(QObject * parent = nullptr):QObject(parent)
    {

    }
    ~LanguageHelper()
    {
    }

    void setLanguage(QObject * pContext, EnumDef::eLang lang)
    {
        if(qApp == nullptr || pContext == nullptr || QQmlEngine::contextForObject(pContext) == nullptr || QQmlEngine::contextForObject(pContext)->engine() == nullptr)
        {
            qDebug() << "[LanguageHelper::loadLanguage]not loaded pApp";
            return;
        }

        qDebug() << mLang << " to " << lang;
        if(mLang == lang)
        {
            qDebug() << "same language";
            return;
        }

        do
        {
            if(lang == EnumDef::LANG_ENG)
            {
                if(qApp->removeTranslator(&(mTranslator)) == false)
                {
                    break;
                }

            }
            else if(lang == EnumDef::LANG_KOR)
            {
                if(mTranslator.load(":/Lang_ko_KR"))
                {
                    qDebug() << "load : Lang_ko_KR";
                    qApp->installTranslator(&(mTranslator));
                    qDebug() << "load : end";
                }
                else
                {
                    break;
                }
            }
            else if(lang == EnumDef::LANG_CHN)
            {
                if(mTranslator.load(":/Lang_zh_CN"))
                {
                    qDebug() << "load : Lang_zh_CN";
                    qApp->installTranslator(&(mTranslator));
                    qDebug() << "load : end";
                }
                else
                {
                    break;
                }
            }

            mLang = lang;

            QQmlEngine::contextForObject(pContext)->engine()->retranslate();

            return;
        }while(0);

        qDebug() << "changed failed";

    }

private:
    QTranslator mTranslator;
};

#endif // LANGUAGEHELPER_H
