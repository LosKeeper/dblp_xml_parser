#include <stdio.h>
#include <string.h>

int main(void) {
    char *cmd = "";
    char *arg1 = "test_balise_a_la_ligne.xml";
    char *arg2 = "test_decodage_html.xml";
    system(strcat(cmd, strcat(arg1, arg2)));
    return 0;
}