#include <stdio.h>
#include <stdlib.h>

void printMatrix(int **a, int n, int m)
{
    int i,j;
    for(i=0; i<n; i++) {
        for(j=0; j<m; j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
}

void storeBinary(int **a, int n, int m){
	FILE *fb = fopen("m.bin","wb");
	fwrite(&n,sizeof(int),1,fb);
	fwrite(&m,sizeof(int),1,fb);
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			fwrite(&a[i][j],sizeof(int),1,fb);
	fclose(fb);
}

void loadBinary(int **a, int *n, int *m){
	FILE *fb = fopen("m.bin","rb");
	fread(n,sizeof(int),1,fb);
	fread(m,sizeof(int),1,fb);
	int i,j;
	for(i=0;i<*n;i++)
		for(j=0;j<*m;j++)
			fread(&a[i][j],sizeof(int),1,fb);
	fclose(fb);
}

int main(){
	FILE *f = fopen("m.txt","r");
	int n,m,i,j;
	fscanf(f,"%d",&n);
	fscanf(f,"%d",&m);
	int **a = malloc(sizeof(int*) * n);
	for(i=0;i<n;i++)
		a[i] = malloc(sizeof(int) * m);
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			fscanf(f,"%d",&a[i][j]);
	printMatrix(a,n,m);
	storeBinary(a,n,m);

	//loadBinary(a,&n,&m);
	for(i=0;i<n;i++)
		free(a[i]);
	free(a);
	fclose(f);

	return 0;
}
