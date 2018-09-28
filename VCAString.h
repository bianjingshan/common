#pragma once


#ifndef MODULE_OK
#define MODULE_OK 0
#endif
#ifndef MODULE_ERROR
#define MODULE_ERROR (-1)
#endif

#ifdef _WIN32
#define VCA_SPRINTF_S sprintf_s
#define VCA_STRICMP stricmp
#define PATH_Separator "\\"
#else
#define VCA_SPRINTF_S snprintf
#define VCA_STRICMP strcasecmp
#define PATH_Separator "/"
#endif

bool GetNum(const char *string_buffer, int *p_num);
bool GetOnePara(char *file_buffer, const char *para_name, int *p_para, int default_value, bool print_msg=false, void *p_log_msg=NULL);
bool GetOneParaUlong(char *file_buffer, const char *para_name, unsigned long *p_para, unsigned long default_value, bool print_msg=false, void *p_log_msg=NULL);
bool GetOneParaDouble(char *file_buffer, const char *para_name, double *p_para, double default_value, bool print_msg=false, void *p_log_msg=NULL);
bool GetOneParaString(char *file_buffer, const char *para_name, char *p_para, bool print_msg=false, void *p_log_msg=NULL);
#if 0
bool char2wchar(char *p_input_string, wchar_t *p_output_string, int output_string_buffer_len);
#endif
#if 0
bool array2String(int array[], int count, char *p_buffer);
bool array2String(unsigned long array[], int count, char *p_buffer);
bool string2Array(char *p_buffer, int array[], int count);
bool string2Array(char *p_buffer, unsigned long array[], int count);
#endif

#ifdef _WIN32
bool GB2312ToUTF8(const char *input_string, char *out_buffer, int out_buffer_len);
bool GB2312ToUnicode(const char *input_string, wchar_t *out_buffer, int out_buffer_len);
#endif


