#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMouseEvent>
#include <QFileDialog>
#include <QScreen>
#include <QMessageBox>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化
    rubberBand=nullptr;

    //初始化 图像处理类
    m_process=new Imageprocess;

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_process;
}

void MainWindow::creatEventFileter()
{
    ui->lab_Image->installEventFilter(this);
}

void MainWindow::destroyEventFilter()
{
    ui->lab_Image->removeEventFilter(this);
}

bool MainWindow::showImage(const Mat *srcMat,  QLabel *lab,QSize m_size)
{
    QImage imageShow(srcMat->data,srcMat->cols,srcMat->rows,srcMat->step,QImage::Format_Grayscale8);
    QImage imageScaled=imageShow.scaled(m_size,Qt::KeepAspectRatio);
    lab->setPixmap(QPixmap::fromImage(imageScaled));
    return true;
}

bool MainWindow::eventFilter(QObject *o, QEvent *e)
{
   if(o!=ui->lab_Image)
    {
       return MainWindow::eventFilter(o,e);
    }

   QMouseEvent *mouseEvent=static_cast<QMouseEvent*> (e);
   if((mouseEvent->button()== Qt::LeftButton) &&
           (mouseEvent->type()==QEvent::MouseButtonPress))
    {
        leftMousePress=true;
        origin=mouseEvent->pos();
        if(rubberBand == nullptr)
        {
            rubberBand=new QRubberBand(QRubberBand::Rectangle,ui->lab_Image);
        }
       rubberBand->setGeometry(QRect(origin,QSize()));
       rubberBand->show();
       return true;
    }
   if((mouseEvent->type()==QEvent::MouseMove)&&(leftMousePress))
   {
       if(rubberBand)
       {
           rubberBand->setGeometry(QRect(origin,mouseEvent->pos()).normalized());
       }
       rubberBand->show();
       return true;
   }
   if ((mouseEvent->button() == Qt::LeftButton)
       && (mouseEvent->type() == QEvent::MouseButtonRelease))
   {
       //鼠标标志位弹起
       leftMousePress = false;

       if (rubberBand)
       {
           termination = mouseEvent->pos();
           QRect cursorRect(qMin(origin.x(),termination.x())
                     ,qMin(origin.y(),termination.y())
                     ,qAbs(origin.x()-termination.x())
                     ,qAbs(origin.y()-termination.y()));

           if(cursorRect.width()<2 && cursorRect.height()<2){
               return false;
           }
           //QPixmap tempPixmap = ui->lab_Image->pixmap()->copy(cursorRect);
           //qDebug()<<cursorRect.left()<<cursorRect.top()<<cursorRect.right()<<cursorRect.bottom();

           m_process->m_Image=m_Image.clone();
           m_process->m_Imageuse=m_Image(Rect(cursorRect.left()*8,cursorRect.top()*8,(cursorRect.right()-cursorRect.left())*8,(cursorRect.bottom()-cursorRect.top())*8));

           showImage(&(m_process->m_Imageuse),ui->lab_matImage,QSize(250,250));

           //ui->lab_matImage->setPixmap(tempPixmap);

           rubberBand->hide();
       }

       return true;
   }

   return false;
}


void MainWindow::on_btn_loadImage_clicked()
{
    QString filename=QFileDialog::getOpenFileName(
                this,
                tr("打开图片"),
                "E:/qtcode/picture",
                tr("图片格式(*.jpg *.png *.bmp)")
                );
    if(filename.isEmpty()){
        ui->statusBar->showMessage(tr("错误：打开图片名字为空"));
    }
    if(!m_Image.empty()){
        m_Image.release();
    }
    m_Image=imread(filename.toStdString(),IMREAD_GRAYSCALE);
    if(!m_Image.empty()){
        showImage(&m_Image,ui->lab_Image,QSize(372,496));
    }
}


void MainWindow::on_btn_matImage_clicked(bool checked)
{
    if(checked==true)
    {
        creatEventFileter();
    }
    else
    {
        destroyEventFilter();
    }
}

void MainWindow::on_btn_filterImage_clicked()
{
    int m_size=3;
    m_size=ui->comboBox_filter->currentText().toInt();
    Imageprocess::filterImage(m_process->m_Imageuse,&(m_process->m_Imagefilter),m_size);
    showImage(&(m_process->m_Imagefilter),ui->lab_filterImage,QSize(250,250));
}

void MainWindow::on_btn_adjustbrightImage_clicked()
{
    int alpha=1;
    int beta=0;
    alpha=ui->lineEdit_alpha->text().toDouble();
    beta=ui->lineEdit_beta->text().toDouble();
    Imageprocess::adjustbrightImage(m_process->m_Imagefilter,&(m_process->m_Imageadjustbright),alpha,beta);
    showImage(&(m_process->m_Imageadjustbright),(ui->lab_adjustbrightImage),QSize(250,250));
}

void MainWindow::on_btn_findedgeImage_clicked()
{
    int threshold1=150;
    int threshold2=100;
    int apertureSize=3;
    threshold1=ui->lineEdit_threshold1->text().toInt();
    threshold2=ui->lineEdit_threshold2->text().toInt();
    apertureSize=ui->comboBox_apertureSize->currentText().toInt();

    Imageprocess::findedgeImage(m_process->m_Imagefilter,&(m_process->m_Imagefindedge),threshold1,threshold2,apertureSize);
    showImage(&(m_process->m_Imagefindedge),(ui->lab_findedgeImage),QSize(250,250));
}

void MainWindow::on_btn_matchImage_clicked()
{
    Imageprocess::findcircle(m_process->m_Imagefindedge,&(m_process->m_Imagecircle));
    showImage(&(m_process->m_Imagecircle),(ui->lab_matchImage),QSize(250,250));
}
