#include "../include/server.h"
#include "../include/user.h"
#include <stdbool.h>

#define MAX_PENDING 5

/** Notes 
 * Login: 
 * - Verify userid and password -> if not decline and send error message to client
 *    - send confirmation to client 
 * 
 * newuser: 
 * - UserID and password need to be case-sensitive 
 *    - reject request if userID already exists 
 * - Store userid and passwords in .txt file (on server side)
 * 
 * send:
 * - precede message from client with userID -> send back to client 
 *    - message size <= 256 chars
 * 
 * logout:
 * - close connection between client
 *    -> STAY RUNNING to allow for other clients to connect
 * 
 */
int main(){
   int server_sock_fd ;
   if ((server_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
      printf("Failed to create socket\n");
      return -1;
   }

   struct sockaddr_in server_addrs;
   server_addrs.sin_family = AF_INET;
   server_addrs.sin_port = htons(SERVER_PORT);
   server_addrs.sin_addr.s_addr = INADDR_ANY;
   
   if (bind(server_sock_fd, (struct sockaddr*)&server_addrs, sizeof(server_addrs)) < 0){ // bind the server address to the specified port
      printf("ERROR: failed to bind server address to socket\n");
      return -1; 
   }

   if (listen(server_sock_fd, MAX_PENDING) < 0){
      printf("ERROR: listening for socket connections\n");
      return -1; 
   }

/* while 1 */
   while(1){
      printf("--- SERVER Port #: %d\n", SERVER_PORT);
      int client_sock_fd;
      if ((client_sock_fd = accept(server_sock_fd, (struct sockaddr*)&server_addrs, (socklen_t*)&server_addrs)) > 0){
         printf("--- Successfully connected to client! ---\n");
         bool logged_in = false; 
         User*user = (User*)calloc(1, sizeof(User));
         if (!user){
            printf("[ERROR] connecting user\n");
            return -1;
         }
         logged_in = false;
         char*test_msg = "Successfully connected to server";
         if (send(client_sock_fd, test_msg, MAX_LINE, 0) < 0){
            printf("[ERROR]: Could not send welcome message\n");
            return -1; 
         }
         
         char init_msg[MAX_LINE]; // array to store the entire message string
         char message_buff[MAX_LINE]; // array that will be altered

/* while 2 */
         while(1){
            ssize_t recieved; 
            if ((recieved = recv(client_sock_fd, init_msg, sizeof(message_buff), 0)) <= 0){ // recieve message from client socket 
               printf("recieved: %zu\n", recieved);
               printf("[ERROR]: Failed to retrieve message\n");
               return -1;
            }
            printf("init:msg = %s\n", &init_msg[1]);
            strcpy(message_buff, init_msg);
            printf("> [from %s]: %s\n", user->uid, message_buff);

            char*tokens[sizeof(message_buff)];
            char*p = strtok(message_buff, " \n");
            int i = 0;
            // loop message buffer, tokenizing each word in the input with a delimiter
            // storing each token in a tokens arr
            while (p != NULL){ 
               tokens[i++] = p;
               p = strtok(NULL, " \n");
            }

            if (strcmp(tokens[0], "login") == 0) {
               int server_login = recieve_login(server_sock_fd, tokens[1], tokens[2]);
               if (server_login == -1){
                  printf("[ERROR] Invalid command usage\n");
               } else if (server_login == 0 && logged_in == false) {
                  printf("Successfully logged user %s in\n", tokens[1]);
                  logged_in = true;
               }
               
            } else if (strcmp(tokens[0], "newuser") == 0) { // if newuser command is found
               int server_newuser = recieve_newuser(server_sock_fd, tokens[1], tokens[2]); // call function to create new user
               if (server_newuser == -1){
                  printf("[ERROR] Invalid command usage\n");
               } else if (server_newuser == -2) {
                  printf("[ERROR] Invalid userid length: should be between 3 and 32 characters\n");
                  return server_newuser;
               } else if (server_newuser == -3) {
                  printf("[ERROR] Invalid password length: should be between 4 and 8 characters\n");
                  return server_newuser;
               }
            } else if (strcmp(tokens[0], "message") == 0) {
               
            } else if (strcmp(tokens[0], "logout") == 0) {

            }
         }

      printf("!! Failed accepting client connection\n");
      return -1;
      }

   } // end of while(1)
   return 0; 
}