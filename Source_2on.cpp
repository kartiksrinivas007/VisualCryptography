#include"Image.h"
#include"make_shares.h"
#include"make_shares_2on.h"
#include<iostream>


int main()
{
	Image image(0, 0);
	char path_original[] = "image5.bmp";
	//std::cout << path_original << std::endl;
	image.read(path_original);

	int n;

	const int image_height = image.getheight();
	const int image_width = image.getwidth();
	std::cout << "image width is "<<image_width << std::endl;

	std::cout << "Enter number of shares ! " << std::endl;
	std::cin >> n;

	int zoom = (int)(sqrt((double)n));
	std::cout << zoom << std::endl;

	const int share_height = zoom *  image_height;
	const int share_width = zoom *  image_width;

	std::cout << "share width is "<< share_width << std::endl;
	
	std::vector<Image>shares(n, Image(share_width, share_height));

	std::cout << "array made ! "<<shares.size() << std::endl;

	//std::cout << "safe" << std::endl;

	dim1s paths;
	//std::cout << "safe" << std::endl;

	generate_paths(paths,n);
	std::cout << "safe after paths " << std::endl;

	std::cout << "path first " << paths[0] << std::endl;

	

	//for debugging the export lets initialize all of them with image4 
	
	make_shares_2on(image,shares, image_width, image_height,zoom,n);

	std::cout << "make _shares is safe ! " << std::endl;

	for (int j = 0; j < n; j++)
	{
		char path[100];
		strcpy(path, paths[j].c_str()); //to convert to char array
		shares[j].Export(path);
	}
    //call generate_paths!
	//now pass the paths while exporting! image array is to be made sor the shares obviously !
	Image combo(share_width, share_height);
	combo.combination(shares[2], shares[3],share_width,share_height);
	combo.Export("combo1.bmp");


	
	//generate zoom factor(int n)
	//resize each image now to the appropriate size according to scheme shares.resize(n,)



	
	return 0;
}