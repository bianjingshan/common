#ifndef _VCA_MATH_LIB_H_
#define _VCA_MATH_LIB_H_


double GetDispersion(double *p_input_data, int input_data_num);
double GetAverage(double *p_input_data, int input_data_num);

//包括start和end
class CVcaRand
{
public:
	CVcaRand(void);
	int GetRand(int start, int end);

	//生成递增排列的不重复随机序列
	bool CreateIncreaseRandSequence(int start, int end, int sequence_num, int *p_sequence_buffer);
};

int VcaMin(int value1, int value2);
double VcaMin(double value1, double value2);

#define VCA_MIN(x,y) ((x>y)? y:x)
#define VCA_MAX(x,y) ((x>y)? x:y)

#endif

