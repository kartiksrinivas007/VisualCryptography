#pragma once
#include<vector>

struct color 
{
	float r, g, b;
	color();
	color(float r,float g,float b);
	~color();
};
class Image
{
public:
	Image(int width,int height);
    ~Image();

    color getcolor(int x ,int y) const;
    void setcolor(const color& color1 , int x ,int y);
    void Export(const char* path) const;
	void read(const char* path);
	int getwidth();
	int getheight();
	void combination(Image& share1, Image& share2,int width, int height);
private:
	int m_width;
	int m_height;
	std::vector<color> m_colors;

};

