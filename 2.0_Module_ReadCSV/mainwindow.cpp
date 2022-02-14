#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen,&QAction::triggered,
            this,&MainWindow::openFile_dialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile_dialog()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open a file",QDir::homePath());
    QMessageBox::information(this,"Selected",file_name);


    QFile inputFile(file_name);
    if(inputFile.open(QIODevice::ReadOnly))
    {
        v_x.clear();
        v_y.clear();
        qv_x.clear();
        qv_y.clear();
        ui->plot->addGraph();
        ui->plot->graph(0)->data().data()->clear();
        ui->plot->replot();
        QTextStream in(&inputFile);
        int count = 0;
        QString x;
        QString y;
        while(!in.atEnd())
        {
            if(count<1)         //ไม่สนใจบรรทัดแรกคือ count = 0
            {
                QString line0 = in.readLine();
            }
            else if(count >= 1) //ไม่สนใจบรรทัดแรกคือ count = 0
            {
                QStringList items = in.readLine().split(',');
                x = items.at(0);    //เอาสิ่งที่อยู่หน้า comma เก็บใน x
                y = items.at(1);    //เอาสิ่งที่อยู่หลัง comma เก็บใน x
                str_x[count] = x;
                str_y[count] = y;
                v_x.push_back(str_x[count].toDouble());
                v_y.push_back(str_y[count].toDouble());
            }
            count++;
        }
        inputFile.close();

        double max_x = *max_element(v_x.begin(), v_x.end());
        double max_y = *max_element(v_y.begin(), v_y.end());

        ui->plot->xAxis->setRange(0,max_x); //max_x คือค่ามากสุดที่แกน x จะโชว์ได้
        ui->plot->yAxis->setRange(0,max_y); //max_ัy คือค่ามากสุดที่แกน y จะโชว์ได้
        for(int i = 1;i<=v_x.size();i++)    //ไม่สนใจบรรทัดแรกคือ count = 0
        {
            qv_x.append(str_x[i].toDouble());
            qv_y.append(str_y[i].toDouble());
            ui->plot->graph(0)->setData(qv_x,qv_y);
            ui->plot->replot();
        }
    }
}


