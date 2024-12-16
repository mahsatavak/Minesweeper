#include "einstellung.h"
#include "ui_einstellung.h"

Einstellung::Einstellung(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Einstellung)
{
    ui->setupUi(this);
}

Einstellung::~Einstellung()
{
    delete ui;
}

int Einstellung::rows() const
{
    return ui->row->value();
}

int Einstellung::cols() const
{
    return ui->col->value();
}

int Einstellung::mines() const
{
    return ui->mine->value();
}

void Einstellung::setRows(int r)
{
    ui->row->setValue(r);
}

void Einstellung::setCols(int c)
{
    ui->col->setValue(c);
}

void Einstellung::setMines(int m)
{
    ui->mine->setValue(m);
}
