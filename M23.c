#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp1 = fopen("test.txt", "r");
    FILE *fp2 = fopen("im.gv", "w");

    printf("%s", "Hello GIT!");

    fclose(fp1);
    fclose(fp2);

}