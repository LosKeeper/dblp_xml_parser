#include <stdio.h>
#include <string.h>

void decode_html(char* encoded_str){
    char * pnt=strstr(encoded_str,"&");
    if(pnt){
        pnt[0]=pnt[1];
        for(size_t k=1;k<strlen(pnt)-5;k++){
            pnt[k]=pnt[k+5];
        }
        pnt[strlen(pnt)-5]='\0';
    }
}
int main(void){
    char chaine[]="Jurgo-S&ouml;ren Prede";
    printf("CHAINE ENCODÉE : %s\n",chaine);
    decode_html(chaine);
    printf("CHAINE DÉCODÉE : %s\n",chaine);
    return 0;
}