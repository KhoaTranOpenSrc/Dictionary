#include <QCoreApplication>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <QDebug>

using namespace std;
using namespace cv;

void imageLabeling(Mat src);
void getBlackWhiteRatio(Mat src);
void findContours(char* filename);
Mat findBoundary(Mat src);
Mat convertToBW(Mat src);
// 龄龇龈龉龊龋龌龙龚龠
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    convertToBW("E:/TuDienHOA/01_DuLieu/CameraCapture/02_Data/cha_jpg_nonascii_original/临.jpg");
//    imageLabeling("E:/TuDienHOA/01_DuLieu/CameraCapture/02_Data/cha_jpg_nonascii_original/龙.jpg");
//    imageLabeling("E:/Documents/Download/source/opencv-master/samples/data/cards.png");
//    getBlackWhiteRatio("E:/TuDienHOA/01_DuLieu/CameraCapture/02_Data/cha_jpg_nonascii_original/一.jpg");
//    findContours("E:/TuDienHOA/01_DuLieu/CameraCapture/02_Data/cha_jpg_nonascii_original/一.jpg");

    Mat src_image = imread("E:/TuDienHOA/01_DuLieu/CameraCapture/02_Data/cha_jpg_nonascii_original/一.jpg");
    src_image = convertToBW(src_image);
    Mat bw;
    cvtColor(src_image, bw, COLOR_BGR2GRAY);
    //imshow("Black Background Image", bw);

    Mat cropped_image = findBoundary(bw);
    //imshow("Cropped Image", cropped_image);
    qDebug() << "Width: " << cropped_image.cols << " - Height: " << cropped_image.rows;

    // Image labeling
    imageLabeling(cropped_image);

    // Get black white ratio
    getBlackWhiteRatio(cropped_image);

    return a.exec();
}

// This function will set background (black - 0) and object (white - 255)
Mat convertToBW(Mat src)
{
    Mat mask;
    inRange(src, Scalar(200, 200, 200), Scalar(255, 255, 255), mask);
    src.setTo(Scalar(255, 255, 255), mask);

    inRange(src, Scalar(1, 1, 1), Scalar(50, 50, 50), mask);
    src.setTo(Scalar(0, 0, 0), mask);

    inRange(src, Scalar(0, 0, 0), Scalar(0, 0, 0), mask);
    src.setTo(Scalar(128, 128, 128), mask);

    inRange(src, Scalar(255, 255, 255), Scalar(255, 255, 255), mask);
    src.setTo(Scalar(0, 0, 0), mask);

    inRange(src, Scalar(128, 128, 128), Scalar(128, 128, 128), mask);
    src.setTo(Scalar(255, 255, 255), mask);
    return src;
}

// Input is gray image
Mat findBoundary(Mat src)
{
    int left = 0, top = 0, right = 0, bottom = 0;
    for(int i = 0; i < src.rows; i++)
    {
        for(int j=0; j < src.cols; j++)
        {
            if(src.at<uchar>(i,j) == 255)
            {
                if((left == 0) || (left > j)) left = j;
                if((right == 0) || (right < j)) right = j;
                if((top == 0) || (top > i)) top = i;
                if((bottom == 0) || (bottom < i)) bottom = i;
            }
        }
    }
    qDebug() << "Left: " << left << " - Top: " << top << " - Right: " << right << " - Bottom: " << bottom;

    // Crop image
    Mat cropped_image = src(Range(top, bottom), Range(left, right));
    return cropped_image;
}

void findContours(char* filename)
{
    Mat src = imread(filename);
    vector<Vec4i> hierarchy;

    // Create binary image from source image
    Mat bw;
    cvtColor(src, bw, COLOR_BGR2GRAY);
    threshold(bw, bw, 40, 255, THRESH_BINARY | THRESH_OTSU);

    vector<vector<Point> > contours0;
    findContours( bw, contours0, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    qDebug() << "Number of contours: " << contours0.size();
}

void getBlackWhiteRatio(Mat src)
{
    int black=0, white=0;
    for(int i = 0; i < src.rows; i++)
    {
        for(int j=0; j < src.cols; j++)
        {
            int k = src.at<uchar>(i,j);
            if(k == 0)
            {
                black++;
            }
            else
            {
                white++;
            }
        }
    }
    qDebug() << "Black: " << black << " - White: " << white;
}

void imageLabeling(Mat src)
{
//    Mat src = imread(filename);
//    src = convertToBW(src);

    // Show output image
    imshow("Black Background Image", src);
    //! [black_bg]

//    Mat bw1;
//    cvtColor(src, bw1, COLOR_BGR2GRAY);
//    threshold(bw1, bw1, 40, 255, THRESH_BINARY | THRESH_OTSU);

    Mat labelImage, stats, centroids;
    int nLabels = connectedComponentsWithStats(src, labelImage, stats, centroids);
    qDebug() << "Number of Labels: " << nLabels;
}
