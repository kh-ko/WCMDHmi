#ifndef SECURITYDTO_H
#define SECURITYDTO_H

#include <QObject>

class SecurityDto
{
public:
    QString mPwd          = "1111";
    QString mAdminPwd     = "0701";

    SecurityDto(){}
    SecurityDto(const SecurityDto& copy) :
        mPwd     (copy.mPwd     ),
        mAdminPwd(copy.mAdminPwd){}

    ~SecurityDto(){}

    SecurityDto& operator=(const SecurityDto& other)
    {
        mPwd      = other.mPwd     ;
        mAdminPwd = other.mAdminPwd;

        return *this;
    }
};
Q_DECLARE_METATYPE(SecurityDto);
#endif // SECURITYDTO_H
