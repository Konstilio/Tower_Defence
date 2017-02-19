#include "resultinfodialog.h"
#include "ui_resultinfodialog.h"

ResultInfoDialog::ResultInfoDialog(EStyle Style, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultInfoDialog)
{
    ui->setupUi(this);

    if (Style == EStyle_Lost)
    {
        ui->m_HeaderLabel->setText("Sorry!");
        ui->m_BodyLabel->setText("You Lost");
    }
    else
    {
        ui->m_HeaderLabel->setText("Congratulations!");
        ui->m_BodyLabel->setText("You Won");
    }

    setStyleSheet(QString("QLabel {color: %1}").arg(ColorFromStyle(Style).name()));
    connect(ui->mp_OkButton, &QPushButton::clicked, this, &QDialog::accept);
}

ResultInfoDialog::~ResultInfoDialog()
{
    delete ui;
}

QColor ResultInfoDialog::ColorFromStyle(ResultInfoDialog::EStyle Style)
{
    if (Style == EStyle_Lost)
        return QColor(200, 20, 0);
    else
        return QColor(0, 20, 200);
}
