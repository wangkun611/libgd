/* $Id$ */

#include "gd.h"
#include <stdio.h>
#include <stdlib.h>

void save_png(gdImagePtr im, const char *filename)
{
	FILE *fp;
	fp = fopen(filename, "wb");
	if (!fp) {
		fprintf(stderr, "Can't save png image %s\n", filename);
		return;
	}
	gdImagePng(im, fp);
	fclose(fp);
}

gdImagePtr read_png(const char *filename)
{
	FILE * fp;
	gdImagePtr im;

	fp = fopen(filename, "rb");
	if (!fp) {
		fprintf(stderr, "Can't read png image %s\n", filename);
		return NULL;
	}
	im = gdImageCreateFromPng(fp);
	fclose(fp);
	return im;
}

int main()
{
 	gdImagePtr im, im2;

	im = gdImageCreateTrueColor(400, 400);

	if (!im) {
		fprintf(stderr, "Can't create 400x400 TC image\n");
		return 1;
	}

	gdImageFilledRectangle(im, 19, 29, 390, 390, 0xFFFFFF);
	gdImageRectangle(im, 19, 29, 390, 390, 0xFF0000);
	save_png(im, "a1.png");

	im2 = gdImageAutoCrop(im, GD_CROP_SIDES);
	if (im2) {
		save_png(im2, "a2.png");
		gdImageDestroy(im2);
	}
	gdImageDestroy(im);

	im = read_png("test_crop_threshold.png");
	if (!im) {
		return 1;
	}

	im2 = gdImageThresholdCrop(im, 0xFFFFFF, 120);
	if (im2) {
		save_png(im2, "a3.png");
		gdImageDestroy(im2);
	}
	gdImageDestroy(im);

	im = read_png("test_crop_threshold.png");
	if (!im) {
		return 1;
	}

	im2 = gdImageThresholdCrop(im, 0xFFFFFF, 70);
	if (im2) {
		save_png(im2, "a4.png");
		gdImageDestroy(im2);
	}

	gdImageDestroy(im);
	return 0;
}