#ifndef TURMA_H
#define TURMA_H

#define MAX_COD_T    40
#define MAX_NOME_T   40
#define MAX_AL_T     60
#define MAX_NOME_AT  80

typedef struct {
    char codigo[MAX_COD_T];
    char nome[MAX_NOME_T];
    int qtd_alunos;
} Turma;

void menu_turma();
void cadastrar_turma();
void buscar_turma();
int  turma_existe(const char *codigo);
int  total_turmas();
void turma_add_aluno(const char *codigo);

#endif