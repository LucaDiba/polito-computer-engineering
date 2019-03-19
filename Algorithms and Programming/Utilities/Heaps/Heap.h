typedef struct heap *Heap;

Heap    HEAPinit(int);
void    HEAPfill(Heap, Item);
void    HEAPsort(Heap);
void	HEAPdisplay(Heap) ;

void HEAPify(Heap h, int i) ;

