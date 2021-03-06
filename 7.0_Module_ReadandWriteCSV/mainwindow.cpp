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

    connect(ui->actionSave,&QAction::triggered,
            this,&MainWindow::saveFile_dialog);



   setcurrentFile("untitled.LTN");

   save = true;
   connect(ui->GraphName_line,&QLineEdit::textEdited,
           this,&MainWindow::File_is_change_init);
   connect(ui->Pressure_line,&QLineEdit::textEdited,
           this,&MainWindow::File_is_change_init);
   connect(ui->Temp_line,&QLineEdit::textEdited,
           this,&MainWindow::File_is_change_init);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile_dialog()
{
    //QString filter = "Text Files (*.csv)";
    QString filter = "Text Files (*.LTN)";
    QString file_name = QFileDialog::getOpenFileName(this,"Open a file",QDir::homePath(),filter);
    QMessageBox::information(this,"Selected",file_name);


    QFile inputFile(file_name);
    if(inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
         QString Graph_name;
         QString P;
         QString T;
         v_x.clear();
         v_y.clear();
         qv_x.clear();
         qv_y.clear();
         ui->plot->addGraph();
         ui->plot->graph(0)->data().data()->clear();
         ui->plot->replot();
         int count = 0;
        while(!in.atEnd())
        {
            if(count <1)
            {
                QStringList items = in.readLine().split(',');
                Graph_name = items.at(0);
                P = items.at(1);
                T = items.at(2);
            }
            else if(count ==1)
            {
                in.readLine();
            }
            else if(count ==2)
            {
                in.readLine();
            }
            else if(count >2)
            {
                QStringList items = in.readLine().split(',');
                v_x.push_back(items.at(0).toDouble());
                v_y.push_back(items.at(1).toDouble());
            }
            count++;
        }
        inputFile.close();

        setcurrentFile(file_name);

        ui->GraphName_line->setText(Graph_name);
        ui->Pressure_line->setText(P);
        ui->Temp_line->setText(T);

        double max_x = *max_element(v_x.begin(), v_x.end());
        double max_y = *max_element(v_y.begin(), v_y.end());
        ui->plot->xAxis->setRange(0,max_x); //max_x ?????????????????????????????????????????????????????? x ???????????????????????????
        ui->plot->yAxis->setRange(0,max_y); //max_???y ?????????????????????????????????????????????????????? y ???????????????????????????
        for(int i = 0;i<v_x.size();i++)    //????????????????????????????????????????????????????????? count = 0
        {
            qv_x.append(v_x.at(i));
            qv_y.append(v_y.at(i));
            ui->plot->graph(0)->setData(qv_x,qv_y);
            ui->plot->replot();
        }

        save = true;

        connect(ui->GraphName_line,&QLineEdit::textEdited,
                this,&MainWindow::File_is_change);
        connect(ui->Pressure_line,&QLineEdit::textEdited,
                this,&MainWindow::File_is_change);
        connect(ui->Temp_line,&QLineEdit::textEdited,
                this,&MainWindow::File_is_change);
    }

}

void MainWindow::saveFile_dialog()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Test"),"",tr("LABTECHTEST (*.LTN);;All Files (*)"));
    QString Graph_Name  = ui->GraphName_line->text();
    QString Pressure = ui->Pressure_line->text();
    QString Temp = ui->Temp_line->text();
    if(fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::information(this,tr("Unable to open file"),file.errorString());
            return;
        }
        QTextStream out(&file);
        QString newline = "\n";
        out <<Graph_Name<<","<<Pressure<<","<<Temp<<"\n"<<"\n"<<"x,y"; //<<"\n"<<"1,2"<<"\n"<<"2,2"<<"\n"<<"3,9"<<"\n"<<"4,50";
        for (int i = 0;i<300;i++)
        {
                out << newline;
                out << i <<","<<10*i*i;
        }
    }
    save = true;

    setcurrentFile(fileName);
    connect(ui->GraphName_line,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change);
    connect(ui->Pressure_line,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change);
    connect(ui->Temp_line,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change);
}

void MainWindow::File_is_change()
{
    save = false;
    QString showName = currFile;
    QString star = "*";
    QString title = "LTN - "+ star + showName;
    setWindowTitle(title);
}

void MainWindow::File_is_change_init()
{
    save = false;
    //QString showName = currFile;
    //QString star = "*";
    QString title = "LTN - untitled.LTN";
    setWindowTitle(title);
}

void MainWindow::saveFile_MessageBox()
{
    QMessageBox::StandardButton reply =  QMessageBox::warning(this,"LTN","Do you want to changes to " + currFile,
                         QMessageBox::Yes|QMessageBox::No);
    if(reply ==QMessageBox::Yes)
    {
        saveFile_dialog();
    }
    else
    {
        return;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(save == false)
    {
        saveFile_MessageBox();
    }

    event->accept();
}

void MainWindow::setcurrentFile(const QString &fileName)
{
    currFile = fileName;
     //textEdit->document()->setModified(false);
     setWindowModified(false);
     QString showName;
     //QString star = "*";
     if (currFile.isEmpty())
        showName = "untitled.LTN";
     else
        showName = currFile;
     QString title = "LTN - "+ showName;
     setWindowTitle(title);

}




