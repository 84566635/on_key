/*
 * onKey.h
 *
 * Created: 2013/4/13 16:54:52
 *  Author: �ӿ���
 */ 


#include <avr/iom16.h>


#ifndef ONKEY_H_
#define ONKEY_H_

//���尴����
#define KEYNUM			2
//���尴���Ĵ�������
#define GET_KEY_STATE()   ~( ((PIND&0x08)>>3) | ((PINA&0x80)>>6) )
//������ʱ
#define ON_TO_COB_DELA  50
#define COB_DELA		5
//����״̬
#define KS_NOM		    0x00  //��ͨ
#define KS_DELA         0x01  //��ʱȥ��
#define KS_ONKEY	    0x02  //��ʼ����
#define KS_COB		    0x03  //����
//��������ֵ
#define KR_NOM			0     //��ͨ(û����)
#define KR_KEY_ON	    0x1   //��ʼ����
#define KR_KEY_COB		0x2   //���� 
//��λһ��
#define KR_KEY_NOM_INDX(i)    (KR_NOM<<(i))
#define KR_KEY_ON_INDX(i)     (KR_KEY_ON<<((i)*2))
#define KR_KEY_COB_INDX(i)	  (KR_KEY_COB<<((i)*2))

unsigned char readKey()
{
	//������״̬
	static unsigned char keyState[KEYNUM] = {0,0};
	//�������ļ�����
	static unsigned char count[KEYNUM] = {0,0};
		
	unsigned char curKey = KRNOM;
	unsigned char result = KR_NOM;
	
	curKey = GET_KEY_STATE();
	
	for (unsigned char i=0 ; i<KEYNUM ; i++)
	{
		if ( (curKey & (1<<i)))  //�����i�����½���״̬ת��
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
		else //û����״̬��0
		{
			keyState[i] = KS_NOM;
			count[i] = 0;
		}
	}
	return result;
}

#endif /* ONKEY_H_ */