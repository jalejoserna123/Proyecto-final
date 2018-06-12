#include "control.h"
#include "ui_control.h"
#include "ui_mainwindow.h"

Control::Control(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Control)
{
    ui->setupUi(this);
}

Control::~Control()
{
    delete ui;
}

void Control::on_pushButton_clicked() //para registrarse
{

    QFile file(control_acceso);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning!","File not open");
    }
    QTextStream in(&file);
    QString a = ui->lineEdit->text();
    QString b = ui->lineEdit_2->text();
    QString c = a + "," + b;
    QString text = in.readAll();
    text.remove("\n");
    text.remove("\r");
    if(c==text)
    {
        QMessageBox::about(this,"Done",("Welcome!",a));
        SetS();
    }

    if(c!=text)
        QMessageBox::warning(this,"Warning!","Username or password incorrect.");

    this->close();
}

void Control::SetS()
{
    s = true;
}

bool Control::GetS() const
{
    return s;
}

void Control::on_pushButton_2_clicked()
{
    SingUp *MySingUp = new SingUp(); MySingUp->show();
}
