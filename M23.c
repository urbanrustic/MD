#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void DFC(int param, int length, int *arr, int *visited) {
    if (visited[param]) {
        return;
    }
    visited[param] = 1;
    for (int i = 1; i < length; i++) {
        if ((visited[i] == 0) && (arr[param*length + i] == 1)) {
            DFC(i, length, arr, visited);
        }
        
    }
}

//Матрица смежности 
int matr(int apex, FILE *fp1) {
    //Создаём массив нулей
    int ar[apex+1][apex+1];
    for (int c = 0; c < apex+1; c++) {
        for (int b = 0; b < apex+1; b++) {
            ar[c][b] = 0;
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
            printf("%d ", k);
        }
        else if (isdigit(c)) {
            v = c-'0';
            printf("%d ", v);
        }
        ///////////////
        if (v && k && fl) {
            ar[v][k] = 1;
            ar[k][v] = 1;
            fl = 0;
            v = 0;
            k = 0;
        }
    }
    for (int i = 0; i < apex+1; i++) {
        for (int j = 0; j < apex+1; j++) {
            printf("%d", ar[i][j]);
        }
        printf("\n");
    }

    int *arr = &ar[0][0];
    int visited[apex+1];
    for (int i = 0; i < apex+1; i++) {
        visited[i] = 0;
    }
    printf("\n");
    DFC(apex, apex+1, arr, visited);

    for (int i = 1; i < apex+1; i++) {
        printf("%d",visited[i]);
    }
    printf("\n");

    int flag = 0;
    for (int i = 1; i < apex+1; i++) {
        if (visited[i] == 1) {
            flag++;
        }
    }
    if (flag == apex) {
        return 1;
    }
    else{
        return 0;
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
    
    printf("%d %d\n", apex, edges);
    

    free(a);

    if ((apex-edges == 1) && matr(apex, fp1)) {
        printf("\n%s\n", "Дерево");
    }
    else {
        printf("\n%s\n","Не является деревом");
    }
    
    
    
    fclose(fp1);
    fclose(fp2);
    system("dot -Tpng im.gv -o '1.png'");
    system("wslview 1.png");
    return 0;
}
