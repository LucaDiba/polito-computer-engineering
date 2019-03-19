#include "union_find_set.h"
int size[LEN];
int find_root(int p){
	return id[p] == p ? p : find_root(id[p]);
}
void union_node(int q,int p){
	p = find_root(p);
	q = find_root(q);	
	if(size[p] < size[q]){
		int t = p;
		p = q;
		q = t;
	}
	id[q] = p;
	size[p] += size[q];
}
void init_node(){
	for (int i = 0; i < LEN; i++)
	{
		id[i] = i;
		size[i] = 1;
	}
}
void print_node(){
	for (int i = 0; i < LEN; i++)
	{
		if(i>0){
			printf(" ");
		}
		printf("%d", id[i]);
	}
	printf("\n");
}
void read_and_union_node(){
	int p,q;
	printf("Unire: ");
	while(scanf(" %d %d",&p,&q)==2){
		union_node(p, q);
		printf("Unito %d e %d: ", p , q);
		print_node();
	}
}
int main()
{
	init_node();
	read_and_union_node();
	print_node();
	return 0;
}
