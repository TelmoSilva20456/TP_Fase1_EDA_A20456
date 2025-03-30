/*!
 *  @file main.c
 *  @author Telmo Silva | a20456
 *  @date 2025-03-25
 *  @project Fase 1 - Estruturas de Dados Avançadas
 *
 *  Programa principal com menu interativo.
 */


#include "antenas.h"
#include <stdio.h>
#include <stdlib.h>

void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void exibir_menu() {
    printf("\n=== Menu de Operacoes ===\n");
    printf("1. Inserir nova antena\n");
    printf("2. Remover antena\n");
    printf("3. Listar antenas\n");
    printf("4. Exibir matriz com efeitos nefastos\n");
    printf("6. Carregar configuracao\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}



int main() {
    int linhas_pos = 12, colunas_pos = 12;
    int linhas_efeito = 10, colunas_efeito = 10;
    Antena* lista = NULL;
    char opcao;
    char** matriz_pos = inicializarMatriz(linhas_pos, colunas_pos);
    char** matriz_efeito = inicializarMatriz(linhas_efeito, colunas_efeito);

    inserir_antenas_iniciais(&lista);

    do {
        limpar_tela();
        exibir_menu();
        scanf(" %c", &opcao);
        while (getchar() != '\n');

        switch (opcao) {
            case '1': {
                char freq;
                int linha, coluna;
                printf("\nInserir nova antena\n");
                printf("Frequencia (caractere): ");
                scanf(" %c", &freq);
                while (getchar() != '\n');
                printf("Linha (1-12): ");
                scanf("%d", &linha);
                while (getchar() != '\n');
                printf("Coluna (1-12): ");
                scanf("%d", &coluna);
                while (getchar() != '\n');

                if (linha >= 1 && linha <= linhas_pos && coluna >= 1 && coluna <= colunas_pos) {
                    Antena* nova = inserirAntena(lista, freq, linha, coluna);
                    if (nova != lista) {
                        printf("\nAntena inserida com sucesso!\n");
                    }
                    lista = nova;
                } else {
                    printf("\nPosicao invalida!\n");
                }
                printf("\nPrima ENTER para continuar...");
                getchar();
                break;
            }

            case '2': {
                int linha, coluna;
                printf("\nRemover antena\n");
                printf("Linha (1-12): ");
                scanf("%d", &linha);
                while (getchar() != '\n');
                printf("Coluna (1-12): ");
                scanf("%d", &coluna);
                while (getchar() != '\n');

                if (linha >= 1 && linha <= linhas_pos && coluna >= 1 && coluna <= colunas_pos) {
                    lista = removerAntena(lista, linha, coluna);
                    printf("\nAntena removida (se existisse).\n");
                } else {
                    printf("\nPosicao invalida!\n");
                }

                printf("\nPrima ENTER para continuar...");
                getchar();
                break;
            }

            case '3': {
                printf("\nListagem de Antenas:\n");
                listarAntenas(lista);
                printf("\nPrima ENTER para continuar...");
                getchar();
                break;
            }

            case '4': {
                for (int i = 0; i < linhas_pos; i++)
                    for (int j = 0; j < colunas_pos; j++)
                        matriz_pos[i][j] = '.';

                for (Antena* atual = lista; atual != NULL; atual = atual->next)
                    matriz_pos[atual->posicao.linha - 1][atual->posicao.coluna - 1] = atual->frequencia;

                printf("\nMapa de Posicionamento (12x12):\n");
                printf("   ");
                for (int j = 1; j <= colunas_pos; j++) printf("%d ", j);
                printf("\n");
                for (int i = 0; i < linhas_pos; i++) {
                    printf("%2d ", i + 1);
                    for (int j = 0; j < colunas_pos; j++) {
                        printf("%c ", matriz_pos[i][j]);
                    }
                    printf("\n");
                }

                for (int i = 0; i < linhas_efeito; i++)
                    for (int j = 0; j < colunas_efeito; j++)
                        matriz_efeito[i][j] = '.';

                EfeitoNefasto* efeitos = calcularEfeitoNefasto(lista, linhas_efeito, colunas_efeito);
                atualizarMatrizComEfeitos(matriz_efeito, efeitos);
                marcarAntenasNaMatriz(matriz_efeito, lista);

                printf("\nMapa de Efeito Nefasto (10x10):\n");
                printf("   ");
                for (int j = 1; j <= colunas_efeito; j++) printf("%d ", j);
                printf("\n");
                for (int i = 0; i < linhas_efeito; i++) {
                    printf("%2d ", i + 1);
                    for (int j = 0; j < colunas_efeito; j++) {
                        printf("%c ", matriz_efeito[i][j]);
                    }
                    printf("\n");
                }

                libertarListaEfeitos(efeitos);
                printf("\nPrima ENTER para continuar...");
                getchar();
                break;
            }

            case '6': {
                char nome_arquivo[100];
                printf("\nNome do ficheiro a carregar: ");
                scanf("%s", nome_arquivo);
                while (getchar() != '\n');

                int novas_linhas, novas_colunas;
                Antena* nova_lista = carregarAntenasDeFicheiro(nome_arquivo, &novas_linhas, &novas_colunas);

                if (nova_lista != NULL) {
                    libertarListaAntenas(lista);
                    lista = nova_lista;
                    printf("\nConfiguracao carregada com sucesso!\n");
                } else {
                    printf("\nErro ao carregar ficheiro!\n");
                }

                printf("\nPrima ENTER para continuar...");
                getchar();
                break;
            }

            case '0':
                printf("\nA encerrar o programa...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                printf("\nPrima ENTER para continuar...");
                getchar();
        }

    } while (opcao != '0');

    libertarListaAntenas(lista);
    libertarMatriz(matriz_pos, linhas_pos);
    libertarMatriz(matriz_efeito, linhas_efeito);
    return 0;
}
