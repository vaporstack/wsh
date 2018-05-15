//
//  wsh_transform.h
//  wash
//
//  Created by Andrew Macfarlane on 1/2/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef wsh_transform_h
#define wsh_transform_h

typedef struct WVec2d
{
	double x;
	double y;

} WVec2d;

typedef struct WVec3d
{
	double x;
	double y;
	double z;

} WVec3d;

typedef struct WTransform2
{
	WVec2d anchor;
	WVec2d position;
	WVec2d rotation;
	WVec2d scale;
	double opacity;
} WTransform2;

typedef struct WTransform
{
	WVec3d anchor;
	WVec3d position;
	WVec3d rotation;
	WVec3d scale;
	double opacity;
} WTransform;

void wsh_transform_reset(WTransform* t);
void wsh_transform_apply(WTransform* t);
void wsh_transform_deapply(WTransform* t);

#endif /* wsh_transform_h */
