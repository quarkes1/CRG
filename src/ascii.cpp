
#include "../header/ascii.h"

const std::vector<std::string> EXp = {
    "oooooooooooo ooooooo  ooooo            ",
    "`888'     `8  `8888    d8'             ",
    " 888            Y888..8P        88     ",
    " 888oooo8        `8888'         88     ",
    " 888            .8PY888.    8888888888 ",
    " 888       o   d8'  `888b       88     ",
    "o888ooooood8 o888o  o88888o     88     "
};

const std::vector<std::string> EX = {
    "oooooooooooo ooooooo  ooooo      ",
    "`888'     `8  `8888    d8'       ",
    " 888            Y888..8P         ",
    " 888oooo8        `8888'          ",
    " 888            .8PY888.         ",
    " 888       o   d8'  `888b        ",
    "o888ooooood8 o888o  o88888o      "
};

const std::vector<std::string> AA = {
    "      .o.             .o.       ",
    "     .888.           .888.      ",
    "    .8 888.         .8 888.     ",
    "   .8' `888.       .8' `888.    ",
    "  .88ooo8888.     .88ooo8888.   ",
    " .8'     `888.   .8'     `888.  ",
    "o88o     o8888o o88o     o8888o "
};

const std::vector<std::string> A = {
    "      .o.        ",
    "     .888.       ",
    "    .8 888.      ",
    "   .8' `888.     ",
    "  .88ooo8888.    ",
    " .8'     `888.   ",
    "o88o     o8888o  "
};

const std::vector<std::string> D = {
    " oooooooooo.    ",
    " `888'   `Y8b   ",
    "  888      888  ",
    "  888      888  ",
    "  888      888  ",
    "  888     d88'  ",
    " o888bood8P'    "
};

const std::vector<std::string> B = {
    " oooooooooo.   ",
    " `888'   `Y8b  ",
    "  888     888  ",
    "  888oooo888'  ",
    "  888    `88b  ",
    "  888    .88P  ",
    " o888bood8P'   "
};

const std::vector<std::string> C = {
    "    .oooooo.   ",
    " `8d8P'  `Y8b  ",
    "  888           ",
    " 888           ",
    " 888           ",
    " `88b    ooo   ",
    "  `Y8bood8P'   "
};

const std::vector<std::string> TL = {
    " ______             __     __            __ ",
    "/_  __/______ _____/ /__  / /  ___  ___ / /_",
    " / / / __/ _ `/ __/  '_/ / /__/ _ \\(_-</ __/",
    "/_/ /_/  \\_,_/\\__/_/\\_\\ /____/\\___/___/\\__/",
    "                                            "
};

const std::vector<std::string> TC = {
    " ______             __     _____                __    __     ",
    "/_  __/______ _____/ /__  / ___/__  __ _  ___  / /__ / /____ ",
    " / / / __/ _ `/ __/  '_/ / /__/ _ \\/  ' \\/ _ \\/ / -_) __/ -_)",
    "/_/ /_/  \\_,_/\\__/_/\\_\\  \\___/\\___/_/_/_/ .__/_/\\__/\\__/\\__/ ",
    "                                       /_/                   "
};

const std::vector<std::string> PAUSED = {
    "    ____                            __",
    "   / __ \\____ ___  __________  ____/ /",
    "  / /_/ / __ `/ / / / ___/ _ \\/ __  / ",
    " / ____/ /_/ / /_/ (__  )  __/ /_/ /  ",
    "/_/    \\__,_/\\__,_/____/\\___/\\__,_/   ",
    "                                      "
};

const std::vector<std::string> Three = {
    "   _____",
    "  |__  /",
    "   /_ < ",
    " ___/ / ",
    "/____/  ",
    "        ",
};

const std::vector<std::string> Two ={
    "   ___ ",
    "  |__ \\",
    "  __/ /",
    " / __/ ",
    "/____/ ",
    "       "
};

const std::vector<std::string> One = {
    "   ___",
    "  <  /",
    "  / / ",
    " / /  ",
    "/_/   ",
    "      "
};

void drawAscii(int _start_x , int _start_y , const std::vector<std::string>& _asc , WORD _color )
{
    for (int y = 0; y < _asc.size(); ++y) {
        const std::string& line = _asc[y];
        
        for (int x = 0; x < line.length(); ++x) {
            
            int abs_x = _start_x + x;
            int abs_y = _start_y + y;
            drawChar(abs_x, abs_y, line[x], _color);
        }
    }
}


/*
int main(){
    init();
    load_chart("test.json");
    gameOverRender();
    Sleep(10000);
}
    */
    