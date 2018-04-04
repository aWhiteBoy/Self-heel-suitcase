#ifndef __FUN_H
#define __FUN_H

#include "include.h"

void road_display(void);
int get_rowcenter(unsigned char *ImageData_in);
void get_target(void);
void servo_PID(void);
int max(int x,int y);
int min(int x,int y);
int abs(int x);
#endif
