#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Матрица смежности 
void matr(int apex, FILE *fp1) {
    //Создаём массив нулей
    int arr[apex+1][apex+1];
    for (int c = 0; c < apex+1; c++) {
        for (int b = 0; b < apex+1; b++) {
            arr[c][b] = 0;
        }   
    }

    int fl = 0;
    int v = 0, k = 0;
    char c;
    rewind(fp1);

    while ((c = fgetc(fp1))!=EOF) {
        if (c == '-') {
            fl = 1;
        }
        ///////////////
        if (isdigit(c) && fl) {
            k = c-'0';
        }
        else if (isdigit(c)) {
            v = c-'0';
        }
        ///////////////
        if (v && k && fl) {
            if (v < k) {
                arr[v][k] = 1;
            }
            else {
                arr[k][v] = 1;
            }
                fl = 0;
                v = 0;
                k = 0;
        }
    }
    
}



int main() {
    FILE *fp1 = fopen("gr.txt", "r");
    FILE *fp2 = fopen("im.gv", "w");

    char* a = (char*)malloc(1*sizeof(char));
    int i = 0, edges = 0, apex = 0;
    char c;

    //Считываем из файла txt
    while ((c = fgetc(fp1))!=EOF) {
        a[i] = c;
        //количество рёбер и максимальная вершина
        if (a[i] == '-') {
            edges++;
        }
        if (isdigit(c) && (apex < (c-'0'))) {
            apex = c-'0';
        }
        a = (char*)realloc(a, (++i+1)*sizeof(char));
        if (a == NULL) {
            exit -1;
        }
    }

    //Заполнение файла gv
    fprintf(fp2, "%s", "graph {\n\t");
    for (int j = 0; j < i; j++) {
        fputc(a[j], fp2);
        if (a[j] == '\n') {
            fputc('\t', fp2);
        }
        if (a[j] == '-') {
            fputc('-', fp2);
        }
        
    }
    fprintf(fp2,"%s","\n}");
    
    printf("Вершин %d Рёбер %d\n", apex, edges);
    

    free(a);

    matr(apex, fp1);
    
    fclose(fp1);
    fclose(fp2);
    system("dot -Tpng im.gv -o '1.png'");
    system("wslview 1.png");
    return 0;
}
