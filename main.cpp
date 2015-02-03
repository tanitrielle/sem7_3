#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <string>
#include <iostream>
#include <clocale>
#include <fstream>
#include <stdio.h>

#include "load_function.h"
#include "AddFunct.h"
#include "GeneratorN.h"

using namespace cv;
using namespace std;
Mat img;

string savePath[8] = { "/home/tatyana/picturesfortest/resultsOfThirdExperiment1/Original/",
                            "/home/tatyana/picturesfortest/resultsOfThirdExperiment1/1/",
                            "/home/tatyana/picturesfortest/resultsOfThirdExperiment1/2/",
                            "/home/tatyana/picturesfortest/resultsOfThirdExperiment1/3/",
                            "/home/tatyana/picturesfortest/resultsOfThirdExperiment1/4/",
                            "/home/tatyana/picturesfortest/resultsOfThirdExperiment1/5/",
                            "/home/tatyana/picturesfortest/resultsOfThirdExperiment1/6/",
                            "/home/tatyana/picturesfortest/resultsOfThirdExperiment1/7/"};

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

    p[0] = CV_IMWRITE_JPEG_QUALITY;
    p[1] = rate;
    p[2] = 0;


    string savePathOriginalImage = generationFor(output_dir, "compression", rate);

    imwrite(savePathOriginalImage.c_str(), original, p);

    Mat compImg = imread(savePathOriginalImage.c_str(), CV_LOAD_IMAGE_COLOR);
    return compImg;

}

void experimentCutCompress(Mat img, int lT, int uT, int kS)
{
    ofstream results;
    results.open("data.txt");
    results << lT << "\t " << uT << "\t " << kS << endl;
    string savePathForOriginalWithCanny = generationFor(savePath[0], "cannyoriginal", 0);
    Mat cannyO = oCanny(img, lT, uT, kS, savePathForOriginalWithCanny);

    for(int number = 1; number <8; ++number)
    {
        Mat currentCopy = MoveDiagonal(img, number, number);
        string savePathForOriginalWithCannyCopy = generationFor(savePath[0], "cannyoriginalcutted", number);
        Mat cannyCopy = oCanny(currentCopy, lT, uT, kS, savePathForOriginalWithCannyCopy);
        for(int rate = 0; rate < 101; ++rate)
        {
            Mat savedImg = SavingCompressedImage(currentCopy, rate, savePath[number]);
            string savePathCompressionWithCanny = generationFor(savePath[number], "cannycompression", rate);
            Mat cannyC = oCanny(savedImg, lT, uT, kS, savePathCompressionWithCanny);
            int difference = MetricNumber(cannyCopy, cannyC);
            double normdiff = difference/Normalizator(cannyCopy);
            results << rate << "\t" <<number <<"\t"<<normdiff<<endl;
            savedImg.release();
            cannyC.release();
        }
        currentCopy.release();
        cannyCopy.release();
    }
}


int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    cout << "Enter filename" << endl;
    img = load_image("/home/tatyana/picturesfortest/picturesfortests/fromphone/");

    cout<<"Введите нижнюю границу детектора Канни. Диапазон принимаемых значений от 0 до 255"<<endl;
    int lowThreshold = low_threshold();

    cout << "Введите верхнюю границу детектора Канни. Диапазон принимаемых значений от 0 до 255."<<endl;
    int upperThreshold = upper_threshold(lowThreshold);

    cout << "Введите размер ядра детектора Канни. Принимает значения 3, 5, 7"<<endl;
    int kernelSize = kernel_size();
    imshow("original", img);
    cout << img.channels() <<endl;
    Mat gray = GreenToGray(img);
    imshow("gray", gray);
    Mat canny = oCanny(img, lowThreshold, upperThreshold, kernelSize, savePath[0]);
    imshow("canny", canny);
    int norma = Normalizator(canny);
    cout<<norma<<endl;
    experimentCutCompress(img, lowThreshold, upperThreshold, kernelSize);
    waitKey(0);

     return 0;

}



