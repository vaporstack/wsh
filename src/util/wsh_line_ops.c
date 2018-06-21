
//  wsh_line_ops.c
//  wsh_line_ops
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "wsh_line_ops.h"

//#include <gl-matrix/gl-matrix.h>
#include <math.h>
#include <wsh/wsh.h>

#include "../util/wsh_math.h"
#include "wsh_ops_point.h"

#define DEBUG_LINE_OPS true

/*
static inline double wsh_dist2d_p( WPoint* a, WPoint* b)
{
	return sqrt( (fabs( a->x - b->x)) * (fabs( a->x - b->x)) +
				(fabs( a->y - b->y)) * (fabs( a->y- b->y)) );
}
*/

WLine* wsh_line_ops_dedupe(WLine* line)
{
	WLine* deduped = wsh_line_create();

	double px, py;
	px = py = -INFINITY;

	for (unsigned long long i = 0; i < line->num; ++i)
	{
		WPoint p = line->data[i];
		if (p.x == px && p.y == py)
			continue;

		//	todo:  add check for first and last being the same
		//	todo: added below, debug it?
		if (i == line->num - 1)
		{
			//	this is the last point,
			//	check it against the first

			WPoint first = deduped->data[0];
			if (first.x == p.x && first.y == p.y)
			{
				//	first
				continue;
			}
		}

		wsh_line_add_point(deduped, p);
		px = p.x;
		py = p.y;
	}

	if (DEBUG_LINE_OPS)
		printf("Dedupe %llu -> %llu\n", line->num, deduped->num);

	return deduped;
}

WLine* wsh_line_ops_subdiv(WLine* line, double r)
{
	return NULL;
}
/*
static double angle_from_points(double ax, double ay, double bx, double by)
{
	float dx    = bx- ax;
	float dy    = by- ay;
	float angle = atan2(dy, dx);
	return  angle;
}
*/


static inline double angle_from_points(double x1, double y1, double x2, double y2)
{
	double dx    = x2 - x1;
	double dy    = y2 - y1;
	double angle = atan2(dy, dx);
	// return atan2(dy, dx);
	
	/*
	if (dy < 0)
	{
		angle += 1.0 * (double)M_PI;
	}
	*/
	return angle;
}

static inline double angle_from_points_degrees(double x1, double y1, double x2, double y2)
{
	double dx    = x2 - x1;
	double dy    = y2 - y1;
	double angle = atan2(dy, dx);
	// return atan2(dy, dx);

	if (dy < 0)
	{
		angle += 2 * (float)M_PI;
	}
	// map to [0, 1] range
	angle /= (2 * (float)M_PI);
	angle *= 360;
	angle -= 270;
	return angle;
}

double wsh_line_ops_angle(WLine* line)
{
	if (line->num < 2)
	{
		printf("Can't angle this line, not enough points!\n");
		return -1;
	}
	WPoint a = line->data[0];
	WPoint b = line->data[line->num - 1];
	return angle_from_points(a.x, a.y, b.x, b.y);
}

double wsh_line_ops_length(WLine* line)
{
	if (line->num < 2)
	{
		printf("Can't length this line, not enough points!\n");
		return -1;
	}
	WPoint a = line->data[0];
	WPoint b = line->data[line->num - 1];

	return wsh_ops_point_dist(a, b);
}

WLine* wsh_line_ops_straighten(WLine* line)
{
	if (line->num < 2)
	{
		printf("Can't straighten this line, not enough points!\n");
		return NULL;
	}
	WPoint a = line->data[0];
	WPoint b = line->data[line->num - 1];

	return NULL;
}

/*
 final float weight = 18;
 final float scale  = 1.0 / (weight + 2);
 int nPointsMinusTwo = nPoints - 2;
 Vec3f lower, upper, center;

 for (int i = 1; i < nPointsMinusTwo; i++) {
 lower = path[i-1];
 center = path[i];
 upper = path[i+1];

 center.x = (lower.x + weight*center.x + upper.x)*scale;
 center.y = (lower.y + weight*center.y + upper.y)*scale;
 }
 }
 */


//	todo: this r parameter is completely ignored, lol
//	also it returns nothing so why does it have a WLine return type lol
//	wtfffffff andrew
WLine* wsh_line_ops_smooth(WLine* line, double r)
{
	double		 weight		 = r;
	double		 scale		 = 1.0 / (weight + 2);
	signed long long nPointsMinusTwo = line->num - 2;
	if (!line->data)
		return NULL;

	for (int i = 1; i < nPointsMinusTwo; i++)
	{
		WPoint* lower  = &line->data[i - 1];
		WPoint* center = &line->data[i];
		WPoint* upper  = &line->data[i + 1];
		center->x      = (lower->x + weight * center->x + upper->x) * scale;
		center->y      = (lower->y + weight * center->y + upper->y) * scale;
	}

	return NULL;
}

static double perp_dist(WPoint p, WPoint a, WPoint b)
{
	double x  = p.x;
	double y  = p.y;
	double x1 = a.x;
	double y1 = a.y;
	double x2 = b.x;
	double y2 = b.y;

	double A = x - x1;
	double B = y - y1;
	double C = x2 - x1;
	double D = y2 - y1;

	double dot    = A * C + B * D;
	double len_sq = C * C + D * D;
	double param  = -1;
	if (len_sq != 0) // in case of 0 length line
		param = dot / len_sq;

	double xx, yy;

	if (param < 0)
	{
		xx = x1;
		yy = y1;
	}
	else if (param > 1)
	{
		xx = x2;
		yy = y2;
	}
	else
	{
		xx = x1 + param * C;
		yy = y1 + param * D;
	}

	double dx = x - xx;
	double dy = y - yy;
	return sqrt(dx * dx + dy * dy);
}

WLine* wsh_line_ops_douglaspeucker(WLine* line, double e)
{
	double		   dmax  = 0;
	int		   index = 0;
	unsigned long long num   = line->num;
	for (int i = 1; i < num - 1; ++i)
	{
		WPoint p = line->data[i];
		WPoint a = line->data[0];
		WPoint b = line->data[num - 1];
		double d = perp_dist(p, a, b);
		if (d > dmax)
		{
			index = i;
			dmax  = d;
		}
	}
	if (dmax > e)
	{

		// printf("dm: %f\n", dmax);

		WLine* res = wsh_line_create();
		WLine* s1  = wsh_line_create();
		wsh_line_concat_range(s1, line, 0, index);
		WLine* l1 = wsh_line_ops_douglaspeucker(s1, e);

		WLine* s2 = wsh_line_create();
		wsh_line_concat_range(s2, line, index, num);
		WLine* l2 = wsh_line_ops_douglaspeucker(s2, e);

		wsh_line_concat(res, l1);
		wsh_line_concat(res, l2);

		free(s1);
		free(s2);
		free(l1);
		free(l2);
		wsh_line_copy_attribs(res, line);
		// wsh_line_concat(res, line, index, num);
		// WLine* l1 = //wsh_line_ops_douglaspeucker(<#WLine *line#>, e)
		// if ( DEBUG_LINE_OPS )
		//	printf("%llu -> %llu\n", line->num, res->num );
		return res;
	}
	else
	{
		WLine* res = wsh_line_create();
		wsh_line_concat(res, line);
		wsh_line_copy_attribs(res, line);
		return res;
	}
}
/*
 function DouglasPeucker(PointList[], epsilon)
 // Find the point with the maximum distance
 dmax = 0
 index = 0
 end = length(PointList)
 for i = 2 to ( end - 1) {
 d = perpendicularDistance(PointList[i], Line(PointList[1], PointList[end]))
 if ( d > dmax ) {
 index = i
 dmax = d
 }
 }
 // If max distance is greater than epsilon, recursively simplify
 if ( dmax > epsilon ) {
 // Recursive call
 recResults1[] = DouglasPeucker(PointList[1...index], epsilon)
 recResults2[] = DouglasPeucker(PointList[index...end], epsilon)

 // Build the result list
 ResultList[] = {recResults1[1...length(recResults1)-1],
 recResults2[1...length(recResults2)]} } else { ResultList[] = {PointList[1],
 PointList[end]}
 }
 // Return the result
 return ResultList[]
 end

 */

WLine* wsh_line_ops_simplify(WLine* line, double r)
{

	if (!line->data)
		return NULL;
	WLine* cpy = wsh_line_create();
	wsh_line_add_point(cpy, line->data[0]);
	for (int i = 0; i < line->num - 1; ++i)
	{
		WPoint a = line->data[i];
		WPoint b = line->data[i + 1];
		double d = wsh_dist2d_p(&a, &b);
		if (d > r)
		{
			wsh_line_add_point(cpy, b);
		}
	}
	wsh_line_add_point(cpy, line->data[line->num - 1]);
	if (DEBUG_LINE_OPS)
		printf("%llu -> %llu\n", line->num, cpy->num);
	// this is probably needlessly expensive, but hey
	return cpy;
}

double wsh_line_ops_sum(WLine* line)
{
	double r = 0;
	for (int i = 0; i < line->num - 1; ++i)
	{
		WPoint a = line->data[i];
		WPoint b = line->data[i + 1];
		double d = wsh_dist2d_p(&a, &b);
		r += d;
	}
	return r;
}

bool wsh_line_ops_rect_contains(WLine* line, WRect* rect)
{
	for (int i = 0; i < line->num; i++)
	{
		WPoint p = line->data[i];
		if (!wsh_rect_within_bounds(rect, p.x, p.y))
			return false;
	}
	return true;
}

bool wsh_line_ops_rect_intersects(WLine* line, WRect* rect)
{
	for (int i = 0; i < line->num; ++i)
	{
		WPoint p = line->data[i];
		if (wsh_rect_within_bounds(rect, p.x, p.y))
			return true;
	}
	return false;
}
