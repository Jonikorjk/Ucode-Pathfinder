#include "../inc/header.h"

void del_matrix(int ** matrix, int size)
{
	for (int j = 0; j < size; j++)
	{
		free(matrix[j]);
	}	
	free(matrix);
}

int ** createFilledMatrix(int r, int c, int filling)
{
	if (!r || !c) return NULL;
	int ** matrix = malloc(r*sizeof(int *));
	for (int i = 0; i < r; i++){
		matrix[i] = malloc(c*sizeof(int));
		for (int j = 0; j < c; j++)
		{
			matrix[i][j] = filling;
		}
	}
	return matrix;
}

int ** createPathMatrix(t_list * names, char ** data, int count){
	int size = mx_list_size(names);
	int i_from;
	int i_to;
	int dist;
	char ** island_len_pair;
	char ** islands_names_pair;
	int ** path_matrix = createFilledMatrix(size, size, 0);
	
	for (int i = 1; i < count; i++)
	{
		island_len_pair = mx_strsplit(data[i], ',');
		islands_names_pair = mx_strsplit(island_len_pair[0], '-');
		dist = mx_atoi(island_len_pair[1], NULL);
		i_from = indexOf(names, islands_names_pair[0]);
		i_to = indexOf(names, islands_names_pair[1]);
		
		if (i_from != -1 && i_to != -1)
		{
			path_matrix[i_from][i_to] = path_matrix[i_to][i_from] = dist;
		}	
		else
		{
			mx_delstr_arr_arr(&island_len_pair, &islands_names_pair, NULL, NULL);
			del_matrix(path_matrix, size);
			return NULL;
		}
		mx_delstr_arr_arr(&island_len_pair, &islands_names_pair, NULL, NULL);
	}
	return path_matrix;
}

