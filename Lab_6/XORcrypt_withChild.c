/* Sa se scrie un program c care citeste un nume de fisier de la tastatura si un caracter
 * (cheie de criptare) tot de la tastatura. Programul va cripta (intr-un process fiu)
 * continutul fisierului introdus de la tastatura folosind ca si cheie de criptare
 * caracterul introdus de utilizator. Rezultatul criptarii va fi scris intr-un fisier
 * cu acelasi nume ca si fisierul initial la care se adauga extensia: .crypt.
 * Criptarea se va realiza conform urmatorului algoritm: crypt = original XOR cheie.*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char fileName[99], key,c;

    printf("Enter file name: ");
    scanf("%s",fileName);
    getchar();
    printf("Enter encryption key: ");
    scanf("%c",&key);

    FILE *f = fopen(fileName,"r");
    strcat(fileName,".crypt");
    FILE *fc = fopen(fileName,"w");

    if(fork() == 0) {
        while((c = fgetc(f)) != EOF)
        {
            c = c^key;
            fputc(c,fc);
        }
        fclose(fc);
        fclose(f);
        exit(0);
    }
    wait(0);
    return 0;
}
