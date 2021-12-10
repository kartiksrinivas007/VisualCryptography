#include"supporting_functions.h"


void factorial(int n, int& result)
{
    result = 1;
    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }
    
}
void print_dim2(dim2& a,int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void swap_column(dim2& a, int i, int j, int n)
{

    for (int count = 0; count < n; count++)
    {
        //for debugging print
        int temp;
        temp = a[count][j];
        a[count][j] = a[count][i];
        a[count][i] = temp;
    }
}
void create_matrices(int k, dim2 &S0, dim2 &S1)
{

}

void create_column_indices(int k, dim2 & S)
{

}
void generate_permutations_controlled(dim2& a, int begin_index, dim3& v, int n, int m)
{
    if (begin_index == m)
    {
        std::cout << "values stored till now : " << v.size() << std::endl;
        // std::cout<<"reached value of a"<<std::endl;
            
         //	std::cout<<std::endl;
         //end reached so fill the stuff into vector
        v.push_back(a);
        if(v.size() >= (size_t)36)
        {
            return;
        }
    }

    for (int i = begin_index; i < m; i++)
    {
        swap_column(a, begin_index, i, n);
        if (v.size() <= 36)
        {
            generate_permutations_controlled(a, begin_index + 1, v, n, m);
        }
    }

}
void give_random_permutation_controlled(dim3& v, int n, int m, dim2& matrix)
{
   
    int random = rand() % 36;
    matrix = v[random];
}

void generate_permutations(dim2& a, int begin_index, dim3& v, int n, int m)
{
    if (begin_index == m)
    {
        // std::cout<<"reached value of a"<<std::endl;
            //print(a,n,m);
         //	std::cout<<std::endl;
         //end reached so fill the stuff into vector
        v.push_back(a);
    }

    for (int i = begin_index; i < m; i++)
    {
        swap_column(a, begin_index, i, n);
        generate_permutations(a, begin_index + 1, v, n, m);
    }
}

void give_random_permutation(dim3& v, int n, int m, dim2 &matrix)
{
    int r;
    factorial(m, r);
    int random = rand() % (r);
    matrix = v[random];
}

void generate_paths(dim1s & paths, int n)
{
    for (int i = 0; i < n; i++)
    {
         std::string s2 = std::to_string(i);
         std::string s1 = "share__";
         std::string s3 = ".bmp";

         std::string result = s1 + s2 + s3;
         
         paths.push_back(result);
              
      
    }
    
}
void generate_J0(int k, dim2& a)
{
    for (int i = 0; i < k - 1; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (j == i)
            {
                a[i][j] = 1;
                continue;
            }

            a[i][j] = 0;
        }
    }
    for (int x = 0; x < k - 1; x++)
    {
        a[k - 1][x] = 1;
    }

    a[k - 1][k - 1] = 0;
}
void generate_J1(int k, dim2& a)
{
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (j == i)
            {
                a[i][j] = 1;
                continue;
            }
            a[i][j] = 0;
        }
    }
}
void generate_X(int k, dim2& a)
{
    int n = (int)pow(2, k);
    for (int i = 0; i < n; i++)
    {
        int temp = i;
        for (int j = 0; j < k; j++)
        {
            a[i][j] = temp % 2;
            temp = temp / 2;
        }
    }
}
void innerproduct(std::vector<int> J, std::vector<int> X, int& inp)
{
    inp = 0;
    for (int i = 0; i < (int)J.size(); i++)
    {
        inp = inp + +J[i] * X[i];
    }
    inp = inp % 2;
}
void generate_S(dim2& S, dim2& J, dim2& X)
{
    //inner product to be calculated modulo 2
    for (int i = 0; i < (int)J.size(); i++)
    {
        for (int j = 0; j < (int)X.size(); j++)
        {
            int inp;
            innerproduct(J[i], X[j], inp);
            S[i][j] = inp;
        }
    }
}
