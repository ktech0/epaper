#include <stdlib.h>
#include "GUI_Paint.h"

#ifndef __NEW_CHART_H__
#define __NEW_CHART_H__

typedef struct c_point{
    uint16_t value;
    char* label;
    char* x_label;
    struct c_point* next;
}ChartPoint;

typedef struct c{
    uint16_t pos_x;
    uint16_t pos_y;
    uint16_t point_count;
    uint16_t max_value;
    uint16_t min_value;
    uint16_t width;
    uint16_t height;
    DOT_PIXEL border_width;
    DOT_PIXEL dot_pixel;
    ChartPoint* point;
}Chart;

extern ChartPoint* new_chart_point(uint16_t value, char* label, char* x_label);
extern Chart* new_chart(uint16_t pos_x, uint16_t pos_y);
extern void chart_push_point(Chart* c, ChartPoint* p);
extern void chart_init(Chart * c);
extern void chart_draw(Chart* c);

#endif
