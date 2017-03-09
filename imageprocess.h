#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include "opencv.hpp"
using namespace cv;

class Imageprocess
{
public:
    Imageprocess();
    static bool filterImage(const Mat &src, Mat *dst, int m_size);
    static bool adjustbrightImage(const Mat &src,Mat *dst,double alphl,double beta);
    static bool findedgeImage(const Mat &src, Mat *dst, int threshold1,int threshold2,int apertureSize);
    static bool findcircle(const Mat &src,Mat *dst);

    Mat m_Image;
    Mat m_Imageuse;
    Mat m_Imagefilter;
    Mat m_Imageadjustbright;
    Mat m_Imagefindedge;
    Mat m_Imagemo;
    Mat m_Imagecircle;

private:

};

#endif // IMAGEPROCESS_H
