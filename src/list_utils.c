#include "../inc/header.h"

int include_isl_name(t_list ** list, char * name){
	if (!name)
	{
		return 0;
	}
	for (t_list * temp = *list; temp; temp = temp->next)
	{
		if (mx_strcmp((char *)temp->data, name) == 0)
		{
			return 0;
		}
	}
	mx_push_back(list, mx_strdup(name));
	return 1;
}

