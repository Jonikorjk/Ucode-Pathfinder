#include "../inc/libmx.h"

void * valueOf(t_list * list, int i){
	int j = 0;
	for (t_list*temp = list; temp; temp = temp->next){
		if (j++ == i) return temp->data;
	}
	return NULL;
}

int indexOf(t_list * list, void * value){
	int i = 0;
	for (t_list * temp = list; temp; temp = temp->next, i++)
	{
		if (!mx_strcmp(value, temp->data)) return i;
	}
	return -1;
}

void mx_clear_list(t_list **list, bool free_content){
	t_list * temp = *list;
	t_list * copy = temp;
	if(!list) return;
	while (temp){
		copy = temp->next;
		if (free_content){
			free(temp->data);
		}
		free(temp);
		temp = copy;
	}
	*list = temp;
}


