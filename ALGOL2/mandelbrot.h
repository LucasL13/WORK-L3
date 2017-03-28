#ifndef __MENDELBROT__
#define __MENDELBROT__


#include "cplx.h"
#include "cplxio.h"
#include "cplxop.h"
#include "ez-draw.h"
#include "Fractale.h"
#define CPLX_X1 -2.4
#define CPLX_X2 2.4
#define CPLX_Y1 -1.5
#define CPLX_Y2 1.5
#define MAX_ITER 50


COMPLEXE* convertir_pixel(Ez_window win, int x, int y);
void *thread_zoom_julia(void* arg);
Ez_image* draw_img_mandelbrot(Ez_window win);
Ez_image* draw_img_julia(Ez_window win, int iter_max, int n);
Ez_image* zoom_julia(Ez_window win, double zoom, int mx, int my);
Ez_image* zoom_mandelbrot(Ez_window win, double zoom, int mx, int my);

#endif
