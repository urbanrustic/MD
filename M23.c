#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp1 = fopen("gr.txt", "r");
    FILE *fp2 = fopen("im.gv", "w");

    char* a = (char*)malloc(1*sizeof(char));
    int i = 0;
    char c;

    while ((c = fgetc(fp1))!=EOF) {
        a[i++] = c;
        a = (char*)realloc(a, (i+1)*sizeof(char));
        if (a == NULL) {
            exit -1;
        }
    }

    for (int j = 0; j < i; j++) {
        printf("%c",a[j]);
    }
    

    free(a);
    fclose(fp1);
    fclose(fp2);

}