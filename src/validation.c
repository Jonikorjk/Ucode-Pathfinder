#include "../inc/header.h"

void throw_error_message(char * message, char * adding, int free_content)
{
	if (adding)
	{
		char *newstr = mx_replace_substr(message, "?", adding);
		if (free_content)
		{
			free(adding);
		}
		mx_printerr(newstr);
		free(newstr);
	}
	else
	{
		mx_printerr(message);
	}
	exit(1);
}

char * check_file_errors(char * filename)
{
	char * file_data = mx_file_to_str(filename);
	if (!file_data)
	{
		throw_error_message("error: file ? does not exist\n", filename, 0);
	}
	else if (mx_strlen(file_data) == 0)
	{
		throw_error_message("error: file ? is empty\n", filename, 0);
	}
	return file_data;
}

int validate_string(char * str, char delim, int end){
	int del_count = 0;
	if (!mx_isalpha(str[0])) return 0;
	for (int i = 0; str[i] != end; i++){
		if (str[i] == delim) del_count++;
		if (!mx_isalpha(str[i]))
		{
			if (!mx_isalpha(str[i + 1])) return 0;
		}
	}
	if (del_count != 1) return 0;
	return 1;
}

static bool bridges_differ(char ** b1, char ** b2)
{
	return (!mx_strcmp(b1[0], b2[0]) && !mx_strcmp(b1[1], b2[1])) ||
			(!mx_strcmp(b1[0], b2[1]) && !mx_strcmp(b1[1], b2[0]));
}

static int lines_doesnt_match(char ** data1, char * pair)
{
	char ** islands_bridge_pair = mx_strsplit(pair, ',');
	char ** data2 = mx_strsplit(islands_bridge_pair[0], '-');
	if (bridges_differ(data1, data2))
	{
		mx_delstr_arr_arr(&islands_bridge_pair, &data2, NULL, NULL);
		return 0;
	}
	else
	{
		mx_delstr_arr_arr(&islands_bridge_pair, &data2, NULL, NULL);
		return 1;
	}
}

int process_isl_str(char * str, char ***names_len_pairs, char *** names_pair, int * dist)
{
	int err = 0;
	if (mx_get_char_index(str, ',') != -1 &&
		validate_string(str, '-', ','))
	{
		(*names_pair) = mx_strsplit(str, ',');
		if (*names_pair)
		{
			(*names_len_pairs) = mx_strsplit((*names_pair)[0], '-');
		}
	}
	if (*names_len_pairs && *names_pair &&
		mx_strcmp((*names_len_pairs)[0], (*names_len_pairs)[1]))
	{
		*dist = mx_atoi((*names_pair)[1], &err);
	}
	return err;
}

void check_data_dup(char ** islands, char * com_line, bool  * error)
{
	if (validate_string(com_line, '-', ',') &&
		!lines_doesnt_match(islands, com_line))
	{
		*error = true;	
	}
}

void process_errors(bool * errors)
{
	if (!errors) return;
	if (errors[0])  // invalid islands count
	{
		throw_error_message("error: invalid number of islands\n", NULL, 0);	
	}
	else if (errors[1])
	{
		throw_error_message("error: duplicate bridges\n", NULL, 0);
	}	
	else if (errors[2])
	{
		throw_error_message("error: sum of bridges lengths is too big\n", NULL, 0);
	}
}

