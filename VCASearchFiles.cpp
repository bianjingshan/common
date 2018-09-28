#ifdef _WIN32
#include<windows.h>  
#else
#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>
#endif
#include <string.h>
#include<stdio.h>
#include "VCASearchFiles.h"


const char *image_ext_name[]={".jpg", ".bmp", ".jpeg", ".png", ".gif", NULL};
const char *video_ext_name[]={".mpg", ".avi", ".mp4", ".dav", ".flv", NULL};
const char *xml_ext_name[]={".xml", NULL};
const char *bin_ext_name[]={".bin", NULL};
const char *code_ext_name[]={".c",".cpp",".h",".hpp", NULL};


bool FileExtNameFilter(const char *p_file_name, const char **filter_ext)
{
	if(filter_ext==NULL)
	{
		return true;
	}
	const char *p_ext_name;
	int	iloop;

	p_ext_name=strrchr(p_file_name, '.');
	if(p_ext_name!=NULL)
	{
		for(iloop=0;iloop<1024;iloop++)
		{
			if(filter_ext[iloop]==NULL)
			{
				break;
			}
#ifdef _WIN32
			if(_stricmp(p_ext_name, filter_ext[iloop])==0)
#else
			if(strcasecmp(p_ext_name, filter_ext[iloop])==0)
#endif
			{
				return true;
			}
		}
	}
	return false;
}

#ifdef _WIN32
int SearchFiles(
	const char* root_path_name, 
	const char *sub_path_name, 
	const char **filter_ext, 
	void (*callback_func_file)(void *p_cbk_data, const char* cbk_root_path_name, const char *cbk_sub_path_name, const char *cbk_file_name),
	void (*callback_func_directory_start)(void *p_cbk_data, const char* cbk_root_path_name, const char *cbk_sub_path_name),
	void (*callback_func_directory_end)(void *p_cbk_data, const char* cbk_root_path_name, const char *cbk_sub_path_name, int file_count),
	void *p_data, 
	int *p_runing_flag)
{
	if(p_runing_flag)
	{
		if(*p_runing_flag<=0)
		{
			return 0;
		}
	}
	
	char path_ext_name[MAX_PATH];
	char next_sub_path_name[MAX_PATH];

	//printf("BrowPathFiles(%s, %s)\r\n", path_name, filterExt);
	//先拼接得到带扩展名的路径名path_ext_name字符串
	sprintf_s(path_ext_name, "%s%s\\*.*", root_path_name, sub_path_name);


	WIN32_FIND_DATA FileData;
	HANDLE    hSearch;
	int        nCount=0;
	int        nCount_sub=0;
	BOOL    fFinished = FALSE;

	// Start searching for path_ext_name files in the current directory.
	hSearch = FindFirstFile(path_ext_name, &FileData); //先搜索本路径下的第一个文件   
	if(hSearch != INVALID_HANDLE_VALUE)
	{
		if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if((strcmp(FileData.cFileName, ".")==0)||(strcmp(FileData.cFileName, "..")==0))
			{
				
			}
			else
			{
				if(callback_func_directory_start!=NULL)
				{
					callback_func_directory_start(p_data, root_path_name, next_sub_path_name);
				}
				sprintf_s(next_sub_path_name, "%s\\%s", sub_path_name, FileData.cFileName);
				nCount_sub=SearchFiles(root_path_name, next_sub_path_name, filter_ext, callback_func_file, callback_func_directory_start, callback_func_directory_end, p_data, p_runing_flag);
				nCount+=nCount_sub;
				if(callback_func_directory_end!=NULL)
				{
					callback_func_directory_end(p_data, root_path_name, next_sub_path_name, nCount_sub);
				}
			}
		}
		else
		{
			if(FileExtNameFilter(FileData.cFileName, filter_ext))
			{
				if(callback_func_file!=NULL)
				{
					callback_func_file(p_data, root_path_name, sub_path_name, FileData.cFileName);
				}
				nCount++;
			}
		}

		while(FindNextFile(hSearch, &FileData))
		{
			if(FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if((strcmp(FileData.cFileName, ".")==0)||(strcmp(FileData.cFileName, "..")==0))
				{
					
				}
				else
				{
					if(callback_func_directory_start!=NULL)
					{
						callback_func_directory_start(p_data, root_path_name, next_sub_path_name);
					}
					sprintf_s(next_sub_path_name, "%s\\%s", sub_path_name, FileData.cFileName);
					nCount_sub=SearchFiles(root_path_name, next_sub_path_name, filter_ext, callback_func_file, callback_func_directory_start, callback_func_directory_end, p_data, p_runing_flag);
					nCount+=nCount_sub;
					if(callback_func_directory_end!=NULL)
					{
						callback_func_directory_end(p_data, root_path_name, next_sub_path_name, nCount_sub);
					}
				}
			}
			else
			{
				if(FileExtNameFilter(FileData.cFileName, filter_ext))
				{
					if(callback_func_file!=NULL)
					{
						callback_func_file(p_data, root_path_name, sub_path_name, FileData.cFileName);
					}
					nCount++;
				}
			}
		}
		if(GetLastError() != ERROR_NO_MORE_FILES)
		{	
			//printf("Couldn't find next file.\r\n");
		}
		// Close the search handle.
		if(!FindClose(hSearch))
		{
			//printf("Couldn't close search handle.\r\n");
		}
	}
	else//否则没找到本路径下的第一个文件,即没找到任何文件
	{
		//printf("No file found.\r\n");
	}
	return nCount;
}
#else
int SearchFiles(
	const char* root_path_name, 
	const char *sub_path_name, 
	const char **filter_ext, 
	void (*callback_func_file)(void *p_cbk_data, const char* cbk_root_path_name, const char *cbk_sub_path_name, const char *cbk_file_name),
	void (*callback_func_directory_start)(void *p_cbk_data, const char* cbk_root_path_name, const char *cbk_sub_path_name),
	void (*callback_func_directory_end)(void *p_cbk_data, const char* cbk_root_path_name, const char *cbk_sub_path_name, int file_count),
	void *p_data, 
	int *p_runing_flag)
{
	if(p_runing_flag)
	{
		if(*p_runing_flag<=0)
		{
			return 0;
		}
	}
	char path_name[MAX_PATH];
	char next_sub_path_name[MAX_PATH];

	snprintf(path_name, MAX_PATH, "%s%s", root_path_name, sub_path_name);

	DIR *dp;
	struct dirent *dirp;
	int        nCount=0;
	int        nCount_sub=0;
	if((dp=opendir(path_name))==NULL)
	{
		printf("opendir.ERROR,%s\n", path_name);
		return 0;
	}
	while((dirp=readdir(dp))!=NULL)
	{
		if(dirp->d_type==DT_DIR)
		{
			if((strcmp(dirp->d_name,".")==0)||(strcmp(dirp->d_name,"..")==0))
			{
				
			}
			else
			{
				
				snprintf(next_sub_path_name, MAX_PATH, "%s/%s", sub_path_name, dirp->d_name);
				if(callback_func_directory_start!=NULL)
				{
					callback_func_directory_start(p_data, root_path_name, next_sub_path_name);
				}
				nCount_sub=0;
				nCount_sub=SearchFiles(root_path_name, next_sub_path_name, filter_ext, callback_func_file, callback_func_directory_start, callback_func_directory_end, p_data, p_runing_flag);
				nCount+=nCount_sub;
				if(callback_func_directory_end!=NULL)
				{
					callback_func_directory_end(p_data, root_path_name, next_sub_path_name, nCount_sub);
				}
			}
		}
		else
		{
			if(FileExtNameFilter(dirp->d_name, filter_ext))
			{
				if(callback_func_file!=NULL)
				{
					callback_func_file(p_data, root_path_name, sub_path_name, dirp->d_name);
				}
				nCount++;
			}
		}
		if(p_runing_flag)
		{
			if(*p_runing_flag<=0)
			{
				break;
			}
		}
	}
	closedir(dp);
	return nCount;
}
#endif


