#ifndef ALUNO_H
#define ALUNO_H

#define MAX_NOME   80
#define MAX_MAT    20
#define MAX_TURMA  40
#define MAX_NOTAS   5

typedef struct {
    char matricula[MAX_MAT];
    char nome[MAX_NOME];
    char turma[MAX_TURMA];
    float notas[MAX_NOTAS];
    int qtd_notas;
} Aluno;

void menu_aluno();
void cadastrar_aluno();
void buscar_aluno();
int  total_alunos();

#endif