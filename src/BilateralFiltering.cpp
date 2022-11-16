#define _USE_MATH_DEFINES

#include "opencv2/core/utility.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

#include "Core/Pixel.h"

using namespace cv;
using namespace std;

static Mat image;

static void help(const char** argv)
{
    printf("\nSample Bilateral Filtering Implementation\n"
           "Call:\n"
           "    %s [image_name -- Default is greyscale_img.jpg]\n\n", argv[0]);
}
const char* keys = "{help||}{@image |greyscale_img.jpg|input image name}";


int main( int argc, const char** argv )
{
    CommandLineParser parser(argc, argv, keys);
    if (parser.has("help"))
    {
        help(argv);
    }
    string filename = parser.get<string>(0);
    
    //read the greyscale image
    image = imread(filename, IMREAD_GRAYSCALE);
    if(image.empty())
    {
        printf("File: %s not found!\n", filename.c_str());
        help(argv);
        return -1;
    }

    
//    for (int i = 0; i < 4; i++) {
//        const uchar* row = image.ptr<uchar>(i);
//        for (int j = 0; j < 4; j++) {
//            cout << (int)row[j] << "\t";
//        }
//        cout << "\n";
//    }



    waitKey(0);
    return 0;
}