#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <iostream>
#include <clocale>
#include <fstream>
#include <stdio.h>
#include "GeneratorN.h"
using namespace cv;

Mat MoveDiagonal(Mat img, int numberX, int numberY)
{
    int width = img.cols - numberX;
    int hight = img.rows - numberY;
    Rect roi = Rect(numberX,numberY,width,hight);
    Mat img_roi = img(roi);
    return img_roi;
}

int MetricNumber(Mat Original, Mat Compression)
{
    int number = 0;

    for (int y = 0; y <Original.rows; ++y)
    {


        unsigned char *const scanLine2(Original.ptr<unsigned char>(y));
        unsigned char *const scanLine3(Compression.ptr<unsigned char>(y));
        for (int x = 0; x < Original.cols; ++x)
            {
            if (scanLine2[x] != scanLine3[x])
                {
                    number++;

                }
            }
    }

    return number;
}

int Normalizator(Mat original)
{
   int number = 0;

    for (int y = 0; y <original.rows; ++y)
    {
        unsigned char *const scanLine(original.ptr<unsigned char>(y));

        for (int x = 0; x < original.cols; ++x)
            {
            if (scanLine[x] == 255)
                {
                    number++;

                }
            }
    }

    return number;
}

Mat GreenToGray(Mat img)
{
    vector<Mat> parts;
    split(img, parts);
    return parts[1];//in parts[1] - green part
}

Mat oCanny(Mat img, int lT, int uT, int kS, string savingPath)
{
    Mat gray = GreenToGray(img);
    Mat edges;
    Canny(gray, edges, (double)lT, uT, kS);
    imwrite(savingPath.c_str(), edges);
    gray.release();
    return edges;
}

Mat SavingCompressedImage(Mat original, int rate, string output_dir)
{
    vector<int> p;

    p.push_back(CV_IMWRITE_JPEG_QUALITY);
    p.push_back(rate);

    string savePathOriginalImage = generationFor(output_dir, "compression", rate);

    imwrite(savePathOriginalImage.c_str(), original, p);

    Mat compImg = imread(savePathOriginalImage.c_str(), CV_LOAD_IMAGE_COLOR);

    return compImg;

}
