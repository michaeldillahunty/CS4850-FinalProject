#include "../include/client.h"
#include "../include/client.h"
#include <sys/socket.h> // https://pubs.opengroup.org/onlinepubs/7908799/xns/syssocket.h.html
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>      // https://www.ibm.com/docs/en/aix/7.2?topic=files-fcntlh-file

#include <string.h>
#define UNUSED(x) (void)(x)

/** References:
   - https://handsonnetworkprogramming.com/articles/differences-windows-winsock-linux-unix-bsd-sockets-compatibility/
   - https://www.programiz.com/c-programming/library-function/string.h/strcat
   - https://man7.org/linux/man-pages/man2/send.2.html
*/

int login(int socket, char*input){
   // param check
   if (socket > 0 && input != NULL && strlen(input) > 0){
      char buffer[MAX_LINE];
      strcpy(buffer, input);
      strtok(buffer, " \n"); // get the login command

      char*user_id = strtok(NULL, " \n"); // will continue tokenizing the previously used string (get the second input which should be username)
      // if (strlen(user_id) < 3 || strlen(user_id) > 32){ // if username is too long or too short
      //    return -2; 
      // }

      char*password = strtok(NULL, " \n"); // 3rd element should be the password
      // if (strlen(password) < 4 || strlen(password) > 8){ // if password is too long or too short
      //    return -3;
      // }

      if (!user_id || !password){ // if an argument is missing
         return -4; 
      }  
      
      return send(socket, input, sizeof(buffer), 0);
   }
   return -1;
}


int create_newuser(int socket, char*input){
   // double checking the parameters being passed exist

   if (socket > 0 && input != NULL && strlen(input) > 0) { 
      char buffer[MAX_SIZE];
      strcpy(buffer, input);
      strtok(buffer, " \n"); // pull command token out
      char*new_uid = strtok(NULL, " \n"); // get second input (username)
      char*new_pwd = strtok(NULL, " \n"); // get third input (password)
      
      if (strlen(new_uid) < 3 || strlen(new_uid) > 32){ // invalid username length
         return -2; 
      }

      if (strlen(new_pwd) < 4 || strlen(new_pwd) > 8){ // invalid password length
         return -3; 
      }

      if (!new_uid || !new_pwd){ // if either are empty / recieved no input
         return -4;
      }

      printf("input: %s\n", input);
      return send(socket, input, sizeof(buffer), 0);

   }
   return -1; // invalid params
}

int send_message(int socket, char*message){
   UNUSED(socket);
   UNUSED(message);
   return -1;
}

int logout(int socket){
   UNUSED(socket);
   return -1;
}

