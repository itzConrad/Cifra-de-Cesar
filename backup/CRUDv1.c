#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#define charConst 100

void menu (){
    int *numeroAvancos = entradaNumeroParaAvancoDeLetras();
    char *palavraAserCriptografada = entradaDaPalavra();
    int escolha = 0, paraLoop=0;
    printf("1 - alterar o número de avanços de caracteres\n");
    printf("2 - criptografar uma mensagem\n");
    printf("3 - descriptografar uma mensagem\n");
    printf("4 - sair do sistema\n");
    printf("Digite sua escolha: \n");
    scanf("%i", &escolha);
    do
    {
        switch (escolha)
        {
        case 1:
            entradaNumeroParaAvancoDeLetras();
            break;
        
        case 2:
            criptografar(*numeroAvancos, *palavraAserCriptografada);
            break;
        
        case 3:
            descriptografar(*numeroAvancos);
            break;
        
        case 4:
            printf("Saindo...");
            paraLoop=1;
            exit(0);
            break;
        
        default:
            break;
        }
    } while (paraLoop==0);
    
}

void criptografar(int *numeroAvancos, char *palavraAserCriptografada ){
    int tapaBuraco;
    int tamanhoEmIntDaPalavra = tamanhoDaString(tapaBuraco);
    char caracterMinusculo[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','ç'};
    char caracterMaiusculo[27]= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','S','Ç'};
    char numero[10] = {'0','1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int controle = 0;
    for(int i = 0; i<tamanhoEmIntDaPalavra; i++){
        for(int j = 0; j<10; j++){
            if (palavraAserCriptografada[i]==numero[j]){
                if (j+numeroAvancos>=10){
                    controle = (j+numeroAvancos)-10;
                    palavraAserCriptografada[i]=numero[controle];
                }else{
                    palavraAserCriptografada[i]=numero[j+ *numeroAvancos];
                }
            }
        }
    }
    for(int i = 0; i<tamanhoEmIntDaPalavra; i++){
        for(int j = 0; j<27; j++){
            if(palavraAserCriptografada[i]==caracterMinusculo){
                if (j+numeroAvancos>=27){
                    controle = (j+numeroAvancos)-27;
                    palavraAserCriptografada[i]=caracterMinusculo[controle];
                }else{
                    palavraAserCriptografada[i]=caracterMinusculo[j+ *numeroAvancos];
                }
            }else if(palavraAserCriptografada[i]==caracterMaiusculo){
                if (j+numeroAvancos>=27){
                    controle = (j+numeroAvancos)-27;
                    palavraAserCriptografada[i]=caracterMaiusculo[controle];
                }else{
                    palavraAserCriptografada[i]=caracterMaiusculo[j+ *numeroAvancos];
                }
            }
        }
    }
    printf("Palavra criptografada: %c", palavraAserCriptografada); 
}
//Palavra do Usuário
char* entradaDaPalavra() {
    char palavraAserCriptografada[charConst];
    printf("Digite a palavra: \n");
    fflush(stdin);
    gets(palavraAserCriptografada);

    tamanhoDaString(&palavraAserCriptografada); 
    return palavraAserCriptografada;
}
//Tamanho da Palavra do Usuário
int tamanhoDaString(char palavraASerCripto){
    char palavraOriginal[] = entradaDaPalavra(palavraASerCripto);
    size_t tamanhoEmIntDaPalavra = strlen(palavraOriginal);
    descriptografar(tamanhoEmIntDaPalavra);
    return tamanhoEmIntDaPalavra;
}
//Numero de Deslocações/Avanços
int entradaNumeroParaAvancoDeLetras() {
    int numeroAvanco;
    printf("Digite o número de avanços: ");
    scanf("%i", &numeroAvanco);
    return numeroAvanco;

}

int descriptografar (int tamanhoDaPalavra) {
    char palavraAserCriptografada[] = entradaDaPalavra();
    int numeroAvancos = entradaNumeroParaAvancoDeLetras();
    char caracterMinusculo[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','ç'};
    char caracterMaiusculo[27]= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','S','Ç'};
    char numero[10] = {'0','1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int controle = 0;
    for(int index = 0; index< tamanhoDaPalavra; index++){
        for(int j = 0; j<10; j++){
            if (palavraAserCriptografada[index]==numero[j]){
                if (j-numeroAvancos<0){
                    controle = (j-numeroAvancos)+10;
                    palavraAserCriptografada[index]=numero[controle];
                }else{
                    palavraAserCriptografada[index]=numero[j- numeroAvancos];
                }
            }
        }
    }
    for(int i = 0; i<tamanhoDaPalavra; i++){
        for(int j = 0; j<27; j++){
            if(palavraAserCriptografada[i]==caracterMinusculo){
                if (j-numeroAvancos<0){
                    controle = (j-numeroAvancos)+27;
                    palavraAserCriptografada[i]=caracterMinusculo[controle];
                }else{
                    palavraAserCriptografada[i]=caracterMinusculo[j- numeroAvancos];
                }
            }else if(palavraAserCriptografada[i]==caracterMaiusculo){
                if (j-numeroAvancos<0){
                    controle = (j-numeroAvancos)+27;
                    palavraAserCriptografada[i]=caracterMaiusculo[controle];
                }else{
                    palavraAserCriptografada[i]=caracterMaiusculo[j- numeroAvancos];
                }
            }
        }
    }
    printf("Palavra descriptografada: %s", palavraAserCriptografada); 
}

int main (){
//abnt
    UINT CPAGE_UTF8 = 65001;
    SetConsoleOutputCP(CPAGE_UTF8);
    system("cls");
//chamada de funções
    entradaDaPalavra();
    menu();
    return 0;
}