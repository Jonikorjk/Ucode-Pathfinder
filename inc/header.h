#ifndef HEADER_H
#define HEADER_H
#define SHORTER_DIST(md, cost, dist) ((md + cost < dist) && (md + cost > 0))
#define EQUAL_DIST(md, cost, dist) ((md + cost == dist) && (md + cost > 0))
#define INT_MAX 2147483647
#include "../libmx/inc/libmx.h"

//VALIDATION
void throw_error_message(char * message, char * adding, int free_content);
char * check_file_errors(char * filename);
int validate_string(char * str, char delim, int end);
int process_isl_str(char * str, char ***names_len_pairs, char *** names_pair, int * dist);
void check_data_dup(char ** islands, char * com_line, bool  * error);
void process_errors(bool * errors);

//OTHERS
int include_isl_name(t_list ** list, char * name);
void del_matrix(int ** matrix, int size);
int ** createFilledMatrix(int r, int c, int filling);
int ** createPathMatrix(t_list * names, char ** lines, int l_count);
t_list * mx_sort_by_ord(t_list * list, t_list * names);
t_list ** generate_permutations(t_list ** lists, t_list * names, int len, int startnode);
void print_results(int ** paths_matrix, t_list ** prev_lists, t_list * names, int * distance, int startnode);
void find_shortest_paths(int ** G, t_list * names, int startnode);
#endif


