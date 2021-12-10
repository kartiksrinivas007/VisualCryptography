#include<iostream>
#include<fstream>

int main()
{
	//we need to read a file and make a new one according to some conditions of 4 times the size !
	//ofstream f;
	//ofstream p;
	FILE* f;
	FILE* p;

	char inputfilename[] = "image2.bmp";
	char outputfilename[] = "share1_imag2.bmp";

	f = fopen(inputfilename, "rb");
	p = fopen(outputfilename, "wb");
	if (p == NULL)
	{
		std::cout << "NOPE!" << std::endl;
	}

	unsigned char b, g, r;
	//copy header info from the code

	char headerinfo[54];
	fread(headerinfo, 54, 1, f);
	fwrite(headerinfo, 54, 1, p);

	while (!feof(f))
	{
		//pixel array needed for real manipulation!
		//otherwise its not possible to make any changes!
		b = fgetc(f);
		g = fgetc(f);
		r = fgetc(f);
		if (b != 0)
		{
			fputc(0, p);
			fputc(0, p);
			fputc(0, p);
			continue;

		}
		fputc(b, p);
		fputc(g, p);
		fputc(r, p);

	}
	fclose(p);
	fclose(f);



	return EXIT_SUCCESS;
}