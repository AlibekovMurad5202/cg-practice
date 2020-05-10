#ifndef __INCLUDES__H__
#define __INCLUDES__H__

#define _USE_MATH_DEFINES

#define INTENSITY_DOUBLE(color) double(color.red()   * 0.36 \
                                     + color.green() * 0.53 \
                                     + color.blue()  * 0.11);

#define INTENSITY_INT(color) int(color.red()   * 0.36 \
                               + color.green() * 0.53 \
                               + color.blue()  * 0.11);

#define SWAP_DOUBLE(a, b) double swap_double_tmp = a; a = b; b = swap_double_tmp;
#define    SWAP_INT(a, b)    int    swap_int_tmp = a; a = b; b = swap_int_tmp;

#define INFO(text)   std::cout << "[ INFO ]:   " << text << std::endl
#define ERROR(text)  std::cout << "[ ERROR ]:  " << text << std::endl
#define RESULT(text) std::cout << "[ RESULT ]: " << text << std::endl

#include <QImage>
#include <math.h>
#include <iostream>
#include <time.h>
#include "Mask.h"

template <class T> T clamp(T value, T min, T max)
{ return value < min ? min : value > max ? max : value; }

#endif // !__INCLUDES__H__