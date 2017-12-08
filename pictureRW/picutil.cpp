#include"picutil.h"
#include<stdio.h>
#include<stdlib.h>

typedef struct                                 //define the BMP File Header
{
	//unsigned short bfType;
	unsigned long bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned long  bfOffBits;
} ClBitMapFileHeader;

typedef struct
{
	unsigned long  biSize;
	long   biWidth;
	long   biHeight;
	unsigned short   biPlanes;
	unsigned short   biBitCount;
	unsigned long  biCompression;
	unsigned long  biSizeImage;
	long   biXPelsPerMeter;
	long   biYPelsPerMeter;
	unsigned long   biClrUsed;
	unsigned long   biClrImportant;
} ClBitMapInfoHeader;					//define the BMP info header;

int *readIMage(const char *filename, int* widthOut, int*heightOut, int *channelOut)
{
	FILE* fp = NULL;
	
	ClBitMapFileHeader bmpFileHeader;
	ClBitMapInfoHeader bmpInfoHeader;
	int width, height,channel;
	int offset;					//图像文件从文件开始到图像数据的偏移
	int mod;					//填充偏移
	int bytes;
	short flag;
	unsigned char tmp;
	unsigned char *imagedata;
	unsigned char *buffer;

	fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		perror(filename);
		exit(-1);
	}

	fread(&flag, sizeof(short), 1, fp);
	if (flag == 0x4D42)					 //BMP图像
	{
		printf("isBMP\n");
		fread(&bmpFileHeader, sizeof(ClBitMapFileHeader), 1, fp);

		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
		printf("bmp文件头信息：\n");
		printf("文件大小：%d \n", bmpFileHeader.bfSize);
		printf("保留字：%d \n", bmpFileHeader.bfReserved1);
		printf("保留字：%d \n", bmpFileHeader.bfReserved2);
		printf("位图数据偏移字节数：%d \n", bmpFileHeader.bfOffBits);

		fread(&bmpInfoHeader, sizeof(ClBitMapInfoHeader), 1, fp);
		channel = bmpInfoHeader.biBitCount/8;
		*channelOut = channel;
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
		printf("bmp文件信息头\n");
		printf("结构体长度：%d \n", bmpInfoHeader.biSize);
		printf("位图宽度：%d \n", bmpInfoHeader.biWidth);
		printf("位图高度：%d \n", bmpInfoHeader.biHeight);
		printf("位图平面数：%d \n", bmpInfoHeader.biPlanes);
		printf("颜色位数：%d \n", bmpInfoHeader.biBitCount);
		printf("压缩方式：%d \n", bmpInfoHeader.biCompression);
		printf("实际位图数据占用的字节数：%d \n", bmpInfoHeader.biSizeImage);
		printf("X方向分辨率：%d \n", bmpInfoHeader.biXPelsPerMeter);
		printf("Y方向分辨率：%d \n", bmpInfoHeader.biYPelsPerMeter);
		printf("使用的颜色数：%d \n", bmpInfoHeader.biClrUsed);
		printf("重要颜色数：%d \n", bmpInfoHeader.biClrImportant);
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");

	}

	fseek(fp, 10, SEEK_SET);
	fread(&offset, 4, 1, fp);
	
	fseek(fp, 18, SEEK_SET);
	fread(&width, 4, 1, fp);
	fread(&height, 4, 1, fp);

	printf("width = %d\n", width);
	printf("height = %d\n", height);
	printf("channel = %d\n", channel);
	*widthOut = width;
	*heightOut = height;

	//system("pause");

	mod = (channel * width) % 4;
	fseek(fp, offset, SEEK_SET);
	imagedata = (unsigned char*)malloc(sizeof(unsigned char) * channel * height*width);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < channel; k++)
			{

				fread(&tmp, sizeof(unsigned char), 1, fp);
				imagedata[(height - i - 1)*width * channel + j * channel + k] = tmp;
			}
		}
		if (mod != 0)
		{
			for (int j = 0; j < mod; j++)
				fread(&tmp, sizeof(unsigned char), 1, fp);
		}
	}
	fclose(fp);


	int* intImage = NULL;
	intImage = (int*)malloc(sizeof(int)*width*height*channel);
	if (intImage == NULL) {
		perror("malloc");
		exit(-1);
	}
	for (int i = 0; i < width*height * channel; i++)
	{
		intImage[i] = (int)imagedata[i];
	}
	free(imagedata);
	return intImage;
}
void storeImage(float *imageOut, const char*fliename, int rows, int cols, const char * refFilename)
{

}