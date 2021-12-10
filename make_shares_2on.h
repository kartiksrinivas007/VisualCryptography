#pragma once
#include"Image.h"
#include"supporting_functions.h"

void make_shares_2on(Image& image, std::vector<Image>&shares, int image_width , int image_height, int zoom,int n);
void subroutine_encode_2on(int x, int y, std::vector<Image>& shares, dim2 &C, int n,int zoom);
void make_C0_2on(dim2& C, int n);
void make_C1_2on(dim2& C, int n);
