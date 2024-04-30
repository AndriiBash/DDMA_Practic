#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 55555

int main()
{
    char buff[1024];
    
    printf("UDP DEMO echo_Server\n");

    int my_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (my_sock < 0) {
        perror("Помилка socket()");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = INADDR_ANY;
    local_addr.sin_port = htons(PORT);

    if (bind(my_sock, (struct sockaddr*)&local_addr, sizeof(local_addr)) < 0) 
    {
        perror("Помилка bind()");
        close(my_sock);
        exit(EXIT_FAILURE);
    }

    printf("PORT %d \n", ntohs(local_addr.sin_port));

    while (1) 
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_size = sizeof(client_addr);
        int bsize = recvfrom(my_sock, buff, sizeof(buff) - 1, 0, (struct sockaddr*)&client_addr, &client_addr_size);
        if (bsize < 0) 
        {
            perror("Помилка recvfrom()");
            continue;
        }

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
        printf("+%s [%s:%d] новий DATAGRAM!\n", client_ip, ntohs(client_addr.sin_port));

        buff[bsize] = 0;
        printf("Клiєнт => Сервер: %s\n", buff);

        sendto(my_sock, buff, bsize, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
    }
    return 0;
}
