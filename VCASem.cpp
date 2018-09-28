#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <semaphore.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "VCASem.h"

void* VcaSemCreate(int init_value)
{
#ifdef _WIN32
	HANDLE *p_sem=(HANDLE *)malloc(sizeof(HANDLE));
	if(p_sem==NULL)
	{
		return NULL;
	}
	*p_sem=CreateSemaphore(NULL,init_value,32767,NULL);
	return (void *)p_sem;
#else
	sem_t *p_sem=(sem_t *)malloc(sizeof(sem_t));
	if(p_sem==NULL)
	{
		return NULL;
	}
	if(sem_init(p_sem, 0, init_value)!=0)
	{
		return NULL;
	}
	return (void *)p_sem;
#endif
}

bool VcaSemTake(void *p_sem)
{
#ifdef _WIN32
	if(0!=WaitForSingleObject(*((HANDLE *)p_sem), INFINITE))
	{
		return false;
	}
#else
	if(sem_wait((sem_t *)p_sem)!=0)
	{
		return false;
	}
#endif
	return true;
}

bool VcaSemGive(void *p_sem)
{
#ifdef _WIN32
	long count;
	if(!ReleaseSemaphore(*((HANDLE *)p_sem),1,&count))
	{
		return false;
	}
#else
	if(sem_post((sem_t *)p_sem)!=0)
	{
		return false;
	}
#endif
	return true;
}



