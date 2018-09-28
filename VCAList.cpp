#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <math.h> 
#include <stdio.h>
#include "VCAList.h"
#include "VCALogManage.h"

VCA_PNODE VCAListCreate(void)
{
	VCA_PNODE p_head;

	p_head=(VCA_PNODE)malloc(sizeof(VCA_NODE));
	if(p_head==NULL)
	{
		LOG_ERROR;
		return NULL;
	}
	p_head->count=0;
	p_head->p_data=NULL;
	p_head->p_next=NULL;
	p_head->p_branch=NULL;
	return p_head;
}

//insert到p_node后
VCA_PNODE VCAListInsert(VCA_PNODE p_node, void *p_data, int data_len)
{
	if(p_node==NULL)
	{
		LOG_ERROR;
		return NULL;
	}
	if(p_data==NULL)
	{
		LOG_ERROR;
		return NULL;
	}
	if(data_len<=0)
	{
		LOG_ERROR;
		return NULL;
	}
	VCA_PNODE p_new_node=(VCA_PNODE)malloc(sizeof(VCA_NODE));
	if(p_new_node==NULL)
	{
		LOG_ERROR;
		return NULL;
	}
	p_new_node->count=0;
	p_new_node->p_branch=NULL;
	p_new_node->p_data=malloc(data_len);
	memcpy(p_new_node->p_data, p_data, data_len);
	p_new_node->p_next=p_node->p_next;
	p_node->p_next=p_new_node;
	return p_new_node;
}


bool VCAListDelete(VCA_PNODE p_node)
{
	if(p_node==NULL)
	{
		LOG_ERROR;
		return false;
	}
	if(p_node->p_data==NULL)
	{
		LOG_ERROR;
		return false;
	}
	free(p_node->p_data);
	if(p_node->p_branch)
	{
		VCAListDestroy(p_node->p_branch);
	}
	p_node->p_next=p_node->p_next->p_next;
	p_node->p_data=p_node->p_next->p_data;
	free(p_node->p_next);
	return true;
}


bool VCAListDestroy(VCA_PNODE p_head)
{
	if(p_head==NULL)
	{
		LOG_ERROR;
		return false;
	}
	VCA_PNODE cruent_node=p_head, next_node;
	while(cruent_node)
	{
		next_node=cruent_node->p_next;
		if(cruent_node->p_data)
		{
			free(cruent_node->p_data);
		}
		if(cruent_node->p_branch)
		{
			VCAListDestroy(cruent_node->p_branch);
		}
		free(cruent_node);
		cruent_node=next_node;
	}
	return true;
}



VCA_PNODE VCAListInsertUnrepeatString(VCA_PNODE branch_head, char *p_string)
{
	VCA_PNODE p_current, p_pre, insert_pos;

	p_pre=branch_head;
	p_current=branch_head->p_next;
	int cmp_result;
	while(p_current)
	{
		cmp_result=strcmp(p_string, (char *)p_current->p_data);
		if(cmp_result==0)
		{
			return p_current;
		}
		else if(cmp_result<0)
		{
			return VCAListInsert(p_pre, p_string, strlen(p_string)+1);
		}
		p_pre=p_current;
		p_current=p_current->p_next;
	}
	return VCAListInsert(p_pre, p_string, strlen(p_string)+1);
}





