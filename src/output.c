#include "../inc/header.h"

static bool cmp_paths(void * a, void *b)
{
  int * p1 = (int *)a;
  int * p2 = (int *)b;
  int i = 0;
  while (p1[i] != -1 && p2[i] != -1)
	{
		if (p1[i] != p2[i])
    {
      return p1[i] > p2[i];
    }
    i++;
	}
	return p1[i] > p2[i];
}

static void show_distance(int ** G, int * real, int dist)
{
  bool print_equal = 0;
  int i = 0;
  int j = 1;
  char * buf = mx_strnew(10000);
  mx_strcat(buf, "Distance: ");
  char * str_dist = mx_itoa(G[real[i++]][real[j++]]);
  mx_strcat(buf, str_dist);
  free(str_dist);
  for ( ;real[j] != -1; i++, j++){
      mx_strcat(buf, " + ");
      str_dist = mx_itoa(G[real[i]][real[j]]);
      mx_strcat(buf, str_dist);
      free(str_dist);
      print_equal = 1;
  }
  if (print_equal)
  {
    mx_strcat(buf, " = ");
    str_dist = mx_itoa(dist);
    mx_strcat(buf, str_dist);
    free(str_dist);
  }
  mx_printstr(buf);
  free(buf);
}

static void show_route(t_list * names, int * path, int last){
    int j = 0;
    char * buf = mx_strnew(10000);
    mx_strcat(buf, "Path: ");
    mx_strcat(buf, valueOf(names, path[0]));
    mx_strcat(buf, " -> ");
    mx_strcat(buf, valueOf(names, path[last]));
    mx_strcat(buf, "\nRoute: ");
    for (; path[j+1] != -1; j++)
    {
        mx_strcat(buf, valueOf(names, path[j]));    
        mx_strcat(buf, " -> ");
    }
    mx_strcat(buf, valueOf(names, path[j]));
    mx_printstr(buf);
    free(buf);
}

static void show_path_info(int ** matrix, t_list * names, int * path, int j, int dist)
{
  mx_printstr("========================================\n");
  show_route(names, path, j);
  mx_printstr("\n");
  show_distance(matrix, path, dist);
  mx_printstr("\n========================================\n");
}

static int arr_len(int * arr)
{
  int j = 0;
  for ( ; arr[j + 1] != -1; j++);
  return j;
}

static void free_arr_of_lists(t_list ** arr, int n, int except, bool free_content)
{
  for (int i = 0; i < n; i++)
  {
    if (i != except)
    {
      mx_clear_list(arr + i, free_content);
    }
  }
  free(arr);
}

void print_results(int ** paths_matrix, t_list ** prev_lists, t_list * names, int * distance, int startnode)
{
    int n = mx_list_size(names);
    int last;
    t_list ** routes = generate_permutations(prev_lists, names, n, startnode);
    for (int i = 1; routes[i]; i++)
    {
      if (i != startnode)
      {
        mx_sort_list(routes[i], cmp_paths);
        for (t_list * route = routes[i]; route; route = route->next)
        {
          int * vertices = route->data;
          last = arr_len(vertices);
          if (vertices[last] > startnode)
          {
            show_path_info(paths_matrix, names, vertices, last, distance[i]);
          }
        }
      }
    }
    free_arr_of_lists(routes, n, startnode, true);
    free_arr_of_lists(prev_lists, n, -1, false);
}


