#include "../include/client.h"
#include <string.h>

#include <sys/socket.h> // https://pubs.opengroup.org/onlinepubs/7908799/xns/syssocket.h.html
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>      // https://www.ibm.com/docs/en/aix/7.2?topic=files-fcntlh-file


/** References:
- https://handsonnetworkprogramming.com/articles/differences-windows-winsock-linux-unix-bsd-sockets-compatibility/


*/

int login_request(int socket, char*userID, char*password){

   return -1;
}

int create_newuser(int socket, char*new_userID, char*new_user_pass){

   return -1;
}

int send_message(int socket, char*message){

   return -1;
}

int logout_request(int socket){
   
   return -1;
}