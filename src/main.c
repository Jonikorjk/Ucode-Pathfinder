#include "../inc/header.h"

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		throw_error_message("usage: ./pathfinder [filename]\n", NULL, 0);
	}
	
	char * file_str = check_file_errors(argv[1]);
	int err = 0;
	int total_dist = 0;
	int dist;
	char ** names_len_pairs;
	char ** inames_pairs;
	
	int file_lines_count = mx_count_words(file_str, '\n');

	bool * error_list = malloc(3 * sizeof(bool));
	int errors_in_list = 3;

	char ** lines = mx_strsplit(file_str, '\n');
	int islands_count = mx_atoi(lines[0], &err);
	t_list * islands_names = NULL;
	
	free(file_str);

	if (err || islands_count <= 0)
	{
		mx_del_strarr(&lines);
		mx_clear_list(&islands_names, 1);
		throw_error_message("error: line 1 is not valid\n", NULL, 0); // nothing to replace
	}
	for (int i = 1; i < file_lines_count; i++)
	{
		dist = 0;
		names_len_pairs = NULL;
		inames_pairs = NULL;
		err = process_isl_str(lines[i], &names_len_pairs, &inames_pairs, &dist);

		if (err || dist <= 0)
		{
			mx_delstr_arr_arr(&lines, NULL, &inames_pairs, &names_len_pairs);
			mx_clear_list(&islands_names, 1);
			throw_error_message("error: line ? is not valid\n", mx_itoa(i + 1), 1);
		}

		for (int j = 1; j < file_lines_count; j++)
		{
			if (i != j)
			{
				check_data_dup(names_len_pairs, lines[j], &error_list[1]);
			}
		}

		include_isl_name(&islands_names, names_len_pairs[0]); 
		include_isl_name(&islands_names, names_len_pairs[1]);
		
		total_dist += dist;
		if(total_dist < 0)
		{
			error_list[2] = true; // total_len_sum is bigger than INT_MAX
		}
		mx_delstr_arr_arr(&inames_pairs, &names_len_pairs, NULL, NULL);
	}

	error_list[0] = (mx_list_size(islands_names) != islands_count);
	//CHECKING FOR ERRORS
	for (int i = 0; i < errors_in_list; i++)
	{
		if (error_list[i])
		{
			mx_clear_list(&islands_names, true);
			mx_del_strarr(&lines);
			process_errors(error_list);
		}
	}

	int ** paths = createPathMatrix(islands_names, lines, file_lines_count);

	for (int i = 0; i < islands_count - 1; i++)
  	{
		find_shortest_paths(paths, islands_names, i);    
    }
	free(error_list);
	mx_del_strarr(&lines);
	del_matrix(paths, islands_count);
	mx_clear_list(&islands_names, true);
	return 0;
}


