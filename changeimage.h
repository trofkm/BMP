#ifndef CHANGEIMAGE_H
#define CHANGEIMAGE_H

#include <QDialog>
#include "mw.h"

namespace Ui {
class ChangeImage;
}

class ChangeImage : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeImage(QWidget *parent = nullptr);
    ~ChangeImage();

private slots:
    void on_LeftUp_btn_clicked();

    void on_leftDown_btn_clicked();

    void on_RightUp_btn_clicked();

    void on_RightDown_btn_clicked();

    void on_Center_clicked();

private:
    Ui::ChangeImage *ui;
};

#endif // CHANGEIMAGE_H
