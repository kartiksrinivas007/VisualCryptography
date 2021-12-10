
#pragma once
#include"Image.h"
#include"supporting_functions.h"


void make_shares(Image& image, int width, int height, Image& share1, Image& share2);
void subroutine_C0(Image&image, int x, int y, Image&share1, Image&share2);
void subroutine_C1(Image& image, int x, int y, Image& share1, Image& share2);
void make_shares_randomized(Image& image, int width, int height, Image& share1, Image& share2);
void subroutine_encode_randomized(Image& image, int x, int y, Image& share1, Image& share2,dim2 &C0);


//std::vector<std::vector<int>>random_matrix_C0(int m,int n);
//std::vector<std::vector<int>>random_matrix_C1(int m,int n);



