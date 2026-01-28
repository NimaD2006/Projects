#ifndef METHODS_H
#define METHODS_H

#include "structs.h"

#include <string>

void gotoxy(short int, short int);
void LoadLevel(Level);
void StartLevel(Level &);
void RestartLevel(Level &);
void ComputeXY(float &, float &, int, int, float);
void ShowMessage(std::string);

#endif