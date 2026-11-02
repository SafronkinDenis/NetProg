#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

int main() {
    const char* server_ip = "172.16.40.1";
    int port = 7; // стандартный порт echo

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cerr << "Ошибка создания сокета" << endl;
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);


    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cerr << "Ошибка подключения к серверу" << endl;
        close(sock);
        return 1;
    }

    cout << "Подключено к echo серверу " << server_ip << ":" << port << endl;
    cout << "Введите сообщение (или 'exit' для выхода): ";

    char send_buf[256];
    char recv_buf[256];

    while (true) {
        cin.getline(send_buf, sizeof(send_buf));

        if (strcmp(send_buf, "exit") == 0) {
            cout << "Выход..." << endl;
            break;
        }

        send(sock, send_buf, strlen(send_buf), 0);

        memset(recv_buf, 0, sizeof(recv_buf));
        int n = recv(sock, recv_buf, sizeof(recv_buf) - 1, 0);

        if (n > 0) {
            recv_buf[n] = '\0';
            cout << "Эхо: " << recv_buf << endl;
        } else {
            cerr << "Соединение закрыто сервером" << endl;
            break;
        }

        cout << "Введите сообщение (или 'exit' для выхода): ";
    }

    close(sock);
    return 0;
}
