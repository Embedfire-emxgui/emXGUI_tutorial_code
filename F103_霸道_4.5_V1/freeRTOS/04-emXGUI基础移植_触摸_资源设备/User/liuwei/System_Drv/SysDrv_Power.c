
#include	"Include.h"

/*============================================================================*/

//GPH13
#define	PWR_ON()	//gpio->GPHDAT	|=  (1<<13);
#define	PWR_OFF()	//gpio->GPHDAT	&= ~(1<<13);

#define	BK_LT_ON()	//gpio->rGPBDAT	|=  (1<<2);
#define	BK_LT_OFF()	//gpio->rGPBDAT	&=~ (1<<2);


/*============================================================================*/

//static	GPIO_REG *gpio=GPIO_REG_VA_BASE;

/*============================================================================*/
/*============================================================================*/

static	void	drvBackLightInit(void)
{

#if 0
	S3C2450_PWM_REG *tmr =TIMER_REG_VA_BASE;
	GPIO_REG *gpio =GPIO_REG_VA_BASE;
	
	int tick_hz,i;
	
	tick_hz =10;
	
	gpio->rGPBCON &= ~(3<<4);
	gpio->rGPBCON |=  (2<<4);  //GPB2->TOUT2
	
	INTR_Disable(INTR_TIMER2);
	
	tmr->TCON  &= ~(0x0F<<12);
	tmr->TCFG0 &= ~(0xFF<<8);		
	tmr->TCFG1 &= ~(0x0F<<8);

//	INTR_SetHandler(INT_NUM_TIMER2,timer2_isr);

	tmr->TCFG0 |= (8<<8);		/* prescaler: 8 */
	tmr->TCFG1 |= (1<<8);		/* divider value :1/4*/
	
	i =CPU_GetPclkHZ()/(8*4*tick_hz) - 1;
	
	tmr->TCNTB2 = 1500;
	tmr->TCMPB2 = 700; //(H/L)duty 55%

	tmr->TCON |=  (1<<13);			/* update TCNTB0&TCMPB0 */
	tmr->TCON &= ~(1<<13);			/* must clear 'manual update', note page 297*/
	tmr->TCON |=  (1<<14);			/* TOUT2 */
	tmr->TCON |=  (1<<15);			/* auto reload */
	tmr->TCON |=  (1<<12);			/* start timer2 */
	
//	INTR_ClearPend(INT_NUM_TIMER2);
//	INTR_Enable(INT_NUM_TIMER2);
#endif

}

/*============================================================================*/

BOOL	SysDrv_PowerON(void)
{

	//PWR_EN - GPH13: 0:OFF; 1:ON.

//	GPIO_SetMode(GPH,13,GPIO_OUTPUT|GPIO_PULL_UP);
//	GPIO_SetMode(GPB,2,GPIO_OUTPUT|GPIO_PULL_UP);
	
	PWR_ON();

#if 0
	BK_LT_ON();
	drvBackLightInit();
#endif
	return TRUE;
	
}

/*============================================================================*/

BOOL	SysDrv_PowerOFF(void)
{
	PWR_OFF();
	return TRUE;
}

/*============================================================================*/

int	arch_SetBacklightBrightness(U8 val)
{
	printf("SetBacklightBrightness -> %d\r\n",val);
	/*
	if(val>0)
	{
		BK_LT_ON();
	}
	else
	{
		BK_LT_OFF();
	}
	*/
}

/*============================================================================*/
/*============================================================================*/
static int batt_adval  =0x0FFF;
static int expwr_adval =0x0000;

/*============================================================================*/

#define	AD_MAX	0x0FFF
#define	AD_VREF	3.3

//////////////////////////

#define	MIN_BAT_VOL		6.4
#define	MAX_BAT_VOL		7.4

#define	EX_PWR_CHK_R0	200
#define	EX_PWR_CHK_R1	20

#define	BATT_CHK_R0 	200
#define	BATT_CHK_R1		20

//////////////////////////
#if 0

int	get_batt_volatage(void)
{
	int i,ad;
	float vol;

	////
	ad	=batt_adval;
	vol = (float)ad*((float)AD_VREF/(float)AD_MAX);
	vol = vol*(float)(BATT_CHK_R0+BATT_CHK_R1)/(float)BATT_CHK_R1;

	i =(int)(vol*1000);
	return	i;
}

int	get_expwr_volatage(void)
{
	int i,ad;
	float vol;

	////
	ad	=expwr_adval;
	vol = (float)ad*((float)AD_VREF/(float)AD_MAX);
	vol = vol*(float)(BATT_CHK_R0+BATT_CHK_R1)/(float)BATT_CHK_R1;

	i =(int)(vol*1000);
	return	i;
}
#endif
/*============================================================================*/

BOOL	SysDrv_GetSystemPowerStatus(SYSTEM_POWER_STATUS* pPwrSta)
{
	float	batt_vol;
	float   extpwr_vol;
	int		ad,percent;
	////

	ad	=batt_adval;
	batt_vol = (float)ad*((float)AD_VREF/(float)AD_MAX);
	batt_vol = batt_vol*(float)(BATT_CHK_R0+BATT_CHK_R1)/(float)BATT_CHK_R1;


	ad	=expwr_adval;
	extpwr_vol = (float)ad*((float)AD_VREF/(float)AD_MAX);
	extpwr_vol = extpwr_vol*(float)(EX_PWR_CHK_R0+EX_PWR_CHK_R1)/(float)EX_PWR_CHK_R1;

	//DebugPrintf("battery -> %d,%.2fV\r\n",ad,vol);

	percent	=(batt_vol-MIN_BAT_VOL)*100/(MAX_BAT_VOL-MIN_BAT_VOL);
	percent	=MAX(0,percent);
	percent	=MIN(100,percent);

	percent =75;
	batt_vol =5;

	pPwrSta->ACLineStatus =AC_LINE_UNKNOWN;

	pPwrSta->BatteryFlag = 0;
	if(extpwr_vol > 4.0)
	{
		pPwrSta->BatteryFlag =BATTERY_FLAG_CHARGING;
	}

	pPwrSta->BatteryLifePercent		=percent;
	pPwrSta->BackupBatteryFlag		=BATTERY_FLAG_UNKNOWN;

	pPwrSta->BatteryVoltage			=batt_vol*1000;
	pPwrSta->BatteryCurrent			=BATTERY_CURRENT_UNKNOWN;
	pPwrSta->BatteryLifeTime		=BATTERY_LIFE_UNKNOWN;
	pPwrSta->BatteryFullLifeTime	=BATTERY_LIFE_UNKNOWN;

	pPwrSta->BackupBatteryVoltage		=BATTERY_VOLTAGE_UNKNOWN;
	pPwrSta->BackupBatteryCurrent		=BATTERY_CURRENT_UNKNOWN;
	pPwrSta->BackupBatteryLifeTime		=BATTERY_LIFE_UNKNOWN;
	pPwrSta->BackupBatteryFullLifeTime	=BATTERY_LIFE_UNKNOWN;

	return	TRUE;

}

/*============================================================================*/

U32	SysDrv_SetSystemPowerState(U32 StateFlags)
{
	switch(StateFlags)
	{

		case	POWER_STATE_ON:
				SysDrv_PowerON();
				break;
				////

		case	POWER_STATE_IDLE:

				break;
				////
		case	POWER_STATE_SUSPEND:

				break;
				////

		case	POWER_STATE_OFF:
				SysDrv_PowerOFF();
				break;
				////

		default:
				break;
	}

	return FALSE;
}

/*============================================================================*/
