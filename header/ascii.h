#pragma once

#include "mainf.h"
#include "global.h"
#include "visual.h"  
#include <string>
#include <vector>

void drawAscii(int _start_x , int _start_y , const std::vector<std::string>& _asc , WORD _color );

extern const std::vector<std::string> EXp;
extern const std::vector<std::string> EX ;
extern const std::vector<std::string> AA ;
extern const std::vector<std::string> A ;
extern const std::vector<std::string> D ;
extern const std::vector<std::string> B ;
extern const std::vector<std::string> C ;
extern const std::vector<std::string> TL ;
extern const std::vector<std::string> TC;
extern const std::vector<std::string> PAUSED;
extern const std::vector<std::string> Three ;
extern const std::vector<std::string> Two;
extern const std::vector<std::string> One;
extern const std::vector<std::string> end;
extern const std::vector<std::string> logo;
extern const std::vector<std::string> st1;
extern const std::vector<std::string> st2;
extern const std::vector<std::string> st3;