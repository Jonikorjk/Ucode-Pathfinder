#include "../inc/libmx.h"

int mx_count_substr(const char *str, const char *sub)
{
	if (!str || !sub)
	{
		return -1;
	}
	if (sub[0] == '\0') return 0;
	int count = 0;
  	int len_sub = mx_strlen(sub);
  	str = mx_strstr(str, sub);
  	while (str)
  	{
   	 	count++;
      	str = mx_strstr(str + len_sub, sub);
	}
	return count;
}


