#include <stdio.h>
#include <string.h>
#include "produto.h"

#define ARQ "produtos.dat"

static int contar() {
    FILE *f = fopen(ARQ, "rb");
    if (!f) return 0;
    fseek(f, 0, SEEK_END);
    int n = ftell(f) / sizeof(Produto);
    fclose(f);
    return n;
}

static void carregar(Produto *v, int n) {
    FILE *f = fopen(ARQ, "rb");
    fread(v, sizeof(Produto), n, f);
    fclose(f);
}

static void salvar(Produto *v, int n) {
    FILE *f = fopen(ARQ, "wb");
    fwrite(v, sizeof(Produto), n, f);
    fclose(f);
}

void cadastrar_produto() {
    Produto p;
    snprintf(p.codigo, MAX_COD, "P%04d", contar() + 1);
    printf("Codigo: %s\n", p.codigo);
    printf("Nome: ");      scanf(" %[^\n]", p.nome);
    printf("Categoria: "); scanf(" %[^\n]", p.categoria);
    printf("Preco: ");     scanf("%f", &p.preco);
    printf("Estoque: ");   scanf("%d", &p.estoque);
    FILE *f = fopen(ARQ, "ab");
    fwrite(&p, sizeof(Produto), 1, f);
    fclose(f);
    printf("Cadastrado!\n");
}

void editar_produto() {
    int n = contar();
    if (!n) { printf("Vazio.\n"); return; }
    char cod[MAX_COD];
    printf("Codigo: "); scanf("%s", cod);
    Produto v[n]; carregar(v, n);
    int i;
    for (i = 0; i < n; i++) if (strcmp(v[i].codigo, cod) == 0) break;
    if (i == n) { printf("Nao encontrado.\n"); return; }
    printf("Nome [%s]: ",      v[i].nome);      scanf(" %[^\n]", v[i].nome);
    printf("Categoria [%s]: ", v[i].categoria); scanf(" %[^\n]", v[i].categoria);
    printf("Preco [%.2f]: ",   v[i].preco);     scanf("%f", &v[i].preco);
    printf("Estoque [%d]: ",   v[i].estoque);   scanf("%d", &v[i].estoque);
    salvar(v, n);
    printf("Atualizado!\n");
}

void listar_produtos() {
    int n = contar();
    if (!n) { printf("Vazio.\n"); return; }
    Produto v[n]; carregar(v, n);
    for (int i = 0; i < n; i++)
        printf("[%s] %s | %s | R$%.2f | Estoque: %d\n",
               v[i].codigo, v[i].nome, v[i].categoria, v[i].preco, v[i].estoque);
}

void buscar_produto() {
    int n = contar();
    if (!n) { printf("Vazio.\n"); return; }
    char t[MAX_NOME];
    printf("Nome ou codigo: "); scanf(" %[^\n]", t);
    Produto v[n]; carregar(v, n);
    for (int i = 0; i < n; i++)
        if (strstr(v[i].nome, t) || strcmp(v[i].codigo, t) == 0)
            printf("[%s] %s | R$%.2f | Estoque: %d\n",
                   v[i].codigo, v[i].nome, v[i].preco, v[i].estoque);
}

void ver_estoque() {
    int n = contar();
    if (!n) { printf("Vazio.\n"); return; }
    Produto v[n]; carregar(v, n);
    for (int i = 0; i < n; i++) {
        char *s = v[i].estoque == 0 ? "SEM ESTOQUE" :
                  v[i].estoque <= 5 ? "BAIXO" : "OK";
        printf("[%s] %s | %d un | %s\n", v[i].codigo, v[i].nome, v[i].estoque, s);
    }
}

void registrar_venda() {
    int n = contar();
    if (!n) { printf("Vazio.\n"); return; }
    char cod[MAX_COD]; int qtd;
    printf("Codigo: "); scanf("%s", cod);
    Produto v[n]; carregar(v, n);
    int i;
    for (i = 0; i < n; i++) if (strcmp(v[i].codigo, cod) == 0) break;
    if (i == n) { printf("Nao encontrado.\n"); return; }
    if (v[i].estoque == 0) { printf("Sem estoque!\n"); return; }
    printf("Produto: %s | Estoque: %d\n", v[i].nome, v[i].estoque);
    printf("Quantidade: "); scanf("%d", &qtd);
    if (qtd > v[i].estoque) { printf("Quantidade insuficiente!\n"); return; }
    v[i].estoque -= qtd;
    salvar(v, n);
    printf("Venda: %d x R$%.2f = R$%.2f | Restante: %d\n",
           qtd, v[i].preco, qtd * v[i].preco, v[i].estoque);
}

void menu_produto() {
    int op;
    do {
        printf("\n1-Cadastrar 2-Editar 3-Listar 4-Buscar 5-Estoque 6-Venda 0-Sair\n");
        printf("Opcao: "); scanf("%d", &op);
        if      (op == 1) cadastrar_produto();
        else if (op == 2) editar_produto();
        else if (op == 3) listar_produtos();
        else if (op == 4) buscar_produto();
        else if (op == 5) ver_estoque();
        else if (op == 6) registrar_venda();
        else if (op != 0) printf("Invalido!\n");
    } while (op != 0);
}