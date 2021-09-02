#include "headers.h"
#include "prompt.h"

int main(void){
    gethostname(hostname, SZE);
    getlogin_r(username, SZE);
    printf("%s \n", hostname);
    printf("%s \n", username);
}