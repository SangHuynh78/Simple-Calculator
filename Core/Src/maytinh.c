/*
 * maytinh.c
 *
 *  Created on: Oct 28, 2022
 *      Author: Admin
 */

#include "maytinh.h"

long int powr(int number)
{
	long int result = 10;
	if (number>0)
	{
		for (int i = 1; i < number; i++)
		{
			result *= 10;
		}
		return result;
	}
	else return 1;
}

long double tinh_toan (char INPUT[50], long double Ans)
{
	long double MATH[50]= {0}, ADD[50] = {0};
	unsigned char i= 0, j=0, sign, counter = 0, counter2 = 0, decimal = 0;
	long double KQ = '@', factor = 0;

	//gộp các ký tự trong INPUT thành biểu thức MATH
	for (i = 0; i<= 50; i++)
	{
		switch ((int)INPUT[i])
		{
		case '0':
			sign = 0;
			factor = factor*10 + sign;
			if (decimal) decimal++ ;
			break;
		case '1':
			sign = 1;
			factor = factor*10 + sign;
			if (decimal) decimal++ ;
			break;
		case '2':
			sign = 2;
			factor = factor*10 + sign;
			if (decimal) decimal++ ;
			break;
		case '3':
			sign = 3;
			factor = factor*10 + sign;
			if (decimal) decimal++ ;
			break;
		case '4':
			sign = 4;
			factor = factor*10 + sign;
			if (decimal) decimal++ ;
			break;
		case '5':
			sign = 5;
			factor = factor*10 + sign;
			if (decimal) decimal++ ;
			break;
		case '6':
			sign = 6;
			factor = factor*10 + sign;
			if (decimal) decimal++ ;
			break;
		case '7':
			sign = 7;
			factor = factor*10 + sign;
			if (decimal) decimal++ ;
			break;
		case '8':
			sign = 8;
			factor = factor*10 + sign;
			if (decimal) decimal++ ;
			break;
		case '9':
			sign = 9;
			factor = factor*10 + sign;
			if (decimal) decimal++ ;
			break;
		case '+':
			if (factor)
			{
				MATH[counter++]=factor/powr(decimal-1);
				MATH[counter++]='+';
			}
			else if (i && MATH[counter-1]=='-')
			{
				counter--;
				MATH[counter++] = '-';
			}
			factor= 0;
			decimal= 0;
			break;
		case '-':
			if (MATH[counter-1]=='x' || MATH[counter-1]=='/') i=100; //lỗi x-, /-
			else if (!i)
			{
				MATH[counter++]=0;
				MATH[counter++]='-';
			}
			else if (factor || (MATH[counter-1]=='+'))
			{
				MATH[counter++]=factor/powr(decimal-1);
				MATH[counter++]='-';
			}
			else if (MATH[counter-1]=='-')
			{
				counter--;
				MATH[counter++] = '+';
			}
			factor= 0;
			decimal= 0;
			break;
		case 'x':
			if ( !i || !factor) i=100;
			//thoát khỏi vòng lặp for(i) lỗi phép nhân đầu biểu thức hoặc lỗi +x , -x , /x , xx
			else{
				MATH[counter++]=factor/powr(decimal-1);
				MATH[counter++] = 'x' ;
				factor= 0;
				decimal=0;
				}
			break;
		case '/':
			if (!i || !factor) i=100;
			//thoát khỏi vòng lặp for(i) lỗi phép chia đầu biểu thức hoặc lỗi +/
			else{
				MATH[counter++]=factor/powr(decimal-1);
				MATH[counter++] = '/' ;
				factor= 0;
				decimal= 0;
				break;
				}
			break;
		case '.':
			if (!decimal) decimal = 1;
			else i= 100;	//thoát khỏi vòng lặp for(i) do lỗi số hạng 2 dấu chấm thập phân a.b.c
			break;
		case '=':
			MATH[counter++]=factor/powr(decimal-1);
			MATH[counter] = '=';
			i=60; 		//thoát khỏi vòng lặp for(i)
			break;
		case 'A':
			if (decimal) i=100;    //lỗi .Ans
			factor = Ans;
			break;
		case 'P':
			if (decimal) i=100;    //lỗi .Pi
			if (!factor) factor = 3.141592654;
			else factor = factor*3.141592654;
			break;
		case 'D':
			break;
		default:
			i= 100;		//thoát khỏi vòng lặp for(i) do lỗi kí tự lạ (đề phòng)
			break;
		}
	}
	//hoàn thành việc gộp các ký tự trong INPUT thành biểu thức MATH

	if (i<70)  //kiểm tra lỗi của phép tính phát hiện trong for(i)
	{
		//thực hiện phép nhân, phép chia trong biểu thức MATH
		for (j=0; j<=counter; j++)
		{
			switch ((int)MATH[j])
			{
				case 'x':
					j++;
					factor = factor*MATH[j];
					break;
				case '/':
					j++;
					if (MATH[j] == 0) j= 100;	//thoát vòng lặp for(j) do lỗi chia cho 0
					else factor = factor/MATH[j];
					break;
				case '+':
					ADD[counter2++]= factor;
					ADD[counter2++]= '+';
					break;
				case '-':
					ADD[counter2++]= factor;
					ADD[counter2++]= '-';
					break;
				case '=':
					ADD[counter2++]= factor;
					ADD[counter2]= '=';
					break;
				default:		//trường hợp MATH[j] là số
					factor = MATH[j];
					break;
			}
		}
		//hoàn thành việc thực hiện phép nhân, phép chia trong biểu thức MATH
		//cho ra biểu thức ADD chỉ còn phép cộng, phép trừ

		if (j<60)  //kiểm tra lỗi của phép tính phát hiện trong for(j)
		{
		//thực hiện phép cộng, phép trừ trong biểu thức ADD
			factor = ADD[0];
			for (int k=1; k<= counter2; k++)
			{
				switch ( (int)ADD[k] )
				{
				case '+':
					k++;
					factor += (long double)ADD[k];
					break;
				case '-':
					k++;
					factor -= (long double)ADD[k];
					break;
				default:
					KQ = (long double)factor;
					break;
				}
			}
		//hoàn thành việc thực hiện phép cộng, phép trừ trong biểu thức ADD
		}
	}
	return KQ;   // '@' nếu phép toán lỗi
				//  dữ kiệu kiểu long double
}	//hết tính toán
