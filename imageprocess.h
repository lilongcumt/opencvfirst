#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include "opencv.hpp"
using namespace cv;

class Imageprocess
{
public:
    Imageprocess();
    bool getImage();
    static bool separateImage(const Mat& src, Mat* dst, Range row, Range col);
//    static bool inverseImage(const Mat& src, Mat* dst,bool direction = 0);
//    void mediaBlur(const Mat& src, Mat* dst, int ksize); //opencv自带
    static bool adjustBrightness(const Mat& src, Mat* dst, double alpha = 1.0, double beta = 0.0);//mat coverTo
    static bool findEdge(const Mat& src, Mat* dst, int threshold );
    static bool morphologyProcess(const Mat& src, Mat* dst, int ksize);

private:
    Mat m_Image;
};

#endif // IMAGEPROCESS_H
