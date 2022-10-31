#include "interface.h"
//#include "polinom.h"
#include "QString"
#include "common.h"
#include <QHBoxLayout>

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Работа №5");
    setFixedSize(400,340);
    name_a = new QLabel("a =",this);
    name_a->setGeometry(40,20,30,25);
    a_chi = new QLineEdit("1",this);
    a_chi->setGeometry(90,20,50,25);
    delimeter_a = new QLabel("/",this);
    delimeter_a->setGeometry(150,20,30,25);
    a_zm = new QLineEdit("1",this);
    a_zm->setGeometry(165,20,50,25);

    name_b = new QLabel("b =",this);
    name_b->setGeometry(40,50,30,25);
    b_chi = new QLineEdit("1",this);
    b_chi->setGeometry(90,50,50,25);
    delimeter_b = new QLabel("/",this);
    delimeter_b->setGeometry(150,50,30,25);
    b_zm = new QLineEdit("1",this);
    b_zm->setGeometry(165,50,50,25);

    name_c = new QLabel("c =",this);
    name_c->setGeometry(40,80,30,25);
    c_chi = new QLineEdit("1",this);
    c_chi->setGeometry(90,80,50,25);
    delimeter_c = new QLabel("/",this);
    delimeter_c->setGeometry(150,80,30,25);
    c_zm = new QLineEdit("1",this);
    c_zm->setGeometry(165,80,50,25);

    name_x = new QLabel("x =",this);
    name_x->setGeometry(40,110,30,25);
    x_chi = new QLineEdit("1",this);
    x_chi->setGeometry(90,110,50,25);
    delimeter_x = new QLabel("/",this);
    delimeter_x->setGeometry(150,110,30,25);
    x_zm = new QLineEdit("1",this);
    x_zm->setGeometry(165,110,50,25);

    roots_btn = new QPushButton ("roots",this);
    roots_btn->setGeometry(20,150,60,30);
    value_btn = new QPushButton ("value",this);
    value_btn->setGeometry(90,150,60,30);
    print_classic_btn = new QPushButton ("classic",this);
    print_classic_btn->setGeometry(160,150,60,30);
    print_canonic_btn = new QPushButton ("canonic",this);
    print_canonic_btn->setGeometry(230,150,60,30);


    QGroupBox* groupbox = new QGroupBox ("Выберите тип", this);
    groupbox ->move(10,200);
    i_mode = new QRadioButton("целые", this);
    i_mode->setGeometry(10,200,130,25);
    c_mode = new QRadioButton("рациональные", this);
    c_mode->setGeometry(160,200,130,25);
    i_mode->setChecked(true);

    QHBoxLayout* vbox = new QHBoxLayout;
    vbox->addWidget(i_mode);
    vbox->addWidget(c_mode);
    groupbox->setLayout(vbox);
    /*
    i_mode = new QRadioButton("целые", this);
    i_mode->setGeometry(10,200,130,25);
    c_mode = new QRadioButton("рациональные", this);
    c_mode->setGeometry(160,200,130,25);
    i_mode->setChecked(true);
*/
    output = new QLabel(this);
    output->setGeometry(10,240,280,40);

    connect(value_btn,SIGNAL(pressed()),this,SLOT(createRequest()));
    connect(print_classic_btn,SIGNAL(pressed()),this,SLOT(createRequest()));
    connect(print_canonic_btn, SIGNAL(pressed()),this,SLOT(createRequest()));
    connect(roots_btn, SIGNAL(pressed()),this,SLOT(createRequest()));
}

TInterface::~TInterface()
{
    delete name_a;
    delete a_chi;
    delete delimeter_a;
    delete a_zm;

    delete name_b;
    delete b_chi;
    delete delimeter_b;
    delete b_zm;

    delete name_c;
    delete c_chi;
    delete delimeter_c;
    delete c_zm;

    delete name_x;
    delete x_chi;
    delete delimeter_x;
    delete x_zm;

    delete value_btn;
    delete roots_btn;
    delete print_classic_btn;
    delete print_canonic_btn;

    delete i_mode;
    delete c_mode;

    delete output;

}
void TInterface::answer(QString msg)

{
    QString text="";
    int p = msg.indexOf(separator);
    int t = msg.mid(p-1,1).toInt();
    msg = msg.mid(p+1,msg.length()-p-2);
    switch (t)
    {
        case VALUE_ANSWER:
            text = "p(";
            p = msg.indexOf(separator);
            text += msg.left(p);
            text += ") = ";
            text += msg.right(msg.length()-p-1);
            output->setText(text);
            break;
        case ERROR:
            text = msg;
            output->setText(text);
            break;
        case ROOT_ANSWER:
        {
            output->setText("Root answer");
            p = msg.indexOf(separator);
            int k = msg.left(p).toInt();
            if (k==0)
            {
                text += "No solution!";
            }
            if (k==1)
            {
                text += "The equation has an solution:\nx = ";
                text += msg.right(msg.length()-p-1);
            }
            if (k==2)
            {
                text += "\nx1 = ";
                msg = msg.right(msg.length()-p-1);
                p = msg.indexOf(separator);
                text += msg.left(p);
                text += "; x2 = ";
                text += msg.right(msg.length()-p-1);
            }
            output->setText(text);
            break;
        }
        case PRINT_ANSWER:
            text = msg;
            output->setText(text);
            break;
        default:
            break;
        }
}
void TInterface::createRequest()

{
    QString msg;
    if (i_mode->isChecked())
    {
        msg << QString().setNum(I_MODE);
        msg << a_chi->text();
        msg << b_chi->text();
        msg << c_chi->text();
       }
    else
    {
        msg << QString().setNum(C_MODE);
        msg << a_chi->text() << a_zm->text();
        msg << b_chi->text() << b_zm->text();
        msg << c_chi->text() << c_zm->text();
    }
        QPushButton *btn = (QPushButton*)sender();
        if (btn == value_btn)
        {
            msg << QString().setNum(VALUE_REQUEST);
            if (i_mode->isChecked())
                msg << x_chi->text();
            else
                msg << x_chi->text() << x_zm->text();
        }
        if(btn == print_classic_btn)
            msg << QString().setNum(PRINT_CLASSIC_REQUEST);
        if(btn == print_canonic_btn)
            msg << QString().setNum(PRINT_CANONIC_REQUEST);
        if(btn == roots_btn)
            msg << QString().setNum(ROOT_REQUEST);
        emit request(msg);
}
