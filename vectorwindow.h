#ifndef VECTORWINDOW_H
#define VECTORWINDOW_H

#include <QDialog>
#include "mw.h"

namespace Ui {
class VectorWindow;
}

class VectorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit VectorWindow(QWidget *parent = nullptr);
    ~VectorWindow();
    void setResolution(QString resolution);

private slots:
    void on_color_btn_clicked();

    void on_Inverse_btn_clicked();

private:
    Ui::VectorWindow *ui;
};

#endif // VECTORWINDOW_H
