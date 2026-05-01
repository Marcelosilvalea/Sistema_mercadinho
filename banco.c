#include <stdio.h>
#include <string.h>
#include "banco.h"

char nome_banco[MAX_NOME_BANCO];

void iniciar_banco() {
    printf("=========================================\n");
    printf("   SISTEMA ESCOLAR - BANCO DE DADOS C   \n");
    printf("=========================================\n");
    printf("Nome do banco de dados: ");
    scanf(" %[^\n]", nome_banco);
    printf("\nBanco '%s' iniciado com sucesso!\n", nome_banco);
    printf("=========================================\n");
}