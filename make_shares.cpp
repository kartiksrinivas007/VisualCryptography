#include"make_shares.h"


/*std::vector<std::vector<int>>random_matrix_C0(int m, int n)
{
	//fill code 
}
std::vector<std::vector<int>>random_matrix_C1(int m, int n)
{
	//fill code
}*/

void subroutine_C0(Image& image, int x, int y, Image& share1, Image& share2)
{
	//generate the matrix randomly(advisable) use that as 'a'
	float a[2][4] = { {0.0,1.0,0.0,1.0},{0.0,1.0,0.0,1.0} };
	//pick colums and fill them up
	share1.setcolor(color(a[0][0], a[0][0], a[0][0]), 2*x, 2*y);
	share1.setcolor(color(a[0][1], a[0][1], a[0][1]), 2 * x + 1, 2 * y);
	share1.setcolor(color(a[0][2], a[0][2], a[0][2]), 2 * x , 2 * y + 1);
	share1.setcolor(color(a[0][3], a[0][3], a[0][3]), 2 * x + 1, 2 * y + 1);

	share2.setcolor(color(a[1][0], a[1][0], a[1][0]), 2 * x, 2 * y);
	share2.setcolor(color(a[1][1], a[1][1], a[1][1]), 2 * x + 1, 2 * y);
	share2.setcolor(color(a[1][2], a[1][2], a[1][2]), 2 * x, 2 * y + 1);
	share2.setcolor(color(a[1][3], a[1][3], a[1][3]), 2 * x + 1, 2 * y + 1);

	
}
void subroutine_encode_randomized(Image& image, int x, int y, Image& share1, Image& share2, dim2& S)
{
	//this will generalize to triple loops! and an array of shares !
	int count = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			share1.setcolor(color( (float)S[0][count], (float)S[0][count], (float)S[0][count] ), 2 * x + i, 2 * y + j);
			count++;
		}
	}
	int count2 = 0;
	for (int i = 0; i< 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			share2.setcolor(color((float)S[1][count2], (float)S[1][count2], (float)S[1][count2]), 2 * x + i, 2 * y + j);
			count2++;
		}
	}


}

void subroutine_C1(Image& image, int x, int y, Image& share1, Image& share2)
{
	//define a get width and get height option in the class image
	//generate the matrix randomly(advisable)
	float a[2][4] = { {0.0,1.0,0.0,1.0},{1.0,0.0,1.0,0.0} };
	//pick colums and fill them up
	share1.setcolor(color(a[0][0], a[0][0], a[0][0]), 2 * x, 2 * y);
	share1.setcolor(color(a[0][1], a[0][1], a[0][1]), 2 * x + 1, 2 * y);
	share1.setcolor(color(a[0][2], a[0][2], a[0][2]), 2 * x, 2 * y + 1);
	share1.setcolor(color(a[0][3], a[0][3], a[0][3]), 2 * x + 1, 2 * y + 1);

	share2.setcolor(color(a[1][0], a[1][0], a[1][0]), 2 * x, 2 * y);
	share2.setcolor(color(a[1][1], a[1][1], a[1][1]), 2 * x + 1, 2 * y);
	share2.setcolor(color(a[1][2], a[1][2], a[1][2]), 2 * x, 2 * y + 1);
	share2.setcolor(color(a[1][3], a[1][3], a[1][3]), 2 * x + 1, 2 * y + 1);
}
void make_shares(Image& image,int width ,int height,Image& share1 ,Image& share2)
{
	//find coordinates of each x ,y pixel and how to manipulate them
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			color c = image.getcolor(x, y);
			if (c.r == 0.0f && c.g == 0.0f && c.b == 0.0f)
			{
				subroutine_C1(image, x, y, share1, share2);
			}
			else
			{
				subroutine_C0(image, x, y, share1, share2);
			}

		}
	}
}
void make_shares_randomized(Image& image, int width, int height, Image& share1, Image& share2)
{
	//precompute C0 and C1 matrices for the problem ..so that computations shouldnt happen from before

	dim2 C0 = { {1,0,0,1},{1,0,0,1} };
	dim2 C1 = { {1,0,1,0},{0,1,0,1} };

	dim3 T0, T1;
	generate_permutations(C0, 0, T0, 2, 4);
	generate_permutations(C1, 0, T1, 2, 4);

	//Now just use T0 and T1 to encode the answers
	//find coordinates of each x ,y pixel and how to manipulate them
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			color c = image.getcolor(x, y);
			if (c.r == 0.0f && c.g == 0.0f && c.b == 0.0f)
			{
				dim2 C0;
				give_random_permutation(T1, 2, 4, C1);
				subroutine_encode_randomized(image, x, y, share1, share2,C1);
			}
			else
			{
				dim2 C1;
				give_random_permutation(T0, 2, 4, C0);
				subroutine_encode_randomized(image, x, y, share1, share2,C0);
			}

		}
	}
	
}