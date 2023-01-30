
#include <stdio.h>

#include "blackDetect.h"
#include "frameDetect.h"
#include "commonType.h"

namespace blackDetect
{
    static int detectYUV(const uint8_t *src, uint32_t w, uint32_t h)
    {
        int black_point_count = 0;
        for (uint32_t j = 0; j < h; ++j)
        {
            int y_stride = w * j;
            for (uint32_t i = 0; i < w; ++i)
            {
                if (*(src + y_stride + i) < 20)
                {   //is black point
                    ++black_point_count;
                }
            }
        }
        float precnt = (float)black_point_count / (w * h);
        //printf("---- detectYUV %d / %d = %f\r\n", black_point_count, w * h, precnt);
        if (precnt > 0.93)
        {   //is black frame
            return frameDetect::kBlackDetect;
        }
        return frameDetect::kNoneDetect;
    }

    int detect(const uint8_t *src, uint32_t w, uint32_t h, int type)
    {
        //R = Y + 1.402* (V - 128);
        //G = Y - 0.34413 * (U - 128) - 0.71414 * (V - 128);
        //B = Y + 1.772 * (U - 128);
        switch (type)
        {
        case commonType::kNV12 :
        case commonType::kI420 :
        case commonType::kI444 :
            return detectYUV(src, w, h);
        case commonType::kARGB :
        case commonType::kNative :
        case commonType::kDXVA2Surface9 :
        case commonType::kD3D9Surface :
        case commonType::kH264 :
        default:
            break;
        }
        return frameDetect::kNoneDetect;
    }
}