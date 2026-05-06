
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
#include "global.h"
#include "visual.h"
#include "json.hpp"
#include "miniaudio.h"



void judge(long long _time);
void restore_input_echo();
void disable_input_echo();
void clearBuffer();
void drawChar(int _abs_pos_x, int _abs_pos_y, char _char, WORD _color);
void render();
void goto_xy(const int __abs_pos_x,const int __abs_pos_y);
int x_trans(const int __pos_x);
int y_trans(const int __pos_y);
long long time_trans(const int _beatx,const int _beaty , const int _beatz ,int _bpm);
void init();
long long getNowMs();
long long getGameTime();
void load_chart(const std::string& _path);
void drawString(int _abs_pos_x, int _abs_pos_y, const char* _str, WORD _color);
void scoreCal(bool _missed,bool _combo);
void empty(const int _x1,const int _x2 ,const int _y1, const int _y2);
void spEffectRender(long long _time);
void playInfoRender();

void RENDER();
