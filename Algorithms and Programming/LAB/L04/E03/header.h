#ifndef E03_HEADER_H
#define E03_HEADER_H

#define MAX 500

int H(int n, int V[]) {
    if(V[n] == -1)
        V[n] = (n - H(H(H(n - 1, V), V), V));
    return V[n];
}

#endif //E03_HEADER_H
