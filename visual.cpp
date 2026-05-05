// CRG (CLI Rhythem Game) project

/*  *
    * 此文件进行相应视觉效果的实现
*/



#include "visual.h"


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
    double duration {800} ;//该动画持续的时间
    double pause {3000};
    const int center = MARGIN_L + RAIL_WIDTH * 2 + 2 ;
    const int Y = MARGIN_T + RAIl_HEIGHT +10; 
    const int BORDER_r = MARGIN_L + RAIL_WIDTH * 4 + 4 +30;

    const int bias = -20 ;//斜线相对于中轴偏移的程度
    int endl = center - bias;
    int endr =  center + bias;
    double v = center / duration;
    
    for (int y=1; y<=Y ;y ++){
        double ratio = y/double(Y);
        line left{},right{};
        left.is_left = true; right.is_left = false;
        int x = center - bias + 2*bias*ratio;
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
              int x_pos = l.x - (beat - now)*v;
              for (int x = x_pos - l.len; x <= x_pos ;x++){
                  if (x>=0 && l.y>=0 && x<=BORDER_r && l.y<=Y)
                    drawChar(x , l.y ,chartype , color);
              }
          }
          else{
              int x_pos = l.x + (beat-now)*v;
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
   int eps = 100; //用来纠正程序运行时间的误差

   //打开
   while (true){
      long long now = getNowMs();
      if (now>=endbeat+eps) break;
      clearBuffer();
      for (line& l :LINE){
          if (l.is_left){
              int x_pos = l.x - duration*v +(endbeat - now)*v;
              for (int x = x_pos - l.len; x <=x_pos ;x++){
                  if (x>=0 && l.y>=0 && x<=BORDER_r && l.y<=Y)
                    drawChar(x , l.y ,chartype , color);
              }
          }
          else{
              int x_pos = l.x + duration*v - (endbeat-now)*v;
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


