#include <stdio.h>


#include "frameDetect.h"
#include "greenDetect.h"
#include "blackDetect.h"

uint32_t frameDetect::_detectMode = 0;

void frameDetect::setDetectMode(uint32_t mode)
{
    _detectMode = mode;
}

int frameDetect::detect(const uint8_t *src, uint32_t w, uint32_t h, int type)
{   
    int result = 0x00;

    //绿屏检测
    if(_detectMode & kGreenDetect) {
        result |= greenDetect::detect(src, w, h, type);
    }

    //黑屏检测
    if(_detectMode & kBlackDetect) {
        result |= blackDetect::detect(src, w, h, type);
    }

    //马赛克检测
    if(_detectMode & kMosaicDetect) {

    }

    return result;
}

