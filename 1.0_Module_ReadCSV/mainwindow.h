#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVector>
#include <QString>
#include <QTextStream>
#include <sstream>
#include <fstream>
#include <string>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void openFile_dialog();


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QString str_x[100000];
    QString str_y[100000];
    QVector<double> v_x;
    QVector<double> v_y;

    QVector<double> qv_x,qv_y;


};
#endif // MAINWINDOW_H
