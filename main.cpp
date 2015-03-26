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
#include "AddFunctMat.h"

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


void experimentCutCompress(Mat img, int lT, int uT, int kS, string filename)
{
    ofstream results;
    string dir = "/home/tatyana/codeblocksprojects/sem7_3/res/";
    char* fname = generationForData(dir, filename);
    results.open(fname);
    cout << fname << endl;
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
            //Mat savedFilteredImg;
            //GaussianBlur( savedImg, savedFilteredImg, Size( 3, 3), 0, 0 );
           // string savePathCompressionWithCannyF = generationFor(savePath[number], "cannycompressionf", rate);
            //Mat cannyCF = oCanny(savedFilteredImg, lT, uT, kS, savePathCompressionWithCannyF);
            int difference = MetricNumber(cannyCopy, cannyC);
            //int diff2 = MetricNumber(cannyCopy, cannyCF);
            int normdiff = Normalizator(cannyCopy);
            results << rate << "\t" <<number <<"\t"<<normdiff<<"\t" <<difference<<endl;
            savedImg.release();
            cannyC.release();
            //savedFilteredImg.release();
            //cannyCF.release();
        }
        currentCopy.release();
        cannyCopy.release();
    }
    cannyO.release();
    results.close();
}

void experimentCutCompressFiltered(Mat img, int lT, int uT, int kS, string filename)
{
    cout << "In" << endl;
    ofstream results;
    string dir = "/home/tatyana/codeblocksprojects/sem7_3/res/";
    char* fname = generationForDataF1(dir, filename);
    results.open(fname);
    cout << fname << endl;
    results << lT << "\t " << uT << "\t " << kS << endl;


    string savePathForOriginalWithCanny = generationFor(savePath[0], "cannyoriginal", 0);

    Mat cannyO = oCanny(img, lT, uT, kS, savePathForOriginalWithCanny);
    cout << "In3" << endl;

    for(int number = 1; number <8; ++number)
    {
        Mat currentCopy = MoveDiagonal(img, number, number);
        cout << "In4" << endl;
        string savePathForOriginalWithCannyCopy = generationFor(savePath[0], "cannyoriginalcutted", number);
        Mat cannyCopy = oCanny(currentCopy, lT, uT, kS, savePathForOriginalWithCannyCopy);

        for(int rate = 0; rate < 101; ++rate)
        {

            Mat savedImg = SavingCompressedImage(currentCopy, rate, savePath[number]);
            Mat savedFilteredImg;
            GaussianBlur( savedImg, savedFilteredImg, Size( 3, 3), 0, 0 );
            //blur(savedImg, savedFilteredImg, Size(3,3));
            string savePathCompressionWithCanny = generationFor(savePath[number], "cannycompression", rate);
            Mat cannyC = oCanny(savedFilteredImg, lT, uT, kS, savePathCompressionWithCanny);

            int difference = MetricNumber(cannyCopy, cannyC);

            int normdiff = Normalizator(cannyCopy);

            results << rate << "\t" <<number <<"\t"<<normdiff<<"\t" <<difference<<endl;
            savedImg.release();
            cannyC.release();
            savedFilteredImg.release();
        }
        currentCopy.release();
        cannyCopy.release();
    }
    results.close();
}

int main(int argc, char *argv[])
{
    FILE *file;
	struct mass {
        int can;
		char name[20];

	};
	struct mass listok[10];
	int j=0;
    string names[10];
	file = fopen("/home/tatyana/picturesfortest/t12/list.txt", "r");

	while (fscanf (file, "%d    %s", &(listok[j].can), listok[j].name) != EOF) {
		printf("%d %s\n", listok[j].can, listok[j].name);
		names[j]=listok[j].name;
		j++;
	}
	string dir="/home/tatyana/picturesfortest/t12/";
    for(int i =0; i<10; ++i)
    {
        img = load_image(dir, names[i]);
        int lowThreshold = listok[i].can;
        int upperThreshold = 2*lowThreshold;
        int kernelSize =3;
        //imshow("original", img);
        //Mat gray = GreenToGray(img);
        //imshow("gray", gray);
        experimentCutCompress(img, lowThreshold, upperThreshold, kernelSize, names[i]);
        experimentCutCompressFiltered(img, lowThreshold, upperThreshold, kernelSize, names[i]);
    }

    cout << "Success" << endl;
    waitKey(0);

    return 0;

}



