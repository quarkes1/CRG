// CRG (CLI Rhythem Game) project

/**
  *
  * 此文件提供所有全局变量的api
*/

#pragma once
#pragma execution_character_set("gbk")

#include <windows.h>
#include <cstdint>
#include <cmath>
#include "json.hpp"
#include "mainf.h"


#include "miniaudio.h"



#define Black           0                                       // 纯黑
#define DarkBlue        FOREGROUND_BLUE                        // 深蓝
#define DarkGreen       FOREGROUND_GREEN                       // 深绿
#define DarkCyan        FOREGROUND_GREEN | FOREGROUND_BLUE     // 深青
#define DarkRed         FOREGROUND_RED                         // 深红
#define DarkMagenta     FOREGROUND_RED | FOREGROUND_BLUE       // 深品红
#define DarkYellow      FOREGROUND_RED | FOREGROUND_GREEN      // 深黄
#define DarkGray        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE  // 深灰
#define LightGray       FOREGROUND_INTENSITY                    // 浅灰
#define Blue            FOREGROUND_BLUE | FOREGROUND_INTENSITY  // 亮蓝
#define Green           FOREGROUND_GREEN | FOREGROUND_INTENSITY // 亮绿
#define Cyan            FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY // 亮青
#define Red             FOREGROUND_RED | FOREGROUND_INTENSITY   // 亮红
#define Magenta         FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY // 亮品红
#define Yellow          FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY // 亮黄
#define White           FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY // 纯白


using json = nlohmann::json;

extern ma_engine engine;
extern ma_sound sound;

extern bool g_audioInited;

constexpr int WIDTH = 120;
constexpr int HEIGHT = 40;//整个屏幕的宽高 注意这里设置过大了容易越界导致绘制溢出
extern const int MARGIN_L;
extern const int MARGIN_R ;
extern const int MARGIN_B ;
extern const int MARGIN_T ;
extern const int RAIL_WIDTH ;
extern const int RAIl_HEIGHT;

extern double speed ;
extern bool AUTOPLAY;

extern char track1 ;
extern char track2;
extern char track3 ;
extern char track4 ;
extern int64_t _maxjudge_ ;
extern int _critical_pure_ ;
extern int _pure_ ;
extern int _far_ ;

extern int64_t gameStart;
extern int64_t ChartAudioStart;

struct MouseState
{
    int x = 0;          // 游戏绝对坐标 X（左上0,0）
    int y = 0;          // 游戏绝对坐标 Y
    bool leftDown = false;  // 左键按下
    bool rightDown = false; // 右键按下
    int wheel = 0;      // 滚轮滚动（+上滚 / -下滚）
};

extern MouseState MOUSESTATE;
extern HANDLE hInput;
extern int GAMESTATUS ;
extern int DEFAULT_CHARTINFO_MODEL;
extern double SPEEDFACTOR;
extern double basespeed;

