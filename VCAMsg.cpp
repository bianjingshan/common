#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/errno.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "VCAMsg.h"

void* VcaMsgCreate(void)
{
#ifdef _WIN32
	return (void *)NULL;
#else
	int *p_id=(int *)malloc(sizeof(int));
	int msg_id;

	for(int iloop=1000;iloop<8000;iloop++)
	{
		msg_id=msgget(iloop, IPC_EXCL);
		if(msg_id<0)
		{
			msg_id=msgget(iloop, IPC_CREAT|0666);
			if(msg_id<0)
			{
				return (void *)NULL;
			}
			else
			{
				*p_id=iloop;
				printf("\nVcaMsgCreate, id=%d, msg_id=%d", *p_id, msg_id);
				return (void *)p_id;
			}
		}
	}
	return (void *)NULL;
#endif
}

bool VcaMsgRecv(void *p_msg, void *p_buffer, int msg_size)
{
#ifdef _WIN32
	return false;
#else
	int *p_id=(int *)p_msg;
	int msg_id;
	msg_id=msgget(*p_id, IPC_EXCL);
	printf("\nVcaMsgRecv, id=%d, msg_id=%d", *p_id, msg_id);
	if(msgrcv(msg_id, p_buffer, msg_size, 0, 0)<0)
	{
		printf("\nVcaMsgRecv, d\n");
		return false;
	}
	printf("\nVcaMsgRecv, c\n");
#endif
	return true;
}

bool VcaMsgSend(void *p_msg, void *p_buffer, int msg_size)
{
#ifdef _WIN32
	return false;
#else
	int *p_id=(int *)p_msg;
	int msg_id;
	msg_id=msgget(*p_id, IPC_EXCL);
	printf("\nVcaMsgSend, id=%d, msg_id=%d", *p_id, msg_id);
	if(msgsnd(msg_id, p_buffer, msg_size, 0)<0)
	{
		return false;
	}
#endif
	return true;
}



