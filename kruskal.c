#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
#define MAXM 100

int num_vertice, num_aresta;
int pai[MAXN];
int aresta_peso[MAXN];

struct g_aresta {
    int peso;
    int v1, v2;
};
struct g_aresta aresta[MAXM];
struct g_aresta arv_min[MAXM];

void heapifyDown(struct g_aresta arr[], int inicio, int final) {
    int raiz = inicio;
    while (2 * raiz + 1 <= final) {
        int filho = 2 * raiz + 1;
        int troca = raiz;

        if (arr[troca].peso > arr[filho].peso)
            troca = filho;

        if (filho + 1 <= final && arr[troca].peso > arr[filho + 1].peso)
            troca = filho + 1;

        if (troca == raiz)
            return;
        
        struct g_aresta temp = arr[raiz];
        arr[raiz] = arr[troca];
        arr[troca] = temp;

        raiz = troca;
    }
}

void buildHeap(struct g_aresta arr[], int n) {
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        heapifyDown(arr, i, n - 1);
}

struct g_aresta extractMin(struct g_aresta arr[], int* n) {
    struct g_aresta min = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    heapifyDown(arr, 0, *n - 1);
    return min;
}

// Union find

int find(int vertice) {
    if (pai[vertice] == vertice)
        return vertice;
    return pai[vertice] = find(pai[vertice]);
}

void join(int v_a, int v_b) {
    v_a = find(v_a);
    v_b = find(v_b);

    if (aresta_peso[v_a] < aresta_peso[v_b])
        pai[v_a] = v_b;
    else if (aresta_peso[v_b] < aresta_peso[v_a])
        pai[v_b] = v_a;
    else {
        pai[v_a] = v_b;
        aresta_peso[v_b]++;
    }
}

int main() {

    scanf("%d %d", &num_vertice, &num_aresta); // ler a entrada da quantidade de vértices e arestas

    for (int i = 0; i < num_aresta; i++)
        scanf("%d %d %d", &aresta[i].v1, &aresta[i].v2, &aresta[i].peso); // ler a entrada do vertice 1, vertice 2 e peso

    //Incializando os pais para o union find
    for (int i = 1; i <= num_vertice; i++)
        pai[i] = i;

    buildHeap(aresta, num_aresta); // construir o heap com as arestas

    //Procurando a árvore geradora mínima e realizando a soma dos pesos
    int tamanho = 0;
    int soma = 0;
    while (tamanho < num_vertice - 1 && num_aresta > 0) {
        struct g_aresta min = extractMin(aresta, &num_aresta);
        if (find(min.v1) != find(min.v2)) {
            join(min.v1, min.v2);
            arv_min[tamanho++] = min;
            soma += min.peso;
        }
    }

    printf("%d", soma); //printa a soma
    
    return 0;
}
