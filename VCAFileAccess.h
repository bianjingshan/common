#ifndef _VCA_FILE_ACCESS_LIB_H_
#define _VCA_FILE_ACCESS_LIB_H_

#ifndef MODULE_OK
#define MODULE_OK 0
#endif
#ifndef MODULE_ERROR
#define MODULE_ERROR (-1)
#endif

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

bool VcaFileExist(const char *p_file_name);
bool VcaMkDir(const char *p_path_name);
bool VcaCopyFile(const char *p_src_file_name, const char *p_dst_file_name);
bool VcaMoveFile(const char *p_src_file_name, const char *p_dst_file_name);
bool DeleteAFile(const char *p_file_name);
bool DeleteAFile(const char *p_root_path_name, const char *p_sub_path_name, const char *p_file_name);
bool IsDirSeparator(char input_c);
const char *strrchr_DirSeparator(const char *p_string);
int VcaCreatePath(const char *p_path_name); //d:/a/b,   d:/a,   d:\a,   d:\a\,   d:/a/
int VcaCreateFilePath(const char *p_file_path_name);
char *ModuleFilePath(void);

/*
p_file_path_name:d:/a/b.jpg | b.jpg |a/b.jpg
p_path_name: d:/a | a/c
p_file_name: b
p_ext_name: jpg | bin
*/
int VcaSplitFileName(const char *p_file_path_name, char *p_path_name, char *p_file_name, char *p_ext_name);
int VcaKeepPath(const char *p_path_name, int keep_path_level, char *p_output_path);
bool SaveBinData(const char *p_file_name, void *p_buffer, unsigned long buffer_lenght);
bool LoadBinFile(const char *p_file_name, void *p_buffer, unsigned long buffer_lenght);
bool LoadBinFile(const char *p_file_name, void *p_buffer, unsigned long buffer_length, unsigned long *p_load_data_length);
bool GetHighLevelPath(const char *p_path_name, char *p_high_level_path_buffer, int buffer_lenght);
unsigned long VcaFileSize(const char *p_file_name);
bool GetFileCreateTime(const char *p_file_name, unsigned long long *p_time);

#endif


