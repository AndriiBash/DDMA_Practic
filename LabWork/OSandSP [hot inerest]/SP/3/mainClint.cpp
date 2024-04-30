#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 777
#define SERVERADDR "127.0.0.1"

int main(int argc, char* argv[])
{
    char buff[1024];
    printf("TCP демо клiєнт\n");

    int my_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (my_sock < 0)
    {
        perror("Помилка socket()");
        return -1;
    }

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVERADDR, &dest_addr.sin_addr) <= 0)
    {
        perror("Невiрна адреса");
        return -1;
    }

    if (connect(my_sock, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) < 0)
    {
        perror("Помилка пiдключення");
        return -1;
    }

    printf("Пiдключення до %s успiшне\n Для виходу введiть 'quit'\n\n", SERVERADDR);

    int nsize = 1024;
    while (1)
    {
        nsize = recv(my_sock, buff, sizeof(buff) - 1, 0);
        if (nsize == 0)
        {
            printf("Сервер закрив з'єднання\n");
            break;
        } else if (nsize < 0)
        {
            perror("Помилка отримання даних");
            break;
        }

        buff[nsize] = '\0';
        printf("Сервер=>Клiєнт: %s", buff);
        printf("Сервер<=Клiєнт: ");
        fgets(buff, sizeof(buff), stdin);
        
        if (strcmp(buff, "quit\n") == 0)
        {
            printf("Вихiд...");
            break;
        }
        send(my_sock, buff, strlen(buff), 0);
    }

    close(my_sock);
    return 0;
}


