#ifndef LANGUAGEHELPER_H
#define LANGUAGEHELPER_H

#include <QObject>
#include <QTranslator>

#include "source/globaldef/EnumDefine.h"

class LanguageHelper : public QObject
{
    Q_OBJECT
public:
    static LanguageHelper * mpSelf;
private:
    QObject * mContext;
    EnumDefine::Language mLanguage = EnumDefine::Language::ENG;
    QTranslator mTranslator;

public:
    static LanguageHelper* getInstance();
    void loadLanguage(EnumDefine::Language value);
    void setContext(QObject * content);
    explicit LanguageHelper(QObject *parent = nullptr);
    ~LanguageHelper();

};

#endif // LANGUAGEHELPER_H
