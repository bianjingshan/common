#ifdef _WIN32
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <windows.h>
#include <shlwapi.h>
#include <fstream>
#include "math.h"
#include <stdlib.h>
#include <direct.h>
#include  <io.h>
#include <ctime>
#include <cstdlib>
#include "math.h"
#include <ShlObj.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#endif
//#include "VCAString.h"
#include "VCAFileAccess.h"

bool VcaFileExist(const char *p_file_name)
{
	int access_result;
#ifdef _WIN32
	access_result=_access(p_file_name, 0);
#else
	access_result=access(p_file_name, F_OK);
#endif
	if(0==access_result)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool VcaMkDir(const char *p_path_name)
{
	if(!VcaFileExist(p_path_name))
	{
#ifdef _WIN32
		_mkdir(p_path_name);
#else
		mkdir(p_path_name, S_IRWXG|S_IRWXO|S_IRWXU);
#endif
	}
	return true;
}

bool DeleteAFile(const char *p_file_name)
{
	if(NULL==p_file_name)
	{
		return false;
	}
	if(p_file_name[0]!=0)
	{
		if(VcaFileExist(p_file_name))
		{
#ifdef _WIN32
			DeleteFile(p_file_name);
#else
			remove(p_file_name);
#endif
		}
	}
	return true;
}

bool DeleteAFile(const char *p_root_path_name, const char *p_sub_path_name, const char *p_file_name)
{
	char temp_file_name[MAX_PATH];

	sprintf(temp_file_name, "%s%s/%s", p_root_path_name, p_sub_path_name, p_file_name);
	return DeleteAFile(temp_file_name);
}

bool VcaCopyFile(const char *p_src_file_name, const char *p_dst_file_name)
{
	VcaCreateFilePath(p_dst_file_name);
#ifdef _WIN32
	if(CopyFile(p_src_file_name, p_dst_file_name, false)==0)
	{
		return false;
	}
#else
	char cmd[1024];
	memset(cmd,0, sizeof(cmd));
	sprintf(cmd,"cp \"%s\" \"%s\"", p_src_file_name, p_dst_file_name);
	system(cmd);
#endif	
	return true;
}

bool VcaMoveFile(const char *p_src_file_name, const char *p_dst_file_name)
{
	VcaCreateFilePath(p_dst_file_name);
#ifdef _WIN32
	if(MoveFile(p_src_file_name, p_dst_file_name)==0)
	{
		return false;
	}
#else
	char cmd[1024];
	memset(cmd,0, sizeof(cmd));
	sprintf(cmd,"mv \"%s\" \"%s\"", p_src_file_name, p_dst_file_name);
	system(cmd);
#endif	
	return true;
}

bool IsDirSeparator(char input_c)
{
#ifdef _WIN32
	if(('/'==input_c)||('\\'==input_c))
#else
	if('/'==input_c)
#endif	
	{
		return true;
	}
	else
	{
		return false;
	}
}

const char *strrchr_DirSeparator(const char *p_string)
{
	const char *p_pointer=p_string+strlen(p_string)-1;

	while(p_pointer>=p_string)
	{
		if(IsDirSeparator(*p_pointer))
		{
			return p_pointer;
		}
		p_pointer--;
	}
	return NULL;
}

int VcaCreatePath(const char *p_path_name)
{
	char temp_path_name[MAX_PATH];
	int str_length;
	int iloop;

	str_length=strlen(p_path_name);
	if(str_length<=0)
	{
		return MODULE_ERROR;
	}
	if(IsDirSeparator(p_path_name[str_length-1]))
	{
		str_length--;
	}
	
	for(iloop=1;iloop<=str_length;iloop++)
	{
		if(IsDirSeparator(p_path_name[iloop])||(p_path_name[iloop]==0))
		{
			memcpy(temp_path_name, p_path_name, iloop);
			temp_path_name[iloop]=0;
			VcaMkDir(temp_path_name);
		}
	}
	return MODULE_OK;
}

int VcaCreateFilePath(const char *p_file_path_name)
{
	char temp_path_name[MAX_PATH];
	const char *p_path_end;
	
	memset(temp_path_name, 0, sizeof(temp_path_name));
	p_path_end=strrchr_DirSeparator(p_file_path_name);
	if(p_path_end==NULL)
	{
		return MODULE_OK;
	}
	memcpy(temp_path_name, p_file_path_name, (p_path_end-p_file_path_name));
	VcaCreatePath(temp_path_name);
	return MODULE_OK;
}

char *ModuleFilePath(void)
{
	static char module_file_path[MAX_PATH];
	static bool startFlag=true;
	if(startFlag)
	{
		startFlag=false;
#ifdef _WIN32
		GetModuleFileName(NULL, module_file_path, MAX_PATH);
		char *p_temp=strrchr(module_file_path, '\\');
		if(p_temp!=NULL)
		{
			*p_temp=0;
		}
#else
		getcwd(module_file_path, MAX_PATH);
#endif
	}
	return module_file_path;
}

int VcaSplitFileName(const char *p_file_path_name, char *p_path_name, char *p_file_name, char *p_ext_name)
{
	if(p_file_path_name==NULL)
	{
		return MODULE_ERROR;
	}
	const char *p_file_name_start, *p_ext_start;
	int temp_length;

	p_file_name_start=strrchr_DirSeparator(p_file_path_name);
	if(p_file_name_start==NULL)
	{
		p_file_name_start=p_file_path_name;
	}
	else
	{
		p_file_name_start++;
	}
	if(strlen(p_file_name_start)<=0)
	{
		return MODULE_ERROR;
	}
	
	p_ext_start=strrchr(p_file_name_start, '.');
	if(p_ext_start==NULL)
	{
		return MODULE_ERROR;
	}
	p_ext_start++;
	if(strlen(p_ext_start)<=0)
	{
		return MODULE_ERROR;
	}
	if(p_path_name)
	{
		temp_length=(p_file_name_start-p_file_path_name-1);
		if(temp_length>0)
		{
			memcpy(p_path_name, p_file_path_name, temp_length);
			p_path_name[temp_length]=0;
		}
		else
		{
			p_path_name[0]=0;
		}
	}
	if(p_file_name)
	{
		temp_length=(p_ext_start-p_file_name_start-1);
		memcpy(p_file_name, p_file_name_start, temp_length);
		p_file_name[temp_length]=0;
	}
	if(p_ext_name)
	{
		temp_length=strlen(p_ext_start);
		memcpy(p_ext_name, p_ext_start, temp_length);
		p_ext_name[temp_length]=0;
	}
	return MODULE_OK;
}


int VcaKeepPath(const char *p_path_name, int keep_path_level, char *p_output_path)
{
	char temp_path_name[MAX_PATH];
	int str_length;
	int iloop, temp_level=0;

	str_length=strlen(p_path_name);
	if(str_length<=0)
	{
		return MODULE_ERROR;
	}
	if((p_path_name[str_length-1]=='/')||(p_path_name[str_length-1]=='\\'))
	{
		str_length--;
	}
	
	for(iloop=1;iloop<=str_length;iloop++)
	{
		if((p_path_name[iloop]=='/')||(p_path_name[iloop]=='\\')||(p_path_name[iloop]==0))
		{
			temp_level++;
			if(temp_level>=keep_path_level)
			{
				break;
			}
		}
	}
	memset(temp_path_name, 0, MAX_PATH);
	memcpy(temp_path_name, p_path_name, iloop);
	strcpy(p_output_path, temp_path_name);
	return MODULE_OK;
}


bool SaveBinData(const char *p_file_name, void *p_buffer, unsigned long buffer_lenght)
{
	VcaCreateFilePath(p_file_name);
	FILE *fp;
	fp=fopen(p_file_name, "wb+");
	if(NULL == fp)
	{
		return false;
	}
	fwrite(p_buffer, 1, buffer_lenght, fp);
	fclose(fp);
	return true;
}

bool LoadBinFile(const char *p_file_name, void *p_buffer, unsigned long buffer_lenght)
{
	FILE *fp;
	fp=fopen(p_file_name, "rb");
	if(NULL == fp)
	{
		memset(p_buffer, 0, buffer_lenght);
		return false;
	}
	int read_len=fread(p_buffer, 1, buffer_lenght, fp);
	fclose(fp);
	if(read_len!=buffer_lenght)
	{
		memset(p_buffer, 0, buffer_lenght);
		return false;
	}
	return true;
}

bool LoadBinFile(const char *p_file_name, void *p_buffer, unsigned long buffer_length, unsigned long *p_load_data_length)
{
	FILE *fp;
	fp=fopen(p_file_name, "rb");
	if(NULL == fp)
	{
		memset(p_buffer, 0, buffer_length);
		return false;
	}
	unsigned long read_len=fread(p_buffer, 1, buffer_length, fp);
	fclose(fp);
	*p_load_data_length=read_len;
	return true;
}


bool GetHighLevelPath(const char *p_path_name, char *p_high_level_path_buffer, int buffer_lenght)
{
	int str_length;
	int iloop;

	str_length=strlen(p_path_name);
	if(str_length<=0)
	{
		return false;
	}
	if((p_path_name[str_length-1]=='/')||(p_path_name[str_length-1]=='\\'))
	{
		str_length--;
	}
	for(iloop=(str_length-1);iloop>0;iloop--)
	{
		if(
			(p_path_name[iloop]=='/')
			||((p_path_name[iloop]=='\\')&&(p_path_name[iloop-1]!='\\'))
			)
		{
			if(iloop>buffer_lenght)
			{
				return false;
			}
			memcpy(p_high_level_path_buffer, p_path_name, iloop);
			p_high_level_path_buffer[iloop]=0;
			return true;
		}
	}
	return false;
}

unsigned long VcaFileSize(const char *p_file_name)
{
	FILE *fp;
	if((fp=fopen(p_file_name,"r"))==NULL)
	{
		return 0;
	}
	fseek(fp,0,SEEK_END);
	unsigned long file_size=ftell(fp);
	fclose(fp);
	return file_size;
}


bool GetFileCreateTime(const char *p_file_name, unsigned long long *p_time)
{
#ifdef _WIN32
	HFILE hFile=_lopen(p_file_name,OF_READ);
	FILETIME ftCreate, ftAccess, ftWrite;
	if (!GetFileTime((HANDLE*)hFile, &ftCreate, &ftAccess, &ftWrite))
	{
		return false;
	}
	ULARGE_INTEGER ui;  
	ui.LowPart=ftCreate.dwLowDateTime;
	ui.HighPart=ftCreate.dwHighDateTime;
	*p_time=((unsigned long long)((LONGLONG)(ui.QuadPart-116444736000000000)/10000000)); 
#else
	struct stat file_buf;
	
	if(stat(p_file_name, &file_buf)!=0)
	{
		return false;
	}
	*p_time=file_buf.st_mtime;
#endif
	return true;
}


