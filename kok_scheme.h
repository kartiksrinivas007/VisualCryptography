#pragma once
#include"Image.h"
#include<string>
#include"supporting_functions.h"
using namespace std;


void make_shares_kok(Image& image, std::vector<Image>& shares, int image_width, int image_height, int zoom, int n);
void subroutine_encode_kok(int x, int y, std::vector<Image>& shares, dim2& S, int  n, int zoom);
void n_combination(std::vector<Image> &shares, Image& comb, int share_width, int share_height);