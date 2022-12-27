#include "../inc/header.h"


static void get_permutation(t_list **paths, t_list ** lists, t_list * names, int * path_inxs, int index, const int cur, int start)
{
  if (cur != start)
  {
    for (t_list *temp = lists[cur]; temp; temp = temp->next)
    {
      path_inxs[index++] = *(int *)temp->data;
      int indx = *(int *)temp->data;
      get_permutation(paths, lists, names, path_inxs, index, indx, start);
      index--;
    }
  }
  else
  {
    path_inxs[index++] = start;
    int i = 0;
    int j = 0;
    int * path = malloc(index * sizeof(int));
    for (i = index - 2; i >= 0; i--)
    {
      path[j++] = path_inxs[i];
    }
    mx_push_back(&paths[path_inxs[1]], path);
  }
}

t_list **generate_permutations(t_list **lists, t_list *islands_names, int len, int snode)
{
  int indexes[200];
  t_list ** paths = malloc((len + 1) * sizeof(t_list *));
  for (int i = 0; i < len; i++)
  {
    paths[i] = mx_create_node(malloc(2));
  }
  paths[len] = NULL;
  for (int i = 0; i < len; i++)
  {
    if (i != snode)
    {
      indexes[0] = -1;
      indexes[1] = i;
      get_permutation(paths, lists, islands_names, indexes, 2, i, snode);
      free(paths[i]->data);
      mx_pop_front(&paths[i]);
    }
  }
  free(paths[snode]->data);
  free(paths[snode]);
  return paths;
}

static void fillCosts(int **paths, int **costs, int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      if (paths[i][j] == 0)
        costs[i][j] = INT_MAX;
      else
        costs[i][j] = paths[i][j];
    }
  }
}

static int findMinDist(int (*dists)[], int (*visited)[], int *next, int n)
{
  int mind = INT_MAX;
  for (int i = 0; i < n; i++)
  {
    if ((*dists)[i] < mind && !(*visited)[i])
    {
      mind = (*dists)[i];
      *next = i;
    }
  }
  return mind;
}

void find_shortest_paths(int **paths, t_list *islands_names, int snode)
{
  int n = mx_list_size(islands_names);
  int dist[n];
  int vertices[200];
  int visited_nodes[n];
  int mindist;
  int n_next;
  t_list ** arr_with_prevs = malloc(n * sizeof(t_list *));

  int **cost = createFilledMatrix(n, n, 0);
  int count_nums = 0;
  fillCosts(paths, cost, n);

  for (int i = 0; i < n; i++)
  {
    int start_copy = snode;
    arr_with_prevs[i] = mx_create_node((void *)&start_copy);
    dist[i] = cost[snode][i];
    visited_nodes[i] = 0;
  }
  
  dist[snode] = 0;
  visited_nodes[snode] = 1;
  
  for (int count = 1; count < n - 1; count++)
  {
    mindist = findMinDist(&dist, &visited_nodes, &n_next, n);
    visited_nodes[n_next] = 1;
    for (int i = 0; i < n; i++)
    {
      if (!visited_nodes[i])
      {
        if (EQUAL_DIST(mindist, cost[n_next][i], dist[i]))
        {
          vertices[count_nums] = n_next;
          mx_push_front(&arr_with_prevs[i], (void *)(&vertices[count_nums++]));
        }
        else if (SHORTER_DIST(mindist, cost[n_next][i], dist[i]))
        {
          dist[i] = mindist + cost[n_next][i];
          vertices[count_nums] = n_next;
          mx_clear_list(&arr_with_prevs[i], false);
          arr_with_prevs[i] = mx_create_node((void *)(&vertices[count_nums++]));
        }
      }
    }
  }
  print_results(paths, arr_with_prevs, islands_names, dist, snode);
  del_matrix(cost, n);
}


