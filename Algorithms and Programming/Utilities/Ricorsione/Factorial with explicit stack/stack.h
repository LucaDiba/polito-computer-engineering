typedef struct stack *S;

S    STACKinit(int maxN);
int  STACKempty(S);
int  STACKsize(S);
void STACKpush(S, int);
int STACKpop(S);
int STACKtop(S);
