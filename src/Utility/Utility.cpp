#include "Utility.h"

//ds: V X V -> R+
//returns the euclidean distance between two pixels of the image
float d_s(Pixel v1, Pixel v2) {
    return v1.l2_norm(v2);
}

//ws : R+ -> [0,1]
//decreasing function - returns a value between 0 & 1 which is inversely prop
//to the distance between two pixels
float w_s(float value) {
    double num = exp(-pow(value, 2) / (2 * pow(SIGMA_S, 2)));
    double den = SIGMA_S * sqrt(2 * M_PI);
    return (num / den);
}

//dc : C X C -> R+
//returns the absolute difference of greyscale values of two pixels of the image
float d_c(u_char g1, u_char g2) {
    return static_cast<float>(abs((g1 - g2)));
}

//wc : R+ -> [0,1]
//decreasing function - returns a value between 0 & 1 which is inversely prop
//to the difference in greyscale values of two pixels
float w_c(float value) {
    float den = 1 + pow(value, 2) / pow(SIGMA_C, 2);
    return (1 / den);
}

bool are_equal(float a, float b){
   return (fabs(a-b) < std::numeric_limits<float>::epsilon()); 
}
