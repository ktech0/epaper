#include <stdlib.h>
#include "GUI_Paint.h"

#ifndef __NEW_CHART_H__
#define __NEW_CHART_H__

typedef struct c_point{
    uint16_t value;
    char *label;
    char *x_label;
    struct c_point *next;
}ChartPoint;

//x轴位置
// 起点：(c->pos_x + c->font_width_y, c->pos_y + (uint16_t)(c->dot_pixel/2) + )
typedef struct c{
    uint16_t pos_x;             //位置座标x（左上角起点）
    uint16_t pos_y;             //位置座标y（左上角起点）
    uint16_t point_count;       //总点数
    uint16_t max_value;         //y最大值
    uint16_t min_value;         //y最小值
    uint16_t width;             //整体宽度
    uint16_t height;            //整体高度
    uint16_t font_max_height_x; //(X)轴字体高度
    uint16_t font_max_width_y;  //(Y)轴字体最宽
    DOT_PIXEL border_width;     //边框宽度
    DOT_PIXEL dot_pixel;        //点宽度
    ChartPoint *point;
}Chart;

extern ChartPoint* new_chart_point(uint16_t value, char *label, char *x_label);
extern Chart* new_chart(uint16_t pos_x, uint16_t pos_y);
extern void chart_push_point(Chart *c, ChartPoint *p);
extern void chart_init(Chart *c);
extern void chart_draw(Chart *c);

#endif
