#ifndef PROFESSOR_H
#define PROFESSOR_H

#define MAX_NOME_P 80
#define MAX_REG    20
#define MAX_DISC_P 60

typedef struct {
    char registro[MAX_REG];
    char nome[MAX_NOME_P];
    char disciplina[MAX_DISC_P];
} Professor;

void menu_professor();
void cadastrar_professor();
void buscar_professor();
int  total_professores();

#endif