// CRG (CLI Rhythem Game) project

/**
  * 
*/

#include "../header/global.h"

ma_engine engine;
ma_sound sound;


const int MARGIN_L = 20;
const int MARGIN_R = 20;
const int MARGIN_B = 3;
const int MARGIN_T = 3; // 轨道距离边界的left right bottom top 间距
const int RAIL_WIDTH = 6;
const int RAIl_HEIGHT = 20;

double speed = 0.02 ;

bool g_audioInited {false};

char track1 = 'D';
char track2 = 'F';
char track3 = 'J';
char track4 = 'K'; //不可使用小写

int64_t _maxjudge_ = 100 ; //超过此范围的不会被判定
int _critical_pure_ = 20 ;
int _pure_ = 40 ;
int _far_ = 80 ;

int64_t gameStart;

int64_t ChartAudioStart;//记录谱面音乐开始播放的时间，用于对齐谱面
