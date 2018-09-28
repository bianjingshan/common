#pragma once

struct strptime_time{
	int sec;
	int min;
	int hour;
	int mday;
	int mon;
	int year;
	int wday;
};

char *strptime(const char *buf, const char *fmt, struct tm *tm);
bool GetTMFromFileName(const char *p_file_name, tm *p_tm);
bool GetTimeFromFileName(const char *p_file_name, tm *p_tm);
bool GetTimeFromFileName(const char *p_file_name, unsigned long *p_time);
bool GetTimeFromFileName(const char *p_file_name, unsigned long long *p_time);


