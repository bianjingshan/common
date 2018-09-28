#ifndef _VCA_LOG_MANAGE_H_
#define _VCA_LOG_MANAGE_H_

class  CVCALogManage
{
public:
	CVCALogManage(void);
	CVCALogManage(const char *p_file_name, const char *root_path=NULL, bool clear_log=true); //p_file_name:a.txt,a/b.txt, root_path:a, a/b
	void SetOutputFileName(const char *p_file_name, const char *root_path=NULL);
	void print(const char *fmt, ...);
	void print_without_time(const char *fmt, ...);
	void Clear(void);
	int GetTimeString(char *p_buffer);
	char m_file_name[4096];
	bool m_output_en;
	char m_msg_buffer[4096];
};


extern CVCALogManage g_vca_error;
extern CVCALogManage g_vca_debug_msg;

//#define VCA_LOG_DEBUG_MODE

#define LOG_INIT {g_vca_error.SetOutputFileName("log/VCA_error.txt");g_vca_debug_msg.SetOutputFileName("log/VCA_debug_msg.txt");}
#define LOG_CLEAR {g_vca_error.Clear();g_vca_debug_msg.Clear();}

#ifdef VCA_LOG_DEBUG_MODE
#define PRINT_CODE printf("%s.%s.%d\r\n", __FUNCTION__, __FILE__, __LINE__)
#define PRINT_CODE_MSG(x) printf("%s.%s.%d(%s)\r\n", __FUNCTION__, __FILE__, __LINE__,x)
#define PRINT_CODE_INT(x) printf("%s.%s.%d(%d)\r\n", __FUNCTION__, __FILE__, __LINE__,x)
#define LOG_CODE PRINT_CODE;g_vca_debug_msg.print("%s.%s.%d", __FUNCTION__, __FILE__, __LINE__)
#define LOG_CODE_MSG(x) g_vca_debug_msg.print("%s.%s.%d(%s)", __FUNCTION__, __FILE__, __LINE__,x)
#define LOG_CODE_INT(x) g_vca_debug_msg.print("%s.%s.%d(%d)", __FUNCTION__, __FILE__, __LINE__,x)
#define LOG_FUNCTION g_vca_debug_msg.print("%s()", __FUNCTION__)

#else
#define PRINT_CODE 
#define PRINT_CODE_MSG(x) 
#define PRINT_CODE_INT(x) 
#define LOG_CODE 
#define LOG_CODE_MSG(x) 
#define LOG_CODE_INT(x) 
#define LOG_FUNCTION 

#endif

#define PRINT_ERROR printf("%s.ERROR.%s.%d\r\n", __FUNCTION__, __FILE__, __LINE__)
#define PRINT_ERROR_INT(x) printf("%s.ERROR.%s.%d,%d\r\n", __FUNCTION__, __FILE__, __LINE__,x)
#define PRINT_ERROR_MSG(x) printf("%s.ERROR.%s.%d,%s\r\n", __FUNCTION__, __FILE__, __LINE__,x)
#define LOG_ERROR {PRINT_ERROR;g_vca_error.print("%s.ERROR.%s.%d", __FUNCTION__, __FILE__, __LINE__);}
#define LOG_ERROR_INT(x) {PRINT_ERROR_INT(x);g_vca_error.print("%s.ERROR.%s.%d,%d", __FUNCTION__, __FILE__, __LINE__, x);}
#define LOG_ERROR_MSG(x) {PRINT_ERROR_MSG(x);g_vca_error.print("%s.ERROR.%s.%d,%s", __FUNCTION__, __FILE__, __LINE__, x);}

#endif

