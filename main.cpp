// CRG (CLI Rhythem Game) project

/**
  * 此项目中的坐标相关设定：
  * 绝对位置以左上为原点，向下，右正向
  * 相对位置以屏幕底端，居中(以设定的WIDTH)为原点，右上正方向
  * 不过很多情况下使用绝对位置更为方便
  *
  * 为区分，进行以下规范：
  * 所有形参以 __val 或 _val 的形式命名
  * 所有容器和常量名使用全大写
*/
#pragma execution_character_set("gbk")

#include "mainf.h"

#define IS_DOWN(key) ((GetAsyncKeyState(key) & 0x8000) != 0)  //用于监听按键信息 ->bool

HANDLE hConsole;
CHAR_INFO buffer[HEIGHT][WIDTH];

class lines//绘制轨道间的分割线和判定线
{
private:
    WORD color = Green ;
    int BORDER= MARGIN_L + RAIL_WIDTH*4 + 4 ;
public:
    void render()
    {   
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
};


struct BPM 
{
    double bpm;
    double count; //用于加载note时的比较；
    bool counted{false};
};

std::vector<BPM> BPMlist;


struct bar_line
{
    long long hitTime;  // 落到判定线的时间（毫秒）
};

std::vector<bar_line> BARLINE;

class bar_lines//绘制小节线
{
private:
    WORD color = White;  
    char chartype = '~';
public:
    void render(long long _now) {
        int BORDER = MARGIN_L + RAIL_WIDTH * 4 + 4;
        int judgeLineY = MARGIN_T + RAIl_HEIGHT; // 判定线Y
        for (auto& bl : BARLINE) {
            int y = judgeLineY - (bl.hitTime - _now) * speed;
            // 只画屏幕内的
            if (y >= MARGIN_T && y <= judgeLineY) {                
                for (int x = MARGIN_L; x <= BORDER; x++) {
                    drawChar(x, y, chartype, color);
                }
            }
        }
    }
};


struct note
{
    int column;
    long long beat;
    long long endbeat;
    int type ; //此处用 0 表示一般的note，1 表示长条
    bool clicked {false};
    bool judged {false};
    int judge{0}; //0 miss; 1 far ; 2 pure ; 3 critical pure
};

std::vector <note> NOTE;

class notes// 绘制note
{
private:
    WORD color = White;  

public:
    void judge_render(int _judge, int _x ,int _y, WORD _purecolor , WORD _farcolor, WORD _misscolor){
        switch (_judge){
                    case 0: drawString(_x, _y, "Miss", _misscolor); break;
                    case 1: drawString(_x, _y, "Far",  _farcolor);  break;
                    case 2: case 3: drawString(_x, _y, "Pure", _purecolor); break;
                }
    }

    void render(long long _now) {
        int judgeLineY = MARGIN_T + RAIl_HEIGHT; // 判定线Y
        for (auto& nt : NOTE) {
            int left = MARGIN_L + RAIL_WIDTH*(nt.column-1) + nt.column;
            int right = MARGIN_L + RAIL_WIDTH*(nt.column) + nt.column-1;
            if (nt.type){ //长条
                int y_bottom = judgeLineY - (nt.beat - _now) * speed;
                int y_top = judgeLineY - (nt.endbeat - _now) * speed;
                bool reached = (y_bottom >= judgeLineY);
                if ((y_bottom >= MARGIN_T && y_bottom <= judgeLineY && !reached))
                {
                    if (y_top< MARGIN_T){
                        for(int y = MARGIN_T ; y <= y_bottom ; y++)
                            for (int x = left ; x <= right ; x++){
                                drawChar(x, y, char('A' + rand() % ('Z' -'A' + 1)) , color);
                            }
                    }
                    else{
                        for(int y = y_top ; y <= y_bottom ; y++)
                            for (int x = left ; x <= right ; x++){
                                drawChar(x, y, char('A' + rand() % ('Z' -'A' + 1)) , color);
                            }
                    }
                }
                else if (reached){
                    if (y_top< MARGIN_T){
                        for(int y = MARGIN_T ; y < judgeLineY ; y++)
                            for (int x = left ; x <= right ; x++){
                                drawChar(x, y, char('A' + rand() % ('Z' -'A' + 1)) , color);
                            }
                    }
                    else{
                        for(int y = y_top ; y < judgeLineY ; y++)
                            for (int x = left ; x <= right ; x++){
                                drawChar(x, y, char('A' + rand() % ('Z' -'A' + 1)) , color);
                            }
                    }
                }
                
                if (nt.judged && _now < (nt.endbeat + _maxjudge_*5) )
                     judge_render(nt.judge, left+1, judgeLineY+5 , Blue,Yellow,Magenta);
                
            }
            else//普通音符
            {
                int y = judgeLineY - (nt.beat - _now) *speed;
                if (y>= MARGIN_T && y <= judgeLineY && !nt.clicked)
                    for (int x =left ; x <=right ;x++) 
                        drawChar(x, y, char('A' + rand() % ('Z' -'A' + 1)) , color);

                if (nt.clicked && abs(_now - nt.beat)<=_maxjudge_*5)
                    judge_render(nt.judge, left+1, judgeLineY+5 , Blue,Yellow,Magenta);
                if ((_now - nt.beat)> _maxjudge_ && (_now - nt.beat) < _maxjudge_*4 && nt.judged && nt.judge ==0)
                    judge_render(nt.judge, left+1, judgeLineY+5 , Blue,Yellow,Magenta);
            }         
        }
    }
};

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

    double proc{0};//进度
};

chartinfo CHARTINFO{};//记录当前谱面的信息，需要结束后清空

struct particle
{
    std::string content;
    int x{0};
    double y{0};
    int len{0};
    long long beat;
    bool activ{false};
};

std::vector <particle> PARTICLE;//记录当前谱面生成的粒子，需要结束时清空

void empty(const int _x1,const int _x2 ,const int _y1, const int _y2)//清空指定区域内可能的特效
{   
    for (int y = _y1; y<=_y2 ; y++)
        for (int x = _x1; x<=_x2;x++)
            drawChar(x,y,' ',White);
}

void playInfoRender()//在轨道右侧指定位置绘制游戏信息
{   
    WORD color = White;
    int BORDER = MARGIN_L + RAIL_WIDTH * 4 + 10;
    int height = 7;
    int width = 40;
    empty(BORDER,BORDER+width, MARGIN_T, MARGIN_T+height);
    
    std::stringstream ss;
    ss << std::setw(9) << std::setfill('0') << CHARTINFO.score;
    std::string scre = ss.str();
    const char *score = scre.c_str();

  
    drawString(BORDER,MARGIN_T+1,score,color);

    
    drawString(BORDER,MARGIN_T+4,CHARTINFO.title.c_str(),color);
    drawString(BORDER,MARGIN_T+6,CHARTINFO.version.c_str(),color);

    drawString(MARGIN_L+ RAIL_WIDTH*2 - 3,MARGIN_T-2,"COMBO",color);
    drawString(MARGIN_L+ RAIL_WIDTH*2 + 3,MARGIN_T-2,std::to_string(CHARTINFO.combo).c_str(),color);

 
}

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

void spEffectRender(long long _time)//绘制轨道两边的下落弹幕效果
{
    WORD color = White;
    int border = MARGIN_L + RAIL_WIDTH * 4 + 4; 
    int border_right = border+30;
    int maxnum = 30 ;
    int maxlen = 20 ;
    int minlen = 10 ;

    int Y = MARGIN_T + RAIl_HEIGHT +3; //粒子最大显示区域
    static std::vector<particle> activeParticle;
    static int remain{0};
    
    
    if (remain < maxnum && !PARTICLE.empty()) {
        int add = maxnum - remain;  
        add = std::min(add, maxnum);
        for(int i = 0 ; i < add ; i++){
            particle pt = getRandomElem(PARTICLE);
            // 过滤空内容的粒子
            if (pt.content.empty()) {
                pt.content = "CRG"; 
            }
            activeParticle.push_back(pt);
            remain++;
        }
    }

    for (auto it = activeParticle.begin(); it != activeParticle.end(); )
    {
        particle &pt = *it;

        if (!pt.activ){

            double t = Y/speed;
            pt.beat = _time + rand() % 3000 + t; 
 
            int contentLen = static_cast<int>(pt.content.length());
            pt.len = std::min(rand()%(maxlen - minlen + 1) + minlen, contentLen);
            if (pt.len < minlen) pt.len = minlen;
            
      
            bool choice = rand()%2;
            if (choice){        
                pt.x = rand() % (MARGIN_L - 3) + 1;
            }
            else{         
                pt.x = rand() % ((border_right) - (border + 3)) + (border + 3);
            }
            // 确保X坐标绝对在屏幕内
            pt.x = std::clamp(pt.x, 0, WIDTH-1);
            pt.activ= true;
        }

        
        double offset = (pt.beat - _time) * speed;
        int y_bottom =  Y - static_cast<int>(offset);
        int y_top = y_bottom - pt.len;
    
        if (y_bottom < 0 || y_top > HEIGHT) {
            it = activeParticle.erase(it); 
            remain--;                      
            continue;                      
        }

        // 绘制粒子内容
        int i = 0;
        for (int y = y_bottom; y >= y_top && y >= 0 && y < HEIGHT ; y--){
            if (i >= static_cast<int>(pt.content.length())) break;
            char ch = pt.content[i++];
            if (pt.x >=0 && pt.x < WIDTH) { // 确保X坐标合法
                drawChar(pt.x, y, ch, color);
            }
        }

        ++it; 
    }   
}

void scoreCal(bool _missed,bool _combo)//更新CHARTINFO的分数
{
    if (_missed) {CHARTINFO.combo = 0 ; return;}
    
    if (_combo) ++CHARTINFO.combo;
    if (CHARTINFO.combo>CHARTINFO.maxcombo) CHARTINFO.maxcombo=CHARTINFO.combo;
    long int total = 100000000;
    double unit;
    if (CHARTINFO.maxcount)unit = total / double(CHARTINFO.maxcount);
        else unit = 1000;
    long int curetscr = unit*CHARTINFO.perfect+ 0.5*unit*CHARTINFO._far + CHARTINFO.critical_perfect;
    
    CHARTINFO.score = curetscr;
}

void judge(long long _time) // 打击判定,记录得分
{   

    WORD color = White;
    int hit_track{-1};
    if (IS_DOWN(track1)) {
        hit_track = 0 ;
        drawChar(MARGIN_L+ hit_track*RAIL_WIDTH+hit_track+2, MARGIN_T + RAIl_HEIGHT+1, track1, color );
    }
    if (IS_DOWN(track2)) {
        hit_track = 1 ;
        drawChar(MARGIN_L+ hit_track*RAIL_WIDTH+hit_track+2, MARGIN_T + RAIl_HEIGHT+1, track2, color );
    }
    if (IS_DOWN(track3)) {
        hit_track = 2 ;
        drawChar(MARGIN_L+ hit_track*RAIL_WIDTH+hit_track+2, MARGIN_T + RAIl_HEIGHT+1, track3, color );
    }
    if (IS_DOWN(track4)) {
        hit_track = 3 ;
        drawChar(MARGIN_L+ hit_track*RAIL_WIDTH+hit_track+2, MARGIN_T + RAIl_HEIGHT+1, track4, color );
    }
    
    bool missed{false};

    bool combo{false};

    for (auto& nt : NOTE){
        if (!nt.type){
            if (nt.column-1 == hit_track){
                long long intvl = abs(_time- nt.beat);
                if ( intvl <= _maxjudge_ && !nt.judged){
                    nt.clicked=true;
                    nt.judged = true ; 
                    combo = true ; 
                    if (intvl <= _critical_pure_) {nt.judge = 3;CHARTINFO.critical_perfect++; CHARTINFO.perfect++;}
                    else if (intvl > _critical_pure_ && intvl <= _pure_){nt.judge = 2;CHARTINFO.perfect++;}
                    else if (intvl > _pure_ && intvl <= _far_){nt.judge = 1;CHARTINFO._far++;}          
                }
            }
            
            //miss
            if (_time-nt.beat>_maxjudge_ && !nt.judged) {
                nt.judged = true ;
                CHARTINFO.miss++;
                missed = true;
            }
        }
        if (nt.type){
            long long b_time = nt.endbeat - _maxjudge_; 
            if (nt.column-1 == hit_track && !nt.judged){
                long long intvl = abs(_time- nt.beat);
                if ( intvl <= _maxjudge_ && !nt.judged){
                    nt.clicked= true;
                    nt.judged = true ; 
                    combo = true ;
                    if (intvl <= _critical_pure_) {nt.judge = 3; CHARTINFO.critical_perfect++; CHARTINFO.perfect++;}
                    else if (intvl > _critical_pure_ && intvl <= _pure_){nt.judge = 2; CHARTINFO.perfect++;}
                    else if (intvl > _pure_ && intvl <= _far_){nt.judge = 1; CHARTINFO._far++;}          
                }
            }
            if (nt.judged && _time <= b_time && hit_track== -1 ){ //长条松手判定
                nt.judge = 0 ;
                CHARTINFO.miss++;
                missed = true ; 
            }         
            if (_time-nt.beat>_maxjudge_ && !nt.judged) {nt.judged = true ; missed = true ;CHARTINFO.miss++;}
        }     
    }
    scoreCal(missed,combo);
}

void disable_input_echo() //关闭输入回显
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    // 去掉 回显 + 行缓冲（按回车才读）
    mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
    SetConsoleMode(hInput, mode);
}

void restore_input_echo() //开启输入回显
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    mode |= (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
    SetConsoleMode(hInput, mode);
}

void clearBuffer() //清空屏幕缓冲区
{
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            buffer[y][x].Char.AsciiChar = ' ';
            buffer[y][x].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        }
    }
}

void drawChar(int _abs_pos_x, int _abs_pos_y, char _char, WORD _color) //在缓冲区绘制字符
{
    
    if (_abs_pos_x >= 0 && _abs_pos_x < WIDTH && _abs_pos_y >=0 && _abs_pos_y < HEIGHT) {
        buffer[_abs_pos_y][_abs_pos_x].Char.AsciiChar = _char;   
        buffer[_abs_pos_y][_abs_pos_x].Attributes = _color;   
    }
}

void drawString(int _abs_pos_x, int _abs_pos_y, const char* _str, WORD _color)//在缓冲区绘制字符串
{
    int x = _abs_pos_x;

    while (*_str != '\0')
    {
        if (x >= 0 && x < WIDTH && _abs_pos_y >= 0 && _abs_pos_y < HEIGHT)
        {
            buffer[_abs_pos_y][x].Char.AsciiChar = *_str;
            buffer[_abs_pos_y][x].Attributes = _color;
        }
        x++;
        _str++;
    }
}

void render() //将缓冲区的图像渲染至控制台
{
    COORD bufferSize = { WIDTH, HEIGHT };
    COORD bufferCoord = { 0, 0 };
    SMALL_RECT writeRegion = { 0, 0, WIDTH-1, HEIGHT-1 };

    WriteConsoleOutput(
        hConsole,
        (CHAR_INFO*)buffer,
        bufferSize,
        bufferCoord,
        &writeRegion
    );
}

void goto_xy(const int __abs_pos_x,const int __abs_pos_y)//移动输出光标->(__abs_pos_x,__abs_pos_y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = __abs_pos_x;   // 列
    pos.Y = __abs_pos_y;   // 行
    SetConsoleCursorPosition(hConsole, pos);
}

int x_trans(const int __pos_x)//x 的相对坐标->绝对坐标
{
    int _center = WIDTH / 2;
    int __abs_pos_x = __pos_x + _center;
    return __abs_pos_x;
}

int y_trans(const int __pos_y)//y 的相对坐标->绝对坐标
{
    int __abs_pos_y = HEIGHT - __pos_y  - 1 ;
    return __abs_pos_y;
}

long long getNowMs() //获取当前的时间
{
    return GetTickCount64();
}

long long getGameTime() //获取相对于开始的时间
{
    return getNowMs() - gameStart;
}



//=================================转谱部分================
/* Malody 的msv json记谱格式为

      "note": [
    { "beat": [0,0,4], "column": 0 },
    { "beat": [0,1,4], "column": 1 },
    { "beat": [0,2,4], "column": 2 },
    { "beat": [0,3,4], "column": 3 }
    其中[x,y,z]表示第x 小节 第 y/z 拍

    "time": [
        {  "beat": [0,0,288],
            "bpm": 203.0
        },
        {
            "beat": [256,0,288],
            "bpm": 203.0
        },]
    记录bpm转变的时间点
*/

long long time_trans(const int _beatx,const int _beaty ,const int _beatz ,int _bpm)//节拍数->绝对ms（从0 开始）
{   
    if (_bpm<= 0) _bpm= 120; //因为load_chart中可能会传入0，进行默认设置
    double bar = (60*1000)/_bpm;
    long long time = static_cast<long long> (_beatx * bar + _beaty*(bar/_beatz));
    return time;
}

void load_chart(const std::string& _path) //加载json谱面-> vector<note>,vector<BPM>,vector<barline>, CHARTINFO,
{   
    BARLINE.clear();
    BPMlist.clear();
    NOTE.clear();
    PARTICLE.clear();

    std::ifstream file(_path);
    if (!file.is_open()) {
        std::cout << "错误：无法打开谱面文件！" << std::endl;
        Sleep(3000);
        return;
    }

    json j;
    file >> j;

    //读取变速信息
    for (auto& note_json :j["time"]){
        auto beat = note_json["beat"];
        BPM b;
        b.bpm = note_json["bpm"].get<double>();;
        int beat_x = beat[0].get<int>();
        int beat_y = beat[1].get<int>();
        int beat_z = beat[2].get<int>();
        b.count = double(beat_x) + double(beat_y) / double(beat_z); //此处记录拍数
        BPMlist.push_back(b);
    }
    std::sort(BPMlist.begin(), BPMlist.end(), [](const BPM& a, const BPM& b) {
    return a.count < b.count;
    });
    
    //读取note
    int notecount = 0 ;
    for (auto& note_json : j["note"]) {

        // 跳过 sound 类型的 note
        if (note_json.contains("sound")) {
            CHARTINFO.soundtrack = note_json["sound"].get<std::string>();
            continue;
        }

        notecount++;
        double bpm {};
        auto beat = note_json["beat"];
        int bx = beat[0].get<int>();
        int by = beat[1].get<int>();
        int bz = beat[2].get<int>();
        double note_beat_count = double(bx) + double(by) / double(bz);

        for (BPM& b : BPMlist){
            if (b.count<= note_beat_count){
                bpm = b.bpm;
            }
            else{break;}
        }
        
        //此处为把 malody 的0- 3 转为 1-4
        int col = note_json["column"].get<int>();
        int column = col + 1;
        
        long long beat_ms = time_trans(bx, by, bz, bpm);

        //长条
        if (note_json.contains("endbeat")) {
            auto endbeat = note_json["endbeat"];
            int ebx = endbeat[0].get<int>();
            int eby = endbeat[1].get<int>();
            int ebz = endbeat[2].get<int>();
            long long end_ms = time_trans(ebx, eby, ebz, bpm);
            NOTE.push_back({column, beat_ms, end_ms, 1});
        } 

        else {
            NOTE.push_back({column,beat_ms, 0, 0});
        }
        
    }
    CHARTINFO.maxcount = notecount;

    //读取谱面信息
    CHARTINFO.title = j["meta"]["song"].contains("title") ? j["meta"]["song"]["title"].get<std::string>() : "未知标题";
    CHARTINFO.artist = j["meta"]["song"].contains("artist") ? j["meta"]["song"]["artist"].get<std::string>() : "未知艺术家";
    CHARTINFO.version = j["meta"].contains("version") ? j["meta"]["version"].get<std::string>() : "1.0";

    for (note &nt : NOTE){
        note *ptr = &nt;
        std::string addr_str = std::to_string(reinterpret_cast<uintptr_t>(ptr));
        particle p{};
        p.content = addr_str;
        PARTICLE.push_back(p);
    }

    if (PARTICLE.empty()) {
    particle p{};
    p.content = "default"; // 避免空字符串
    PARTICLE.push_back(p);
    }
}
//==========================================================================

void init()
{   
    srand(time(NULL));
    SetConsoleOutputCP(65001);
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    disable_input_echo();
    gameStart = getNowMs();
}

/*
void test()//note测试
{
    BARLINE.push_back({500});
    BARLINE.push_back({1500});
    BARLINE.push_back({2500});
    BARLINE.push_back({3000});
    BARLINE.push_back({3500});
    BARLINE.push_back({4000});
    NOTE.push_back({1, 600 , 0 , 0}) ;
    NOTE.push_back({2, 1300 , 0 , 0}) ;
    NOTE.push_back({3, 1400 , 1800 , 1}) ;
    NOTE.push_back({1, 1300 , 0 , 0}) ;
    NOTE.push_back({1, 2500 , 0 , 0}) ;
    NOTE.push_back({2, 3000 , 0 , 0}) ;
    NOTE.push_back({3, 4000 , 4800 , 1}) ;
    NOTE.push_back({1, 5000 , 0 , 0}) ;
    NOTE.push_back({1, 6000, 0 , 0}) ;
    NOTE.push_back({2, 7000 , 0 , 0}) ;
    NOTE.push_back({3, 8000 , 9800 , 1}) ;
    NOTE.push_back({1, 9000 , 0 , 0}) ;
}
*/

void RENDER()//游戏进程中所有过程渲染
{       
        clearBuffer();
        lines line;
        long long now = getGameTime();
        judge(now);
        line.render();
        bar_lines bl;
        bl.render(now);
        notes nt;
        nt.render(now);
        
        spEffectRender(now);
        playInfoRender();

        render();
}

int main(){
    init();
    load_chart("test.json");
    ArcOpenRender();
  
    while (true){
        drawChar(WIDTH-1,HEIGHT-1,'F',White);
        RENDER();
        Sleep(8);
    }
}