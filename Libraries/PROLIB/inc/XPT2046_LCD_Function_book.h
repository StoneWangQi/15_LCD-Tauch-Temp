#ifndef __XPT2046_LCD_FUNCTION_BOOK_H__
#define	__XPT2046_LCD_FUNCTION_BOOK_H__


#include "stm32f10x.h"


typedef union {
  struct{
    unsigned char BIT0:1;unsigned char BIT1:1;unsigned char BIT2:1;unsigned char BIT3:1;
    unsigned char BIT4:1;unsigned char BIT5:1;unsigned char BIT6:1;unsigned char BIT7:1;
    //unsigned char BIT8:1;unsigned char BIT9:1;unsigned char BIT10:1;unsigned char BIT11:1;
    //unsigned char BIT12:1;unsigned char BIT13:1;unsigned char BIT14:1;unsigned char BIT15:1;
  }DATA_BIT;
  uint8_t DATA_BYTE;
}Per_XPT2046_LCD_type;


/*******************************触摸状态机相关*************************************/
typedef enum
{
	XPT2046_STATE_RELEASE  = 0,	//触摸释放
	XPT2046_STATE_WAITING,			//触摸按下
	XPT2046_STATE_PRESSED,			//触摸按下
}enumTouchState	;
 
#define TOUCH_NOT 		        0
#define TOUCH_PRESSED 				1
#define TOUCH_NOT_PRESSED			2


//触摸消抖阈值
#define DURIATION_TIME				3
//触屏信号有效电平
#define             XPT2046_PENIRQ_ActiveLevel                     0
#define             XPT2046_PENIRQ_Read()                          GPIO_ReadInputDataBit ( XPT2046_PENIRQ_GPIO_PORT, XPT2046_PENIRQ_GPIO_PIN )

/// 声明 XPT2046 相关的外部全局变量 
extern volatile uint8_t               ucXPT2046_TouchFlag;
extern volatile                       Per_XPT2046_LCD_type  XPT2046_LCD_flag;
    #define bXPT2046_LCD_10ms         XPT2046_LCD_flag.DATA_BIT.BIT0


/*******************************触摸坐标判断 *************************************/

typedef	struct{          //液晶坐标结构体 		
	/*负数值表示无新数据*/
   int16_t x;			//记录最新的触摸参数值
   int16_t y; 	
	/*用于记录连续触摸时(长按)的上一次触摸位置*/
	 int16_t pre_x;		
   int16_t pre_y;	
} strType_XPT2046_Coordinate;   

typedef struct{         //校准因子结构体 
	 float  An,  		 //注:sizeof(long double) = 8
					Bn,     
					Cn,   
					Dn,    
					En,    
					Fn,     
					Divider;
} strType_XPT2046_Calibration;

typedef struct{         //校准系数结构体（最终使用）
	 float dX_X,  			 
					dX_Y,     
					dX,   
					dY_X,    
					dY_Y,    
					dY;
} strType_XPT2046_TouchPara;

/// 声明 XPT2046 相关的外部全局变量 
extern strType_XPT2046_TouchPara      strXPT2046_TouchPara[];
//  触摸校验4点校验点
extern strType_XPT2046_Coordinate     strCrossCoordinate[4];
extern strType_XPT2046_Coordinate     strScreenSample[4];


/*******************************触摸函数 *************************************/
uint8_t XPT2046_TouchDetect(void);
uint8_t XPT2046_ReadAdc_Smooth_XY ( strType_XPT2046_Coordinate * pScreenCoordinate );

#endif /* __BSP_TOUCH_H */
