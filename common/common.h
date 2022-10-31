#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum messages
{
    VALUE_REQUEST = 1,
    VALUE_ANSWER,
    PRINT_CLASSIC_REQUEST,
    PRINT_CANONIC_REQUEST,
    PRINT_ANSWER,
    ROOT_REQUEST,
    ROOT_ANSWER,
    ERROR,
};

enum modes
{
    I_MODE = 1,
    C_MODE,

};

extern const QChar separator;
QString& operator<< (QString&,const QString&);

#endif // COMMON_H
