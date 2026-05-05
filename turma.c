#include <stdio.h>
#include <string.h>
#include "banco.h"
#include "turma.h"

void cadastrar_turma() {
    if (banco.qtd_turmas >= MAX_TURMAS) {
        printf("Limite de turmas atingido!\n"); return;
    }
    Turma *t = &banco.turmas[banco.qtd_turmas];
    printf("Turma (ex: 3B): ");    scanf(" %[^\n]", t->codigo);
    printf("Turno (ex: Manha): "); scanf(" %[^\n]", t->turno);
    t->qtd_alunos = 0;

    /* verifica duplicata */
    for (int i = 0; i < banco.qtd_turmas; i++) {
        if (strcmp(banco.turmas[i].codigo, t->codigo) == 0 &&
            strcmp(banco.turmas[i].turno,  t->turno)  == 0) {
            printf("Turma ja existe!\n"); return;
        }
    }
    banco.qtd_turmas++;
    banco_salvar();
    printf("Turma %s - %s cadastrada!\n", t->codigo, t->turno);
}

void buscar_turma() {
    char cod[MAX_COD_T];
    printf("Nome da turma: "); scanf(" %[^\n]", cod);
    for (int i = 0; i < banco.qtd_turmas; i++) {
        if (strcmp(banco.turmas[i].codigo, cod) == 0) {
            printf("Turma : %s | Turno: %s | Alunos: %d\n",
                   banco.turmas[i].codigo,
                   banco.turmas[i].turno,
                   banco.turmas[i].qtd_alunos);
            return;
        }
    }
    printf("Turma nao encontrada.\n");
}

void menu_turma() {
    printf("\nTotal de turmas: %d\n", banco.qtd_turmas);
    if (banco.qtd_turmas > 0) {
        printf("%-15s %-10s %s\n", "Turma", "Turno", "Alunos");
        printf("%-15s %-10s %s\n", "-----", "-----", "------");
        for (int i = 0; i < banco.qtd_turmas; i++)
            printf("%-15s %-10s %d\n",
                   banco.turmas[i].codigo,
                   banco.turmas[i].turno,
                   banco.turmas[i].qtd_alunos);
    }
    int op;
    do {
        printf("\n1-Cadastrar  2-Buscar  0-Voltar\nOpcao: ");
        scanf("%d", &op);
        if      (op == 1) cadastrar_turma();
        else if (op == 2) buscar_turma();
        else if (op != 0) printf("Invalido!\n");
    } while (op != 0);
}