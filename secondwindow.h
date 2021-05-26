#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
//#include "mw.h"

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();
    void setResolution(QString resolution);

private slots:

    void on_Inverse_btn_clicked();

private:
    Ui::SecondWindow *ui;
};

#endif  //SECONDWINDOW_H
