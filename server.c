//Binome: Abbou Thierry Xiao Tian

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>

int main(int argc, char**argv) {
    char buff[100];
    int sock=socket(PF_INET6,SOCK_STREAM,0);
    if(sock<0){
        perror("socket");exit(1);
    }
    struct sockaddr_in6 address_sock;
    memset(&address_sock, 0, sizeof(address_sock));
    address_sock.sin6_family=AF_INET6;
    address_sock.sin6_port=htons(42460);
    
    int r=bind(sock,(struct sockaddr *)&address_sock,sizeof(struct sockaddr_in6));
    if(r<0){
        perror("bind"); close(sock);exit(1);
    }
    
    r=listen(sock,1024);
    if(r<0){
        perror("listen");close(sock);exit(1);
    }
    printf("J'attends le ou les client(s)\n");
    while(1){
        int sock2=accept(sock,NULL,NULL);
        if (sock2<0){
            perror("accept"); continue;
        }
        printf("client arrivé\n");
        while ( (r=read(sock2,buff,99)) >0) {
            buff[r]='\0';
            
            printf("%d octets reçus\n",r);
            printf("Reçu %s\n",buff);
        }
        close(sock2);
        printf("client parti\n");
    }
}