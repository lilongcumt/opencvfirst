#include "imageprocess.h"
#include <QDebug>

Imageprocess::Imageprocess()
{

}

bool Imageprocess::filterImage(const Mat &src, Mat *dst,int m_size)
{

    if(src.channels()!=1){
        qDebug()<<"滤波 输入图片不是灰度图片";
        return false;
    }
    //高斯滤波
    //GaussianBlur(src,*dst,Size(m_size,m_size),0,0);

    //中值滤波
    medianBlur(src,*dst,m_size);
    //均值滤波
    //blur(src,*dst,Size(m_size,m_size),Point(-1,-1));

}

bool Imageprocess::adjustbrightImage(const Mat &src, Mat *dst, double alpha, double beta)
{
    if(src.channels()!=1){
        qDebug()<<"调整亮度 输入图片不是灰度图片";
        return false;
    }
    int height = src.rows;
    int width = src.cols;
    dst->create(src.size(),src.type());
    for( int y = 0; y < height; ++y ){
        for( int x = 0; x < width; ++x ){
            dst->at<uchar>(y,x) = saturate_cast<uchar>( alpha*src.at<uchar>(y,x) + beta  );
        }
    }
    return true;
}

bool Imageprocess::findedgeImage(const Mat &src, Mat *dst, int m_size1,int )
{
    if(src.channels()!=1){
        qDebug()<<"寻找边缘 输入图片不是灰度图片";
        return false;
    }


}
