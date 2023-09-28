#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void writePixel(float rgb[3], char ascii)
{
	printf("\x1b[38;2;%d;%d;%dm%c\x1b[0m", (int)rgb[0],(int)rgb[1],(int)rgb[2], ascii);
}
int main(int argc, char *argv[])
{	
	int w,h,c,densityLen;
	char density[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,^`'. ";
	unsigned char *img = stbi_load(argv[1], &w, &h, &c, 3);
	densityLen = strlen(density);
	if (img==NULL)
	{
		printf("Failed loading image\n");
		return 1;
	}
	printf("Loaded image with width of %dpx, a height of %dpx and %d channels\n",w,h,c);
	for (int j=0; j<h; j++)
	{
		for (int i=0; i<w; i++)
		{
			unsigned char* pixelOffset = img + (i + w * j) * (unsigned)c;
			float rgb[3] =
			{
				(float)pixelOffset[0],
				(float)pixelOffset[1],
				(float)pixelOffset[2]
			};
			float indx = (((rgb[0]+rgb[1]+rgb[2]/3)/3)/255)*densityLen;
			char ascii = density[(int)indx];
			writePixel(rgb, ascii);
		}
		printf("\n");
	}
	stbi_image_free(img);
	return 0;
}
