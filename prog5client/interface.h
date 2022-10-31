#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QHBoxLayout>

class TInterface : public QWidget
{
    Q_OBJECT
    QLabel *name_a, *delimeter_a;
    QLineEdit *a_chi,*a_zm;
    QLabel *name_b, *delimeter_b;
    QLineEdit *b_chi,*b_zm;
    QLabel *name_c, *delimeter_c;
    QLineEdit *c_chi,*c_zm;
    QLabel *name_x, *delimeter_x;
    QLineEdit *x_chi,*x_zm;

    QPushButton *value_btn;
    QPushButton *roots_btn;
    QPushButton *print_classic_btn;
    QPushButton *print_canonic_btn;

    QGroupBox *groupBox;
    QRadioButton *i_mode;
    QRadioButton *c_mode;
    QLabel *output;

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

signals:
    void request(QString);

public slots:
    void answer(QString);
    void createRequest();
};
#endif // TINTERFACE_H
