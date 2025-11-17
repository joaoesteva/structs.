#include <stdio.h>
#include <string.h>

#define TAM 100

struct Categoria {
    int codigo;
    char nome[50];
};

struct Produto {
    int codigo;
    char titulo[100];
    char descricao[256];
    int categoria; 
    int preco; 
};

void cadastrarCategoria(struct Categoria v[], int *qtd) {
    if (*qtd >= TAM) {
        printf("Nao eh possivel cadastrar mais categorias.\n");
        return;
    }

    int codigo;
    char nome[50];

    printf("Digite o codigo da categoria: ");
    scanf("%d", &codigo);

    for (int i = 0; i < *qtd; i++) {
        if (v[i].codigo == codigo) {
            printf("Erro: ja existe categoria com esse codigo.\n");
            return;
        }
    }

    printf("Digite o nome da categoria: ");
    getchar(); 
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    v[*qtd].codigo = codigo;
    strcpy(v[*qtd].nome, nome);

    (*qtd)++;

    printf("Categoria cadastrada com sucesso!\n");
}

void imprimirCategorias(struct Categoria v[], int qtd) {
    if (qtd == 0) {
        printf("Nenhuma categoria cadastrada.\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        printf("Codigo: %d | Nome: %s\n", v[i].codigo, v[i].nome);
    }
}

void imprimirProdutos(struct Produto vp[], int qtdProdutos,
                      struct Categoria vc[], int qtdCategorias)
{
    if (qtdProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtdProdutos; i++) {
        char nomeCategoria[50] = "Categoria nao encontrada";

        for (int j = 0; j < qtdCategorias; j++) {
            if (vc[j].codigo == vp[i].categoria) {
                strcpy(nomeCategoria, vc[j].nome);
                break;
            }
        }

        double precoReal = vp[i].preco / 100.0;

        printf("Codigo: %d\n", vp[i].codigo);
        printf("Titulo: %s\n", vp[i].titulo);
        printf("Descricao: %s\n", vp[i].descricao);
        printf("Categoria: %s\n", nomeCategoria);
        printf("Preco: R$ %.2f\n", precoReal);
        printf("-----------------------------------\n");
    }
}

void selectionSortPorDescricao(struct Produto v[], int qtd) {
    int i, j, min;
    struct Produto temp;

    for (i = 0; i < qtd - 1; i++) {
        min = i;
        for (j = i + 1; j < qtd; j++) {
            if (strcmp(v[j].descricao, v[min].descricao) < 0) {
                min = j;
            }
        }
        if (min != i) {
            temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }
}

void buscaBinariaPorDescricao(struct Produto v[], int qtd, char *x) {
    int inicio = 0, fim = qtd - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(x, v[meio].descricao);

        if (cmp == 0) {
            printf("Produto encontrado:\n");
            printf("Codigo: %d\n", v[meio].codigo);
            printf("Titulo: %s\n", v[meio].titulo);
            printf("Descricao: %s\n", v[meio].descricao);
            return;
        } else if (cmp > 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("Produto com descricao \"%s\" nao encontrado.\n", x);
}

int main(void) {
    struct Categoria categorias[TAM];
    struct Produto produtos[TAM];
    int qtdCategorias = 0, qtdProdutos = 0;
    
    cadastrarCategoria(categorias, &qtdCategorias);
    cadastrarCategoria(categorias, &qtdCategorias);

    printf("\n--- Lista de Categorias ---\n");
    imprimirCategorias(categorias, qtdCategorias);

    produtos[qtdProdutos].codigo = 1;
    strcpy(produtos[qtdProdutos].titulo, "Notebook");
    strcpy(produtos[qtdProdutos].descricao, "Notebook Gamer");
    produtos[qtdProdutos].categoria = categorias[0].codigo;
    produtos[qtdProdutos].preco = 599900; 
    qtdProdutos++;

    produtos[qtdProdutos].codigo = 2;
    strcpy(produtos[qtdProdutos].titulo, "Mouse");
    strcpy(produtos[qtdProdutos].descricao, "Mouse sem fio");
    produtos[qtdProdutos].categoria = categorias[1].codigo;
    produtos[qtdProdutos].preco = 2500; /
    qtdProdutos++;

    printf("\n--- Lista de Produtos ---\n");
    imprimirProdutos(produtos, qtdProdutos, categorias, qtdCategorias);

    selectionSortPorDescricao(produtos, qtdProdutos);
    printf("\n--- Produtos Ordenados por Descricao ---\n");
    imprimirProdutos(produtos, qtdProdutos, categorias, qtdCategorias);

    char busca[256];
    printf("\nDigite descricao do produto para buscar: ");
    getchar();
    fgets(busca, 256, stdin);
    busca[strcspn(busca, "\n")] = '\0';

    buscaBinariaPorDescricao(produtos, qtdProdutos, busca);

    return 0;
}

