#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdbool.h>

static void die(const char *msg) {
    int err = errno;
    fprintf(stderr,"%s\n",msg);

}
static void die(const char *msg){
    int err = errno;
    fprintf(stderr,"[%d]%s\n",err,msg);
    abort();
}



static void do_something(int connfd) {
    char rbuf[64] = {};
    ssize_t n = read(connfd, rbuf, sizeof(rbuf) - 1);
    if (n < 0) {
        die("read() error");
        return;
    }
    printf("Client says: %s\n", rbuf);

    char wbuf[] = "world";
    write(connfd, wbuf, strlen(wbuf));
}

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        die("socket()");
    }

    // Reuse address if it's still in TIME_WAIT state
    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(1234);  // Use htons for port number conversion
    addr.sin_addr.s_addr = ntohl(INADDR_ANY);  // Bind to all available interfaces

    int rv = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (rv < 0) {
        die("bind()");
    }

    rv = listen(fd, SOMAXCONN);
    if (rv < 0) {
        die("listen()");
    }

    while (true) {
        //accept
        struct sockaddr_in client_addr = {};
        socklen_t addrlen = sizeof(client_addr);
        int connfd = accept(fd, (struct sockaddr *)&client_addr, &addrlen);
        if (connfd < 0) {
            continue;
        }

        do_something(connfd);

        close(connfd);
    }

    return 0;
}
    