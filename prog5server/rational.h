#ifndef TRATIONAL_H
#define TRATIONAL_H
#include <iostream>
using namespace std;
#include <QString>

class rational
{
    public:
        rational();
        rational (const int&);
        rational(int, int);
        rational(const QByteArray&);
        int chi, zm;

        static QChar SEPARATOR;
        static void setSeparator(QChar);

        rational operator+ (const rational&);
        rational operator* (const rational&);
        rational operator/(const rational& );
        rational sqrt(rational );
        bool operator!=(const rational& );
        bool operator==(const rational& );
        rational operator-();
        rational operator-(const rational& );
        bool operator>=(const rational& );
        bool operator>(const rational& );
        bool operator<(const rational& );
        int Sokr();
        friend rational sqrt(rational);
        friend QByteArray& operator>> (QByteArray&, rational&);

        friend QString& operator<<(QString&, rational);
        operator QString ();
        int get_chi ();
        int get_zm ();
};

#endif // TRATIONAL_H
