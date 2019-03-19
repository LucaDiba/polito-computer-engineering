/*Principio di moltiplicazione*/

typedef struct {
	int *scelte;
	int num.scelte;
} Livello;
int princ_molt(int pos, Livello * val, int *sol, int n, int count){
	int i;
	if(pos >=n){
		for (i=0; i<n; i++)
			printf("%d ", sol[i]);
		printf("\n");
		return count+1;
	}
	for (i=0; i<val[pos].num_scelte; i++){
		sol[pos] = val[pos].scelte[i];
		count = princ_molt(pos+1, val, sol, n count);
	}
}

/* Disposizioni semplici */
int disp_sempl(int pos, int *val, int *sol, int *mark, int n, int k, int count){
	int i;
	if(pos >= k){
		for(i=0; i<k; i++)
			printf("%d ", sol[i]);
		printf("\n");
		return count+1;
	}
	for(i=0; i<n; i++){
		if(mark[i]==0){
			mark[i]=1;
			sol[pos] = val[i];
			count = disp_sempl(pos+1, val, sol, mark, n, k, count);
			mark[i] = 0;
		}
	}
	return count;
}

/* Disposizioni ripetute */
int disp_rip(int pos, int *val, int *sol, int n, int k, int count){
	int i;
	if(pos>=k){
		for(i=0;i<k;i++)
			printf("%d ", sol[i]);
		printf("\n");
		return count+1;
	}
	for(i=0; i<n; i++){
		sol[pos] = val[i];
		count = disp_ripet(pos+1, val, sol, n, k, count);
	}
	return count;
}

/* Permutazioni semplici */
int perm_sempl(int pos, int *val, int *sol, int *mark, int n,int count){
	int i;
	if(pos>=n){
		for(i=0; i<n; i++)
			printf("%d ", sol[i]);
		printf("\n");
		return count+1;
	}
	for(i=0; i<n; i++){
		if(mark[i]==0){
			mark[i] = 1;
			sol[pos] = val[i];
			count = perm_sempl(pos+1, val, sol, mark, n, count);
			mark[i] = 0;
		}
	}
	return count;
}
	
/* Permutazioni ripetute */
int perm_rip(int pos, int *dist_val, int *sol, int *mark, int k, int n, int count){
	int i;
	if(pos>=k){
		for(i=0; i<k; i++)
			printf("%d ", sol[i]);
		printf("\n");
		return count+1;
	}
	for(i=0; i<n;i++){
		if(mark[i]>0){
			mark[i]--;
			sol[pos] = dist_val[i];
			count = perm_rip(pos+1, dist_val, sol, mark, k, n, count);
			mark[i]++;
		}
	}
	return count;
}

/* Combinazioni semplici */
int comb_sempl(int pos,int*val,int*sol,int n,int k,int start,int count){
	int i;
	if(pos >= k){
		for(i=0; i<k; i++)
			printf("%d ", sol[i]);
		printf("\n");
		return count+1;
	}
	for(i=start; i<n; i++){
		sol[pos] = val[i];
		count = comb_sempl(pos+1, val, sol, n, k, i+1, count);
	}
	return count;
}

/* Combinazioni ripetute */
int comb_rip(int pos,int *val,int *sol,int n,int k,int start,int count){
	int i
	if(pos >= k){
		for(i=0; i<k; i++)
			printf("%d ", sol[i]);
		printf("\n");
		return count+1;
	}
	for(i=start; i<n; i++){
		sol[pos]=val[i];
		count = comb_rip(pos+1, val, sol, n, k, i, count);
	}
	return count;
}

/* Powerset divide et impera */
int powerset(int pos, int *val, int *sol, int k,
            int start, int count) {
   int i;
   if (start >= k) {
       for (i = 0; i < pos; i++)
           printf("%d ", sol[i]);
       printf("\n");
       return count+1;
   }
   for (i = start; i < k; i++) {
       sol[pos] = val[i];
       count = powerset(pos+1, val, sol, k, i+1, count);
   }
   count = powerset(pos, val, sol, k, k, count);
   return count;
}

/* Powerset disp rip */
int powerset(int pos,int *val,int *sol,int k,int count) {
   int j;
   if (pos >= k) {
       printf("{ \t");
       for (j=0; j<k; j++)
           if (sol[j]!=0)
               printf("%d \t", val[j]);
       printf("} \n");
       return count+1;
   }
   sol[pos] = 0;
   count = powerset(pos+1, val, sol, k, count);
   sol[pos] = 1;
   count = powerset(pos+1, val, sol, k, count);
   return count;
}

/* Powerset comb sempl */
int powerset_r(int* val, int k, int* sol, int n,
              int pos, int start){
   int count = 0, i;
   if (pos == n){
       printf("{ ");
       for (i = 0; i < n; i++)
           printf("%d ", sol[i]);
       printf(" }\n");
       return 1;
   }
   for (i = start; i < k; i++){
       sol[pos] = val[i];
       count += powerset_r(val, k, sol, n, pos+1, i+1);
   }
   return count;
}
int powerset(int* val, int k, int* sol){
   int count = 0, n;

   for(n = 1; n <= k; n++){
       count += powerset_r(val, k, sol, n, 0, 0);
   }
   return count;
}