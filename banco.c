#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "banco.h"

Banco banco;
char  arquivo_banco[80];

/* Gera o nome do arquivo a partir do nome do banco
   Ex: "Escola Tia Malena" -> "escola_tia_malena.dat" */
static void gerar_nome_arquivo(const char *nome, char *dest) {
    int j = 0;
    for (int i = 0; nome[i] && j < 70; i++) {
        char c = nome[i];
        if (c >= 'A' && c <= 'Z') c += 32;   /* minusculo */
        if (c == ' ') c = '_';               /* espaco vira _ */
        if ((c>='a'&&c<='z') || (c>='0'&&c<='9') || c=='_')
            dest[j++] = c;
    }
    dest[j] = '\0';
    strcat(dest, ".dat");
}

/* Carrega o banco do arquivo. Retorna 1 se ok, 0 se nao existe */
int banco_carregar(const char *nome) {
    gerar_nome_arquivo(nome, arquivo_banco);
    FILE *f = fopen(arquivo_banco, "rb");
    if (!f) return 0;
    fread(&banco, sizeof(Banco), 1, f);
    fclose(f);
    return 1;
}

/* Salva o banco inteiro no arquivo .dat */
void banco_salvar() {
    FILE *f = fopen(arquivo_banco, "wb");
    if (!f) { printf("Erro ao salvar!\n"); return; }
    fwrite(&banco, sizeof(Banco), 1, f);
    fclose(f);
}

/* Menu inicial: criar ou abrir banco */
void menu_banco() {
    char nome[MAX_NOME_BANCO];
    int op;

    printf("\n=========================================\n");
    printf("       SISTEMA ESCOLAR — BANCO DE DADOS  \n");
    printf("=========================================\n");
    printf("  1 - Criar novo banco de dados\n");
    printf("  2 - Abrir banco existente\n");
    printf("  0 - Sair\n");
    printf("=========================================\n");
    printf("Opcao: ");
    scanf("%d", &op);

    if (op == 0) exit(0);

    if (op == 1) {
        printf("Nome do novo banco: ");
        scanf(" %[^\n]", nome);
        char arq[80];
        gerar_nome_arquivo(nome, arq);

        /* verifica se ja existe */
        FILE *f = fopen(arq, "rb");
        if (f) {
            fclose(f);
            printf("Banco '%s' ja existe! Abrindo...\n", nome);
            banco_carregar(nome);
        } else {
            /* inicializa banco zerado */
            memset(&banco, 0, sizeof(Banco));
            strncpy(banco.nome, nome, MAX_NOME_BANCO - 1);
            strncpy(arquivo_banco, arq, 79);
            banco_salvar();
            printf("Banco '%s' criado!\n", nome);
        }

    } else if (op == 2) {
        printf("Nome do banco: ");
        scanf(" %[^\n]", nome);
        if (!banco_carregar(nome)) {
            printf("Banco '%s' nao encontrado.\n", nome);
            printf("Dica: o arquivo seria '%s'\n", arquivo_banco);
            menu_banco(); /* volta ao menu */
        } else {
            printf("Banco '%s' carregado!\n", banco.nome);
        }

    } else {
        printf("Opcao invalida!\n");
        menu_banco();
    }
}