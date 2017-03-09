#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QRubberBand>
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

    //处理鼠标框选事件
    void creatEventFileter();
    void destroyEventFilter();
    bool eventFilter(QObject *o, QEvent *e);


    bool showImage(const Mat *src, QLabel *lab,QSize m_size);//再label中显示Mat格式存储的的图片
    void on_Trackbar();

private slots:

    void on_btn_loadImage_clicked();

    void on_btn_matImage_clicked(bool checked);

    void on_btn_filterImage_clicked();

    void on_btn_adjustbrightImage_clicked();

private:
    Ui::MainWindow *ui;
    Mat m_Image;
    Imageprocess *m_process;
    bool leftMousePress;//鼠标左键按下标志位
    QPoint origin;    //用户选择的初始坐标和终止坐标
    QPoint termination;
    QRubberBand *rubberBand;    //橡皮筋框

};

#endif // MAINWINDOW_H
