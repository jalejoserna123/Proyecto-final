#ifndef CONTROL_H
#define CONTROL_H
#define control_acceso "control.txt"

#include <QDialog>
#include <QMainWindow>
#include <fstream>
#include <QFile>
#include "control.h"
#include "singup.h"

namespace Ui {
class Control;
}

class Control : public QDialog
{
    Q_OBJECT

public:
    explicit Control(QWidget *parent = 0);
    ~Control();
    bool s = false;
    void SetS();
    bool GetS() const;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Control *ui;
};

#endif // CONTROL_H
