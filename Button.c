

#include "Button.h"
#include "Eeprom.h"
#include "Led.h"
#include "Temp.h"

#define IN_ON   0
#define IN_OFF  1

#define BUTTON_SWITCH       PD_IDR_IDR5  //����
#define BUTTON_LIGHT        PD_IDR_IDR4  //�ƿ���
#define BUTTON_SEEDLING     PD_IDR_IDR6  //����ʱ��     
#define BUTTON_GROW         PD_IDR_IDR7 //������
#define BUTTON_FRUIT        PD_IDR_IDR0 //����ʱ��

#define BUTTON_WATER        PB_IDR_IDR7 //��ˮλ���

//�Ƿ񿪵Ʊ�־λ
static u8 button_light_flag = 0;
//ˮλ���Ʊ�־λ
static u8 button_water_flag = 0;
//��ǰģʽ��־
static u8 button_mode_flag = 0;
//�Ƿ���
static u8 Button_switch_flag = 0;

void ButtonInit(void) {
    //���ܰ���
    PD_DDR_DDR0 = 0;//��--����̨��,���¾���Զ�ص�״̬���ٰ��»ָ���׼����
    PD_CR1_C10 = 1;
    PD_CR2_C20 = 0;
    
    PD_DDR_DDR7 = 0;//���ؼ�--���������������ػ���
    PD_CR1_C17 = 1;
    PD_CR2_C27 = 0;
    
    PD_DDR_DDR4 = 0;//������-��Ӧ������
    PD_CR1_C14 = 1;
    PD_CR2_C24 = 0;
    
    PD_DDR_DDR5 = 0;//������--��Ӧ������
    PD_CR1_C15 = 1;
    PD_CR2_C25 = 0;
    
    PD_DDR_DDR6 = 0;//������--��Ӧ������
    PD_CR1_C16 = 1;
    PD_CR2_C26 = 0;
    
    //ˮλ�ͼ��
    PB_DDR_DDR7 = 0;
    PB_CR1_C17 = 1;
    PB_CR2_C27 = 0;
    
    if(EepromRead(10) == 0x55) {
        button_light_flag = EepromRead(11);
        button_water_flag = EepromRead(12);  
        button_mode_flag = EepromRead(13);  
    } else {
        EepromWrite(10,0x55);
        EepromWrite(11,0x00);
        EepromWrite(12,0x00);
        EepromWrite(13,0x00);
        button_light_flag = EepromRead(11);
        button_water_flag = EepromRead(12);  
        button_mode_flag = EepromRead(13);   
    }
    LedSetSwitch(1);//�رտ���ָʾ
    LedSetMode(button_mode_flag);//�رտ���led
    LedSetLight(button_light_flag);//�ָ�LED״̬
}




u8 ButtonReadWaterFlag(void) {
    return button_water_flag;
}

void  ButtonSetWaterFlag(u8 cmd) {
    button_water_flag = cmd;
    EepromWrite(12,button_water_flag);
}
//��ȡˮλ״̬
u8 ButtonReadWater(void) {
    if(BUTTON_WATER == 0) {
        return 0x80;
    } else {
        return 0x00;
    }
}

u8 ButtonGetSwitch(void) {
    return Button_switch_flag;
}

//���ذ���
u8 ButtonReadSwitch(void) {
    static u16 buntu_count = 0;
    static u8 buntu_count_small = 0;
    if(BUTTON_SWITCH == IN_ON) {
        if(buntu_count < 2000) {
            if(buntu_count_small < 50) {
                buntu_count_small++;
            } else {
                buntu_count_small = 0;
                buntu_count++;
            }
            if(buntu_count == 2000) {
                buntu_count++;
                if(Button_switch_flag == 0x80) {
                    Button_switch_flag = 0;
                    LedSetSwitch(1);
                } else {
                    Button_switch_flag = 0x80;
                    LedSetSwitch(0);
                }
                return 0x80;
            }
        } else {
           
        }
    } else {
        buntu_count = 0;
    }
    return 0x00;
}


u8 ButtonGetLightFlag(void) {
    return button_light_flag;
}

/**********************************************��������***************************************************** 
* ��������: void ButtonSetLightFlag(u8 data) 
* �������: u8 data 
* ���ز���: void  
* ��    ��: ����led�Ƿ���Կ�����־λ  
* ��    ��: by lhb_steven
* ��    ��: 2016/3/14
************************************************************************************************************/ 
void ButtonSetLightFlag(u8 data) { 
    button_light_flag = data;
    EepromWrite(11,button_light_flag);
}

//��ƿ��ؼ�
u8  ButtonReadLight(void) {
    static u16 buntu_count = 0;
    if(BUTTON_LIGHT == IN_ON) {
        if(buntu_count < 6000) {
            buntu_count++;
            if(buntu_count == 5000) {//����ʱ�䵽��
                if(button_light_flag == 0) {
                    ButtonSetLightFlag(1);
                } else {
                    ButtonSetLightFlag(0);
                }
                TempSetLight(1);
                LedSetLight(button_light_flag);
                return 0x80;
            }
        } else {
            
        }
    } else {
        buntu_count = 0;
    }
    return 0x00;
}

void ButtonSetModeFlag(u8 data) {
    button_mode_flag = data;
    EepromWrite(13,button_mode_flag);
}

//����ѡ�񰴼�
u8 ButtonReadMode(void) {
    static u16 buntu_count1 = 0;
    static u16 buntu_count2 = 0;
    static u16 buntu_count3 = 0;
    if(BUTTON_SEEDLING == IN_ON) {
        if(buntu_count1 < 1000) {
            buntu_count1++;
        } else {
            if(buntu_count1 == 1000) {
                buntu_count1++;
                ButtonSetModeFlag(0);
                return 0x01;
            }
        }
    } else {
        buntu_count1 = 0;
    }
    if(BUTTON_GROW == IN_ON) {
        if(buntu_count2 < 1000) {
            buntu_count2++;
        } else {
            if(buntu_count2 == 1000) {
                buntu_count2++;
                ButtonSetModeFlag(1);
                return 0x02;
            }
        }
    } else {
        buntu_count2 = 0;
    }
    if(BUTTON_FRUIT == IN_ON) {
        if(buntu_count3 < 1000) {
            buntu_count3++;
        } else {
            if(buntu_count3 == 1000) {
                buntu_count3++;
                ButtonSetModeFlag(2);
                return 0x03;
            }
        }
    } else {
        buntu_count3 = 0;
    }
    LedSetMode(button_mode_flag);
    return 0x00;
}

