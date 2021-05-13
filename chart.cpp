#include "chart.h"

ChartPoint* new_chart_point(uint16_t value, char *label, char *x_label)
{
    ChartPoint *point = (ChartPoint*)malloc(sizeof(ChartPoint));
    point->value = value;
    point->label = label;
    point->x_label = x_label;
    point->next = NULL;
    return point;
}

Chart* new_chart(uint16_t pos_x, uint16_t pos_y)
{
    Chart *chart = (Chart*)malloc(sizeof(Chart));
    chart->pos_x = pos_x;
    chart->pos_y = pos_y;
    chart->point = NULL;
    chart->width = 640;
    chart->height = 384;
    chart->border_width = DOT_PIXEL_4X4; //1~8
    chart->dot_pixel = DOT_PIXEL_6X6; //1~8
    return chart;
}

void chart_push_point(Chart *c, ChartPoint *p)
{
    if (c->point == NULL){
        c->point = p;
    }else{
        ChartPoint* _p = c->point;
        while (_p->next != NULL){
            _p = _p->next;
        }
        _p->next = p;
    }
}

void chart_init(Chart *c)
{
    c->point_count = 0;
    c->max_value = 0;
    c->min_value = 0;
    ChartPoint* _p = c->point;
    while (_p != NULL){
        if (_p->value > c->max_value){
            c->max_value = _p->value;
        }
        if (_p->value < c->min_value){
            c->min_value = _p->value;
        }
        
        _p = _p->next;
        c->point_count++;
    }
}

void chart_draw(Chart *c)
{
    chart_init(c);
    //画X轴
    Paint_DrawLine(c->pos_x + 100, c->pos_y + c->height, c->pos_x + c->width, c->pos_y + c->height, BLACK, c->border_width, LINE_STYLE_SOLID);
    //画Y轴
    Paint_DrawLine(c->pos_x, c->pos_y, c->pos_x, c->pos_y + c->height, BLACK, c->border_width, LINE_STYLE_SOLID);
    //画点和标签
    ChartPoint *p = c->point;
    uint16_t x = c->pos_x + c->border_width;
    uint16_t x_width = (c->width - c->border_width) / (c->point_count + 1);
    while (p != NULL)
    {
        //画点
        x = x + x_width;
        uint16_t y = c->pos_y + c->height - (uint16_t)((float)p->value / (float)c->max_value * (c->height - c->border_width)) + 10;
        Paint_DrawPoint(x, y, BLACK, c->dot_pixel, DOT_STYLE_DFT);
        //画标签
        uint16_t text_x = x + (uint16_t)(c->dot_pixel / 2) + 1;
        Paint_DrawString_CN(text_x, y, p->label, &Font16CN, BLACK, WHITE);
        p = p->next;
    }
}
