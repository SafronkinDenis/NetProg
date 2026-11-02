#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

int main() {
    const char* server_ip = "172.16.40.1";
    int port = 13; //standart

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        cerr << "Ошибка создания сокета" << endl;
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    char send_buf[1] = {0};
    sendto(sock, send_buf, 1, 0,
           (struct sockaddr*)&server_addr, sizeof(server_addr));

    char recv_buf[256];
    memset(recv_buf, 0, sizeof(recv_buf));

    struct sockaddr_in from_addr;
    socklen_t from_len = sizeof(from_addr);

    int n = recvfrom(sock, recv_buf, sizeof(recv_buf) - 1, 0,
                     (struct sockaddr*)&from_addr, &from_len);

    if (n > 0) {
        recv_buf[n] = '\0';
        cout << "Получено от daytime сервера: " << recv_buf << endl;
    } else {
        cerr << "Ошибка получения данных или таймаут" << endl;
    }

    close(sock);
    return 0;
}
