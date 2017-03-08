#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::loadImage(Mat *dstMat, QImage *dstImage)
{
    QString filename=QFileDialog::getOpenFileName(
                this,
                tr("打开图片"),
                "F:/qtcode/picture",
                tr("图片格式(*.png *.jpg *.bmp)")
                );
    if(filename.isEmpty()){
        ui->statusBar->showMessage(QStringLiteral("打开图片名字为空"),2000);
        return false;
    }
    if(!dstMat->empty()){
        dstMat->release();
    }
    *dstMat = imread(filename.toStdString(),IMREAD_GRAYSCALE);
    //解决Qlabel显示OpenCV中Mat图像数据，对齐
    QImage image4show(dstMat->data,dstMat->cols,dstMat->rows,dstMat->step,QImage::Format_Grayscale8);
    *dstImage=image4show;


    namedWindow("first");
    namedWindow("second");
    namedWindow("third");
    namedWindow("fourth");

//    Mat tempImage,tempImage1,tempImage2,tempImage3,tempImage4;

//    medianBlur(m_Image,tempImage,1);

//    Imageprocess::adjustBrightness(m_Image,&tempImage1,2,5);
//    imshow("first",tempImage1);

//    Imageprocess::findEdge(tempImage1,&tempImage2,50);
//    imshow("second",tempImage2);

//    Imageprocess::morphologyProcess(tempImage2,&tempImage3,2);
//    imshow("third",tempImage3);

//    Imageprocess::findEdge(tempImage3,&tempImage4,3);
//    imshow("fourth",tempImage4);


    return true;

}

void MainWindow::on_btn_loadImage_clicked()
{

    QImage image4show;
    if(!loadImage(&m_Image,&image4show)){
        return;
    }
    QImage imageSccled=image4show.scaled(QSize(372,496),Qt::KeepAspectRatio);
    ui->lab_Image->setPixmap(QPixmap::fromImage(imageSccled));
    qDebug()<<m_Image.rows<<m_Image.cols;
}

