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
#include <QFileSystemWatcher>
#include <QMessageBox>
#include <QCloseEvent>
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

    void newFile();
    void openFile_dialog();
    void saveFile_dialog();
    void File_is_change();
    void File_is_change_init();
    void saveFile_MessageBox();
    void closeEvent(QCloseEvent *event);
    void normalSave();
    void directSave(const QString &fileName);







private:
    Ui::MainWindow *ui;

    QString str_x[100000];
    QString str_y[100000];
    QVector<double> v_x;
    QVector<double> v_y;

    QVector<double> qv_x,qv_y;

    void setcurrentFile(const QString &fileName);
    QString currFile;

    QFileSystemWatcher watcher;

    bool save;

};
#endif // MAINWINDOW_H
