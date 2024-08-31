#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define CHAR_CONST 100

void abnt(){
    UINT CPAGE_UTF8 = 65001;
    SetConsoleOutputCP(CPAGE_UTF8);
}

void menu();
void criptografarRecursivo(char *palavra, int numeroAvancos, int indice);
void descriptografarRecursivo(char *palavra, int numeroAvancos, int indice);
char* entradaDaPalavra();
int tamanhoDaString(char *palavraOriginal);
int entradaNumeroParaAvancoDeLetras();
int normalizarAvancos(int avanco, int limite);

void menu() {
    abnt();
    int numeroAvancos = entradaNumeroParaAvancoDeLetras();
    char *palavraAserCriptografada = entradaDaPalavra();
    int escolha = 0, paraLoop = 0;
    
    do {
        printf("\n1 - Alterar o número de avanços de caracteres\n");
        printf("2 - Criptografar uma mensagem\n");
        printf("3 - Descriptografar uma mensagem\n");
        printf("4 - Sair do sistema\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);
        getchar(); // Consome o caractere '\n' deixado pelo scanf

        switch (escolha) {
            case 1:
                numeroAvancos = entradaNumeroParaAvancoDeLetras();
                break;
            case 2:
                criptografarRecursivo(palavraAserCriptografada, numeroAvancos, 0);
                printf("Palavra criptografada: %s\n", palavraAserCriptografada);
                break;
            case 3:
                descriptografarRecursivo(palavraAserCriptografada, numeroAvancos, 0);
                printf("Palavra descriptografada: %s\n", palavraAserCriptografada);
                break;
            case 4:
                printf("Saindo...\n");
                paraLoop = 1;
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (paraLoop == 0);

    free(palavraAserCriptografada);
}

int normalizarAvancos(int avanco, int limite) {
    return avanco % limite;
}

void criptografarRecursivo(char *palavra, int numeroAvancos, int indice) {
    char caracterMinusculo[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','ç'};
    char caracterMaiusculo[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','Ç'};
    char numero[10] = {'0','1','2','3','4','5','6','7','8','9'};

    if (palavra[indice] == '\0') return;

    numeroAvancos = normalizarAvancos(numeroAvancos, 27);

    for (int j = 0; j < 10; j++) {
        if (palavra[indice] == numero[j]) {
            palavra[indice] = numero[(j + numeroAvancos) % 10];
            break;
        }
    }

    for (int j = 0; j < 27; j++) {
        if (palavra[indice] == caracterMinusculo[j]) {
            palavra[indice] = caracterMinusculo[(j + numeroAvancos) % 27];
            break;
        } else if (palavra[indice] == caracterMaiusculo[j]) {
            palavra[indice] = caracterMaiusculo[(j + numeroAvancos) % 27];
            break;
        }
    }

    criptografarRecursivo(palavra, numeroAvancos, indice + 1);
}

void descriptografarRecursivo(char *palavra, int numeroAvancos, int indice) {
    char caracterMinusculo[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','ç'};
    char caracterMaiusculo[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','Ç'};
    char numero[10] = {'0','1','2','3','4','5','6','7','8','9'};

    if (palavra[indice] == '\0') return;

    numeroAvancos = normalizarAvancos(numeroAvancos, 27);

    for (int j = 0; j < 10; j++) {
        if (palavra[indice] == numero[j]) {
            palavra[indice] = numero[(j - numeroAvancos + 10) % 10];
            break;
        }
    }

    for (int j = 0; j < 27; j++) {
        if (palavra[indice] == caracterMinusculo[j]) {
            palavra[indice] = caracterMinusculo[(j - numeroAvancos + 27) % 27];
            break;
        } else if (palavra[indice] == caracterMaiusculo[j]) {
            palavra[indice] = caracterMaiusculo[(j - numeroAvancos + 27) % 27];
            break;
        }
    }

    descriptografarRecursivo(palavra, numeroAvancos, indice + 1);
}

char* entradaDaPalavra() {
    abnt();
    char *palavraAserCriptografada = malloc(CHAR_CONST * sizeof(char));
    if (palavraAserCriptografada == NULL) {
        printf("Erro de alocação de memória\n");
        exit(1);
    }
    printf("Digite a palavra: ");
    fgets(palavraAserCriptografada, CHAR_CONST, stdin);
    palavraAserCriptografada[strcspn(palavraAserCriptografada, "\n")] = 0;
    printf("Palavra a ser modificada: %s\n", palavraAserCriptografada);
    return palavraAserCriptografada;
}

int tamanhoDaString(char *palavraOriginal) {
    return strlen(palavraOriginal);
}

int entradaNumeroParaAvancoDeLetras() {
    int numeroAvanco;
    printf("Digite o número de avanços: ");
    scanf("%d", &numeroAvanco);
    getchar(); // Consome o caractere '\n' deixado pelo scanf
    return numeroAvanco;
}

int main() {
    abnt();
    system("cls");
    menu();

    return 0;
}