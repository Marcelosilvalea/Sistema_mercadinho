#include <stdio.h>
#include <string.h>
#include "turma.h"

#define ARQ "turmas.dat"

int total_turmas() {
    FILE *f = fopen(ARQ, "rb");
    if (!f) return 0;
    fseek(f, 0, SEEK_END);
    int n = ftell(f) / sizeof(Turma);
    fclose(f);
    return n;
}

int turma_existe(const char *codigo) {
    FILE *f = fopen(ARQ, "rb");
    if (!f) return 0;
    Turma t;
    while (fread(&t, sizeof(Turma), 1, f) == 1)
        if (strcmp(t.codigo, codigo) == 0) { fclose(f); return 1; }
    fclose(f);
    return 0;
}

void cadastrar_turma() {
    Turma t;
    t.qtd_alunos = 0;
    printf("Nome/codigo da turma (ex: 3A, Turma B): ");
    scanf(" %[^\n]", t.nome);
    /* codigo e o proprio nome em maiusculo sem espacos */
    snprintf(t.codigo, MAX_COD_T, "%s", t.nome);

    if (turma_existe(t.codigo)) {
        printf("Turma '%s' ja existe!\n", t.nome);
        return;
    }

    FILE *f = fopen(ARQ, "ab");
    fwrite(&t, sizeof(Turma), 1, f);
    fclose(f);
    printf("Turma '%s' cadastrada!\n", t.nome);
}

void buscar_turma() {
    char cod[MAX_COD_T];
    printf("Nome/codigo da turma: "); scanf(" %[^\n]", cod);
    FILE *f = fopen(ARQ, "rb");
    if (!f) { printf("Nenhuma turma cadastrada.\n"); return; }
    Turma t; int ok = 0;
    while (fread(&t, sizeof(Turma), 1, f) == 1) {
        if (strcmp(t.codigo, cod) == 0) {
            printf("Turma   : %s\n", t.nome);
            printf("Alunos  : %d\n", t.qtd_alunos);
            ok = 1; break;
        }
    }
    if (!ok) printf("Turma nao encontrada.\n");
    fclose(f);
}

/* Incrementa o contador de alunos de uma turma */
void turma_add_aluno(const char *codigo) {
    FILE *f = fopen(ARQ, "r+b");
    if (!f) return;
    Turma t;
    while (fread(&t, sizeof(Turma), 1, f) == 1) {
        if (strcmp(t.codigo, codigo) == 0) {
            t.qtd_alunos++;
            fseek(f, -(long)sizeof(Turma), SEEK_CUR);
            fwrite(&t, sizeof(Turma), 1, f);
            break;
        }
    }
    fclose(f);
}

void menu_turma() {
    int n = total_turmas();
    printf("\nTotal de turmas: %d\n", n);

    /* lista todas as turmas com total de alunos */
    if (n > 0) {
        FILE *f = fopen("turmas.dat", "rb");
        Turma t;
        printf("%-20s %s\n", "Turma", "Alunos");
        printf("%-20s %s\n", "-----", "------");
        while (fread(&t, sizeof(Turma), 1, f) == 1)
            printf("%-20s %d\n", t.nome, t.qtd_alunos);
        fclose(f);
    }

    int op;
    do {
        printf("\n1-Cadastrar turma  2-Buscar turma  0-Voltar\nOpcao: ");
        scanf("%d", &op);
        if      (op == 1) cadastrar_turma();
        else if (op == 2) buscar_turma();
        else if (op != 0) printf("Invalido!\n");
    } while (op != 0);
}