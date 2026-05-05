#include <stdio.h>
#include "banco.h"
#include "aluno.h"
#include "professor.h"
#include "turma.h"

int main() {
    menu_banco();  /* cria ou abre o banco */

    int op;
    while (1) {
        printf("\n======= %s =======\n", banco.nome);
        printf("1-ALUNOS  2-PROFESSORES  3-TURMAS  0-SAIR\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if      (op == 1) menu_aluno();
        else if (op == 2) menu_professor();
        else if (op == 3) menu_turma();
        else if (op == 0) {
            banco_salvar();
            printf("Dados salvos. Ate logo!\n");
            return 0;
        }
        else printf("Invalido!\n");
    }
}
