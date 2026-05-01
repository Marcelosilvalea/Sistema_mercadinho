#include <stdio.h>
#include <string.h>
#include "aluno.h"
#include "turma.h"

#define ARQ "alunos.dat"

int total_alunos() {
    FILE *f = fopen(ARQ, "rb");
    if (!f) return 0;
    fseek(f, 0, SEEK_END);
    int n = ftell(f) / sizeof(Aluno);
    fclose(f);
    return n;
}

static int proximo_id() {
    return total_alunos() + 1;
}

void cadastrar_aluno() {
    /* exige que exista ao menos uma turma */
    if (total_turmas() == 0) {
        printf("Cadastre uma turma antes de cadastrar alunos!\n");
        return;
    }

    Aluno a;
    snprintf(a.matricula, MAX_MAT, "A%04d", proximo_id());
    printf("Matricula gerada: %s\n", a.matricula);

    printf("Nome: "); scanf(" %[^\n]", a.nome);

    /* lista as turmas disponiveis */
    printf("\nTurmas disponiveis:\n");
    FILE *ft = fopen("turmas.dat", "rb");
    if (ft) {
        /* reutilizamos a struct Turma inline */
        typedef struct { char codigo[20]; char nome[40]; int qtd; } T;
        T t;
        while (fread(&t, sizeof(T), 1, ft) == 1)
            printf("  -> %s\n", t.nome);
        fclose(ft);
    }

    printf("Turma do aluno: "); scanf(" %[^\n]", a.turma);

    if (!turma_existe(a.turma)) {
        printf("Turma '%s' nao existe! Cadastre a turma primeiro.\n", a.turma);
        return;
    }

    printf("Qtd notas (max %d): ", MAX_NOTAS); scanf("%d", &a.qtd_notas);
    if (a.qtd_notas > MAX_NOTAS) a.qtd_notas = MAX_NOTAS;
    int i;
    for (i = 0; i < a.qtd_notas; i++) {
        printf("Nota %d: ", i+1); scanf("%f", &a.notas[i]);
    }

    FILE *f = fopen(ARQ, "ab");
    fwrite(&a, sizeof(Aluno), 1, f);
    fclose(f);

    turma_add_aluno(a.turma);
    printf("Aluno cadastrado! Matricula: %s\n", a.matricula);
}

void buscar_aluno() {
    char mat[MAX_MAT];
    printf("Matricula (ex: A0001): "); scanf("%s", mat);
    FILE *f = fopen(ARQ, "rb");
    if (!f) { printf("Nenhum aluno cadastrado.\n"); return; }
    Aluno a; int ok = 0;
    while (fread(&a, sizeof(Aluno), 1, f) == 1) {
        if (strcmp(a.matricula, mat) == 0) {
            printf("\nMatricula: %s\n", a.matricula);
            printf("Nome     : %s\n", a.nome);
            printf("Turma    : %s\n", a.turma);
            printf("Notas    :");
            int i;
            for (i = 0; i < a.qtd_notas; i++) printf(" %.1f", a.notas[i]);
            printf("\n");
            ok = 1; break;
        }
    }
    if (!ok) printf("Aluno nao encontrado.\n");
    fclose(f);
}

void menu_aluno() {
    printf("\nTotal de alunos cadastrados: %d\n", total_alunos());
    int op;
    do {
        printf("\n1-Cadastrar aluno  2-Buscar aluno  0-Voltar\nOpcao: ");
        scanf("%d", &op);
        if      (op == 1) cadastrar_aluno();
        else if (op == 2) buscar_aluno();
        else if (op != 0) printf("Invalido!\n");
    } while (op != 0);
}