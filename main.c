#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "rs232.c"


char Buffer[100];
int Num_Porta = 5;
int Baud = 115200;
int tamanho = 0;
int i = 0;
int j,p = 0;
char  *point;

main()
{
    time_t rawtime;
  	struct tm * timeinfo;
  
    if(!OpenComport(Num_Porta,Baud)){
    	printf("\n Aberto porta COM %d e velocidade de %d", (Num_Porta + 1), Baud);
    }
	for(i=0;i<50000;i++);
	
	
	FILE *fp;

	fp = fopen("test5.txt","a+");

    while(1)
    {
		
		j = PollComport(Num_Porta,(char *)&Buffer[p],(sizeof(Buffer) - p));
		
		if(j > 0){
			
			p = j + p;
			
			if(p > 25 && strchr((char *)&Buffer, 'W') ){
			
				point = strchr((char *)&Buffer, 'W');
				Buffer[*point] = '\0';
				
				printf("\n Quantidade de dados lidos: %d", p);
				printf("\n Quantidade : %d", strlen((char*)&Buffer));
		
				time (&rawtime);
					
		    	timeinfo = localtime (&rawtime);
	
				fprintf(fp,"\n%s - %s",Buffer,asctime(timeinfo));
				
				p = i = 0;
				j = sizeof(Buffer);
				while(j--){
					Buffer[i++] = '\0';
				}
				
			}else{
				if(j > 25){
					p = i = 0;
					j = sizeof(Buffer);
					while(j--){
						Buffer[i++] = '\0';
					}
				}
			}
		}
		
        for(i=0;i<5000;i++);
    }
}

