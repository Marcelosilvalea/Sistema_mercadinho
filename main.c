#include <stdio.h>
#include "banco.h"
#include "aluno.h"
#include "professor.h"
#include "turma.h"

int main() {
    iniciar_banco();

    int op;
    while (1) {
        printf("\n========= %s =========\n", nome_banco);
        printf("1-ALUNOS  2-PROFESSORES  3-TURMAS  0-SAIR\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if      (op == 1) menu_aluno();
        else if (op == 2) menu_professor();
        else if (op == 3) menu_turma();
        else if (op == 0) { printf("Saindo...\n"); return 0; }
        else printf("Invalido!\n");
    }
}