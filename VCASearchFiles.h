#ifndef _SEARCH_FILES_H_
#define _SEARCH_FILES_H_

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

extern const char *image_ext_name[];
extern const char *video_ext_name[];
extern const char *xml_ext_name[];
extern const char *bin_ext_name[];
extern const char *code_ext_name[];

bool FileExtNameFilter(const char *p_file_name, const char **filter_ext);
int SearchFiles(
	const char* root_path_name, //"a:\b\c"
	const char *sub_path_name, //"\d\e"
	const char **filter_ext=NULL, 
	void (*callback_func_file)(void *p_cbk_data, const char* cbk_root_path_name, const char *cbk_sub_path_name, const char *cbk_file_name)=NULL, //filename="%s%s/%s",cbk_root_path_name,cbk_sub_path_name,cbk_file_name
	void (*callback_func_directory_start)(void *p_cbk_data, const char* cbk_root_path_name, const char *cbk_sub_path_name)=NULL, //filename="%s%s",cbk_root_path_name,cbk_sub_path_name
	void (*callback_func_directory_end)(void *p_cbk_data, const char* cbk_root_path_name, const char *cbk_sub_path_name, int file_count)=NULL,
	void *p_data=NULL, 
	int *p_runing_flag=NULL);

#endif

