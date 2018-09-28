#include <time.h>
#include <stdarg.h>
#ifdef _WIN32

#else
#include <unistd.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "VCAString.h"
#include "VCAFileAccess.h"
#include "VCALogManage.h"

CVCALogManage g_vca_error;
CVCALogManage g_vca_debug_msg;

CVCALogManage::CVCALogManage(void)
{
	m_output_en=true;
	m_file_name[0]=0;
}

CVCALogManage::CVCALogManage(const char *p_file_name, const char *root_path, bool clear_log)
{
	m_output_en=true;
	SetOutputFileName(p_file_name, root_path);
	if(clear_log)
	{
		Clear();
	}
}


void CVCALogManage::SetOutputFileName(const char *p_file_name, const char *root_path)
{
	if(root_path==NULL)
	{
		VCA_SPRINTF_S(m_file_name, 4096, "%s/%s", ModuleFilePath(), p_file_name);
	}
	else
	{
		VCA_SPRINTF_S(m_file_name, 4096, "%s/%s", root_path, p_file_name);
	}
}


void CVCALogManage::print(const char *fmt, ...)
{
	if(m_output_en)
	{
		int data_len=0, temp_len;
		data_len+=GetTimeString(m_msg_buffer);
		data_len+=sprintf(m_msg_buffer+data_len, ", ");
		va_list args;
		va_start(args, fmt);
		temp_len=vsprintf(m_msg_buffer+data_len, fmt, args);
		if(temp_len<0)
		{
			PRINT_ERROR;
			return;
		}
		data_len+=temp_len;
		data_len+=sprintf(m_msg_buffer+data_len, "\n");

		if(!VcaFileExist(m_file_name))
		{
			VcaCreateFilePath(m_file_name);
		}
		FILE *fp;
		fp=fopen(m_file_name, "a");
		if(fp==NULL)
		{
			PRINT_ERROR;
			return;
		}
		int temp_result;
		temp_result=fwrite(m_msg_buffer, data_len, 1, fp);
		fclose(fp);		
	}
}

void CVCALogManage::print_without_time(const char *fmt, ...)
{
	if(m_output_en)
	{
		int data_len=0, temp_len;
		va_list args;
		va_start(args, fmt);
		temp_len=vsprintf(m_msg_buffer+data_len, fmt, args);
		if(temp_len<0)
		{
			PRINT_ERROR;
			return;
		}
		data_len+=temp_len;
		data_len+=sprintf(m_msg_buffer+data_len, "\n");

		if(!VcaFileExist(m_file_name))
		{
			VcaCreateFilePath(m_file_name);
		}
		FILE *fp;
		fp=fopen(m_file_name, "a");
		if(fp==NULL)
		{
			PRINT_ERROR;
			return;
		}
		int temp_result;
		temp_result=fwrite(m_msg_buffer, data_len, 1, fp);
		fclose(fp);		
	}
}



void CVCALogManage::Clear(void)
{
	remove(m_file_name);
}

int CVCALogManage::GetTimeString(char *p_buffer)
{
	time_t temp_time;
	time(&temp_time);
	struct tm *tt=localtime(&temp_time);
	return sprintf(p_buffer, "%04u-%02u-%02u %02u:%02u:%02u", tt->tm_year+1900,tt->tm_mon+1,tt->tm_mday,tt->tm_hour,tt->tm_min,tt->tm_sec);
}


