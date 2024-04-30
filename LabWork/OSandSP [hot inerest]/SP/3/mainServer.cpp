#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define MY_PORT 777
#define MAX_CLIENTS 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int nclients = 0;

void *toClient(void *client_socket);

int main(int argc, char* argv[]) 
{
    char buff[1024];
    printf("TCP демо сервер\n");

    int mysocket;
    if ((mysocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        perror("Помилка socket()");
        return -1;
    }

    struct sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(MY_PORT);
    local_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(mysocket, (struct sockaddr*)&local_addr, sizeof(local_addr)) < 0) 
    {
        perror("Помилка bind");
        close(mysocket);
        return -1;
    }

    if (listen(mysocket, SOMAXCONN) < 0)
    {
        perror("Помилка listen");
        close(mysocket);
        return -1;
    }

    while (1) 
    {
        printf("Чекаю на пiдключення...\n");
        int client_socket;
        struct sockaddr_in client_addr;
        socklen_t client_addr_size = sizeof(client_addr);

        if ((client_socket = accept(mysocket, (struct sockaddr*)&client_addr, &client_addr_size)) < 0)
        {
            perror("Помилка accept");
            close(mysocket);
            return -1;
        }

        pthread_t thread;
        if (pthread_create(&thread, NULL, toClient, (void *)&client_socket) != 0) 
        {
            perror("Помилка pthread_create");
            close(client_socket);
            continue;
        }

        pthread_detach(thread);
    }

    close(mysocket);
    return 0;
}

void *toClient(void *client_socket) 
{
    int my_sock = *((int*)client_socket);
    char buff[20 * 1024];
    const char *sHELLO = "Привiт\r\n";
    send(my_sock, sHELLO, strlen(sHELLO), 0);

    ssize_t bytes_recv;
    while ((bytes_recv = recv(my_sock, buff, sizeof(buff), 0)) > 0) {
        send(my_sock, buff, bytes_recv, 0);
    }

    pthread_mutex_lock(&mutex);
    nclients--;
    printf("-вiдключено\n");
    pthread_mutex_unlock(&mutex);

    close(my_sock);
    return NULL;
}
