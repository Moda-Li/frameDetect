#ifndef _FRAME_DETECT_H_
#define _FRAME_DETECT_H_

#include <stdint.h>


class frameDetect
{
public:
    enum
    {
        kNoneDetect = 0x00,  //关闭帧检测/检测无异常
        kGreenDetect = 0x01,    //使能绿屏检测
        kBlackDetect = 0x02,    //使能黑屏检测
        kMosaicDetect = 0x04,   //花屏/马赛克检测
    };  //kGreenDetect|kBlackDetect|kMosaicDetect 使能 绿屏, 黑屏, 马赛克 检测


    static void setDetectMode(uint32_t mode);
    static int detect(const uint8_t *src, uint32_t w, uint32_t h, int type);

private:
    frameDetect(/* args */);

private:
    static uint32_t _detectMode;
};

#endif