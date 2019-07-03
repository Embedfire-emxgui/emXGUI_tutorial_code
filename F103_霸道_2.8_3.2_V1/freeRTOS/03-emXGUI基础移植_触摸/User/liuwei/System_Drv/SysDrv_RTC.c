
#include	"Include.h"

/*============================================================================================*/

#define	DEF_YEAR	2011
#define	DEF_MONTH	1
#define	DEF_DAY		1
#define	DEF_HOUR	0
#define	DEF_MIN		0
#define	DEF_SEC		0

/*============================================================================================*/

BOOL SysDrv_SetLocalTime(const local_time_t *tm);
BOOL SysDrv_GetLocalTime(local_time_t *tm);

/*============================================================================================*/

static u8 My_RTC_Init(void)
{

	return 0;
}

/*============================================================================================*/

int	SysDrv_RTC_Init(void)
{		
		local_time_t	time;
		////	

		My_RTC_Init();


		SysDrv_GetLocalTime(&time);
		
		if(time.year<2000)	goto	time_reset;
		if(time.year>2099)	goto	time_reset;
		
		if(time.mon<1)	goto	time_reset;
		if(time.mon>12)	goto	time_reset;
		
		if(time.day<1)		goto	time_reset;
		if(time.day>31)	goto	time_reset;
		
		if(time.hour>23)	goto	time_reset;
		if(time.min>59)	goto	time_reset;
		if(time.sec>59)	goto	time_reset;

		////	
		return TRUE;
			
time_reset:
		time.year	=DEF_YEAR;
		time.mon	=DEF_MONTH;
		time.day	=DEF_DAY;
		time.hour	=DEF_HOUR;
		time.min	=DEF_MIN;
		time.sec	=DEF_SEC;
		SysDrv_SetLocalTime(&time);
		return TRUE;
					
}

/*============================================================================================*/

BOOL SysDrv_SetLocalTime(const local_time_t *tm)
{
	U16	year;
	char	month,day,hour,min,sec;
	////
	
	year=((tm->year-2000)/10)<<4;
	year|=((tm->year-2000)%10);
	
	////
		
	month=(tm->mon/10)<<4;
	month|=(tm->mon%10);
	
	////

	day=(tm->day/10)<<4;
	day|=(tm->day%10);
	
	////

	hour=(tm->hour/10)<<4;
	hour|=(tm->hour%10);
	
	////
		
	min=(tm->min/10)<<4;
	min|=(tm->min%10);
	
	////
	
	sec=(tm->sec/10)<<4;
	sec|=(tm->sec%10);
	
	////
/*
	if(1)
	{
		RTC_DateTypeDef d;
		RTC_TimeTypeDef t;

		d.RTC_Year  =tm->year%100;
		d.RTC_Month =tm->mon;
		d.RTC_Date  =tm->day;
		d.RTC_WeekDay =0;

		t.RTC_Hours   =tm->hour;
		t.RTC_Minutes =tm->min;
		t.RTC_Seconds =tm->sec;

		RTC_SetDate(RTC_Format_BIN,&d);
		RTC_SetTime(RTC_Format_BIN,&t);

	}
*/
//	DebugPrintf("arch_SetLocalTime:%04d/%02d/%02d %02d:%02d:%02d\n",tm->year,tm->mon,tm->day,tm->hour,tm->min,tm->sec);

	return	TRUE;
}

/*============================================================================================*/

BOOL SysDrv_GetLocalTime(local_time_t *tm)
{/*
	RTC_DateTypeDef d;
	RTC_TimeTypeDef t;

	RTC_GetDate(RTC_Format_BIN,&d);
	RTC_GetTime(RTC_Format_BIN,&t);
	
	tm->year =d.RTC_Year+2000;
	tm->mon  =d.RTC_Month;
	tm->day  =d.RTC_Date;

	tm->hour =t.RTC_Hours;
	tm->min  =t.RTC_Minutes;
	tm->sec  =t.RTC_Seconds;
*/
	return FALSE;
	
}


/*============================================================================================*/
/*============================================================================================*/
