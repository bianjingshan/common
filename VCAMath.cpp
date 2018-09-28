#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <math.h> 
#include <stdio.h>
#include "VCAMath.h"

CVcaRand::CVcaRand(void)
{
	srand(unsigned(time(0)));
}

int CVcaRand::GetRand(int start, int end)
{
	int rand_data;
	if((end-start)>RAND_MAX)
	{
		rand_data=(int)((long)(rand()*((long)RAND_MAX+1))+rand());
	}
	else
	{
		rand_data=rand();
	}
	return start+rand_data%(end-start+1);
}

bool CVcaRand::CreateIncreaseRandSequence(int start, int end, int sequence_num, int *p_sequence_buffer)
{
	if(sequence_num<=0)
	{
		return false;
	}
	if(sequence_num>(end-start+1))
	{
		return false;
	}
	int index_num=(end-start+1);
	int *p_index_buffer=(int *)malloc(sizeof(int)*index_num);
	int *p_index_seq = (int *)malloc(sizeof(int)*sequence_num);
	int rand_index;
	int index_num_rest=index_num;
	int output_cnt=0;
	for(int iloop=0;iloop<index_num;iloop++)
	{
		p_index_buffer[iloop] = iloop;
	}
	for (int iloop = 0; iloop < sequence_num; iloop++)
	{
		rand_index=GetRand(0, index_num_rest-1);
		p_index_seq[iloop]= p_index_buffer[rand_index];
		p_index_buffer[rand_index]=p_index_buffer[index_num_rest-1];
		index_num_rest--;
	}
	for(int iloop=0;iloop<index_num;iloop++)
	{
		p_index_buffer[iloop] = 0;
	}
	for (int iloop = 0; iloop < sequence_num; iloop++)
	{
		p_index_buffer[p_index_seq[iloop]]=1;
	}
	for(int iloop=0;iloop<index_num;iloop++)
	{
		if(1==p_index_buffer[iloop])
		{
			p_sequence_buffer[output_cnt]=iloop+start;
			output_cnt++;
		}
	}
	return true;
}


int VcaMin(int value1, int value2)
{
	if(value1>value2)
	{
		return value2;
	}
	else
	{
		return value1;
	}
}

double VcaMin(double value1, double value2)
{
	if(value1>value2)
	{
		return value2;
	}
	else
	{
		return value1;
	}
}

double GetDispersion(double *p_input_data, int input_data_num)
{	
	if(p_input_data==NULL)
	{
		return 0;
	}
	if(input_data_num<=0)
	{
		return 0;
	}
	double temp_data=0, avg_data, dispersion_data=0;
	for(int iloop=0;iloop<input_data_num;iloop++)
	{
		temp_data+=p_input_data[iloop];
	}
	avg_data=temp_data/input_data_num;

	double temp_d;
	for(int iloop=0;iloop<input_data_num;iloop++)
	{
		temp_d = p_input_data[iloop] - avg_data;
		if (temp_d > 0)
		{
			dispersion_data += temp_d;
		}
		else
		{
			dispersion_data -= temp_d;
		}
	}
	return (dispersion_data/input_data_num/avg_data);
}

double GetAverage(double *p_input_data, int input_data_num)
{	
	if(p_input_data==NULL)
	{
		return 0;
	}
	if(input_data_num<=0)
	{
		return 0;
	}
	double temp_data=0, avg_data;
	for(int iloop=0;iloop<input_data_num;iloop++)
	{
		temp_data+=p_input_data[iloop];
	}
	avg_data=temp_data/input_data_num;
	return avg_data;
}

