#include <stdio.h>
#include <malloc.h>

void complete(int **a, int n)
{
    int i,j;
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            a[i][j] = n*i+j+1;
}

void printMatrix(int **a, int n)
{
    int i,j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
}

void showColOddNoSums(int **a,int n) {
    int i,j;
    for(j=0; j<n; j++) {
        int s=0;
        for(i=0; i<n; i++)
            if(a[i][j]%2)
                s+=a[i][j];
        printf("%d ",s);
    }
}

int main()
{
    int **a,n,i;
    printf("N=");
    scanf("%d",&n);
    a = malloc(n*sizeof(int*));
    for(i=0;i<n;i++)
	    a[i] = malloc(n*sizeof(int));
    complete(a,n);
    //printMatrix(a,n);
    showColOddNoSums(a,n);
    for (i = 0; i < n; i++)
        free(a[i]);
    free(a);
    return 0;
}
