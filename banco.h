#ifndef BANCO_H
#define BANCO_H

#include <stdio.h>

#define MAX_NOME_BANCO  60
#define MAX_ALUNOS     200
#define MAX_PROFESSORES 50
#define MAX_TURMAS      30

#define MAX_NOME   80
#define MAX_MAT    20
#define MAX_TURMA  40
#define MAX_NOTAS   5
#define MAX_REG    20
#define MAX_DISC   60
#define MAX_COD_T  40

typedef struct {
    char matricula[MAX_MAT];
    char nome[MAX_NOME];
    char turma[MAX_TURMA];
    float notas[MAX_NOTAS];
    int qtd_notas;
} Aluno;

typedef struct {
    char registro[MAX_REG];
    char nome[MAX_NOME];
    char disciplina[MAX_DISC];
} Professor;

typedef struct {
    char codigo[MAX_COD_T];
    char turno[20];
    int qtd_alunos;
} Turma;

/* Estrutura principal do banco — tudo num so lugar */
typedef struct {
    char nome[MAX_NOME_BANCO];
    int qtd_alunos;
    int qtd_professores;
    int qtd_turmas;
    Aluno      alunos[MAX_ALUNOS];
    Professor  professores[MAX_PROFESSORES];
    Turma      turmas[MAX_TURMAS];
} Banco;

extern Banco banco;
extern char  arquivo_banco[80];

void menu_banco();
int  banco_carregar(const char *nome);
void banco_salvar();

#endif