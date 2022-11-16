#pragma once
#define _USE_MATH_DEFINES

#include "Core/Pixel.h"
#include <cmath>
#include <limits>

typedef unsigned char u_char;

//tweak the below bilateral filtering parameters
const float SIGMA_S = 10.0f, SIGMA_C = 50.0f;

float d_s(Pixel, Pixel);

float w_s(float);

float d_c(u_char, u_char);

float w_c(float);

bool are_equal(float, float);
