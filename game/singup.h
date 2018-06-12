#ifndef SINGUP_H
#define SINGUP_H
#define control_acceso "control.txt"

#include <QDialog>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class SingUp;
}

class SingUp : public QDialog
{
    Q_OBJECT

public:
    explicit SingUp(QWidget *parent = 0);
    ~SingUp();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SingUp *ui;
};

#endif // SINGUP_H
