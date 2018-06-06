#include "rules.h"
#include "ui_rules.h"

Rules::Rules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rules)
{
    ui->setupUi(this);
    this->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Rules"));
}

Rules::~Rules()
{
    delete ui;
}
