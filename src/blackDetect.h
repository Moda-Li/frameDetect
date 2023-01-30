#ifndef _BLACK_DETECT_H_
#define _BLACK_DETECT_H_

#include <stdint.h>

namespace blackDetect
{
    int detect(const uint8_t *src, uint32_t w, uint32_t h, int type);
}

#endif