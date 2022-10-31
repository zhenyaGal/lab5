#include "polinom.h"

TPolinom::TPolinom(number x, number y, number z)
{
    this->printMode = EPrintModeClassic;
    this->a = x;
    this->b = y;
    this->c = z;
}


number TPolinom::value(number x)
{
    return a*x*x+b*x+c;
}
void TPolinom::setPrintMode(EPrintMode m)
{
    printMode = m;
}
number* TPolinom::calculateRoots()
{
    number* roots = (number* ) malloc(sizeof(number)*2);
    *roots=NULL;
    number discriminant = b*b - number(4)*a*c;

    if(discriminant > number(0))
    {
            roots[0] = (-b + sqrt(discriminant)) / (number(2)*a);
            roots[1] = (-b - sqrt(discriminant)) / (number(2)*a);
     }
    else if (discriminant == 0)
    {
        roots[0] = (-b) / (number(2)*a);
        roots[1] = roots[0];
    }
    else
    {

        cout<<"Discriminant < 0";
        free(roots);
        return NULL;
    }

    return roots;

}

QString& operator<< (QString& os,int p)
{
    os += QString:: number (p);
    return os;
}

QString& operator<< (QString& os, TPolinom& p)
{

   if (p.printMode == EPrintModeClassic )
    {
       os += "p(x) = ";
       os << p.a;
       os += "x^2";
        if (p.b>=0)
            os+="+";
        os << p.b;
        os+="*x";
        if (p.c>=0)
            os+="+";
        os<<p.c;
    }
    if (p.printMode == EPrintModeCanonic )
    {
       number* roots=p.calculateRoots();
       if(roots!=NULL)
       {
           if(roots[0]!=roots[1])
           {
               os += "p(x) = ";
               os << p.a;
               os += "(x";
               if (roots[0]<0)
               {
                   os += "+";
                   os << number(-1)*roots[0];

               }
               else
               {
                   os += "-";
                   os << roots[0];
               }
               os += ")(x";
               if (roots[1]<0)
               {
                   os += "+";
                   os << number(-1)*roots[1];
               }
               else
               {
                   os += "-";
                   os << roots[1];
               }
               os += ")";
           }

           else
               os += "Can not output canonical form!\n";

       }
       else
           os += "Can not output canonical form!\n";
       free(roots);
   }   
   return os;

}
