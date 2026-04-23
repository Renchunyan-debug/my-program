//矩阵键盘输入两位数代表起始站点和终止站点，十位代表线（1为A线，2为B线），个位代表站点（1-9）
//矩阵键盘11代表切换输入下一个，10代表确认，开始计算，16表示清空

#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned int start_station,finish_station,start,finish;
unsigned int all_station_count,first_station_count,second_station_count;
unsigned int key_num,money,count1,count2;
unsigned char input=1;

void get_station();//输入
void one_line();//同线
void two_line();//换乘
void money_counter();//计算
void show_English_one();//将数字转化为字母显示
void show_English_two();

void main()
{
	LCD_Init();//初始化
	//以下皆为初始提示
	LCD_ShowString(1,1,"input two number");
	LCD_ShowString(2,1,"start  end      ");
	Delay(3000);
	LCD_ShowString(1,1,"10   11   16    ");
	LCD_ShowString(2,1,"sure next empty ");
	Delay(5000); 
	LCD_ShowString(1,1,"                ");
	LCD_ShowString(2,1,"                ");

	while(1)
	{
		key_num=MatrixKey();
		get_station();//得到两个站点
		if((start_station/10)==(finish_station/10))one_line();//不换乘，一条线
		if((start_station/10)!=(finish_station/10))two_line();//换乘，两条线
		if(key_num==10)money_counter();//确认，开始计算
	}
}
void get_station()
{
	if(key_num)
		{
			if(input==1&&key_num<10)	//输入密码
			{
				if(count1<2)	
				{
					start_station*=10;				
					start_station+=key_num;		
					count1++;	
				}
			
			 LCD_ShowNum(1,1,start_station,2);
			}
			else if(key_num==11)//确认第一个，可以开始输入第二个
			{
				input=2;
				show_English_one();
			}
			else if(input==2&&key_num<10)//输入第二个
			{			
				if(count2<2)	
				{
					finish_station*=10;				
					finish_station+=key_num;		
					count2++;	
				}
				
				LCD_ShowNum(1,4,finish_station,2);				
			}
			else if(key_num==16)//清空
			{
				start_station=0;
				finish_station=0;
				LCD_ShowNum(1,1,start_station,2);
				LCD_ShowNum(1,4,finish_station,2);
				input=1;
				get_station();
			}
		}	
}
void one_line()//一条线，判断个位大小然后加减
{
	if(start_station>finish_station)
	{
		all_station_count=start_station-finish_station;
	}else{
		all_station_count=finish_station-start_station;
	}
	//不足三站按三站计算
	if(all_station_count<=3)
	{
		all_station_count=3;
	}
	else if(all_station_count>3&&all_station_count<=6)
	{
		all_station_count=6;
	}
	else if(all_station_count>6)
	{
		all_station_count=9;
	}	  
}
void two_line()
{
	//取站点号
	start=start_station%10;
	finish=finish_station%10;
	//计算到换乘点的距离
	if(start>=5)
		first_station_count=start-5;
	else
		first_station_count=5-start;
	
	if(finish>=5)
		second_station_count=finish-5;
	else
		second_station_count=5-finish;
	
	//计算总站数
	all_station_count=first_station_count+second_station_count;	
	
	
	//不足三站按三站计算
  if(all_station_count<=3)
	{
		all_station_count=3;
	}
	else if(all_station_count>3&&all_station_count<=6)
	{
		all_station_count=6;
	}
	else if(all_station_count>6&&all_station_count<=9)
	{
		all_station_count=9;
	}
}
void money_counter()//计算费用
{
	show_English_two();
	money=(all_station_count/3)*5;
	LCD_ShowString(2,1,"              ");
	LCD_ShowNum(2,1,money,2);
}
void show_English_one()//将输入的数字转化为标准的显示
{
	if(start_station>20)
	{
		LCD_ShowString(1,1,"B");
	}
	else
	{
		LCD_ShowString(1,1,"A");
	}
}
void show_English_two()
{
	if(finish_station>20)
	{
		LCD_ShowString(1,4,"B");
	}
	else
	{
		LCD_ShowString(1,4,"A");
	}	
}