#include <stdio.h>
#include <string.h>
#include "banco.h"
#include "aluno.h"

void cadastrar_aluno() {
    if (banco.qtd_turmas == 0) {
        printf("Cadastre uma turma antes!\n"); return;
    }
    if (banco.qtd_alunos >= MAX_ALUNOS) {
        printf("Limite de alunos atingido!\n"); return;
    }

    Aluno *a = &banco.alunos[banco.qtd_alunos];

    /* matricula automatica */
    snprintf(a->matricula, MAX_MAT, "A%04d", banco.qtd_alunos + 1);
    printf("Matricula: %s\n", a->matricula);

    printf("Nome: "); scanf(" %[^\n]", a->nome);

    /* lista turmas disponiveis */
    printf("Turmas disponiveis:\n");
    for (int i = 0; i < banco.qtd_turmas; i++)
        printf("  %d. %s - %s\n", i+1,
               banco.turmas[i].codigo,
               banco.turmas[i].turno);

    printf("Turma (ex: 3B): "); scanf(" %[^\n]", a->turma);

    /* valida turma */
    int idx = -1;
    for (int i = 0; i < banco.qtd_turmas; i++)
        if (strcmp(banco.turmas[i].codigo, a->turma) == 0) { idx = i; break; }

    if (idx == -1) {
        printf("Turma '%s' nao existe!\n", a->turma); return;
    }

    printf("Qtd notas (max %d): ", MAX_NOTAS);
    scanf("%d", &a->qtd_notas);
    if (a->qtd_notas > MAX_NOTAS) a->qtd_notas = MAX_NOTAS;
    for (int i = 0; i < a->qtd_notas; i++) {
        printf("Nota %d: ", i+1);
        scanf("%f", &a->notas[i]);
    }

    banco.qtd_alunos++;
    banco.turmas[idx].qtd_alunos++;
    banco_salvar();
    printf("Aluno cadastrado! Matricula: %s\n", a->matricula);
}

void buscar_aluno() {
    char mat[MAX_MAT];
    printf("Matricula (ex: A0001): "); scanf("%s", mat);
    for (int i = 0; i < banco.qtd_alunos; i++) {
        if (strcmp(banco.alunos[i].matricula, mat) == 0) {
            Aluno *a = &banco.alunos[i];
            printf("\nMatricula: %s\n", a->matricula);
            printf("Nome     : %s\n",  a->nome);
            printf("Turma    : %s\n",  a->turma);
            printf("Notas    :");
            for (int j = 0; j < a->qtd_notas; j++)
                printf(" %.1f", a->notas[j]);
            printf("\n");
            return;
        }
    }
    printf("Aluno nao encontrado.\n");
}

void menu_aluno() {
    printf("\nTotal de alunos: %d\n", banco.qtd_alunos);
    int op;
    do {
        printf("\n1-Cadastrar  2-Buscar  0-Voltar\nOpcao: ");
        scanf("%d", &op);
        if      (op == 1) cadastrar_aluno();
        else if (op == 2) buscar_aluno();
        else if (op != 0) printf("Invalido!\n");
    } while (op != 0);
}