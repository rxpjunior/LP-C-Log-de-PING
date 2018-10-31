#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Funcao que cria log apenas quando o ping tiver sucesso
void pingSucesso(char h[]){
    char tempo[9]; //Variavel que armazenara o momento do ping
    printf("\nComando sendo executado: %s",h);
    if(system(h)==0){
        //Variaveis e concatenacoes
        char aux1[20]="-";
        char aux2[]="Pingou ";
        char aux3[9];
        _strtime(aux3);
        strcat(aux1,aux2);
        strcat(aux1,aux3);
        registraLog(aux1); //Variavel com a mensagem de ping com sucesso a ser passada para gravar no arquivo
    }
}
//Funcao que cria log apenas se o ping tiver fracasso
void pingFracasso(char h[]){
    char tempo[9]; //Variavel que armazenara o momento do ping
    printf("\nComando sendo executado: %s",h);
    if(system(h)!=0){
        //Variaveis e concatenacoes
        char aux1[20]="-";
        char aux2[]="Pingou ";
        char aux3[9];
        _strtime(aux3);
        strcat(aux1,aux2);
        strcat(aux1,aux3);
        registraLog(aux1); //Variavel com a mensagem de ping com sucesso a ser passada para gravar no arquivo
    }
}
//Funcao que loga ambas as situacoes
void pingAmbos(char h[]){
    char tempo[9]; //Variavel que armazenara o momento do ping
    printf("\nComando sendo executado: %s",h);
    if(system(h)==0){
        //Variaveis e concatenacoes
        char aux1[20]="-";
        char aux2[]="Pingou ";
        char aux3[9];
        _strtime(aux3);
        strcat(aux1,aux2);
        strcat(aux1,aux3);
        registraLog(aux1); //Variavel com a mensagem de ping com sucesso a ser passada para gravar no arquivo
    }
    else{
        //Variaveis e concatenacoes
        char aux1[20]="-";
        char aux2[]="NaoPingou ";
        char aux3[9];
        _strtime(aux3);
        strcat(aux1,aux2);
        strcat(aux1,aux3);
        registraLog(aux1);
    }
}

//Funcao que escreve nos arquivos de log o momento e se o ping teve sucesso ou não
void registraLog(char p[]){
    FILE *pont_arq; // Cria variável ponteiro para o arquivo
    char strg[20]; //variavel que recebera a mensagem
    strcpy(strg,p); //Copiando a string passada como argumento para variável local da funcao

    //Verifica se a string recebida tem a substring Nao, para que o arquivo aberto seja o de sucesso ou fracasso do ping
    if(strstr(strg,"Nao")==0){
        pont_arq = fopen("Sucesso.txt", "a");
    }
    else pont_arq = fopen("fracasso.txt", "a");

    //Testando se o arquivo foi realmente criado
    if(pont_arq == NULL){
        printf("Erro na abertura do arquivo!");
        return 1; //Encerra a funcao se não conseguir conectar ao arquivo
        }

    //Usando fprintf para armazenar a string no arquivo
    fprintf(pont_arq, "%s\r\n", strg); // o \r\n e para pular linha no arquivo de log

    //Usando fclose para fechar o arquivo
    fclose(pont_arq);

    return 0;
}

//Funcao que executa o teste de acordo com o solicitado
void executaPing(char opcao, char strg[]){
    char aux1;
    char aux2[40]="";
    aux1=opcao;
    strcat(aux2,strg);
    if(opcao=='1'){
        while(1){
            pingSucesso(aux2);
        }
    }
    else
    if(opcao==2){
        while(1){
            pingFracasso(aux2);
        }
    }
    else{
        while(1){
            pingAmbos(aux2);
        }
    }
}


int main(){
    char aux1[11];
    char aux2[]="ping ";
    char aux3[]=" -n 1 -w 2";
    char opcao=0;
    while((opcao!='1') && (opcao!='2') && (opcao!='3') ){
    fflush(stdin);
    printf("Entre com a opcao desejada:\n\nPara logar apenas as tentativas COM sucesso aperte 1\nPara logar apenas as tentativas SEM sucesso aperte 2\nPara logar ambas aperte 3\n");
    scanf("%c",&opcao);
    if(opcao!='1' && opcao!='2' && opcao!='3') printf("Opcao invalida, tente novamente\n");
    }

    printf("Entre com o ip a ser monitorado: ");
    scanf("%s",&aux1);
    strcat(aux2,aux1);
    strcat(aux2,aux3);
    executaPing(opcao,aux2);
}

