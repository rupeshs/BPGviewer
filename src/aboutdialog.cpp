#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QFileInfo>
#include <QDateTime>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    QFileInfo fi(qApp->applicationFilePath());
    QDateTime dt=fi.created();
    ui->labelDate->setText(QString("Build on "+dt.toString()));

}

AboutDialog::~AboutDialog()
{
    delete ui;
}
