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
#include <QMessageBox>
#include <QCloseEvent>
#include <QPrinter>
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

    void newFile();                             //New
    void openFile_dialog();                     // Open
    void saveFile_dialog();                     //Save As..
    void File_is_change();                      //Check ที่ Open มา
    void File_is_change_init();                 // Check ของ Untitle
    void saveFile_MessageBox();                 //หากแก้หรือเพิ่มก็จะถามว่า Save ไหม
    void closeEvent(QCloseEvent *event);        //ฟังก์ชันก่อนปิดโปรแกรม
    void normalSave();                          //Choose Save or Save As
    void directSave(const QString &fileName);   //Save

    void printPreview();                        //Print Preview
    void renderPlot(QPrinter *printer);         //ตัวเพิ่มสิ่งที่จะ Print ในกระดาษ

    void mouseWheel();
    void mousePress();





private:
    Ui::MainWindow *ui;

    QVector<double> v_x;                        //ใช้วาดกราฟ 0
    QVector<double> v_y;                        //ใช้วาดกราฟ 0

    QVector<double> qv_x,qv_y;                  //ใช้วาดกราฟ 0



    void setcurrentFile(const QString &fileName);
    QString currFile;


    bool save;                                  // check save

    QPixmap m_image;                            //ใช้กับ Print

};
#endif // MAINWINDOW_H
