#ifndef MW_H
#define MW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MW; }
QT_END_NAMESPACE

class MW : public QMainWindow
{
    Q_OBJECT

public:
    MW(QWidget *parent = nullptr);
    ~MW();

private slots:
    void on_actionOpen_triggered();

private:
    Ui::MW *ui;
    QString currentFile = "";
};
#endif // MW_H
