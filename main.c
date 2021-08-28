
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <locale.h> //para caracteres especiais (configura a região)
#include <windows.h> //permite alterações necessária no SO


void space(){
    /*
    for(int i=0; i<20;i++){
        printf("\n");
    }
    */
    system("cls");
}

void forca(int chances){
    printf("\n -------------");
    printf("\n |           | ");
    printf("\n |           -");
    printf("\n |           %i",chances);
    printf("\n |");
    printf("\n |");
    printf("\n |");
    printf("\n |");
    printf("\n |");
    printf("\n |");
    printf("\n |");
    printf("\n -\n");
}

void pvp(char* str){
    char senha[20];
    char v1;
    int vc=1;
    printf("PLAYER 1 - Insira uma palavra: ");
    scanf("%s",&senha);
    while(vc==1){
        printf("Esta é a palavra que deseja inserir: %s? (S/N)",senha);
        scanf(" %c",&v1);
        if(v1=='S' || v1=='s'){
            vc=0;
        }else if(v1=='N' || v1=='n'){
            printf("PLAYER 1 - Insira uma palavra: ");
            scanf("%s",&senha);
        }
    }
    strcpy(str,senha);
    space();
}
void getString(char* str){  //função que gera palavras aleatorias para o game
    char nome[][20]={"LIVRO","JANTAR","PAREDE","COMPUTADOR","GARRAFA","NÚMERO","PROGRAMAÇÃO","FACULDADE","CAMISA","CARTA"}; //Matriz que contem as palavras
    srand((unsigned)time(NULL)); // Ajuste necessario para usar rand()
    int aleatorio = rand() % 10; //Gera um numero aletorio de 0 até o número expecifiado
    //printf("%d\n",aleatorio);

    strcpy(str,nome[aleatorio]);    //gambiarra p passar string de uma função p outra kkkk
}

/*
void npc(char* str){
    char s[50]; //vetor que armazena a palavra aleatoria
    getString(s); //chamando função palavra ramdom -- salvando a palavra em s
    //s[0]='p';
    //printf("%s\n", s); //teste para ver se palavra random esta OK
    //hideWord(s);    //chamand função hide (q já exibe)
    strcpy(str,s);
}
*/



void hideWord(char* str){
    int count = 0,wordLen=strlen(str);
    char hiden[20]="";
    //printf("%s\n", hiden);
    while(count<wordLen){
        strcat(hiden,"_"); //strcat() para concatenar duas palavras
        count++;
    }
    strcpy(str,hiden);
    //printf("%s",hiden);
}

int searchLetter(char letra, char str[20], char* hide){
    //printf("%c",letra);
    //printf("\n%s",str);
    int tai = 0;
    for(int i=0;i<strlen(str);i++){
        if(letra == str[i]){
            hide[i]=str[i];
            tai=1;
        }
    }
    //printf("%s",hide);
    return tai;
}

void game(int op){
    char palavra[20];
    char hide[20];
    char letterList[10];
    int chances = 6,tryL, gameLoop=1, vetorCount=0;
    char letra;



    if(op==1){
        getString(palavra);
        //printf("%s\n", palavra);
        strcpy(hide,palavra);
        hideWord(hide);
    }else if(op==2){
        pvp(palavra);
        //printf("%s\n", palavra);
        strcpy(hide,palavra);
        hideWord(hide);
        for(int i =0;i<strlen(palavra);i++){
            palavra[i] = toupper(palavra[i]);
        }
    }

    while(gameLoop){
        forca(chances);
        printf("Palavra: ");
        for(int i=0;i<strlen(hide);i++){ //exibe palavra oculta (traços)
            printf("%c ",hide[i]);
        }
        printf("(%zi letras)",strlen(hide)); //quantidade de letras contida na palavra secreta
        printf("\nChances Restantes: ");
        printf("%i",chances);
        printf("\nLetras incorretas: ");
        for(int i=0;i<vetorCount;i++){
            printf("%c ",letterList[i]);
        }
        printf("\nDigite uma letra (ou então a palavra):");
        scanf(" %c",&letra); // Pula caracteres brancos e lê o caractere seguinte
        letra = toupper(letra);

        for(int i=0;i<vetorCount;i++){  //verificar se a letra já foi digitada
            if(letra==letterList[i]){
                printf("\nEstá letra já foi digitada, tente outra:");
                scanf(" %c",&letra);
                letra = toupper(letra);
                i=-1;
            }
        }


        tryL = searchLetter(letra,palavra,hide);

        if(tryL == 0){
            chances = chances-1;
            letterList[vetorCount] = letra;
            vetorCount++;
            //printf("\nNao há letra %c nesta palavra\n",letra);
        }
        space();
        if(chances==0){
            gameLoop=0;
            printf("\nNão foi dessa vez, você perdeu!\n");
        }else if(strcmp(palavra,hide)==0){
            gameLoop=0;
            printf("\nPrabens, você acertou!\n");
        }

    }
    fflush(stdin); //limpa o buffer//não funciona no netbeans, por isso os dois getchar();
    printf("Precione qualquer tecla para continuar...\n");
    //getchar();  //duas ou limpar o buffer para não capitar restos
    getchar();
    space();
    menu();
}

void menu(){

    int option;

    printf("JOGO DA FORCA EM C \n");
    printf("1 - Jogar \n");
    printf("2 - Jogar PvP \n");
    printf("3 - Sair do jogo \n");
    printf("Escolha uma das opções a cima:");

    scanf("%i",&option);
    while(option<1 || option>3){
        printf("\nOpção invalida, tente novamente:");
        scanf("%i",&option);
    }

    if(option == 1){
        space();
        game(1);
    }else if(option == 2){
        space();
        game(2);
    }else if(option == 3){
        //nada :)
    }
}

int main(){
    system("color 0a");
    setlocale(LC_ALL, "Portuguese"); //configura o idioma da região mas apenas funciona com printf

    //para o scanf tem que mudar o codepage do terminal
    unsigned int cp    = 1252; //Codepage latin2

    SetConsoleCP(cp);       //Estabelecendo o codepage de entrada 1252(latin2)
    SetConsoleOutputCP(cp);  //Estabelecendo o codepage de saída 1252(latin2)

    menu();

}
