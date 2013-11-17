#ifndef LRD_2
#define LRD_2


#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;

char c;
char rgb[3];
char white = 0xFF;
char black = 0x00;
char threshold[3] = { 0x0F, 0x11, 0x11 };
int cnt = 0;
int start;
int filesize;
ifstream mypic;
ofstream myoutpic;

struct pixel_color{
	char r;
	char g;
	char b;
} a_pixel_color, treshold_ref;

void erode_picture();
int erode(int x, int y);
void color_pixel_black();
void color_pixel_white();
int get_pixel_color(struct pixel_color* pixel_rgb, int x, int y);
int size();
int filter();
int filter_struct();




#endif