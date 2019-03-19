#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node
{
  int item;
  link next;
};

int count (link x);
void traverse (link h);
void traverseR (link h);
link delet(link x, int item);

int main(int argc, char *argv[]) {

  int i, N;
  link x;

  if (argc < 2) {
    printf("error: missing argument\n");
    printf("the correct format is:\n");
    printf("%s N \n", argv[0]);
    return 0;
  }

  N = atoi(argv[1]);

  link t = malloc(sizeof *t);

  x = t;
  t->item =1;
  t->next =NULL;

  printf("i-th element in the list = %d\n", t->item);

  for (i = 2; i <=N; i++) {
    x = (x->next = malloc(sizeof *x));
    x->item = i; x->next = NULL;
    printf("i-th element in the list = %d\n", x->item);
  }

  printf("count the number of elements in the  list\n");
  printf("the list has %d elements \n", count(t));

  printf("visit the list \n");
  traverse(t);
  printf("\n");

  printf("visit the list in reverse order \n");
  traverseR(t);
  printf("\n");

  printf("input element to be removed:");
  scanf("%d", &i);
  printf("list after deleting element %d\n", i);
  traverse ( t = delet(t, i));
  printf("\n");

  printf("cancel elements one by one \n");
  for (i = 1; i <=N; i++) {
    printf("list after deleting element %d\n", i);
    traverse ( t = delet(t, i));
    printf("\n");
  }
  printf("\n");
  return 1;
}

int count (link x) {
  if (x == NULL)
    return 0;
  return 1 + count(x->next);
}

void traverse (link h) {
  if (h == NULL)
    return;
  printf("%d ", h->item);
  traverse(h->next);
}

void traverseR (link h) {
  if (h == NULL)
    return;
  traverseR(h->next);
  printf("%d ", h->item);
}

link delet(link x, int item) {
  link t;
  if ( x == NULL )
    return NULL;
  if ( x->item == item) {
    t = x->next;
    free(x);
    return t;
  }
  x->next = delet(x->next, item);
  return x;
}
