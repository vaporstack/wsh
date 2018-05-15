//
//  w_color.h
//  wash
//
//  Created by Andrew Macfarlane on 1/2/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef w_color_h
#define w_color_h


typedef struct{
	float r;
	float g;
	float b;
	float a;
} WColor;

typedef struct{
	int r;
	int g;
	int b;
	int a;
} WColorShort;

typedef struct{
	double r;
	double g;
	double b;
	double a;
} WColor16;


typedef struct {
	double r;       // a fraction between 0 and 1
	double g;       // a fraction between 0 and 1
	double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
	double h;       // angle in degrees
	double s;       // a fraction between 0 and 1
	double v;       // a fraction between 0 and 1
} hsv;

//	hue is 0-360
hsv   rgb2hsv(rgb in);
rgb   hsv2rgb(hsv in);


#endif /* w_color_h */
