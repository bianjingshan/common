#ifndef _CRC_LIB_H_
#define _CRC_LIB_H_

typedef unsigned int CRC_UINT_32;

CRC_UINT_32 CRC32(unsigned char *p_buffer, CRC_UINT_32 len);
unsigned char CRC8(unsigned char *p_buffer, unsigned long len);
#endif

