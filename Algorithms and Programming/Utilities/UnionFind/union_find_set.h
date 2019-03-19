#include <stdio.h>
#ifndef LEN
#define LEN 11
#endif

/**
 * roots for every node;
 */
int id[LEN];

/**
 * @desc find the root for p node
 * @param p the node to find 
 * @return the root of the node p
 */
int find_root_node(int p);

/**
 * @desc union two node;
 * @param p first node
 * @param q second node
 */
void union_node(int p,int q);

/**
 * @desc initialization
 */
void init_node();

/**
 * @desc print all node
 */
void print_node();

/**
 * @desc read all data and do union
 * @format %d-%d
 */
void read_and_union_node();
