#pragma once

#include "mainf.h"  
#include <string>
#include <vector>

void drawAscii(int _start_x = 10, int _start_y = 5, const std::vector<std::string> _asc , WORD _color = White);

extern const std::vector<std::string> EXp;
extern const std::vector<std::string> EX ;
extern const std::vector<std::string> AA ;
extern const std::vector<std::string> A ;
extern const std::vector<std::string> D ;
extern const std::vector<std::string> B ;
extern const std::vector<std::string> C ;