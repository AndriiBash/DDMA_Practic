#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 77793
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    char buff[BUFFER_SIZE];
    char buffadr[100];

    printf("UDP DEMO клiєнт\nЩоб вийти, напишiть 'quit'\n");

    printf("Введiть IP адресу сервера: \n");
    fgets(buffadr, sizeof(buffadr) - 1, stdin);
    printf("IP адреса сервера: %s\n", buffadr);

    int my_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (my_sock < 0)
    {
        perror("Помилка socket()");
        return -1;
    }

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, buffadr, &dest_addr.sin_addr) != 1) {
        printf("Невiдомий хост\n");
        close(my_sock);
        return -1;
    }

    while (1) 
    {
        printf("Клiєнт => Сервер: ");
        fgets(buff, sizeof(buff) - 1, stdin);

        if (!strcmp(buff, "quit\n")) break;

        sendto(my_sock, buff, strlen(buff), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));

        struct sockaddr_in server_addr;
        socklen_t server_addr_size = sizeof(server_addr);
        int n = recvfrom(my_sock, buff, sizeof(buff) - 1, 0, (struct sockaddr*)&server_addr, &server_addr_size);

        if (n < 0) 
        {
            perror("Помилка recvfrom()");
            close(my_sock);
            return -1;
        }

        buff[n] = 0;
        printf("Сервер => Клiєнт: %s", buff);
    }

    close(my_sock);
    return 0;
}
