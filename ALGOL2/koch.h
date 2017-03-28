#ifndef __KOCH__
#define __KOCH__
#include "listep.h"
#include "listep_op.h"
#include "math.h"
#include "ez-draw.h"

#define PI 3.141592654

PLISTE triangle(double x, double y, double c);
PLISTE koch(int n, double x, double y, double c);
PLISTE koch_center(int n, double c, int choix);

PLISTE koch_a(int n, double x, double y, double c, int angle);
PLISTE zoom_koch(PLISTE list, double i, int x, int y);
PLISTE koch_inverse(int n, double x, double y, double c);

#endif
