#define _USE_MATH_DEFINES

#include "opencv2/core/utility.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

#include "Core/Pixel.h"
#include "Utility/Utility.h"

using namespace cv;
using namespace std;

static Mat image;
const float SPATIAL_DISTANCE = 10.0;

static void help(const char** argv)
{
    printf("\nSample Bilateral Filtering Implementation\n"
           "Call:\n"
           "    %s [image_name -- Default is greyscale_img.jpg]\n\n", argv[0]);
}
const char* keys = "{help||}{@image |greyscale_img.jpg|input image name}";


//returns the spatial neighborhood of a pixel
//neighbors of a pixel are defined as all pixels which are a specific euclidean distance from
//that pixel
static vector<Pixel> spatial_neighborhood(Pixel v) {
    vector<Pixel> neighbors;

    //consider a probable smaller area based on the spatial distance
    //rather than the entire image
    int x_top_limit = v.getX() - static_cast<int>(ceil(SPATIAL_DISTANCE));
    int x_bottom_limit = v.getX() + static_cast<int>(ceil(SPATIAL_DISTANCE));
    
    int y_top_limit = v.getY() - static_cast<int>(ceil(SPATIAL_DISTANCE));
    int y_bottom_limit = v.getY() + static_cast<int>(ceil(SPATIAL_DISTANCE));
    
    for (int i = max(x_top_limit,0); i < min(x_bottom_limit, image.rows); i++) {
        const uchar* row = image.ptr<uchar>(i);
        for (int j = max(y_top_limit,0); j < min(y_bottom_limit, image.cols); j++) {
            Pixel p(i, j);
            if (!(v.getX() == p.getX() && v.getY() == p.getY()) //exclude the target pixel from its neighbor list
                && (d_s(p, v) < SPATIAL_DISTANCE || are_equal(d_s(p,v), SPATIAL_DISTANCE)))
                neighbors.push_back(p);
        }
    }
    return neighbors;
}

//μ: C^V -> R^V
//the normalization function which returns a normalized value for each pixel
//of the image based on d_s, w_s, d_c, w_c, 
//and N(v) -> spatial neighborhood of the pixel
static float normalization(Pixel v) {

    //find neighbors of a given pixel
    vector<Pixel> neighbors = spatial_neighborhood(v);

    float norm_sum = 0.0f;
    for (Pixel p : neighbors) {
        norm_sum += (w_s(d_s(v, p)) * 
                    w_c(d_c(
                        image.at<uchar>(p.getX(), p.getY()), 
                        image.at<uchar>(v.getX(), v.getY()))
                    ));
    }
    return norm_sum;
}

static void bilateral_filtering(Mat image) {
    //initialize new empty Mat for filtered greyscale image
    Mat filtered_img(image.rows, image.cols, CV_32FC1, Scalar(0));

    for (int i = 0; i < image.rows; i++) {
        const uchar* row = image.ptr<uchar>(i);
        for (int j = 0; j < image.cols; j++) {
            Pixel v(i, j);
            printf("\nProcessing pixel (%d, %d) - Start",i, j);
			vector<Pixel> neighbors = spatial_neighborhood(v);

			float num = 0.0f;
			for (Pixel p : neighbors) {
				num += (w_s(d_s(v, p)) * 
							w_c(d_c(
								image.at<uchar>(p.getX(), p.getY()), 
								image.at<uchar>(v.getX(), v.getY()))
							) * static_cast<int>(image.at<uchar>(p.getX(), p.getY())));
			}
            filtered_img.at<float>(v.getX(), v.getY()) =  (num / normalization(v));
            //filtered_img.at<float>(v.getX(), v.getY()) =  0.0f;
            
            printf("\nProcessing pixel (%d, %d) - End",i, j);
            int val = (int)image.at<uchar>(v.getX(), v.getY());
            printf("\nOriginal Greyscale value for pixel (%d, %d) is %d",i, j, val);
            float val1 = (num / normalization(v));
            printf("\nFiltered Greyscale value for pixel (%d, %d) is %f",i, j, val1);
        }
    }
    cout << "\n\n\n";
    cout << filtered_img;
    imwrite("bilateral_filtered_img.jpg", filtered_img);
}

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

    bilateral_filtering(image);

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