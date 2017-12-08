#ifndef		__PICUTIL__
#define	    __PICUTIL__

int *readIMage(const char *filename, int* widthOut, int*heightOut,int *channel);
void storeImage(float *imageOut, const char*fliename, int rows, int cols, const char * refFilename);



#endif
