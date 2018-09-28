#ifndef _VCA_SEM_LIB_H_
#define _VCA_SEM_LIB_H_

void* VcaSemCreate(int init_value);
bool VcaSemTake(void *p_sem);
bool VcaSemGive(void *p_sem);

#endif

