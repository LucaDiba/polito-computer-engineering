#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int mat_search(char mat[10][10], int r, int c, char s[20]);

int main()
{
    int count;
    char str[] = "foo";
    char mat[10][10]={
    {'x','f','o','o','x',' ',' ',' ',' ',' '},
    {'y','o','x','z','f',' ',' ',' ',' ',' '},
    {'x','o','2','f','o',' ',' ',' ',' ',' '},
    {'g','4','x','a','o',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ','f','o','o'}, //questa non viene considerata poiché fuori dal range
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
    count = mat_search(mat, 4, 5, str);
    printf("Stringa trovata %i volte", count);
    return 0;
}

int mat_search(char mat[10][10], int r, int c, char s[20]){
    int i, j, s_i, s_j, k, d, dx, dy, count = 0, len = strlen(s);
    char car;
    int det[4][4] = {   { 1,  1, 0,   0},   //Righe - da(0,0) a (r,c)
                        {-1, -1, r-1, c-1}, //Righe - da(r,c) a (0,0)
                        { 1,  1, 0,   0},   //Colonne - da (0,0) a (r,c)
                        {-1, -1, c-1, r-1}};//Colonne - da (r,c) a (0,0)
    for(d=0; d<4; d++){
        dx = det[d][0];
        dy = det[d][1];
        s_i= det[d][2];
        s_j= det[d][3];
        if(d==2){
            i = r;
            r = c;
            c = i;
        }
        for(i=s_i; (dx==1 && i<r) || (dx==-1 && i>=0) ; i+=dx){
            k = 0;
            for(j=s_j; (dy==1 && j<c) || (dy==-1 && j>=0) ; j+=dy){
                if(d<2)
                    car = mat[i][j];
                else
                    car = mat[j][i];

                if(s[k] == car){
                    k++;
                    if(k == len){
                        count++;
                        k=0;
                    }
                }else{
                    k=0;
                }
            }
        }

    }
    return count;
}
