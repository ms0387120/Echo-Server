#include <stdio.h>
#include <stdlib.h>
#include <string.h>     /* provide functions about string, ex: `bzero()`, `strlen()`*/
#include <sys/types.h>  /* contains a number of basic derived types */
#include <sys/socket.h> /* provide functions and data structures of socket */
#include <arpa/inet.h>  /* convert internet address and dotted-decimal notation */
#include <netinet/in.h> /* provide constants and structures needed for internet domain addresses*/
#include <unistd.h>     /* `read()` and `write()` functions */
#include <time.h>       /* provide functions about time */

#define PORT 8888
#define MAX_SIZE 2048
#define MAX_CONNECTION 5


int main() {

  char str[100];
  int svr_fd;                   // socket file descriptor, return by `socket()`
  struct sockaddr_in svr_addr;  // address of server, used by `bind()`

  int cli_fd;                   // descriptor of incomming client, return by `accept()`
  struct sockaddr_in cli_addr;  // address of client, used by `accept()`
  socklen_t addr_len;           // size of address, used by `accept()`

  time_t ticks;                 // store current time
  int write_bytes;              // number of byte, return by `write()`
  char buf[MAX_SIZE];           // buffer to store msg


  /* 1) Create the socket, use `socket()`
        AF_INET: IPv4
        SOCK_STREAM: Stream Socket (TCP)
  */
  svr_fd = socket(AF_INET, SOCK_STREAM, 0);

  /* 2) Bind the socket to port, with prepared sockaddr_in structure */
  bzero(&svr_addr, sizeof(svr_addr));
  svr_addr.sin_family = AF_INET;
  svr_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  svr_addr.sin_port = htons(PORT);

  bind(svr_fd, (struct sockaddr*)&svr_addr , sizeof(svr_addr));
  listen(svr_fd, MAX_CONNECTION);
  cli_fd = accept(svr_fd, (struct sockaddr*) NULL, NULL);

  while(1) {
    bzero(str, 100);
    read(cli_fd,str,100); 
    printf("%s",str);
    write(cli_fd, str, strlen(str)+1);
  }

}
