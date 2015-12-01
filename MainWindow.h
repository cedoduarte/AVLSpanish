#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AVL.h"

namespace Ui
{
class MainWindow;
}

class QSpinBox;
class QStandardItemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_preOrdenPushButton_clicked();
    void on_postOrdenPushButton_clicked();
    void on_inOrdenPushButton_clicked();
    void on_insertarPushButton_clicked();
    void on_eliminarPushButton_clicked();
    void on_vaciarPushButton_clicked();
    void on_limpiarPushButton_clicked();
private:
    void configuraSpinBox(QSpinBox *spinBox) const;
    void display(const QString &mensaje);
    bool existe(int dato);

    Ui::MainWindow *ui;
    AVL mAVL;
    QStandardItemModel *mModel;
};

#endif // MAINWINDOW_H
