

#ifndef _WIN32
#include <string.h>
#include <iconv.h>
#include <iostream>
#include "VCACode.h"

using namespace std;

CodeConverter::CodeConverter(const char *from_charset,const char *to_charset) 
{
	cd = iconv_open(to_charset,from_charset);
}
	
CodeConverter::~CodeConverter() 
{
	iconv_close(cd);
}
	
int CodeConverter::convert(char *inbuf,int inlen,char *outbuf,int outlen) 
{
	char **pin = &inbuf;
	char **pout = &outbuf;
	size_t temp_inlen, temp_outlen;
	
	memset(outbuf,0,outlen);
	temp_inlen=inlen;
	temp_outlen=outlen;
	return iconv(cd, pin, &temp_inlen, pout, &temp_outlen);
}

#endif
