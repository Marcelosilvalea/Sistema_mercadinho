#include <stdio.h>
#include <string.h>
#include "banco.h"
#include "professor.h"

void cadastrar_professor() {
    if (banco.qtd_professores >= MAX_PROFESSORES) {
        printf("Limite de professores atingido!\n"); return;
    }
    Professor *p = &banco.professores[banco.qtd_professores];
    snprintf(p->registro, MAX_REG, "P%04d", banco.qtd_professores + 1);
    printf("Registro: %s\n", p->registro);
    printf("Nome: ");       scanf(" %[^\n]", p->nome);
    printf("Disciplina: "); scanf(" %[^\n]", p->disciplina);
    banco.qtd_professores++;
    banco_salvar();
    printf("Professor cadastrado! Registro: %s\n", p->registro);
}

void buscar_professor() {
    char reg[MAX_REG];
    printf("Registro (ex: P0001): "); scanf("%s", reg);
    for (int i = 0; i < banco.qtd_professores; i++) {
        if (strcmp(banco.professores[i].registro, reg) == 0) {
            Professor *p = &banco.professores[i];
            printf("\nRegistro  : %s\n", p->registro);
            printf("Nome      : %s\n",  p->nome);
            printf("Disciplina: %s\n",  p->disciplina);
            return;
        }
    }
    printf("Professor nao encontrado.\n");
}

void menu_professor() {
    printf("\nTotal de professores: %d\n", banco.qtd_professores);
    int op;
    do {
        printf("\n1-Cadastrar  2-Buscar  0-Voltar\nOpcao: ");
        scanf("%d", &op);
        if      (op == 1) cadastrar_professor();
        else if (op == 2) buscar_professor();
        else if (op != 0) printf("Invalido!\n");
    } while (op != 0);
}
