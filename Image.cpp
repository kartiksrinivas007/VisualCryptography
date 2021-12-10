#include"Image.h"
#include<fstream> 
#include<iostream>

 color::color()
   :r(0),g(0),b(0)
 {

 }
 color::color(float r0, float g0,float b0)
   :r(r0),g(g0),b(b0)
 {

 }
 color::~color()
 {

 }
 Image::Image(int width ,int height)
   :m_width(width),m_height(height),m_colors(std::vector<color>(width*height))
{

}
 void Image::combination(Image& share1, Image& share2,int width ,int height)
 {
     for (int y = 0; y < m_height; y++)
     {
         for (int x = 0; x < m_width; x++)
         {
             color c1 = share1.getcolor(x, y);
             color c2 = share2.getcolor(x, y);
             int num1 = (int)c1.r;
             int num2 = (int)c2.r;
             int num3 = num1 & num2; //biwise and the values of the float ..which is either one or zero
             color  c3 = getcolor(x, y);
             //possible access errors
             c3.r = (float)num3;
             c3.g = (float)num3;
             c3.b = (float)num3;
             setcolor(c3, x, y);
            
         }
     }
 }

Image::~Image()
{
}
int Image::getheight()
{
    return m_height;
}
int Image::getwidth()
{
    return m_width;
}
color Image::getcolor(int x ,int y) const
{
	return m_colors[y*m_width + x];
}
void Image:: setcolor(const color& color1,int  x,int y)
{
	m_colors[y*m_width + x].r = color1.r;
	m_colors[y*m_width + x].g = color1.g;
	m_colors[y*m_width + x].b = color1.b;
}
void Image::read(const char* path)
{
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);
    
    if (!f.is_open())
    {
        std::cout << "File can not be opened" << std::endl;
        return;
    }
    const int fileheadersize = 14;
    const int informationheadersize = 40;
    
    unsigned char fileheader[fileheadersize];
    unsigned char informationheader[informationheadersize];

    f.read(reinterpret_cast<char*>(fileheader), fileheadersize);
    f.read(reinterpret_cast<char*>(informationheader), informationheadersize);

    if (fileheader[0] != 'B' || fileheader[1] != 'M')
    {
        std::cout << "NOT A BITMAP IMAGE" << std::endl;
        return;
    }

    int filesize = (fileheader[2]) + (fileheader[3] << 8) + (fileheader[4] <<16) + (fileheader[5] << 24);
    m_width = (informationheader[4]) + (informationheader[5] << 8) + (informationheader[6] << 16) + (informationheader[7] << 24);
    m_height = (informationheader[8]) + (informationheader[9] << 8) + (informationheader[10] << 16) + (informationheader[11] << 24);

    m_colors.resize(m_width * m_height);

    const int paddingamount = ((4 - ((m_width * 3) % 4)) % 4);
                    
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            unsigned char color1[3];
            f.read(reinterpret_cast<char*>(color1), 3);
            //you can use setcolor method here as well but lets not use a proxy object
            m_colors[x + y * m_width].b = static_cast<float>(color1[0]) / 255.0f;//fraction needed
            m_colors[x + y * m_width].g = static_cast<float>(color1[1]) / 255.0f;
            m_colors[x + y * m_width].r = static_cast<float>(color1[2]) / 255.0f;


        }
        f.ignore(paddingamount);

    }
    f.close();
    std::cout << "FILE READ SUCCESSFULLY" << std::endl;

}
void Image:: Export(const char* path) const
{
       std::ofstream f;
       	f.open(path,std::ios::out|std::ios::binary);

       	if(!f.is_open())
       	{
       		std::cout<<"could not open file"<<std::endl;

       	}
       	unsigned char bmppad[3] = {0,0,0};
       	const int paddingamount  = ((4 - (m_width*3)%4)%4); //to determine how much padding is needed

       	const int fileheadersize =14;
       	const int informationheadersize = 40;
       	const int filesize = fileheadersize + informationheadersize + paddingamount* m_height + 3*m_height*m_width;
       	
        unsigned char fileheader[fileheadersize];

        fileheader[0] = 'B';
        fileheader[1] = 'M';

        fileheader[2] = filesize;
        fileheader[3] = filesize>>8;
        fileheader[4] = filesize>>16;
        fileheader[5] = filesize>>24;

        fileheader[6] = 0;
        fileheader[7] = 0;

        fileheader[8] = 0;
        fileheader[9] = 0;

        fileheader[10] = fileheadersize + informationheadersize;
        fileheader[11] = 0;
        fileheader[12] = 0;
        fileheader[13] = 0;

        unsigned char informationheader[informationheadersize];
        
        informationheader[0] = informationheadersize;
        informationheader[1] = 0;
        informationheader[2] = 0;
        informationheader[3] = 0;
        //width variables
        informationheader[4] = m_width;
        informationheader[5] = m_width>>8;
        informationheader[6] = m_width>>16;
        informationheader[7] = m_width>>24;
        //hieght variables
        informationheader[8] = m_height;
        informationheader[9] = m_height>>8;
        informationheader[10] = m_height>>16;
        informationheader[11] = m_height>>24;
        //planes
        informationheader[12] = 1;
        informationheader[13] = 0;
        //bits per pixel
        informationheader[14] = 24;
        informationheader[15] = 0;
        //compression
        informationheader[16] = 0;
        informationheader[17] = 0;
        informationheader[18] = 0;
        informationheader[19] = 0;
        //imagesize(nocompression)
        informationheader[20] = 0;
        informationheader[21] = 0;
        informationheader[22] = 0;
        informationheader[23] = 0;
        //x pixels per m
        informationheader[24] = 0;
        informationheader[25] = 0;
        informationheader[26] = 0;
        informationheader[27] = 0;
        //y pixels per m
        informationheader[28] = 0;
        informationheader[29] = 0;
        informationheader[30] = 0;
        informationheader[31] = 0;
        //total colors
        informationheader[32] = 0;
        informationheader[33] = 0;
        informationheader[34] = 0;
        informationheader[35] = 0;
        //important colors
        informationheader[36] = 0;
        informationheader[37] = 0;
        informationheader[38] = 0;
        informationheader[39] = 0;
        
        f.write(reinterpret_cast<char*>(fileheader), fileheadersize);
        f.write(reinterpret_cast<char*>(informationheader), informationheadersize);
            
        for (int y = 0; y < m_height; y++)
        {
            for (int x = 0; x < m_width; x++)
            {
                unsigned char r = static_cast<unsigned char>(getcolor(x, y).r * 255.0f);
                unsigned char g = static_cast<unsigned char>(getcolor(x, y).g * 255.0f);
                unsigned char b = static_cast<unsigned char>(getcolor(x, y).b * 255.0f);

                unsigned char color_channel[] = { b, g ,r };
                f.write(reinterpret_cast<char*>(color_channel), 3);
            }
            f.write(reinterpret_cast<char*>(bmppad), paddingamount);

        }
        f.close();
        std::cout << "file could be created" << std::endl;


}
 
