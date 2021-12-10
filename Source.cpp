#include"Image.h"
#include"make_shares.h"

int main()
{
	
	Image image(0, 0);
	image.read("image5.bmp");

	const int height = image.getheight();
	const int width = image.getwidth();

	const int share_height = 2 * height;
	const int share_width = 2 * width;

	//now create 2 shares 
	Image share_2(share_width,share_height), share_1(share_width,share_height);

	make_shares_randomized(image, width, height, share_1, share_2);

	share_1.Export("share1.bmp");
	share_2.Export("share2.bmp");

	Image combo(0, 0);
	combo.read("share2.bmp");
	combo.combination(share_1, share_2, share_width, share_height);
	combo.Export("combo.bmp");


	return EXIT_SUCCESS;
}