// CRG (CLI Rhythem Game) project

/*  *
    * 此文件进行相应视觉效果的实现
*/



#include "visual.h"

inline int round2int(double val) //这个是用来避免后面截断的误差加的
{
    return (val >= 0) ? (int)(val + 0.5) : (int)(val - 0.5);
}

inline void lineRender()
{       
        WORD color = Green ;
        int BORDER= MARGIN_L + RAIL_WIDTH*4 + 4 ;
        for (int x = MARGIN_L; x <= BORDER; x ++) drawChar(x , MARGIN_T -1 , '-',color);
        for (int x = MARGIN_L; x <= BORDER; x += (RAIL_WIDTH + 1)) {
            for (int y = MARGIN_T; y < MARGIN_T + RAIl_HEIGHT; y++) {
                drawChar(x, y,'|',color);
            }
        }
        for (int x = MARGIN_L; x <= BORDER; x ++) drawChar(x , MARGIN_T + RAIl_HEIGHT , '=',color);//判定线
        for (int x = MARGIN_L; x <= BORDER; x += (RAIL_WIDTH + 1)) {
            for (int y = MARGIN_T; y < MARGIN_T + RAIl_HEIGHT+2; y++) {
                drawChar(x, y,'|',color);
            }
        }
        for (int x = MARGIN_L; x <= BORDER; x ++) drawChar(x , MARGIN_T + RAIl_HEIGHT+2 , '-',color);
}

struct line
{
    int len{100}; //此处给出很大的值，到时超出部分不画就是了
    bool is_left{};
    int y{};
    int x{};//此处若为左边的记右端，右边的记左端
};

std::vector<line>LINE{};

void ArcOpenRender()//绘制开始和结束时的效果
{   
    WORD color = White;
    long long starttime = getNowMs();
    char chartype {'#'};
    double duration {500} ;//该动画持续的时间
    double pause {3000};
    const int center = MARGIN_L + RAIL_WIDTH * 2 + 2 ;
    const double Y = MARGIN_T + RAIl_HEIGHT + 5; 
    const int BORDER_r = MARGIN_L + RAIL_WIDTH * 4 + 4 +35;

    const int bias = 30 ;
    const int subbias = 20 ; //转角偏移的程度
    int c_X = center+bias ; //转角的x 坐标
    int c_Y = (Y/5)*3 ; //转角的y 坐标

    double v = center / duration;
    
    for (int y=1; y<c_Y ;y ++){
        double ratio = 1 - y/double(c_Y);
        line left{},right{};
        left.is_left = true; right.is_left = false;
        int x = c_X - round2int( subbias*ratio );
        left.x = x ; right.x = x;
        left.y = y; right.y =y;
        LINE.push_back(left);
        LINE.push_back(right);
    }

    for (int y=c_Y ; y<Y ; y++){
        double ratio = (y-c_Y)/double(Y -c_Y);
        line left{},right{};
        left.is_left = true; right.is_left = false;
        int x = c_X - round2int( subbias*ratio);
        left.x = x ; right.x = x;
        left.y = y; right.y =y;
        LINE.push_back(left);
        LINE.push_back(right);
    }
    
    const long long beat { starttime + duration} ;
    const long long endbeat {starttime + duration*2 + pause};

    //合上
    while (true){
      long long now = getNowMs();
      if (now>=beat) break;
      clearBuffer();
      for (line& l :LINE){
          if (l.is_left){
              int x_pos = l.x - round2int( (beat - now)* v );
              for (int x = x_pos - l.len; x <= x_pos ;x++){
                  if (x>=0 && l.y>=0 && x<=BORDER_r && l.y<=Y)
                    drawChar(x , l.y ,chartype , color);
              }
          }
          else{
              int x_pos = l.x + round2int( (beat-now)*v );
              for (int x = x_pos+ l.len ; x>= x_pos ; x--){
                  if (x>=0 && l.y>=0 && x<=BORDER_r && l.y<=Y)
                    drawChar(x , l.y ,chartype , color);
              }
          }        
      }
      render();
      Sleep(1);
   }


   Sleep(pause);

   long long t = getNowMs();
   int eps = 300; //用来纠正程序运行时间的误差

   //打开
   while (true){
      long long now = getNowMs();
      if (now>=endbeat+eps) break;
      clearBuffer();
      lineRender();
      playInfoRender();
      for (line& l :LINE){
          if (l.is_left){
              int x_pos = l.x - round2int( duration*v) + round2int( (endbeat - now)*v );
              for (int x = x_pos - l.len; x <=x_pos ;x++){
                  if (x>=0 && l.y>=0 && x<=BORDER_r && l.y<=Y)
                    drawChar(x , l.y ,chartype , color);
              }
          }
          else{
              int x_pos = l.x + round2int(duration*v) - round2int( (endbeat-now)*v );
              for (int x = x_pos+ l.len ; x>= x_pos ; x--){
                  if (x>=0 && l.y>=0 && x<=BORDER_r && l.y<=Y)
                    drawChar(x , l.y ,chartype , color);
              }
          }        
      }
      render();
      Sleep(1);
   }
  
}


