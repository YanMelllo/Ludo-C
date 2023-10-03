#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

//constantes para dar um valor a cada jogador
#define VERDE 1;
#define VERMELHO 2; 

//struct com vetores de cada jogador
struct jogadores{
    int jogadorVerde[4];
    int jogadorVermelho[4];
};
struct jogadores tab;

int rodaDados();
void preencheTabuleiro();
void tabuleiro();
int contaSeis(int *casas_andar);
void verde();
void vermelho();
int casasColoridas(int casas_andar, int casa);
void casasIguais(int cor, int jogador, int *reDado);
void ganhador(int *vencedor);
void printVencedor(int vencedor);


int main(){
    int vencedor = 0; 
    srand(time(0));

    preencheTabuleiro();
    tabuleiro();
    tab.jogadorVerde[3] = 56;
    tab.jogadorVermelho[3] = 31;

    //loop no qual o jogo ocorre, as funções são chamadas e o jogo continua até um vencedor ser confirmado
    while(vencedor == 0)
    {
        verde(); 
        tabuleiro();
        ganhador(&vencedor);
        if(vencedor != 0)
        {
            break;
        }
        vermelho();
        tabuleiro();
        ganhador(&vencedor);
        if(vencedor != 0)
        {
            break;
        }
    }

    printVencedor(vencedor);
    printf("\n");
    return 0;
}
int rodaDados(){
    return 1 + (rand() % 6); 
}

//função que define todos os valores dos vetores como 0
void preencheTabuleiro(){
    for(int i = 0; i < 4; i++)
    {
        tab.jogadorVerde[i] = 0;
        tab.jogadorVermelho[i] = 0;
    }
}

//função que armazena e conta os dados 6 rolados por cada jogador
int contaSeis(int *casas_andar){
    int cont_seis = 0;
    int num_rodado;
    int d; 
    do{
        d = rodaDados();
        if(d == 6)
        {
            casas_andar[cont_seis] = d;
            cont_seis++;
        }
        else
        {
            casas_andar[cont_seis] = d; 
        }
    }while(d == 6 && cont_seis < 3);
    return cont_seis; 
}

//função para executar a logica do primeiro jogador. Chama os dados e checka se o 6 não ocorreu 3 vezes.
//chama as outras funções de verificação durante seu processo
void verde(){
    int cont_seis, casas_andar[3] = {0,0,0}, jVerde = 1, reDado=0;

    cont_seis = contaSeis(casas_andar);

    if(cont_seis < 3)
    {   
        int peao;
        printf("Jogador Verde: Voce tem as seguintes valores para andar: ");
        for(int i = 0; i < cont_seis + 1; i++)
        {
            printf("%d ", casas_andar[i]);
        }
        printf("\n");
        printf("Digite 5 para passar a vez\n");
        for(int i = 0; i < cont_seis + 1; i++)
        {
            printf("Qual peao deseja mover %d casas (1-4): ", casas_andar[i]);
            scanf("%d", &peao);
            peao--;
            if(peao > 3)
            {
                printf("Voce passou a vez.\n");
                continue;
            }
            else if(tab.jogadorVerde[peao] == 0 && casas_andar[i] < 6)
            {
                printf("E preciso um 6 parar retirar um peao da saida. Jogue outro numero.\n");
                i--; 
            }
            else
            {
                if(tab.jogadorVerde[peao] >= 52)
                {
                    int final = casasColoridas(casas_andar[i], tab.jogadorVerde[peao]);
                    if(final == 1)
                    {
                        tab.jogadorVerde[peao] += casas_andar[i];
                        printf("Linha de chegada!!\n"); 
                        printf("Peao %d, casa: %d \n", peao+1, tab.jogadorVerde[peao]);
                        reDado = 2;
                    }
                    else if(final == 2)
                    {
                        printf("Este peao ja esta na linha de chegada. Escolha outro peao.\n");
                        i--;
                    }
                    else
                    {
                        printf("Este peao nao chega ate a linha de chegada. Escolha outro peao.\n");
                        i--;
                    }
                }
                else if(tab.jogadorVerde[peao] == 0)
                {
                    tab.jogadorVerde[peao]++;
                    printf("Peao %d, casa: %d \n", peao+1, tab.jogadorVerde[peao]);
                }
                else{
                    tab.jogadorVerde[peao] += casas_andar[i];
                    casasIguais(jVerde, tab.jogadorVerde[peao], &reDado);
                    printf("Peao %d, casa: %d \n", peao+1, tab.jogadorVerde[peao]);
                }
            }
        }
        if(reDado == 1)
        {
            printf("\nPor ter capturado um peao adversario voce pode jogar novamente.\n\n");
            verde();
        }
        else if(reDado == 2)
        {
            int checka_vencedor=0;
            ganhador(&checka_vencedor);
            if(checka_vencedor == 0)
            {
                printf("\nPor ter chegado a linha de chegada voce pode jogar novamente.\n\n");
                verde();
            }
        }
    }
    else
    {
        printf("3 seis, perdeu a vez.\n");
    }
}

//função para executar a logica do segundo jogador. Chama os dados e checka se o 6 não ocorreu 3 vezes.
//chama as outras funções de verificação durante seu processo
void vermelho()
{
    int cont_seis, casas_andar[3] = {0,0,0}, jVermelho = 2, reDado=0;

    cont_seis = contaSeis(casas_andar);

    if(cont_seis < 3)
    {   
        int peao;
        printf("Jogador Vermelho: Voce tem as seguintes valores para andar: ");
        for(int i = 0; i < cont_seis + 1; i++)
        {
            printf("%d ", casas_andar[i]);
        }
        printf("\n");
        printf("Digite 5 para passar a vez\n");
        for(int i = 0; i < cont_seis + 1; i++)
        {
            printf("Qual peao deseja mover %d casas (1-4): ", casas_andar[i]);
            scanf("%d", &peao);
            peao--;
            if(peao > 3)
            {
                printf("Voce passou a vez.\n");
                break;
            }
            else if(tab.jogadorVermelho[peao] == 0 && casas_andar[i] < 6)
            {
                printf("E preciso um 6 parar retirar um peao da saida. Jogue outro numero.\n");
                i--; 
            }
            else
            {
                if(tab.jogadorVermelho[peao] >= 52)
                {
                    int final = casasColoridas(casas_andar[i], tab.jogadorVermelho[peao]);
                    if(final == 1)
                    {
                        tab.jogadorVermelho[peao] += casas_andar[i];
                        printf("Linha de chegada!!\n"); 
                        printf("Peao %d, casa: %d \n", peao+1, tab.jogadorVermelho[peao]);
                    }
                    else if(final == 2)
                    {
                        printf("Este peao ja esta na linha de chegada. Escolha outro peao.\n");
                        i--;
                    }
                    else
                    {
                        printf("Este peao nao chega ate a linha de chegada. Escolha outro peao.\n");
                        i--;
                    }
                }
                else if(tab.jogadorVermelho[peao] == 0)
                {
                    tab.jogadorVermelho[peao]++;
                    printf("Peao %d, casa: %d \n", peao+1, tab.jogadorVermelho[peao]);
                }
                else{
                    tab.jogadorVermelho[peao] += casas_andar[i];
                    casasIguais(jVermelho, tab.jogadorVermelho[peao], &reDado);
                    printf("Peao %d, casa: %d \n", peao+1, tab.jogadorVermelho[peao]);
                }
            }
        }
        if(reDado == 1)
        {
            printf("\nPor ter capturado um peao adversario voce pode jogar novamente.\n\n");
            vermelho();
        }
        else if(reDado == 2)
        {
            int checka_vencedor=0;
            ganhador(&checka_vencedor);
            if(checka_vencedor == 0)
            {
                printf("\nPor ter chegado a linha de chegada voce pode jogar novamente.\n\n");
                vermelho();
            }
        }
    }
    else
    {
        printf("3 seis, perdeu a vez.\n");
    }

}

//função que verifica se um peao movido caiu em uma casa com o peão adversario. Se sim, checka se essa casa é segura ou não
void casasIguais(int cor, int jogador, int *reDado)
{
    int casas_seguras[8] = {1, 9, 14, 22, 27, 35, 40, 48}, verificaCasa=0;
    if(cor == 1)
    {
        for(int i = 0; i < 4; i++)
        {
            if(jogador - 26 == tab.jogadorVermelho[i])
            {
                if(tab.jogadorVermelho[i] == 0)
                {
                    break;
                }
                for(int j = 0; j < 8; j++)
                {
                    if(jogador == casas_seguras[j])
                    {
                        verificaCasa++;
                    }
                }
                if(verificaCasa == 1)
                {
                    printf("\nCasa segura, o peao adversario nao pode ser capturado.\n");
                    break;
                }
                else
                {
                    printf("\nVoce capturou o peao vermelho %d\n", i+1);
                    tab.jogadorVermelho[i] = 0;
                    *reDado = 1;
                    break;
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < 4; i++)
        {
            if(jogador - 26 == tab.jogadorVerde[i])
            {
                if(tab.jogadorVerde[i] == 0)
                {
                    break;
                }
                for(int j = 0; j < 8; j++)
                {
                    if(jogador == casas_seguras[j])
                    {
                        verificaCasa++;
                    }
                }
                if(verificaCasa == 1)
                {
                    printf("\nCasa segura, o peao adversario nao pode ser capturado.\n");
                    break;
                }
                else
                {
                    printf("\nVoce capturou o peao verde %d\n", i+1);
                    tab.jogadorVerde[i] = 0;
                    *reDado = 1;
                    break;
                }
            }
        }
    }
}

//checka se o dado é o suficiente para chegar a linha de chegada. Também verifica se o peao já esta la para não ser mais movido
int casasColoridas(int casas_andar, int casa)
{
    if(casa == 57)
    {
        return 2; 
    }
    else if(casa + casas_andar == 57)
    {
        return 1;
    }
    else
    {
        return 0; 
    }
}

//printa o tabuleiro em seu status atual
void tabuleiro()
{
    printf("---TABULEIRO---\n");
    printf("Jogador Verde:\n");
    printf("Peao 1, casa: %d\nPeao 2, casa: %d\nPeao 3, casa: %d\nPeao 4, casa: %d\n", tab.jogadorVerde[0], tab.jogadorVerde[1], tab.jogadorVerde[2], tab.jogadorVerde[3]);
    printf("\n");
    printf("Jogador Vermelho:\n");
    printf("Peao 1, casa: %d\nPeao 2, casa: %d\nPeao 3, casa: %d\nPeao 4, casa: %d\n", tab.jogadorVermelho[0], tab.jogadorVermelho[1], tab.jogadorVermelho[2], tab.jogadorVermelho[3]);
    printf("\n---------------\n");
}

//verifica o ganhador para os condicionais na função main
void ganhador(int *vencedor)
{
    int conta_verde = 0, conta_vermelho = 0;
    for(int i = 0; i < 4; i++)
    {
        if(tab.jogadorVerde[i] == 57)
        {
            conta_verde++;
        }
    }
    if(conta_verde == 4)
    {
        *vencedor = VERDE;
    }
    for(int i = 0; i < 4; i++)
    {
        if(tab.jogadorVermelho[i] == 57)
        {
            conta_vermelho++;
        }
    }
    if(conta_vermelho == 4)
    {
        *vencedor = VERMELHO;
    }
}

//printa o jogador vencedor
void printVencedor(int vencedor)
{
    if(vencedor == 1)
    {
        printf("O JOGADOR VERDE VENCEU!!!\n");
    }
    else if(vencedor == 2)
    {
        printf("O JOGADOR VERMELHO VENCEU!!!\n");
    }
    else
    {
        printf("Erro. O vencedor nao pode ser definido.\n");
    }
}