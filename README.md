# Homework_23
<h1 align="center">Draw Graph</h1>
<h2 align="center">Поставленная задача</h2>
Пользователь вводит граф в файл:(пример графа)
<h6>1-2</h6>
<h6>2-3</h6>
<h6>1-4</h6>
<h6>4-5</h6>
<h6>2-6</h6>
Вывести граф в формате png и определить является ли он деревом
<i>Выволнить задание на языке программирования Си(С).</i>
<h2 align="center">Описание</h2>
Программа считывает данные из файла записывает их в массив. Определяется количество рёбер.

```c
    while ((c = fgetc(fp1))!=EOF) {
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
```
Ищем максимальную вершину в графе.
```c
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
```
Заполняем файл на gv, для вывода графа.
```c
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
```
Определяем является ли граф деревом.
```c
    if ((apex-edges == 1) && matr(apex, fp1)) {
        printf("%s\n", "Дерево");
    }
    else {
        printf("%s\n","Не является деревом");
    }
```
Выводим на экран картинку графа.
```c
    system("dot -Tpng im.gv -o '1.png'");
    system("wslview 1.png");
```
Создания матрицы смежности из считываемого файла.
```c
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
```
В функцию DFC(Поиск связанных рёбер в графе) Поставляем указатель на первый символ в матрице. Определяем сколько вершин было посещено после функции и сравниваем количество посещённых вершин с количеством вершин.
```c
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
```
Функция для определения связанных вершин в графе.
```c
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
```
<h3 align="center">Программа завершается с выводом на экран картинки графа в формате png и определения является ли получееный граф деревом.</h3>

