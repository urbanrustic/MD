#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Функция для выявления связанных вершин
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

    int ar[apex+1][apex+1];
    for (int i = 0; i < apex+1; i++) {
        for (int j = 0; j < apex+1; j++) {
            ar[i][j] = 0;
        }   
    }

    int fl1 = 0, fl2 = 0;
    int v = 0, k = 0;
    char c;
    //Возвращение к началу файла
    rewind(fp1);

    while ((c = fgetc(fp1))!=EOF) {
        if (v && k && fl1 && fl2) {
            ar[v][k] = 1;
            ar[k][v] = 1;
            fl1 = 0;
            fl2 = 0;
            v = 0;
            k = 0;
        }

        if (c == '\n') {
            fl2 = 1;
        }
        if (c == '-') {
            fl1 = 1;
        }
        if (isdigit(c) && fl1 && !fl2) {
            k = c-'0' + k*10;
        }
        else if (isdigit(c)) {
            v = c-'0' + v*10;
        }
    }

    if (v && k && fl1) {
            ar[v][k] = 1;
            ar[k][v] = 1;
            fl1 = 0;
            v = 0;
            k = 0;
        }   

    //Указатель на первый символ для матрицы смежности
    int *arr = &ar[0][0];
    int visited[apex+1];
    for (int i = 0; i < apex+1; i++) {
        visited[i] = 0;
    }

    DFC(apex, apex+1, arr, visited);

    int flag = 0;
    for (int i = 1; i < apex+1; i++) {
        if (visited[i] == 1) {
            flag++;
        }
    }

    if (flag == apex) {
        return 1;
    }
    else {
        return 0;
    }
}


int main() {

    FILE *fp1 = fopen("gr.txt", "r");
    FILE *fp2 = fopen("im.gv", "w");

    char* graf = (char*)malloc(1*sizeof(char));
    int i = 0, edges = 0, apex = 0;
    char c;

    //Считываем из файла txt
    while ((c = fgetc(fp1))!=EOF) {
        if (c == ' '){
            continue;
        }
        
        graf[i] = c;
        //количество рёбер
        if (graf[i] == '-') {
            edges++;
        }
        graf = (char*)realloc(graf, (++i+1)*sizeof(char));
        if (graf == NULL) {
            exit -1;
        }
    }
    //Максимальная вершина
    int count = 0;
    int j = 0;
    while (graf[j]) {
        while (graf[j] && graf[j]!='-' && graf[j]!='\n' && isdigit(graf[j])) {
            count = graf[j]-'0' + count*10;
            j++;
        }
        if (count > apex) {
            apex = count;
        }
        count = 0;
        j++;
    }
    
    //Заполнение файла gv
    fprintf(fp2, "%s", "graph {\n\t");
    for (int j = 0; j < i; j++) {
        fputc(graf[j], fp2);
        if (graf[j] == '\n') {
            fputc('\t', fp2);
        }
        if (graf[j] == '-') {
            fputc('-', fp2);
        }
        
    }
    fprintf(fp2,"%s","\n}");
    
    free(graf);

    if ((apex-edges == 1) && matr(apex, fp1)) {
        printf("%s\n", "Дерево");
    }
    else {
        printf("%s\n","Не является деревом");
    }
    
    fclose(fp1);
    fclose(fp2);
    system("dot -Tpng im.gv -o '1.png'");
    system("wslview 1.png");
    return 0;
}
