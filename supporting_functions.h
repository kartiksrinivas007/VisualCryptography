#pragma once
#include"Image.h"
#include<vector>
#include<stdlib.h>
#include<string>
#include<iostream>


 typedef std::vector<std::vector<int>> dim2 ;
 typedef std::vector<std::vector<std::vector<int>>>  dim3;
 typedef std::vector<std::string> dim1s;
 


void create_matrices(int k, dim2 & S0, dim2 & S1);
void create_column_indices(int k,dim2  &S);

void generate_permutations(dim2& a, int begin_index, dim3& v, int n, int m);
void generate_permutations_controlled(dim2& a, int begin_index, dim3& v, int n, int m);

void give_random_permutation(dim3& v, int n, int m, dim2 &matrix);
void give_random_permutation_controlled(dim3& v, int n, int m, dim2& matrix);

void swap_column(dim2& a, int i, int j, int n);
void factorial(int n, int& result);
void innerproduct(std::vector<int> J, std::vector<int> X, int& inp);


void generate_paths(dim1s&,int n);
void print_dim2(dim2& a,int n);

void generate_J0(int k, dim2& a);
void generate_J1(int k, dim2& a);
void generate_X(int k, dim2& a);
void generate_S(dim2& S, dim2& J, dim2& X);



