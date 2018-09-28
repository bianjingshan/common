#ifndef _VCA_MSG_H_
#define _VCA_MSG_H_

void* VcaMsgCreate(void);
bool VcaMsgSend(void *p_msg, void *p_buffer, int msg_size);
bool VcaMsgRecv(void *p_msg, void *p_buffer, int msg_size);

#endif

