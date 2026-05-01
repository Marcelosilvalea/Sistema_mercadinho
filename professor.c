#include <stdio.h>
#include <string.h>
#include "professor.h"

#define ARQ "professores.dat"

int total_professores() {
    FILE *f = fopen(ARQ, "rb");
    if (!f) return 0;
    fseek(f, 0, SEEK_END);
    int n = ftell(f) / sizeof(Professor);
    fclose(f);
    return n;
}

void cadastrar_professor() {
    Professor p;
    snprintf(p.registro, MAX_REG, "P%04d", total_professores() + 1);
    printf("Registro gerado: %s\n", p.registro);
    printf("Nome: ");       scanf(" %[^\n]", p.nome);
    printf("Disciplina: "); scanf(" %[^\n]", p.disciplina);
    FILE *f = fopen(ARQ, "ab");
    fwrite(&p, sizeof(Professor), 1, f);
    fclose(f);
    printf("Professor cadastrado! Registro: %s\n", p.registro);
}

void buscar_professor() {
    char reg[MAX_REG];
    printf("Registro (ex: P0001): "); scanf("%s", reg);
    FILE *f = fopen(ARQ, "rb");
    if (!f) { printf("Nenhum professor cadastrado.\n"); return; }
    Professor p; int ok = 0;
    while (fread(&p, sizeof(Professor), 1, f) == 1) {
        if (strcmp(p.registro, reg) == 0) {
            printf("\nRegistro  : %s\n", p.registro);
            printf("Nome      : %s\n", p.nome);
            printf("Disciplina: %s\n", p.disciplina);
            ok = 1; break;
        }
    }
    if (!ok) printf("Professor nao encontrado.\n");
    fclose(f);
}

void menu_professor() {
    printf("\nTotal de professores cadastrados: %d\n", total_professores());
    int op;
    do {
        printf("\n1-Cadastrar professor  2-Buscar professor  0-Voltar\nOpcao: ");
        scanf("%d", &op);
        if      (op == 1) cadastrar_professor();
        else if (op == 2) buscar_professor();
        else if (op != 0) printf("Invalido!\n");
    } while (op != 0);
}