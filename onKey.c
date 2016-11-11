#include "onKey.h"

unsigned char readKey()
{
	//各按键状态
	static unsigned char keyState[KEYNUM] = {0,0};
	//各按键的计数器
	static unsigned char count[KEYNUM] = {0,0};
		
	unsigned char curKey = KRNOM;
	unsigned char result = KR_NOM;
	
	curKey = GET_KEY_STATE();
	
	for (unsigned char i=0 ; i<KEYNUM ; i++)
	{
		if ( (curKey & (1<<i)))  //如果第i个按下进行状态转移
		{
			switch(keyState[i])
			{
				case KS_NOM:   keyState[i] = KS_DELA;  
				break;
				
				case KS_DELA:  keyState[i] = KS_ONKEY;
				result |=  KR_KEY_ON_INDX(i);
				break;
				
				case KS_ONKEY: count[i] ++;
				if ( count[i] >= ON_TO_COB_DELA )
				{
					count[i] = 0;
					keyState[i] = KS_COB;
					result |= KR_KEY_COB_INDX(i);
				}
				break;
				
				case KS_COB:  count[i] ++;
				if ( count[i] >= COB_DELA )
				{
					count[i] = 0;
					result |= KR_KEY_COB_INDX(i);
				}
				break;
				
				default: break;
			}
		}
		else //没按下状态清0
		{
			keyState[i] = KS_NOM;
			count[i] = 0;
		}
	}
	return result;
}
