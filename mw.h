#ifndef MW_H
#define MW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include "secondwindow.h"
#include "mypicture.h"





QT_BEGIN_NAMESPACE
namespace Ui { class MW; }
QT_END_NAMESPACE

class MW : public QMainWindow
{
    Q_OBJECT

public:
    MW(QWidget *parent = nullptr);
    ~MW();
    //static Bitmap*bmp;
    static QString filename;

private slots:
    void on_actionOpen_triggered();

    void on_InverseColors_Btn_clicked();

private:
    Ui::MW *ui;
    QString currentFile = "";
};
#endif  //MW_H
