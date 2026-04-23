#ifndef PRODUTO_H
#define PRODUTO_H

#define MAX_COD  20
#define MAX_NOME 80
#define MAX_CAT  40

typedef struct {
    char codigo[MAX_COD];
    char nome[MAX_NOME];
    char categoria[MAX_CAT];
    float preco;
    int estoque;
} Produto;

void menu_produto();
void cadastrar_produto();
void editar_produto();
void listar_produtos();
void buscar_produto();
void ver_estoque();
void registrar_venda();

#endif