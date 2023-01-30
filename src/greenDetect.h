#ifndef _GREEN_DETECT_H_
#define _GREEN_DETECT_H_

#include <stdint.h>

namespace greenDetect
{
    int detect(const uint8_t *src, uint32_t w, uint32_t h, int type);
}

#endif