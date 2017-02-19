#ifndef RESULTINFOWIDGET_H
#define RESULTINFOWIDGET_H

#include <QDialog>

namespace Ui {
class ResultInfoDialog;
}

class ResultInfoDialog : public QDialog
{
    Q_OBJECT

public:
    enum EStyle
    {
        EStyle_Won
        , EStyle_Lost
    };

    explicit ResultInfoDialog(EStyle Style ,QWidget *parent = 0);
    ~ResultInfoDialog();

private:
    QColor ColorFromStyle(EStyle);
    Ui::ResultInfoDialog *ui;
};

#endif // RESULTINFOWIDGET_H
