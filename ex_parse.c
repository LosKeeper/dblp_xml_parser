#include <stdio.h>
#include <string.h>


int main(void){
    int k;
    FILE * entree=fopen("ex_parse.txt","r");
    char buffer[1000];
    fgets(buffer,1000,entree);
    char titre[100];
    strcpy(buffer-1,strstr(buffer, ";"));
    strcpy(titre,buffer);
    strstr(titre,";")[0]='\0';
    strstr(buffer,";")[8]='\0';
    for(k=0; k<sizeof(buffer); k++)
    {
        if(buffer[k]!=';')
        {
            /**
             * faire une fonction annexe qui retire le caractère lu a l'iteration par le k.
             */
        }
        else
        {
            /**
             * si on lit le caractère ';' alors on retire le k-ième caractère (le ;) puis renvoie le buffer don le deuxième
             */
        }
        
    }
    printf("%s\n",buffer);
    printf("%s\n",titre);  
}
