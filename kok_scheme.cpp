#include"kok_scheme.h"
#include"supporting_functions.h"


void subroutine_encode_kok(int x, int y, std::vector<Image>& shares, dim2& S, int  n, int zoom)
{
	//std::cout << "safe inside function";
	for (int i = 0; i < n; i++)
	{
		int colcount = 0;
		for (int j = 0; j < zoom; j++)
		{
			for (int k = 0; k < zoom; k++)
			{
				shares[i].setcolor(color((float)S[i][colcount], (float)S[i][colcount], (float)S[i][colcount]), zoom * x + j, zoom * y + k);
				colcount++; //now we have to go to next column in C
			}
		}
	}
}

void make_shares_kok(Image& image, std::vector<Image>& shares, int image_width, int image_height, int zoom, int n)
{

	int X_size = (int)pow(2, n);
	dim2 J0, J1, X, S0, S1;
	J0.resize(n, vector<int>(n, 0));
	J1.resize(n, vector<int>(n, 0));
	X.resize(X_size, vector<int>(n, 0));
	S0.resize(n, vector<int>(X_size, 0));
	S1.resize(n, vector<int>(X_size, 0));


	generate_J0(n, J0);
	generate_J1(n, J1);
	generate_X(n, X);
	generate_S(S0, J0, X);
	generate_S(S1, J1, X);

	
	
	std::cout << "safe till S0 and S1" << std::endl;

	dim3 T0, T1;

	generate_permutations_controlled(S0, 0, T0, n, X_size);
	generate_permutations_controlled(S1, 0, T1, n, X_size);

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
				give_random_permutation_controlled(T1, n, n, black);
				//std::cout << "safe till call of encode subroutine" << std::endl;
				subroutine_encode_kok(x, y, shares, black, n, zoom);
			}
			else
			{
				dim2 white;
				give_random_permutation_controlled(T0, n, n, white);
				subroutine_encode_kok(x, y, shares, white, n, zoom);
			}

		}
	}
	std::cout << "SAFE TILL END OF LOOP" << std::endl;

}
void n_combination(std::vector<Image>& shares, Image &comb, int share_width, int share_height)
{
	for (int i = 0; i < (int)shares.size()-1; i++)
	{
		comb.combination(shares[i], shares[i + 1],share_width,share_height);
	}
}
