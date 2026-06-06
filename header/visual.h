// CRG (CLI Rhythem Game) project

/**
  * 
*/

#pragma once

#include <vector>
#include <ctime>
#include <windows.h>
#include "global.h"
#include "mainf.h"
#include "ascii.h"

void gameOpenRender();
void gameOverRender();
void normalChangeRender();
void StartRender();
void MenuRender();
void SettingRender();

std::vector<std::string> ChartChoiceRender();