#include "singup.h"
#include "ui_singup.h"

SingUp::SingUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SingUp)
{
    ui->setupUi(this);
}

SingUp::~SingUp()
{
    delete ui;
}

void SingUp::on_pushButton_clicked()
{
    QFile file(control_acceso);

    if(!file.open(QFile::Append | QFile::Text))
    {
        QMessageBox::warning(this,"title","Archivo no se pudo abrir");
    }
    QTextStream out(&file);
    QString a = ui->lineEdit->text();
    QString b = ui->lineEdit_2->text();
    QString c = b + "," + a;
    out << c;
    out << "\n";
    QMessageBox::about(this,"Done","Done!, Now log in.");
    file.flush();
    file.close();
    this->close();
}
