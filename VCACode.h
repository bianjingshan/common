#pragma once

#ifndef _WIN32

#include <iconv.h>

class CodeConverter {
private:
	iconv_t cd;
public:
	CodeConverter(const char *from_charset,const char *to_charset);
	~CodeConverter();
	int convert(char *inbuf,int inlen,char *outbuf,int outlen);
}; 

#endif
