#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QFileDialog>
#include "imageprocess.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool loadImage(Mat *dstMat,QImage *dstImage);

private slots:
    void on_btn_loadImage_clicked();

private:
    Ui::MainWindow *ui;
    Mat m_Image;

};

#endif // MAINWINDOW_H
