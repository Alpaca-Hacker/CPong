//
// Created by paul on 14/08/2021.
//

#include "headers/utility.h"

float clampF(const float low, const float num, const float max) {
    if (num > max) {
        return num < low ? low : max;
    } else {
        return num < low ? low : num;
    }
}