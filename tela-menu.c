#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>

void linhaCol(int lin, int col);
void box(int lin1, int col1, int lin2, int col2);
int menu(int lin1, int col1, int qtd, char lista[3][40]);
void textColor(int letras, int fundo);
  //COR DA LETRA
  enum{BLACK,                 //0
       BLUE,                  //1
       GREEN,                 //2
       CYAN,                  //3
       RED,                   //4
       MAGENTA,               //5
       BROWN,                 //6
       LIGHTGRAY,             //7
       DARKGRAY,              //8
       LIGHTBLUE,             //9
       LIGHTGREEN,            //10
       LIGHTCYAN,             //11
       LIGHTRED,              //12
       LIGHTMAGENTA,          //13
       YELLOW,                //14
       WHITE                  //15
       
       };  
  //COR DO FUNDO
  enum{_BLACK=0,                 //0
       _BLUE=16,                  //1
       _GREEN=32,                 //2
       _CYAN=48,                  //3
       _RED=64,                   //4
       _MAGENTA=80,               //5
       _BROWN=96,                 //6
       _LIGHTGRAY=112,             //7
       _DARKGRAY=128,              //8
       _LIGHTBLUE=144,             //9
       _LIGHTGREEN=160,            //10
       _LIGHTCYAN=176,             //11
       _LIGHTRED=192,              //12
       _LIGHTMAGENTA=208,          //13
       _YELLOW=224,                //14
       _WHITE=240                  //15       
       };  
       

void textColor(int letra, int fundo){
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letra + fundo);
     }
     
void linhaCol(int lin, int col){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){col-1,lin-1});// coorddenada na tela
     
     //funcao para deixar o cursor invisivel
     HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_CURSOR_INFO info;
     info.dwSize = 100;
     info.bVisible = FALSE;
     SetConsoleCursorInfo(consoleHandle, &info);
}
void box(int lin1, int col1, int lin2, int col2){
     int i,j , tamlin, tamcol;
     
     //achar o tamanho do box
     tamlin = lin2 - lin1;
     tamcol = col2 - col1;
     
     //Monta o Box
     
     for (i=col1; i<=col2; i++){ // linhas
         linhaCol(lin1,i);
         printf("%c",196);
         linhaCol(lin2,i);
         printf("%c",196);
         }
        
     for (i=lin1; i<=lin2; i++){ //colunas
         linhaCol(i,col1);
         printf("%c",179);
         linhaCol(i,col2);
         printf("%c",179);
         }
     for (i=lin1+1;i<lin2;i++){
         for(j=col1+1;j<col2;j++){
            linhaCol(i,j);printf(" ");
         }
         }
     //Posição dos cantos
     linhaCol(lin1,col1);
     printf("%c",218);
     linhaCol(lin1,col2);
     printf("%c",191);
     linhaCol(lin2,col1);
     printf("%c",192);
     linhaCol(lin2,col2);
     printf("%c",217);       
     
     }
int menu(int lin1, int col1, int qtd, char lista[3][40]){
     int opc=1, lin2, col2, linha,i,tamMaxItem, tecla;
     
     //calcula as coordenadas
     tamMaxItem = strlen(lista[0]);
     //tamanho maximo do item
     for(i=1; i<qtd;i++){
       if(strlen(lista[i])>tamMaxItem){
          tamMaxItem = strlen(lista[i]); 
       } 
     }
     lin2 = lin1+(qtd*2+2);
     col2 = col1+tamMaxItem+4;
     
     //Monta Tela
     textColor(WHITE, _BLUE);
     setlocale(LC_ALL,"C");
     box(lin1,col1,lin2,col2);
     setlocale(LC_ALL,"");
     //laço das opcões
     while(1){
     
        linha=lin1+2;
        for(i=0;i<qtd;i++){           
           if(i+1==opc)textColor(BLACK, _LIGHTGREEN);
           else textColor(WHITE, _BLUE);
        linhaCol(linha,col1+2);
        printf("%s",lista[i]);
        linha +=2;
        }
       
       //Aguarda tecla
       linhaCol(1,1);
       tecla= getch();
       linhaCol(22,1);
       //printf(" tecla:  %d   ",tecla);  
       //Opção
       if(tecla==27){ //ESC
       opc=0; break;
       }
       else if(tecla==13){ //ENTER
       break;
       }
       //Seta para cima
       else if(tecla==72){ //se possivel seleciona o item anterior - seta para cima
            if(opc>1)opc--;  // se opcao for maior que 1, pode voltar 
       
       }
       else if(tecla==80 ){        //seta para baixo
            if (opc<qtd)opc++;                //Se opcao for menor que quantidade de itens, posso avançar
                  
                           
       //printf("tecla: %d ",opc);     
       }
     }
     return opc;
}     

int main()
{
    int opc;
    char lista[5][40]={"Pizza de Frango", "Pizza Portuguesa", "Pizza Baiana", "Pizza de Brocolis", "Pizza de Calabresa"};
    
    setlocale(LC_ALL,"");
    while(true){
       opc = menu(10,10,5,lista);
    
       if (opc==0){
       break;
       }
    
        linhaCol(1,1);
        textColor(WHITE, _RED);
        printf("\nEscolheu a opção %d", opc);

    }
  textColor(WHITE, _BLACK);
  linhaCol(24,1);
  printf("");
  
  return 0;
}
