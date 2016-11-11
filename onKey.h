/*
 * onKey.h
 *
 * Created: 2013/4/13 16:54:52
 *  Author: 钟俊浩
 */ 


#include <avr/iom16.h>


#ifndef ONKEY_H_
#define ONKEY_H_

//定义按键数
#define KEYNUM			2
//定义按键的触发条件
#define GET_KEY_STATE()   ~( ((PIND&0x08)>>3) | ((PINA&0x80)>>6) )
//连击延时
#define ON_TO_COB_DELA  50
#define COB_DELA		5
//按键状态
#define KS_NOM		    0x00  //普通
#define KS_DELA         0x01  //延时去抖
#define KS_ONKEY	    0x02  //初始按下
#define KS_COB		    0x03  //连击
//按键返回值
#define KR_NOM			0     //普通(没按下)
#define KR_KEY_ON	    0x1   //初始按下
#define KR_KEY_COB		0x2   //连击 
//两位一键
#define KR_KEY_NOM_INDX(i)    (KR_NOM<<(i))
#define KR_KEY_ON_INDX(i)     (KR_KEY_ON<<((i)*2))
#define KR_KEY_COB_INDX(i)	  (KR_KEY_COB<<((i)*2))

extern unsigned char readKey();

#endif /* ONKEY_H_ */
