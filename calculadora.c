#include <stdio.h>      // Biblioteca de entrada e saída (printf, scanf, FILE...)
#include <stdlib.h>     // Biblioteca para funções do sistema (system, EXIT_SUCCESS...)
#include <time.h>       // Biblioteca para data e hora (time, localtime, strftime)

// ─── Compatibilidade multiplataforma ─────────────────────────────────────────

#ifdef _WIN32
    #include <windows.h>
    #define LIMPAR_TELA()     system("cls")
    #define PAUSAR()          system("pause")
    #define CONFIGURAR_UTF8() SetConsoleOutputCP(65001)
#else
    #define LIMPAR_TELA()     system("clear")
    #define PAUSAR()          do { \
                                  printf("\nPressione Enter para continuar..."); \
                                  while (getchar() != '\n'); \
                              } while (0)
    #define CONFIGURAR_UTF8() /* nao necessario em Linux/macOS */
#endif

// ─── Constantes ───────────────────────────────────────────────────────────────

#define ARQUIVO_HISTORICO "historico.txt"
#define TAM_LINHA         256

// ─── Protótipos ───────────────────────────────────────────────────────────────

void  salvarHistorico(const char *operacao, float v1, float v2, float resultado);
void  exibirHistorico(void);
void  limparHistorico(void);
float lerNumero(void);
int   lerOpcao(void);

// ─── Implementações ───────────────────────────────────────────────────────────

/*
 * Salva uma operação no arquivo de histórico com data e hora.
 */
void salvarHistorico(const char *operacao, float v1, float v2, float resultado)
{
    FILE *arquivo = fopen(ARQUIVO_HISTORICO, "a");

    if (arquivo == NULL)
    {
        printf("\nAviso: nao foi possivel salvar no historico.\n");
        return;
    }

    time_t agora   = time(NULL);
    struct tm *t   = localtime(&agora);
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "%d/%m/%Y %H:%M", t);

    fprintf(arquivo, "[%s] %s: %.2f e %.2f = %.2f\n",
            timestamp, operacao, v1, v2, resultado);

    fclose(arquivo);
}

/*
 * Exibe o conteúdo do arquivo de histórico.
 */
void exibirHistorico(void)
{
    FILE *arquivo = fopen(ARQUIVO_HISTORICO, "r");

    if (arquivo == NULL)
    {
        printf("\nNenhum historico encontrado.\n");
        return;
    }

    printf("\n===== HISTORICO =====\n");

    char linha[TAM_LINHA];
    int  vazio = 1;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        printf("%s", linha);
        vazio = 0;
    }

    if (vazio)
        printf("(historico vazio)\n");

    fclose(arquivo);
}

/*
 * Apaga o conteúdo do arquivo de histórico.
 */
void limparHistorico(void)
{
    FILE *arquivo = fopen(ARQUIVO_HISTORICO, "w");

    if (arquivo != NULL)
    {
        fclose(arquivo);
        printf("\nHistorico apagado com sucesso!\n");
    }
    else
    {
        printf("\nErro ao tentar apagar o historico.\n");
    }
}

/*
 * Lê e valida um número float do teclado.
 * Rejeita entradas não-numéricas e limpa o buffer automaticamente.
 */
float lerNumero(void)
{
    float numero;
    char  lixo;

    while (1)
    {
        int lidos = scanf("%f", &numero);

        while ((lixo = getchar()) != '\n' && lixo != EOF);

        if (lidos == 1)
            break;

        printf("Valor invalido. Digite um numero: ");
    }

    return numero;
}

/*
 * Lê e valida a opção do menu.
 * Rejeita entradas não-numéricas e limpa o buffer automaticamente.
 */
int lerOpcao(void)
{
    int  opcao;
    char lixo;

    while (1)
    {
        int lidos = scanf("%d", &opcao);

        while ((lixo = getchar()) != '\n' && lixo != EOF);

        if (lidos == 1)
            break;

        printf("Opcao invalida. Digite um numero: ");
    }

    return opcao;
}

// ─── Programa principal ───────────────────────────────────────────────────────

int main(void)
{
    CONFIGURAR_UTF8();

    int   opcao;
    float valor1, valor2, resultado;

    do
    {
        LIMPAR_TELA();

        printf("=================================\n");
        printf("          CALCULADORA            \n");
        printf("=================================\n");
        printf("1 - Soma\n");
        printf("2 - Subtracao\n");
        printf("3 - Multiplicacao\n");
        printf("4 - Divisao\n");
        printf("5 - Historico\n");
        printf("6 - Limpar Historico\n");
        printf("7 - Sair\n");
        printf("=================================\n");
        printf("Escolha uma opcao: ");

        opcao = lerOpcao();

        switch (opcao)
        {
            case 1:
                printf("\nPrimeiro valor: ");
                valor1 = lerNumero();

                printf("Segundo valor: ");
                valor2 = lerNumero();

                resultado = valor1 + valor2;
                printf("\nResultado: %.2f\n", resultado);

                salvarHistorico("SOMA", valor1, valor2, resultado);
                PAUSAR();
                break;

            case 2:
                printf("\nPrimeiro valor: ");
                valor1 = lerNumero();

                printf("Segundo valor: ");
                valor2 = lerNumero();

                resultado = valor1 - valor2;
                printf("\nResultado: %.2f\n", resultado);

                salvarHistorico("SUBTRACAO", valor1, valor2, resultado);
                PAUSAR();
                break;

            case 3:
                printf("\nPrimeiro valor: ");
                valor1 = lerNumero();

                printf("Segundo valor: ");
                valor2 = lerNumero();

                resultado = valor1 * valor2;
                printf("\nResultado: %.2f\n", resultado);

                salvarHistorico("MULTIPLICACAO", valor1, valor2, resultado);
                PAUSAR();
                break;

            case 4:
                printf("\nPrimeiro valor: ");
                valor1 = lerNumero();

                printf("Segundo valor: ");
                valor2 = lerNumero();

                if (valor2 == 0.0f)
                {
                    printf("\nErro: divisao por zero!\n");
                }
                else
                {
                    resultado = valor1 / valor2;
                    printf("\nResultado: %.2f\n", resultado);
                    salvarHistorico("DIVISAO", valor1, valor2, resultado);
                }

                PAUSAR();
                break;

            case 5:
                exibirHistorico();
                PAUSAR();
                break;

            case 6:
                limparHistorico();
                PAUSAR();
                break;

            case 7:
                printf("\nEncerrando programa...\n");
                break;

            default:
                printf("\nOpcao invalida! Escolha entre 1 e 7.\n");
                PAUSAR();
        }

    } while (opcao != 7);

    return EXIT_SUCCESS;
}
