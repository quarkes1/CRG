// CRG (CLI Rhythem Game) project

/*  *
    * 此文件进行相应视觉效果的实现
*/



#include "../header/visual.h"

inline int round2int(double val) //这个是用来避免后面截断的误差加的
{
    return (val >= 0) ? (int)(val + 0.5) : (int)(val - 0.5);
}

inline void drawInfo()//供gameOpenRender调用,绘制中央的信息
{   
    const double Y = MARGIN_T + RAIl_HEIGHT + 5;
    const int center_x = MARGIN_L + RAIL_WIDTH * 2 + 2 ;
    const int center_y = round2int(Y/2);

    int x_bias = 12;
    int y_bias = 6;
    int start_X = center_x - x_bias;
    int end_X = center_x + x_bias;
    int start_Y = center_y - y_bias;
    int end_Y = center_y + y_bias;

    //清除区域
    for (int x = start_X ; x<= end_X ;x++){
        for (int y = start_Y ;y <end_Y ; y++)
            drawChar(x, y, ' ', White);
    }

}

inline void showScore()//供gameOverRender调用，绘制分数
{   
    WORD color = White;
    const int center_x = MARGIN_L + RAIL_WIDTH * 2 + 2 ;
    const int center_y = round2int((MARGIN_T + RAIl_HEIGHT + 5)/2.0); 
    int x_bias = 10;
    int y_bias = 5;

    int start_x = center_x - x_bias;
    int start_y = center_y - y_bias;
    
    int rank{0};
    if (CHARTINFO.score >= 9900000) rank = 0;
    else if (CHARTINFO.score >= 9800000) rank =1;
    else if (CHARTINFO.score >= 9500000) rank =2;
    else if (CHARTINFO.score >= 9200000) rank =3;
    else if (CHARTINFO.score >= 8900000) rank =4;
    else if (CHARTINFO.score >= 8600000) rank =5;
    else rank =6;


    if (CHARTINFO.tracklost) drawAscii(8 , 2, TL,White);
    else drawAscii(2,2,TC, White);

    switch(rank){
        case 0: drawAscii(start_x,start_y,EXp, color);
        case 1: drawAscii(start_x,start_y,EX, color);
        case 2: drawAscii(start_x,start_y,AA, color);
        case 3: drawAscii(start_x +4,start_y,A, color);
        case 4: drawAscii(start_x +4 ,start_y,B, color);
        case 5: drawAscii(start_x +4 ,start_y,C, color);
        case 6: drawAscii(start_x +4,start_y,D, color);
    }


    int x = center_x -6 ; int y  = MARGIN_T + RAIl_HEIGHT - 3;

    std::stringstream ss0;
    ss0<< CHARTINFO.critical_perfect;
    std::string cp = ss0.str();

    std::stringstream ss1;
    ss1 << std::setw(8) << std::setfill('0') << CHARTINFO.score;
    std::string scre = ss1.str() ;
    const char *score = scre.c_str();

    std::stringstream ss2;
    ss2<< CHARTINFO.perfect;
    std::string p = ss2.str()+ " +" + cp;
    const char *pure = p.c_str();

    std::stringstream ss3;
    ss3<<CHARTINFO._far;
    std::string f= ss3.str();
    const char *_far = f.c_str();

    std::stringstream ss4;
    ss4<<CHARTINFO.miss;
    std::string l = ss4.str();
    const char *lost = l.c_str();


    std::stringstream ss5;
    ss5<<CHARTINFO.maxcombo;
    std::string cmb = ss5.str();
    const char *rec = cmb.c_str();

    drawString(center_x - strlen(score)/2 , y-2 , score ,color );
    drawString(x, y,"Pure",Blue); drawString(x+ 11 , y , pure , White); 
    drawString(x, y+1 ,"Far",Yellow); drawString(x+ 11 , y+1 , _far , White);
    drawString(x, y +2,"Lost",Red); drawString(x+ 11, y+2, lost , White);
    drawString(x, y +3,"Max Recall",White); drawString(x+ 11 , y+3 ,rec , White);

}

inline void lineRender()//供gameOpenRender绘制谱面分割线等
{       
        WORD color = White ;
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

void gameOpenRender()//绘制开始时的效果
{   
    WORD color = White;
    int64_t starttime = getNowMs();
    char chartype {'#'};
    double duration {500} ;//该动画持续的时间
    double pause {2500};
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
    
    const int64_t beat { starttime + duration} ;
    const int64_t endbeat {starttime + duration*2 + pause};


    //合上
    audioInit();
    audioPlay("sound/screenclose.wav");
    while (true){
      int64_t now = getNowMs();
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
      if (now - starttime >= (duration/5) *2)
        drawInfo();
      render();
      Sleep(1);
   }
    Sleep(pause);
    ma_sound_stop(&sound);
    ma_sound_uninit(&sound);

    int64_t t = getNowMs();
    int eps = 500; //用来纠正程序运行时间的误差


   //打开
    audioInit();
    audioPlay("sound/screenopen.wav");
    while (true){
        int64_t now = getNowMs();
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
    ma_sound_stop(&sound);
    ma_sound_uninit(&sound);   
}

void gameOverRender()//绘制结束时的效果
{
     
    WORD color = White;
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
    

    //渲染tracklost / trackcomplete
    audioInit();
    if (CHARTINFO.tracklost) audioPlay("sound/lost.wav");
    else audioPlay("sound/complete.wav");
    int64_t s = getNowMs();
    while (true){  
        int64_t now = getNowMs();
        if (now - s >= 3000)  break;    
        clearBuffer();
        lineRender();
        playInfoRender();
        spEffectRender(getGameTime());

        //drawAscii(2, MARGIN_T + RAIl_HEIGHT/2 , end , White);
        if (now -s >= 200){
            if (CHARTINFO.tracklost) drawAscii (MARGIN_L, MARGIN_T + RAIl_HEIGHT/2 , TL ,White);
            else  drawAscii (MARGIN_L, MARGIN_T + RAIl_HEIGHT/2 , TC ,White);
        }
        render();
        Sleep(1);
    }
    ma_sound_stop(&sound);
    ma_sound_uninit(&sound);

    //合上
    audioInit();
    int64_t starttime = getNowMs();
    const int64_t beat { starttime + duration} ;
    const int64_t endbeat {starttime + duration*2 + pause};
    audioPlay("sound/screenclose.wav");

    while (true){
      int64_t now = getNowMs();
      if (now>=beat) break;
      clearBuffer();
      lineRender();
      playInfoRender();
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
    ma_sound_stop(&sound);
    ma_sound_uninit(&sound);



   int64_t t = getNowMs();
   int eps = 300; //用来纠正程序运行时间的误差

   //打开
    audioInit();
    audioPlay("sound/screenopen.wav");
    while (true){
        int64_t now = getNowMs();
        if (now>=endbeat+eps) break;
        clearBuffer();
        showScore();
        render();
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
    ma_sound_stop(&sound);
    ma_sound_uninit(&sound);


    clearBuffer();

    audioInit();
    if (CHARTINFO.tracklost) audioPlay("sound/tracklost.wav");
    else audioPlay("sound/trackcomplete.wav");

    showScore();
    render();
}
