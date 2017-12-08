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
	int offset;					//ͼ���ļ����ļ���ʼ��ͼ�����ݵ�ƫ��
	int mod;					//���ƫ��
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
	if (flag == 0x4D42)					 //BMPͼ��
	{
		printf("isBMP\n");
		fread(&bmpFileHeader, sizeof(ClBitMapFileHeader), 1, fp);

		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n");
		printf("bmp�ļ�ͷ��Ϣ��\n");
		printf("�ļ���С��%d \n", bmpFileHeader.bfSize);
		printf("�����֣�%d \n", bmpFileHeader.bfReserved1);
		printf("�����֣�%d \n", bmpFileHeader.bfReserved2);
		printf("λͼ����ƫ���ֽ�����%d \n", bmpFileHeader.bfOffBits);

		fread(&bmpInfoHeader, sizeof(ClBitMapInfoHeader), 1, fp);
		channel = bmpInfoHeader.biBitCount/8;
		*channelOut = channel;
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
		printf("bmp�ļ���Ϣͷ\n");
		printf("�ṹ�峤�ȣ�%d \n", bmpInfoHeader.biSize);
		printf("λͼ��ȣ�%d \n", bmpInfoHeader.biWidth);
		printf("λͼ�߶ȣ�%d \n", bmpInfoHeader.biHeight);
		printf("λͼƽ������%d \n", bmpInfoHeader.biPlanes);
		printf("��ɫλ����%d \n", bmpInfoHeader.biBitCount);
		printf("ѹ����ʽ��%d \n", bmpInfoHeader.biCompression);
		printf("ʵ��λͼ����ռ�õ��ֽ�����%d \n", bmpInfoHeader.biSizeImage);
		printf("X����ֱ��ʣ�%d \n", bmpInfoHeader.biXPelsPerMeter);
		printf("Y����ֱ��ʣ�%d \n", bmpInfoHeader.biYPelsPerMeter);
		printf("ʹ�õ���ɫ����%d \n", bmpInfoHeader.biClrUsed);
		printf("��Ҫ��ɫ����%d \n", bmpInfoHeader.biClrImportant);
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