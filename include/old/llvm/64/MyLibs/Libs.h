#pragma once
#include "MyNoises.h"
#include "2DEngine.h"


//#include <iostream>
//using namespace std;
int chunksize = 16;
int scale = 2;
double cot(double values)
{
	return (cos(values) / sin(values));
}

int abs_int(int num)
{
	if (num >= 0)return num;
	else return -num;
}

//class MyArrf
//{
//public:
//	float* arr = NULL;
//	MyArrf(int size)
//	{
//		float* arr = (float*)malloc(size * sizeof(float));
//	}
//
//	float get(int place)
//	{
//		return (arr[place]);
//	}
//	void set(int place, float num)
//	{
//		arr[place] = num;
//	}
//};



class Myarr
{
	int size;
	int* arr= nullptr;
	int type = 0;
public:
	Myarr(int size,int = NULL)
	{
		do {
			int* arr = (int*)malloc(size * sizeof(int));
			type = 0;
		} while (arr = nullptr);
	}
	Myarr(int size, float = NULL)
	{
		do {
			float* arr = (float*)malloc(size * sizeof(float));
			type = 1;
		} while (arr = nullptr);
	}

	Myarr(const Myarr &other)
	{
		
	}
	void operator = (int a)
	{

	}
	

};



//int* createArr(int size, int)
//{
//	return (int*)malloc(size*sizeof(int));
//}
//char* createArr(int size,char)
//{
//	return (char*)malloc(size * sizeof(char));
//}
//
//float* createArr(int size,float)
//{
//	return (float*)malloc(size * sizeof(float));
//}
//double* createArr(int size, double )
//{
//	return (double*)malloc(size * sizeof(double));
//}
//SFML!!

const int tilesize = 16 * 1;

class Chunk
{
public:
	//unsigned short** blocks = NULL;
	//unsigned short** blocks = (unsigned short**)malloc((16 * sizeof(unsigned short*)) + (16 * 16 * sizeof(unsigned short)));//[16][16];
	unsigned short sizeArrBlocks = 16;
	unsigned short* blocks = (unsigned short*)malloc(sizeArrBlocks * sizeArrBlocks * sizeof(unsigned short));//[16][16];
	unsigned short* locateBlocks = blocks;
	GradientNoise test;
	Vertex* world = (Vertex*)malloc(6 * 16 * 16 * sizeof(Vertex));//[6 * 16 * 16] ;
	Vertex* locateWorld = world;//[6 * 16 * 16] ;
	Texture image;
	bool gen = false;
	int temp = 0;
	Chunk()
	{
		temp = 0;
		while (blocks == nullptr)
		{
			blocks = (unsigned short*)malloc(sizeArrBlocks * sizeArrBlocks * sizeof(unsigned short));
			temp++;
			if (temp > 10000) exit(0);
		}
		temp = 0;
		while (world == nullptr)
		{
			world = (Vertex*)malloc(6 * 16 * 16 * sizeof(Vertex));
			temp++;
			if (temp > 10000) exit(0);
		}
		test.SetSeed(seed);

		image.loadFromFile("images/world/worldtiles.jpg");//1 block = 16*16, 2*2 = 32*32;
		
		//do {
		//	world = (Vertex*)calloc(6 * 16 * 16, sizeof(Vertex));
		//} while (!world);



		//do
		//{
		//	blocks = (unsigned short**)malloc(16 * sizeof(unsigned short*));
		//} while (blocks == NULL);

		//for (int i = 0; i < 16; i++)
		//{
		//	//blocks[i] = NULL;
		//
		//	//do {
		//	//	blocks[i] = (unsigned short*)realloc(blocks[i], 16 * sizeof(unsigned short));
		//	//} while (blocks[i] ==NULL);
		//
		//	for (int j = 0; j < 16; j++)
		//	{
		//
		//
		//	}
		//
		//}

	}
	void init(void)
	{
		temp = 0;
		while (blocks == nullptr)
		{
			blocks = (unsigned short*)malloc(sizeArrBlocks * sizeArrBlocks * sizeof(unsigned short));

			temp++;
			if (temp > 10000) exit(-1);
		}
		temp = 0;
		while (world == nullptr)
		{
			world = (Vertex*)malloc(6 * 16 * 16 * sizeof(Vertex));
			temp++;
			if (temp > 10000) exit(-1);
		}
		test.SetSeed(seed);

		image.loadFromFile("images/world/worldtiles.jpg");
	}

	void draw(RenderWindow *window,int i, int j)
	{
		if (!gen)
		{
			for (int x = 0; x < chunksize; x++)
			{
				for (int y = 0; y < chunksize; y++)
				{
					if (test.Noise(i * 16 + x, j * 16 + y, 1, 32) < -0.5) blocks[x * sizeArrBlocks + y] = 1;
					else if (test.Noise(i * 16 + x, j * 16 + y, 1, 32) < -0.3) blocks[x * sizeArrBlocks + y] = 2;
					else if (test.Noise(i * 16 + x, j * 16 + y, 1, 32) < 0) blocks[x * sizeArrBlocks + y] = 3;
					//else if (test.Noise(i * 16 + x, j * 16 + y, 1, 3) < 1) blocks[x * sizeArrBlocks + y] = 4;
					else blocks[x * sizeArrBlocks + y] = 4;
					//world[(16 * i * 6 + j * 6)] = Vertex(Vector2f(i * 16 * 16 * scale, j * 16 * 16 * scale), Color(255, 255, 255), Vector2f(16 * (blocks[x][y] + 1) % 2, 16 * ((int)(blocks[x][y] / 2))));//0:16|16:32 //ÄÎÄÅËÀÒÜ!!!!
					//world[(16 * i * 6 + j * 6) + 0] = Vertex(Vector2f(j * 16 * 16 * scale + x * 16 + 16, j * 16 * 16 * scale + y * 16), Color(255, 255, 255), Vector2f(16 * (blocks[x * sizeArrBlocks + y] + 1) % 2, 16 * ((int)(blocks[x * sizeArrBlocks + y] / 2))));
					//world[(16 * i * 6 + j * 6) + 1] = Vertex(Vector2f(i * 16 * 16 * scale + x * 16 + 16, j * 16 * 16 * scale + y * 16), Color(255, 255, 255), Vector2f((16 * (blocks[x * sizeArrBlocks + y] + 1) % 2) + 16, (16 * ((int)(blocks[x * sizeArrBlocks + y] / 2)))));
					//world[(16 * i * 6 + j * 6) + 2] = Vertex(Vector2f(i * 16 * 16 * scale + x * 16 + 16, j * 16 * 16 * scale + y * 16 + 16), Color(255, 255, 255), Vector2f((16 * (blocks[x * sizeArrBlocks + y] + 1) % 2) + 16, (16 * ((int)(blocks[x * sizeArrBlocks + y] / 2))) + 16));
					//world[(16 * i * 6 + j * 6) + 3] = Vertex(Vector2f(i * 16 * 16 * scale + x * 16 + 16, j * 16 * 16 * scale + y * 16 + 16), Color(255, 255, 255), Vector2f((16 * (blocks[x * sizeArrBlocks + y] + 1) % 2) + 16, (16 * ((int)(blocks[x * sizeArrBlocks + y] / 2))) + 16));
					//world[(16 * i * 6 + j * 6) + 4] = Vertex(Vector2f(i * 16 * 16 * scale + x * 16, j * 16 * 16 * scale + y * 16 + 16), Color(255, 255, 255), Vector2f((16 * (blocks[x * sizeArrBlocks + y] + 1) % 2), (16 * ((int)(blocks[x * sizeArrBlocks + y] / 2))) + 16));
					//world[(16 * i * 6 + j * 6) + 5] = Vertex(Vector2f(i * 16 * 16 * scale + x * 16, j * 16 * 16 * scale + y * 16), Color(255, 255, 255), Vector2f(16 * (blocks[x * sizeArrBlocks + y] + 1) % 2, 16 * ((int)(blocks[x * sizeArrBlocks + y] / 2))));


					world[x * 16 * 6 + y * 6 + 0] = Vertex(Vector2f((i * 16 * tilesize + x * tilesize), (j * 16 * tilesize + y * tilesize)), Color(255, 255, 255), Vector2f((16 * ((int)((blocks[x * sizeArrBlocks + y] + 1) % 2))), (16 * ((int)((blocks[x * sizeArrBlocks + y] - 1) / 2)))));
					world[x * 16 * 6 + y * 6 + 1] = Vertex(Vector2f((i * 16 * tilesize + x * tilesize) + tilesize, (j * 16 * tilesize + y * tilesize)), Color(255, 255, 255), Vector2f((16 * ((int)((blocks[x * sizeArrBlocks + y] + 1) % 2))) + 16, (16 * ((int)((blocks[x * sizeArrBlocks + y] - 1) / 2)))));
					world[x * 16 * 6 + y * 6 + 2] = Vertex(Vector2f((i * 16 * tilesize + x * tilesize) + tilesize, (j * 16 * tilesize + y * tilesize) + tilesize), Color(255, 255, 255), Vector2f((16 * ((int)((blocks[x * sizeArrBlocks + y] + 1) % 2))) + 16, (16 * ((int)((blocks[x * sizeArrBlocks + y] - 1) / 2))) + 16));
					world[x * 16 * 6 + y * 6 + 3] = Vertex(Vector2f((i * 16 * tilesize + x * tilesize) + tilesize, (j * 16 * tilesize + y * tilesize) + tilesize), Color(255, 255, 255), Vector2f((16 * ((int)((blocks[x * sizeArrBlocks + y] + 1) % 2))) + 16, (16 * ((int)((blocks[x * sizeArrBlocks + y] - 1) / 2))) + 16));
					world[x * 16 * 6 + y * 6 + 4] = Vertex(Vector2f((i * 16 * tilesize + x * tilesize), (j * 16 * tilesize + y * tilesize) + tilesize), Color(255, 255, 255), Vector2f((16 * ((int)((blocks[x * sizeArrBlocks + y] + 1) % 2))), (16 * ((int)((blocks[x * sizeArrBlocks + y] - 1) / 2))) + 16));
					world[x * 16 * 6 + y * 6 + 5] = Vertex(Vector2f((i * 16 * tilesize + x * tilesize), (j * 16 * tilesize + y * tilesize)), Color(255, 255, 255), Vector2f((16 * ((int)((blocks[x * sizeArrBlocks + y] + 1) % 2))), (16 * ((int)((blocks[x * sizeArrBlocks + y] - 1) / 2)))));
					
					//cout << x * sizeArrBlocks + y << " / y =" << y << " / x = " << x << "ur = " << (16 * ((int)((blocks[x * sizeArrBlocks + y]-1) / 2))) << endl;
				}
				//cout << "====================================" << endl;
			}
			gen = true;

			



		}
		window->draw(world, 6 * 16 * 16, Triangles, &image);
	}

	
	~Chunk()
	{
		free(locateWorld);
		free(locateBlocks);
	}

}; 
