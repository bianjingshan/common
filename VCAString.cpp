#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "VCALogManage.h"
#include "VCAMath.h"
#include "VCAString.h"

#ifdef _WIN32
#include "windows.h"
#endif

bool GetNum(const char *string_buffer, int *p_num)
{
	const char *p_start_string;
	char *p_end_string;

	p_start_string=string_buffer;
	*p_num=strtol(p_start_string, &p_end_string, 10);
	if(p_end_string==p_start_string)
	{
		*p_num=0;
		return false;
	}
	return true;
}

bool GetOnePara(char *file_buffer, const char *para_name, int *p_para, int default_value, bool print_msg, void *p_log_msg)
{
	char *p_end_string;
	bool return_value=false;
	CVCALogManage *p_log=(CVCALogManage *)p_log_msg;
	char temp_string[256];

	if(file_buffer==NULL)
	{
		return false;
	}
	if(para_name==NULL)
	{
		return false;
	}
	if(p_para==NULL)
	{
		return false;
	}
	if(GetOneParaString(file_buffer, para_name, temp_string))
	{
		*p_para=strtol(temp_string, &p_end_string, 10);
		if(p_end_string!=temp_string)
		{
			return_value=true;
		}
	}
	sprintf(temp_string, "%s:%d", para_name, *p_para);
	if(!return_value)
	{
		*p_para=default_value;
		strcat(temp_string, "(default)");
	}
	if(print_msg)printf("\r\n%s", temp_string);
	if(p_log)p_log->print("%s", temp_string);
	return return_value;
}



bool GetOneParaUlong(char *file_buffer, const char *para_name, unsigned long *p_para, unsigned long default_value, bool print_msg, void *p_log_msg)
{
	char *p_end_string;
	bool return_value=false;
	CVCALogManage *p_log=(CVCALogManage *)p_log_msg;
	char temp_string[256];

	if(file_buffer==NULL)
	{
		return false;
	}
	if(para_name==NULL)
	{
		return false;
	}
	if(p_para==NULL)
	{
		return false;
	}
	if(GetOneParaString(file_buffer, para_name, temp_string))
	{
		*p_para=strtoul(temp_string, &p_end_string, 10);
		if(p_end_string!=temp_string)
		{
			return_value=true;
		}
	}
	sprintf(temp_string, "%s:%lu", para_name, *p_para);
	if(!return_value)
	{
		*p_para=default_value;
		strcat(temp_string, "(default)");
	}
	if(print_msg)printf("\r\n%s", temp_string);
	if(p_log)p_log->print("%s", temp_string);
	return return_value;
}



bool GetOneParaDouble(char *file_buffer, const char *para_name, double *p_para, double default_value, bool print_msg, void *p_log_msg)
{
	char *p_end_string;
	bool return_value=false;
	CVCALogManage *p_log=(CVCALogManage *)p_log_msg;
	char temp_string[256];

	if(file_buffer==NULL)
	{
		return false;
	}
	if(para_name==NULL)
	{
		return false;
	}
	if(p_para==NULL)
	{
		return false;
	}
	if(GetOneParaString(file_buffer, para_name, temp_string))
	{
		*p_para=strtod(temp_string, &p_end_string);
		if(p_end_string!=temp_string)
		{
			return_value=true;
		}
	}
	sprintf(temp_string, "%s:%f", para_name, *p_para);
	if(!return_value)
	{
		*p_para=default_value;
		strcat(temp_string, "(default)");
	}
	if(print_msg)printf("\r\n%s", temp_string);
	if(p_log)p_log->print("%s", temp_string);
	return return_value;
}

#if 0
char* GetOneParaString(char *file_buffer, const char *para_name, bool print_msg, void *p_log_msg)
{
	char *p_search_string, *p_start_string;
	CVCALogManage *p_log=(CVCALogManage *)p_log_msg;

	if(file_buffer==NULL)
	{
		return NULL;
	}
	if(para_name==NULL)
	{
		return NULL;
	}

	p_search_string=strstr(file_buffer, para_name);
	if(p_search_string!=NULL)
	{
		p_start_string=p_search_string+strlen(para_name)+1;
		if(print_msg)
		{
			printf("\r\n%s:%s", para_name, p_start_string);
		}
		if(p_log)
		{
			p_log->print("%s:%s", para_name, p_start_string);
		}
		return p_start_string;
	}
	else
	{
		if(print_msg)
		{
			printf("\r\n%s:NULL(default)", para_name);
		}
		if(p_log)
		{
			p_log->print("%s:NULL(default)", para_name);
		}
		return NULL;
	}
}
#endif


bool GetOneParaString(char *file_buffer, const char *para_name, char *p_para, bool print_msg, void *p_log_msg)
{
	char *p_start_string, *p_end_string, *p_end_string_r, *p_end_string_n;
	char temp_para_name[256];
	int para_len=0;
	CVCALogManage *p_log=(CVCALogManage *)p_log_msg;

	p_para[0]=0;
	if(file_buffer==NULL)
	{
		return false;
	}
	if(para_name==NULL)
	{
		return false;
	}
	VCA_SPRINTF_S(temp_para_name, sizeof(temp_para_name), "%s ", para_name);
	p_start_string=strstr(file_buffer, temp_para_name);
	if(p_start_string==NULL)
	{
		if(print_msg)
		{
			printf("\r\n%s:%s(default)", para_name, p_para);
		}
		if(p_log)
		{
			p_log->print("%s:%s(default)", para_name, p_para);
		}
		return false;
	}
	p_start_string=p_start_string+strlen(temp_para_name);
	p_end_string_n=strchr(p_start_string, '\n');
	p_end_string_r=strchr(p_start_string, '\r');
	if((p_end_string_n!=NULL)&&(p_end_string_r!=NULL))
	{
		p_end_string=VCA_MIN(p_end_string_n, p_end_string_r);
	}
	else
	{
		p_end_string=VCA_MAX(p_end_string_n, p_end_string_r);
	}
	
	if(p_end_string==NULL)
	{
		para_len=strlen(p_start_string);
	}
	else
	{
		para_len=p_end_string-p_start_string;
	}
	memcpy(p_para, p_start_string, para_len);
	p_para[para_len]=0;
	if(print_msg)
	{
		printf("\r\n%s:%s", para_name, p_para);
	}
	if(p_log)
	{
		p_log->print("%s:%s", para_name, p_para);
	}
	return true;
}

#if 0
bool char2wchar(char *p_input_string, wchar_t *p_output_string, int output_string_buffer_len)
{
	int length=MultiByteToWideChar(CP_ACP,0,p_input_string,-1,NULL,0);
	if((length+1)>output_string_buffer_len)
	{
		return false;
	}
	MultiByteToWideChar(CP_ACP, 0, p_input_string, length, p_output_string, length+1);
	p_output_string[length]=0;
	return true;
}
#endif

#if 0
bool array2String(int array[], int count, char *p_buffer)
{
	if(array==NULL)
	{
		return false;
	}
	if(p_buffer==NULL)
	{
		return false;
	}
	int offset_len=0;
	for(int iloop=0;iloop<count;iloop++)
	{
		offset_len+=sprintf(p_buffer+offset_len, "%d,", array[iloop]);
	}
	if(offset_len>0)
	{
		p_buffer[offset_len-1]=0;
	}
	return true;
}

bool array2String(unsigned long array[], int count, char *p_buffer)
{
	if(array==NULL)
	{
		return false;
	}
	if(p_buffer==NULL)
	{
		return false;
	}
	int offset_len=0;
	for(int iloop=0;iloop<count;iloop++)
	{
		offset_len+=sprintf(p_buffer+offset_len, "%lu,", array[iloop]);
	}
	if(offset_len>0)
	{
		p_buffer[offset_len-1]=0;
	}
	return true;
}


bool string2Array(char *p_buffer, int array[], int count)
{
	if(array==NULL)
	{
		return false;
	}
	int temp_count=0;
	char *p_start_string=p_buffer;
	char *p_end_string;
	while(1)
	{
		if(p_start_string==NULL)
		{
			return false;
		}
		array[temp_count]=strtol(p_start_string, &p_end_string, 10);
		if(p_end_string==p_start_string)
		{
			return false;
		}
		temp_count++;
		if(temp_count>=count)
		{
			return true;
		}
		p_start_string=strchr(p_start_string, ',');
		if(p_start_string==NULL)
		{
			return false;
		}
		p_start_string++;
	}
}


bool string2Array(char *p_buffer, unsigned long array[], int count)
{
	if(array==NULL)
	{
		return false;
	}
	int temp_count=0;
	char *p_start_string=p_buffer;
	char *p_end_string;
	while(1)
	{
		if(p_start_string==NULL)
		{
			return false;
		}
		array[temp_count]=strtol(p_start_string, &p_end_string, 10);
		if(p_end_string==p_start_string)
		{
			return false;
		}
		temp_count++;
		if(temp_count>=count)
		{
			return true;
		}
		p_start_string=strchr(p_start_string, ',');
		if(p_start_string==NULL)
		{
			return false;
		}
		p_start_string++;
	}
}
#endif

#ifdef _WIN32
bool GB2312ToUTF8(const char *input_string, char *out_buffer, int out_buffer_len)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, input_string, -1, NULL, 0);
	wchar_t * pwBuf = new wchar_t[nwLen + 1];//+1的作用是保证字符串有结束符
	ZeroMemory(pwBuf, nwLen * 2 + 2);  
	::MultiByteToWideChar(CP_ACP, 0, input_string, strlen(input_string), pwBuf, nwLen);  
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);  
	if(nLen>=out_buffer_len)
	{
		delete []pwBuf;
		return false;
	}
	ZeroMemory(out_buffer, nLen + 1);  
	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, out_buffer, nLen, NULL, NULL);  
	delete []pwBuf;
	return true;
}

bool GB2312ToUnicode(const char *input_string, wchar_t *out_buffer, int out_buffer_len)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, input_string, -1, NULL, 0);
	if(nwLen>=out_buffer_len)
	{
		return false;
	}
	ZeroMemory(out_buffer, nwLen * 2 + 2);  
	::MultiByteToWideChar(CP_ACP, 0, input_string, strlen(input_string), out_buffer, nwLen);  
	return true;
}
#endif

