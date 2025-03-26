//Binome: Abbou Thierry Xiao Tian

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char* argv[]) {
	



















    int descr=socket(PF_INET6,SOCK_STREAM,0);
    if(descr<0){
        perror("socket");exit(1);
    }
    struct sockaddr_in6 adress_sock;
    memset(&adress_sock,0,sizeof(adress_sock));
    adress_sock.sin6_family = AF_INET6;
    adress_sock.sin6_port = htons(42460);
    int r = inet_pton(AF_INET6, "::1", &adress_sock.sin6_addr);
    if(r==0){puts("adresse incompréhensible");close(descr);exit(1);}
    if(r<0){perror("pton");close(descr);exit(1);}
    r=connect(descr,(struct sockaddr *)&adress_sock,
              sizeof(struct sockaddr_in6));
    if(r<0){perror("connect"); close(descr);exit(1);}
    
    char *mess="SALUT!\n";
    write(descr,mess,strlen(mess)); //on pourrait tester si >0
    mess="Ciao!\n";
    write(descr,mess,strlen(mess));
    close(descr);
    return 0;
}