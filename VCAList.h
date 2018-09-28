#ifndef _VCA_LIST_H_
#define _VCA_LIST_H_


typedef struct VCA_Node
{
	int count;
	void *p_data;
	struct VCA_Node *p_branch;
	struct VCA_Node *p_next;
}VCA_NODE, *VCA_PNODE;

VCA_PNODE VCAListCreate(void);
VCA_PNODE VCAListInsert(VCA_PNODE p_node, void *p_data, int data_len);
VCA_PNODE VCAListInsertUnrepeatString(VCA_PNODE branch_head, char *p_string);
bool VCAListDelete(VCA_PNODE p_node);
bool VCAListDestroy(VCA_PNODE p_head);

#endif

