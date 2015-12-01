#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QStandardItemModel>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mModel = new QStandardItemModel(this);

    configuraSpinBox(ui->insertarSpinBox);
    configuraSpinBox(ui->eliminarSpinBox);
    ui->listView->setModel(mModel);
    setWindowTitle("EXCÉNTA EXAMEN");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_preOrdenPushButton_clicked()
{
    display("preorden");
    mAVL.preorden(mAVL.getRaiz(), [&](NodoAVL *nodo) {
        display(QString::number(nodo->getDato()));
    });
}

void MainWindow::on_postOrdenPushButton_clicked()
{
    display("postorden");
    mAVL.postorden(mAVL.getRaiz(), [&](NodoAVL *nodo) {
        display(QString::number(nodo->getDato()));
    });
}

void MainWindow::on_inOrdenPushButton_clicked()
{
    display("inorden");
    mAVL.inorden(mAVL.getRaiz(), [&](NodoAVL *nodo) {
        display(QString::number(nodo->getDato()));
    });
}

void MainWindow::on_insertarPushButton_clicked()
{
    const int dato = ui->insertarSpinBox->value();
    if (existe(dato)) {
        return;
    }
    mAVL.inserta(dato);
    display(QString("Usted insertó: %1").arg(dato));
}

void MainWindow::on_eliminarPushButton_clicked()
{
    const int dato = ui->eliminarSpinBox->value();
    if (!existe(dato)) {
        return;
    }
    mAVL.elimina(dato);
    display(QString("Usted eliminó: %1").arg(dato));
}

void MainWindow::on_vaciarPushButton_clicked()
{
    // vacía el árbol
    QVector<int> contenido;
    mAVL.inorden(mAVL.getRaiz(), [&](NodoAVL *nodo) {
        contenido.append(nodo->getDato());
    });
    for (int ix : contenido) {
        mAVL.elimina(ix);
    }
    on_limpiarPushButton_clicked();
    display("Usted vacío el árbol");
}

void MainWindow::configuraSpinBox(QSpinBox *spinBox) const
{
    spinBox->setMinimum(-INT_MAX);
    spinBox->setMaximum(INT_MAX);
}

void MainWindow::display(const QString &mensaje)
{
    mModel->appendRow(new QStandardItem(mensaje));
}

bool MainWindow::existe(int dato)
{
    QVector<int> contenido;
    mAVL.inorden(mAVL.getRaiz(), [&](NodoAVL *nodo) {
        contenido.append(nodo->getDato());
    });
    for (int ix : contenido) {
        if (ix == dato) {
            return true;
        }
    }
    return false;
}

void MainWindow::on_limpiarPushButton_clicked()
{
    mModel->clear();
}
