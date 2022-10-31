#include "application.h"
#include "rational.h"
#include "common.h"
#include <iostream>

QByteArray& operator>>(QByteArray& arr, int& q)
{

    int p = arr.indexOf(separator);
    if(p>0)
    {
        q = atoi(arr.left(p));
        arr = arr.right(arr.length()-p-1);
    }
    return arr;
}

QString& operator<<(QString&s, int r)
{
    //r.Sokr();
    s += QString().setNum(r);
    return s;
}

TApplication::TApplication(int argc, char *argv[])
            : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                         QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(pars, this);

    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(recieve(QByteArray)));
}

void TApplication::recieve(QByteArray msg)
{
    std::cout<<"START\n";
    QString answer, s;
    int pos = msg.indexOf(separator);
    int t, mode = msg.left(pos).toInt();
    msg = msg.right(msg.length()-pos-1);
    if (mode == C_MODE)
    {
        rational a, b, c, x, v;
        msg >> a >> b >> c;
        TPolinom<rational> p(a, b, c);
        pos = msg.indexOf(separator);
        t = msg.left(pos).toInt();
        switch (t)
        {
            case VALUE_REQUEST:
                if (a.get_zm()==0||b.get_zm()==0||c.get_zm()==0)
                {
                    s << "Denominator < 0!";
                    answer << QString().setNum(ERROR);
                }
                else
                {
                    if (a.get_chi()==0)
                    {
                        s << "The coefficient a cannot be zero!";
                        answer << QString().setNum(ERROR);
                    }
                    else
                    {
                        msg = msg.right(msg.length()-pos-1);
                        msg >> x;
                        v = p.value(x);
                        s <<(QString)x << (QString)v;
                        answer << QString().setNum(VALUE_ANSWER);
                    }
                }
                answer += s;
                break;

            case PRINT_CLASSIC_REQUEST:
            if (a.get_zm()==0||b.get_zm()==0||c.get_zm()==0)
                    {
                        s += "Denominator < 0!";
                        answer << QString().setNum(ERROR);
                    }
                    else
                    {
                        if (a.get_chi()==0)
                        {
                            s += "The coefficient a cannot be zero!";
                            answer << QString().setNum(ERROR);
                        }
                        else
                        {
                            p.setPrintMode(EPrintModeClassic);
                            s<<p;
                            answer << QString().setNum(PRINT_ANSWER);
                        }
                    }
                    answer << s;
                    break;

        case PRINT_CANONIC_REQUEST:
            {
                if (a.get_zm()==0||b.get_zm()==0||c.get_zm()==0)
                {
                    s += "Denominator < 0!";
                    answer << QString().setNum(ERROR);
                }
                else
                {
                    if (a.get_chi()==0)
                    {
                        s += "The coefficient a cannot be zero!";
                        answer << QString().setNum(ERROR);
                    }
                    else
                    {

                        p.setPrintMode(EPrintModeCanonic);
                        s<<p;
                        answer << QString().setNum(PRINT_ANSWER);
                    }
                }
                answer << s;
                break;
            }
            case ROOT_REQUEST:
            {
                if (a.get_zm()==0||b.get_zm()==0||c.get_zm()==0)
                {
                    s << "Denominator < 0! ";
                    answer << QString().setNum(ERROR);
                }
                else
                {
                    if (a.get_chi()==0)
                    {
                        s << "The coefficient a cannot be zero!";
                        answer << QString().setNum(ERROR);
                    }
                    else
                    {
                        rational* roots = p.calculateRoots();
                        if (roots != NULL )
                        {
                            if(roots[0]==roots[1])
                            {
                                s << QString().setNum(1);
                                s << (QString)roots[0];
                            }
                            else
                            {
                                s << QString().setNum(2);
                                s << (QString)roots[0] << (QString)roots[1];
                            }
                        }
                        else
                            s << QString().setNum(0);
                        free (roots);
                        answer << QString().setNum(ROOT_ANSWER);
                    }
                }
                answer += s;
                break;
            }
            default:
                break;
            }
    }
    if (mode == I_MODE)
    {
        int a, b, c, x, v;
        msg >> a >> b >> c;
        TPolinom<int> p(a, b, c);
        pos = msg.indexOf(separator);
        t = msg.left(pos).toInt();
        switch (t)
        {
            case VALUE_REQUEST:

                {
                    if (a==0)
                    {
                        s << "The coefficient a cannot be zero!";
                        answer << QString().setNum(ERROR);
                    }
                    else
                    {
                        msg = msg.right(msg.length()-pos-1);
                        msg >> x;
                        v = p.value(x);
                        s << ("(" + QString().setNum(x) + ")") << QString().setNum(v);
                        answer << QString().setNum(VALUE_ANSWER);
                    }
                }
                answer += s;
                break;

            case PRINT_CLASSIC_REQUEST:


                        if (a == 0)
                        {
                            s += "The coefficient a cannot be zero!";
                            answer << QString().setNum(ERROR);
                        }
                        else
                        {
                            p.setPrintMode(EPrintModeClassic);
                            s<<p;
                            answer << QString().setNum(PRINT_ANSWER);
                        }

                    answer << s;
                    break;

        case PRINT_CANONIC_REQUEST:

                    if (a == 0)
                    {
                        s += "The coefficient a cannot be zero!";
                        answer << QString().setNum(ERROR);
                    }
                    else
                    {

                        p.setPrintMode(EPrintModeCanonic);
                        s<<p;
                        answer << QString().setNum(PRINT_ANSWER);
                    }

                answer << s;
                break;

            case ROOT_REQUEST:
            {

                    if (a==0)
                    {
                        s << "The coefficient a cannot be zero!";
                        answer << QString().setNum(ERROR);
                    }
                    else
                    {
                        int* roots = p.calculateRoots();
                        if (roots != NULL )
                        {
                            if(roots[0]==roots[1])
                            {
                                s << QString().setNum(1);
                                s << QString::number(roots[0]);
                            }
                            else
                            {
                                s << QString().setNum(2);
                                s << QString::number (roots[0]) << QString::number (roots[1]);
                            }
                        }
                        else
                            s << QString().setNum(0);
                        free (roots);
                        answer << QString().setNum(ROOT_ANSWER);
                    }

                answer += s;
                break;
            }
            default:
                break;
            }
    }
    std::cout<<answer.toStdString()<<"\n";
    comm->send(QByteArray().append(answer));
    }
