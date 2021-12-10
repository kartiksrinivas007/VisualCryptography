#include "Image.h"


int main()
{
	const int width = 640;
	const int height = 480;
	const int delta = 40;
	const int delta2 = 200;


	Image image(width, height);
	for (int y0 = 0; y0 < height; y0++)
	{
		for (int x0 = 0; x0 < width; x0++)
		{
			image.setcolor(color(1.0f, 1.0f, 1.0f), x0, y0);
		}
	}

	for (int y = height/8; y < 3*height/4; y++)
	{
		for (int x = width/2 - delta; x < width/2 + delta; x++)
		{
			image.setcolor(color(0.0f, 0.0f, 0.0f), x, y);

		}
	}
	
	for (int y1 = 3*height / 4 ; y1 < 3*height/4 + delta ; y1++)
	{
		for (int x1 = width / 2 - delta2 ; x1 < width/2 + delta2; x1++)
		{
			image.setcolor(color(0.0f, 0.0f, 0.0f), x1, y1);
		}
	}
	image.Export("image5.bmp");

	Image copy(0, 0);

	copy.read("image5.bmp");
	//now since the input is ready ..time to mess with the pixel array !
	/* i need to pick the first 4 pixels ..the last 4 i mean where I will manipulate the pixel by the random
	methods....ie C0 and C1 manipulation method ..which I can call to use the functions later on!*/

	copy.Export("image5copy.bmp");

	return 0;
}
