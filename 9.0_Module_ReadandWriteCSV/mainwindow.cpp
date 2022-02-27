#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
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

    connect(ui->actionNew,&QAction::triggered,
            this,&MainWindow::newFile);

    connect(ui->actionSave_2,&QAction::triggered,
            this,&MainWindow::normalSave);

    connect(ui->actionPrint,&QAction::triggered,
            this,&MainWindow::printPreview);




   setcurrentFile("untitled.LTN");

   save = true;
   ui->actionSave_2->setEnabled(!save);
   // File_is_change_init();
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

void MainWindow::newFile()
{
    if(save == true)
    {
        v_x.clear();
        v_y.clear();
        qv_x.clear();
        qv_y.clear();
        ui->plot->addGraph();
        ui->plot->graph(0)->data().data()->clear();
        ui->plot->replot();
        ui->GraphName_line->clear();
        ui->Pressure_line->clear();
        ui->Temp_line->clear();
        setcurrentFile("untitled.LTN");
    }
    else if(save == false)
    {
        saveFile_MessageBox();
        //normalSave();
        v_x.clear();
        v_y.clear();
        qv_x.clear();
        qv_y.clear();
        ui->plot->addGraph();
        ui->plot->graph(0)->data().data()->clear();
        ui->plot->replot();
        ui->GraphName_line->clear();
        ui->Pressure_line->clear();
        ui->Temp_line->clear();
        setcurrentFile("untitled.LTN");
    }
    File_is_change_init();
    save = true;
    ui->actionSave_2->setEnabled(!save);

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
        ui->plot->xAxis->setRange(0,max_x); //max_x คือค่ามากสุดที่แกน x จะโชว์ได้
        ui->plot->yAxis->setRange(0,max_y); //max_ัy คือค่ามากสุดที่แกน y จะโชว์ได้
        for(int i = 0;i<v_x.size();i++)    //ไม่สนใจบรรทัดแรกคือ count = 0
        {
            qv_x.append(v_x.at(i));
            qv_y.append(v_y.at(i));
            ui->plot->graph(0)->setData(qv_x,qv_y);
            ui->plot->replot();
        }

        save = true;
        ui->actionSave_2->setEnabled(!save);
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
    ui->actionSave_2->setEnabled(!save);
    statusBar()->showMessage(tr("File saved"), 2000);
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
    //ui->actionSave_2->setEnabled(!save);
    QString showName = currFile;
    QString star = "*";
    QString title = "LTN - "+ star + showName;
    //if(title == "LTN - *untitled.LTN")
    //{
     //   ui->actionSave_2->setEnabled(!save);
   // }
    setWindowTitle(title);

}

void MainWindow::File_is_change_init()
{
    save = false;
    ui->actionSave_2->setEnabled(!save);
    //QString showName = currFile;
    //QString star = "*";
    QString showName = currFile;
    QString star = "*";
    QString title = "LTN - "+ star + showName;
    setWindowTitle(title);

}

void MainWindow::saveFile_MessageBox()
{
    QMessageBox::StandardButton reply =  QMessageBox::warning(this,"LTN","Do you want to changes to " + currFile,
                         QMessageBox::Yes|QMessageBox::No);
    if(reply ==QMessageBox::Yes)
    {
        normalSave();
        //saveFile_dialog();
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

void MainWindow::normalSave()
{
    if(currFile.isEmpty()||currFile == "*untitled.LTN" || currFile == "untitled.LTN")
    {
        saveFile_dialog();
    }
    else{
        directSave(currFile);
    }
}

void MainWindow::directSave(const QString &fileName)
{
    QString errorMessage;

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QString Graph_Name  = ui->GraphName_line->text();
    QString Pressure = ui->Pressure_line->text();
    QString Temp = ui->Temp_line->text();
    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        //QTextStream out(&file);
        QTextStream out(&file);
        QString newline = "\n";
        out <<Graph_Name<<","<<Pressure<<","<<Temp<<"\n"<<"\n"<<"x,y"; //<<"\n"<<"1,2"<<"\n"<<"2,2"<<"\n"<<"3,9"<<"\n"<<"4,50";
        for (int i = 0;i<300;i++)
        {
                out << newline;
                out << i <<","<<10*i*i;
        }


        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                           .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    } else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                       .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("Application"), errorMessage);

    }

    //setCurrentFile(fileName);
    save = true;
    ui->actionSave_2->setEnabled(!save);
    setcurrentFile(fileName);
    connect(ui->GraphName_line,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change);
    connect(ui->Pressure_line,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change);
    connect(ui->Temp_line,&QLineEdit::textEdited,
            this,&MainWindow::File_is_change);
    statusBar()->showMessage(tr("File saved"), 2000);
    //return true;
}

void MainWindow::printPreview()
{
    QPrinter printer;
    QPrintPreviewDialog previewDialog(&printer, this);
    connect(&previewDialog, SIGNAL(paintRequested(QPrinter*)), SLOT(renderPlot(QPrinter*)));
    previewDialog.exec();
}

void MainWindow::renderPlot(QPrinter *printer)
{
      printer->setPageSize(QPrinter::A4);
      //printer->setOrientation(QPrinter::Landscape);
/*
      QCPPainter painter(printer);
      QRectF pageRect = printer->pageRect(QPrinter::DevicePixel);

      int plotWidth = ui->plot->viewport().width();
      int plotHeight = ui->plot->viewport().height();
      double scale = pageRect.width()/(double)plotWidth;
      qDebug() << plotHeight;
      painter.setMode(QCPPainter::pmVectorized);
      painter.setMode(QCPPainter::pmNoCaching);
      painter.setMode(QCPPainter::pmNonCosmetic); // comment this out if you want cosmetic thin lines (always 1 pixel thick independent of pdf zoom level)

      //const QRect rect = QRect(0, 0, 100, 50);
      //painter.drawText(rect, Qt::AlignCenter, tr("Qt\nProject"));
      painter.scale(scale, scale);
      //painter.drawText(100, 50, 500, 500, Qt::AlignLeft|Qt::AlignBottom, "KOMGRICH TRANGANPAIBOON\n"
                                                                    //     "Pressure");
      //painter.drawImage(QRect(0, plotHeight+100, 500, 500), QImage("C:/Users/KOM/Desktop/kkk.png"));
      //ui->centralwidget->render(&painter); //ใช้ print mainwindow
      //ui->plot->toPainter(&painter, plotWidth, plotHeight);
        m_image = ui->centralwidget->grab();

      m_image.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
      painter.drawPixmap(0,0,m_image);
      painter.end();
*/
      /*TEST2*/
      QCPPainter painter(printer);

      painter.begin(printer);
      painter.setMode(QCPPainter::pmVectorized);
      painter.setMode(QCPPainter::pmNoCaching);
      painter.setMode(QCPPainter::pmNonCosmetic);

      //printer->pageRect().width();
      double xscale = printer->pageRect().width() / double(ui->centralwidget->width());
      double yscale = printer->pageRect().height() / double(ui->centralwidget->height());
      double scale = qMin(xscale, yscale);
      painter.translate(printer->paperRect().center());

      painter.scale(scale, scale);
      painter.translate(-width()/2, -height()/2);
      //ui->centralwidget->render(&painter);
      //ui->centralwidget->grab();
      m_image = ui->centralwidget->grab();
      //painter.drawImage(QRect(0, 100, 500, 500), QImage("C:/Users/KOM/Desktop/kkk.png"));
      m_image.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
      painter.drawPixmap(0,0,m_image);
      //ui->plot->toPainter(&painter, xscale, yscale);
      painter.end();
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




