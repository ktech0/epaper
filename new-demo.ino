#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
#include <stdlib.h>
#include "chart.h"

//流程：
// 屏幕初始化
// 定义两种黑红画布 handler
// 1. 创建画布缓冲区(需要创建黑红两张)
// 2. 清空画布缓冲区(需要清空黑红两张)
// 3. 画布上绘制图形
// 4. 将缓冲区显示在屏幕上
// 5. 屏幕休眠
// 6. 最后释放缓冲区（可选需要释放黑红两张）

//两张画布
UBYTE *BlackImage, *RYImage;

void setup()
{
  init_screen();
  create_canvas();

  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);
  Paint_DrawPoint(8, 8, BLACK, DOT_PIXEL_8X8, DOT_STYLE_DFT);
  Paint_DrawPoint(632, 376, BLACK, DOT_PIXEL_8X8, DOT_STYLE_DFT);
  // Chart* chart = new_chart(0, 0);
  // ChartPoint *point1 = new_chart_point(30, "30度", "2021-10-01");
  // ChartPoint *point2 = new_chart_point(45, "45度", "2021-10-02");
  // chart_push_point(chart, point1);
  // chart_push_point(chart, point2);
  // chart_draw(chart);
  
//  Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
//  Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
//  Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
//  Paint_DrawPoint(10, 110, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
//  Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
//  Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
//  Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
//  Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//  Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, WHITE);
//  Paint_DrawString_CN(130, 20, "微雪电子", &Font24CN, WHITE, BLACK);
//  Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);
//  Paint_DrawString_CN(0, 250, "多云转阴 36", &Font16CN, WHITE, BLACK);
//
//  //2.Draw red image
  Paint_SelectImage(RYImage);
  Paint_Clear(WHITE);
//  Paint_DrawCircle(160, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
//  Paint_DrawCircle(210, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//  Paint_DrawLine(85, 95, 125, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
//  Paint_DrawLine(105, 75, 105, 115, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
//  Paint_DrawString_CN(130, 0, "你好abc", &Font12CN, BLACK, WHITE);
//  Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);
//  Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
  Paint_DrawString_CN(100, 200, "hello world", &Font16CN, WHITE, BLACK);

  display_canvas();
  sleep_screen();
  drop_canvas();
}

void loop()
{
  while(true){
    delay(5000);
  }
}

//屏幕初始化
void init_screen()
{
  DEV_Module_Init();
  EPD_7IN5BC_Init();
  EPD_7IN5BC_Clear();
  DEV_Delay_ms(500);
}

//创建画布缓冲区
void create_canvas()
{
  UWORD Imagesize = ((EPD_7IN5BC_WIDTH % 8 == 0) ? (EPD_7IN5BC_WIDTH / 8 ) : (EPD_7IN5BC_WIDTH / 8)) * EPD_7IN5BC_HEIGHT;
  if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for black memory...\r\n");
    while(1);
  }
  if ((RYImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for red memory...\r\n");
    while(1);
  }
  Paint_NewImage(BlackImage, EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT, 0, WHITE);
  Paint_NewImage(RYImage, EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT, 0, WHITE);
}

//清空画布缓冲区
void clear_canvas()
{
  Paint_SelectImage(BlackImage);
  Paint_Clear(WHITE);
  Paint_SelectImage(RYImage);
  Paint_Clear(WHITE);
}

//画布缓冲区显示在屏幕
void display_canvas()
{
  EPD_7IN5BC_Display(BlackImage, RYImage);
  DEV_Delay_ms(2000);
}

//屏幕休眠
void sleep_screen()
{
  EPD_7IN5BC_Sleep();
}

//销毁画布缓冲区
void drop_canvas()
{
  free(BlackImage);
  BlackImage = NULL;
  free(RYImage);
  RYImage = NULL;
}
