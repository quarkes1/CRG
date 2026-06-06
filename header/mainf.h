
#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <windows.h>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <random>
#include <cstdint>
#include <filesystem>
#include "global.h"
#include "visual.h"
#include "json.hpp"
#include "ascii.h"
#include "miniaudio.h"

namespace fs = std::filesystem;

void judge(int64_t _time);
void restore_input_echo();
void disable_input_echo();
void clearBuffer();
void drawChar(int _abs_pos_x, int _abs_pos_y, char _char, WORD _color);
void render();
void goto_xy(const int __abs_pos_x,const int __abs_pos_y);
int x_trans(const int __pos_x);
int y_trans(const int __pos_y);
int64_t time_trans(const int _beatx,const int _beaty , const int _beatz ,int _bpm);
void init();
int64_t getNowMs();
int64_t getGameTime();
void load_chart(const std::string& _path);
void drawString(int _abs_pos_x, int _abs_pos_y, const char* _str, WORD _color);
void scoreCal(bool _missed,bool _combo , int _hitTrack);
void empty(const int _x1,const int _x2 ,const int _y1, const int _y2);
void spEffectRender(int64_t _time , bool _openrender );
void playInfoRender();

template<typename T>
T getRandomElem(const std::vector<T>& vec)//用于在vector中随机选元素
{
    if (vec.empty()) {
        // 空容器时返回默认构造的对象，避免崩溃
        static T defaultVal{};
        return defaultVal;
    }
    static std::random_device rd;
    static std::mt19937 gen(rd());
    // 生成 [0, size-1] 随机下标
    std::uniform_int_distribution<> dis(0, (int)vec.size() - 1);
    
    return vec[dis(gen)];
}



void audioInit();
void audioPlay(const char* _audioPath);
void audioPlay(const std::string & _audioPath);

void PLAYRENDER();

void playChart(const std::string& _chartPath,const std::string& _audioPath );
void pauseChart();
void updateMouse();

std::vector<std::string> getFoldersInDir(const std::string& _dirPath) ;
std::vector<std::string> getFilesInDir(const std::string& _dirPath, const std::string& _suffix );

struct chartinfo
{
    std::string title;
    std::string soundtrack; 
    std::string version; 
    std::string artist;
    int maxcount{0};//物量

    int maxcombo{0};
    long int score{0};
    int combo{0};
    int critical_perfect{0};
    int perfect{0};
    int _far{0};
    int miss{0}; 

    int status{0}; //0表示正常播放 1 表示暂停 在经过pauseChart处理后（已改变choice）就会置0；
    int choice{0}; ////1继续 2重来 3退出 （在暂停状态下的行为）

    bool tracklost{false};
    int recall{0}; 
    int model{2}; //设置谱面难度，1为正常，0为简单，2为困难

    float proc{-1};//播放进度(s)
    float total_duration{0};//总时长(s)
};

extern chartinfo CHARTINFO;

struct particle
{
    std::string content;
    int x{0};
    double y{0};
    int len{0};
    int64_t beat;
    bool activ{false};
};

extern std::vector <particle> PARTICLE;

