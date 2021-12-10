#include"make_shares_2on.h"

void make_C0_2on(dim2& c, int n)
{
	for (int i = 0;i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == 0)
			{
				c[i][j] = 1;
				continue;
			}
			else c[i][j] = 0;
		}
	}
}
void make_C1_2on(dim2& c, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == i)
			{
				c[i][j] = 1;
				continue;
			}
			else c[i][j] = 0;
		}
	}

}
void subroutine_encode_2on(int x, int y, std::vector<Image>& shares, dim2& C, int  n,int zoom)
{
	//std::cout << "safe inside function";
	for (int i = 0; i < n; i++)
	{
		int colcount = 0;
		for (int j = 0; j < zoom; j++)
		{
			for (int k = 0; k < zoom; k++)
			{
				shares[i].setcolor(color( (float)C[i][colcount], (float)C[i][colcount], (float)C[i][colcount] ), zoom * x + j, zoom * y + k);
				colcount++; //now we have to go to next column in C
			}
		}
	}
}
void make_shares_2on(Image& image, std::vector<Image>& shares, int image_width, int image_height, int zoom,int n)
{
	dim2 C0;
	dim2 C1;
	C0.resize(n, std::vector<int>(n, 0));
	C1.resize(n, std::vector<int>(n, 0));

	make_C0_2on(C0,n);
	make_C1_2on(C1,n);

	print_dim2(C0,n);
	print_dim2(C1,n);
	std::cout << "safe till C0 and C1" << std::endl;

	dim3 T0, T1;

	generate_permutations(C0, 0, T0, n, n);
	generate_permutations(C1, 0, T1, n, n);

	std::cout << "T0 size is = " << T0.size() << std::endl;
	
	//Now just use T0 and T1 to encode the answers
	//find coordinates of each x ,y pixel and how to manipulate them
	for (int y = 0; y < image_height; y++)
	{
		for (int x = 0; x < image_width; x++)
		{
			color c = image.getcolor(x, y);
			if (c.r == 0.0f && c.g == 0.0f && c.b == 0.0f)
			{
				dim2 black;
				give_random_permutation(T1, n, n, black);
				//std::cout << "safe till call of encode subroutine" << std::endl;
				subroutine_encode_2on(x, y, shares, black,n,zoom);
			}
			else
			{
				dim2 white;
				give_random_permutation(T0, n, n, white);
				subroutine_encode_2on(x, y, shares, white,n,zoom);
			}

		}
	}
	std::cout << "SAFE TILL END OF LOOP" << std::endl;
}