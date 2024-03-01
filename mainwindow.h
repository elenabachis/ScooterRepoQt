#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableView>
#include <QFileDialog>
#include <ScooterController.h>
#include <QtCore>
#include <QStandardItemModel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;
using namespace domain;
using namespace controller;


class MainWindow : public QMainWindow
{
    Q_OBJECT
    Controller *controller;
    QStandardItemModel *model;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    QString on_idEdit_editingFinished();

    QString on_modelEdit_editingFinished();

    int on_yearEdit_editingFinished();

    int on_monthEdit_editingFinished();

    int on_dayEdit_editingFinished();

    int on_kilometerEdit_editingFinished();

    QString on_addressEdit_editingFinished();


    State on_stateComboBox_currentTextChanged(const QString &arg1);

    State on_stateComboBox_textActivated(const QString &arg1);

    void on_Add_clicked();

    void on_actionOpen_triggered();

    void on_showButton_clicked();

    void on_filterButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
