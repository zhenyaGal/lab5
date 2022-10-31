#include "rational.h"
#include "cmath"

#include "common.h"

QChar rational::SEPARATOR = separator;

rational::rational()
{

}

rational::rational(const int& r)
{
    this->chi = r;
    this->zm = 1;

}

rational::rational(int x,  int y)
{
    this->chi = x;
    this->zm = y;
    this->Sokr();
}
rational rational::operator+ (const rational& c)
{
    rational t;
    t.chi = chi*c.zm + zm*c.chi;
    t.zm = c.zm * zm;
    t.Sokr();
    return t;
}
rational rational::operator* (const rational& c)
{
    rational t;
    t.chi = chi*c.chi;
    t.zm = zm*c.zm;
    t.Sokr();
    return t;
}



rational rational::operator/(const rational& r)
{
    rational t;
    t.chi=chi*r.zm;
    t.zm=zm*r.chi;
    t.Sokr();
    return t;
}


bool rational::operator!=(const rational& r)
{
    return (chi*r.zm!=r.chi*zm);
}


bool rational::operator==(const rational& r)
{
    return (chi*r.zm==r.chi*zm);
}


rational rational::operator- ()
{
    rational t;
    t.chi = -chi;
    t.zm = zm;
    return t;
}

rational rational::operator-(const rational& r)
{
    rational t;
    t.chi=chi*r.zm-r.chi*zm;
    t.zm=zm*r.zm;
    t.Sokr();
    return t;
}

bool rational::operator>=(const rational& r)
{
    return (chi * r.zm >= r.chi * zm);
}

bool rational::operator>(const rational& r)
{
   return(chi * r.zm > r.chi * zm);
}

bool rational::operator<(const rational& r)
{
    return (chi * r.zm < r.chi * zm);
}

int rational::Sokr()
{
    int a = abs((int)chi);
    int b = abs((int)zm);
    while (a != b)
    {
        if (a > b)
        {
            int tmp = a;
            a = b;
            b = tmp;
        }
        b = b - a;
    }
    chi = chi / a;
    zm = zm / a;
    return 0;
}

rational sqrt (rational r)
{
    rational t;
    r.Sokr();
    t.chi=(sqrt(r.chi));
    t.zm=(sqrt(r.zm));
    if(((t.chi-(int)t.chi)!=0)||((t.zm-(int)t.zm)!=0)) throw 1;
    return t;
}


ostream& operator<<(ostream& os, rational c)
{
    c.Sokr();
    os<<c.chi<<"/"<<c.zm;
    return os;

}
istream& operator>>(istream& is, rational& c)
{
    is >> c.chi>>c.zm;
    while (c.zm == 0)
    {
        cout<<"Enter a fraction with a zero denominator: ";
        is>>c.chi>>c.zm;
    }

    return is;

}
QString& operator<<(QString&s, rational r)
{
    r.Sokr();
    s += "(";
    s += QString().setNum(r.chi);
    s += "/";
    s += QString().setNum(r.zm);
    s += ")";
    return s;
}
rational::rational(const QByteArray& arr)
{

    int p = arr.indexOf(rational::SEPARATOR);
    chi = arr.left(p).toInt();
    zm = arr.right(arr.length()-p-1).toInt();
    if (zm<=0.0) throw 1;
    this->Sokr();
}

QByteArray& operator>>(QByteArray& arr, rational& q)
{

    int p = arr.indexOf(rational::SEPARATOR);
    p = arr.indexOf(rational::SEPARATOR,p+1);
    if(p>0)
    {
        q = rational(arr.left(p));
        arr = arr.right(arr.length()-p-1);
    }
    return arr;
}

rational::operator QString ()
{
    QString s;
    if (*this<0)
    {
        s += "-(";
        s += QString().setNum(-chi);
        s += "/";
        s += QString().setNum(zm);
        s += ")";
    }
    else
    {
        s += "(";
        s += QString().setNum(chi);
        s += "/";
        s += QString().setNum(zm);
        s += ")";
    }
    return s;
}



void rational::setSeparator(QChar ch)
{
    SEPARATOR = ch;
}

int rational::get_chi ()
{
    return chi;
}

int rational::get_zm ()
{
    return zm;
}
