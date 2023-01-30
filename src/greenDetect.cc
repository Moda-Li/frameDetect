#include <stdio.h>

#include "greenDetect.h"
#include "frameDetect.h"
#include "commonType.h"

namespace greenDetect
{
    static int detectNV12(const uint8_t *src, uint32_t w, uint32_t h)
    {
        int green_point_count = 0;
        uint32_t y_stride = w * h;
        uint32_t uv_h = h >> 1;
        for(uint32_t j = 0; j < uv_h; ++j)
        {
            int uv_stride = y_stride + w * j;
            for (uint32_t i = 0; i < w; i += 2)
            {
                int offset = uv_stride + i;
                const int U = (*(src + offset) - 128);
                const int V = (*(src + offset + 1) - 128);
                
                if (60 + 0.34413 * U + 2.11614 * V < 0 && 60 + 0.71414 * (V - 128) + 2.11613 * (U - 128) < 0)
                {   //is green point
                    ++green_point_count;
                }
            }
        }
        float precnt = (float)green_point_count / (w * h >> 2);
        //printf("---- detectNV12 %d / %d = %f\r\n", green_point_count, w * h >> 2, precnt);
        if(precnt > 0.02)
        {   //is green frame
            return frameDetect::kGreenDetect;
        }
        return frameDetect::kNoneDetect;
    }

    static int detectI420(const uint8_t *src, uint32_t w, uint32_t h)
    {
        int green_point_count = 0;
        uint32_t u_data = w * h;
        uint32_t v_data = w * h + (w * h >> 2);
        uint32_t uv_h = h >> 2;
        for (uint32_t j = 0; j < uv_h; ++j)
        {
            uint32_t stride = w * j;
            for (uint32_t i = 0; i < w; ++i)
            {
                int u_stride = u_data + stride + i;
                int v_stride = v_data + stride + i;
                const int U = (*(src + u_stride) - 128);
                const int V = (*(src + v_stride) - 128);

                if (60 + 0.34413 * U + 2.11614 * V < 0 && 60 + 0.71414 * (V - 128) + 2.11613 * (U - 128) < 0)
                {   //is green point
                    ++green_point_count;
                }
            }
        }
        float precnt = (float)green_point_count / (w * h >> 2);
        //printf("---- detectI420: %d / %d = %f\r\n", green_point_count, w * h >> 2, precnt);
        if(precnt > 0.02)
        {   //is green frame
            return frameDetect::kGreenDetect;
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
            return detectNV12(src, w, h);
        case commonType::kI420 :
            return detectI420(src, w, h);
        case commonType::kI444 :
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