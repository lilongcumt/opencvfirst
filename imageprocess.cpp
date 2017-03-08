#include "imageprocess.h"

Imageprocess::Imageprocess()
{
    m_Image=Mat::zeros(1,1,CV_8UC1);
}

bool Imageprocess::separateImage(const Mat &src, Mat *dst, Range row, Range col)
{
    if(!src.empty()){
        *dst=src(row,col).clone();
        return true;
    }
    return false;
}

bool Imageprocess::adjustBrightness(const Mat &src, Mat *dst, double alpha, double beta)
{
    if(src.channels()!=1)
    {
        std::cout << "this method only take care of gray value image" << std::endl;
        return false;
    }
    int height=src.rows;
    int width=src.cols;
    dst->create(src.size(),src.type());
    for(int y=0;y<height;++y){
        for(int x=0;x<width;++x){
            dst->at<uchar>(y,x)=saturate_cast<uchar>(alpha*src.at<uchar>(y,x)+beta);
        }
    }
    return true;
}

bool Imageprocess::findEdge(const Mat &src, Mat *dst, int threshold)
{
    if(src.channels()!=1){
        std::cout << "this method only take care of gray value image" << std::endl;
        return false;
    }

    dst->create(src.size(),src.type());
    Mat temp(src.size(),src.type());
    temp=src.clone();

    Canny(temp,*dst,threshold,threshold);

}

bool Imageprocess::morphologyProcess(const Mat &src, Mat *dst, int ksize)
{
    if(src.channels()!=1){
        std::cout << "this method only take care of gray value image" << std::endl;
        return false;
    }
    dst->create(src.size(),src.type());

    Mat element = getStructuringElement(0,Size(ksize,ksize));

    morphologyEx(src,(*dst),MORPH_CLOSE,element);

    return true;
}
