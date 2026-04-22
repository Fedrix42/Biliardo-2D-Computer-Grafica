#include "utils.h"
#include <cmath>

int compute_relative_speed(float speed, unsigned window_height){
    return static_cast<int>(std::round(window_height * speed));
}