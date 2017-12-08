
#include<stdio.h>
#include<stdlib.h>
#include"picutil.h"
#define _CRT_SECURE_NO_WARNINGS

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

int main()
{
	FILE* fp = NULL;
	FILE* ofp = NULL;
	ClBitMapFileHeader bmpFileHeader;
	ClBitMapInfoHeader bmpInfoHeader;
	const char* picname = "input.bmp";
	const char* outputfile = "otput.bmp";
	int offset;
	int width;
	int height;
	int channel;
	int mod;
	int bytes;
	short flag;
	unsigned char tmp;
	//unsigned char *imagedata;
	int * imagedata;
	imagedata = readIMage(picname, &width, &height, &channel);
	unsigned char *buffer = NULL;
	/*
	fp = fopen(picname, "rb");
	if (fp == NULL)
	{
		perror(picname);
		exit(-1);
	}

	fread(&flag, sizeof(short), 1, fp);
	if (flag == 0x4D42)
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
	printf("offset %d\n", offset);
	fseek(fp, 0, SEEK_SET);
	buffer = (unsigned char *)malloc(offset);
	fread(buffer, sizeof(unsigned char), offset, fp);
	fseek(fp, 18, SEEK_SET);
	fread(&width, 4, 1, fp);
	fread(&height, 4, 1, fp);
	printf("%d*%d\n", width, height);
	

	system("pause");
	mod = (3*width) % 4;
	fseek(fp, offset, SEEK_SET);
	imagedata = (unsigned char*)malloc(sizeof(unsigned char) * 3 * height*width);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				
				fread(&tmp, sizeof(unsigned char), 1, fp);
				imagedata[(height-i-1)*width*3 + j * 3 + k] = tmp;
			}
		}
		if (mod != 0)
		{
			for (int j = 0; j < mod; j++)
				fread(&tmp, sizeof(unsigned char), 1, fp);
		}
	}
	*/
	int count = 0;
	for (int i = 2; i < height*width * 3; i += 3)
	{
		printf("%d  ", imagedata[i]);
		count++;
		if (count == width)
		{
			count = 0;
			printf("\n");
		}
	}
	/*
	system("pause");
	printf("Writing output image to %s\n", outputfile);
	ofp = fopen(outputfile, "wb");
	if (ofp == NULL) {
		perror("opening output file");
		exit(-1);
	}
	bytes = fwrite(buffer, 1, offset, ofp);
	if (bytes != offset) {
		printf("error writing header!\n");
		exit(-1);
	}


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				tmp=imagedata[(height - i - 1)*width * 3 + j * 3 + k];
				fwrite(&tmp, sizeof(unsigned char), 1, ofp);
				
			}
		}
		if (mod != 0)
		{
			for (int j = 0; j < mod; j++)
				fwrite(&tmp, sizeof(unsigned char), 1, ofp);
		}
	}

	*/
	//fclose(fp);
	//fclose(ofp);
	free(buffer);
	return 0;


}