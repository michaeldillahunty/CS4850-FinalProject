#include "../include/client.h"

/** References: 
   - https://man7.org/linux/man-pages/man3/inet_pton.3.html


*/


// int main(int argc, char*argv[]){
int main(){
   printf("-------- Chatroom V1 --------\n");
   
   // char*input_addr;

   int client_sock_fd; ; // creating a socket
   if ((client_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){ // error check socket initialization
      printf("ERROR: failed to create socket\n");
      return -1; 
   }

   // setting socket address struct fields
   /// https://www.binarytides.com/socket-programming-c-linux-tutorial/
   struct sockaddr_in server_addrs;
   server_addrs.sin_family = AF_INET;
   server_addrs.sin_port = htons(SERVER_PORT);
   server_addrs.sin_addr.s_addr = INADDR_ANY;

   // if(inet_pton(AF_INET, input_addr, &server_addrs.sin_addr) <= 0 ){
   //    printf("ERROR: invalid server address\n");
   //    return -1; 
   // }

   // joining chat room
   if (connect(client_sock_fd, (struct sockaddr*)&server_addrs, sizeof(server_addrs)) == -1){
      printf("ERROR: failed to connect client to socket\n");
      return -1; 
   }
   char temp_arr[MAX_LINE];
   char message_arr[MAX_LINE];
   if (recv(client_sock_fd, message_arr, sizeof(message_arr), 0) <= 0){
      printf("ERROR: failed to recieve initial message from socket\n");
      return -1;
   }
   printf("Message Arr: %s\n", &message_arr[0]);
   printf("[Server Message] >> %s\n", message_arr);
   
   while (1){  
      
      printf("> ");
      
      // read user input from stdin and store in message_arr
      // fgets(message_arr, MAX_LINE, stdin);

      if (fgets(temp_arr, MAX_LINE, stdin) == NULL){
         printf("[ERROR] Failed to get user input\n");
         return -1; 
      }
      strcpy(message_arr, temp_arr);
      printf("MA : %s", message_arr);
      printf("temp: %s", temp_arr);
      // printf("AFTER SEG FAULT\n");
      char*tokens[sizeof(message_arr)];
      char*delim_command = strtok(message_arr, " \n");
      int i = 0;
      while (delim_command != NULL){
         tokens[i++] = delim_command;
         delim_command = strtok(NULL, " \n");
      }

      for (int k = 0; k < 3; k++){
         printf("tokens[%d]: %s\n", k, tokens[k]);
      }
      
      if (strcmp(tokens[0], "login") == 0){ // 1st element in inputs array should be the command
         printf("Login Message Arr: %s\n", message_arr);
         /* 
            <login> [username] [password]
         */
      /*
         char*user_id = strtok(NULL, " \n");
         char*user_id = strtok(NULL, " \n"); // will continue tokenizing the previously used string (get the second input which should be username)
         if (strlen(user_id) < 3 || strlen(user_id) > 32){
            printf("Failed to login [UserID should be between 3 and 32 characters]\n");
         }
         // char*password = strtok(NULL, " \n");
         char*password = strtok(NULL, " \n"); // 3rd element should be the password
         if (strlen(password) < 4 || strlen(password) > 8){
            printf("Failed to login [Password should be between 4 and 8 characters]\n");
         }
         if (!user_id || !password){
            printf("  Invalid command - Try again\nin format <command> [userid] [password]\n");
         }  
      */
         int client_login = login(client_sock_fd, message_arr);
         if (client_login == -2){ // invalid user_id
            printf("Failed to login [UserID should be between 3 and 32 characters]\n");
         } else if (client_login == -3) {
            printf("Failed to login [Password should be between 4 and 8 characters]\n");
         } else if (client_login == -4) {
            printf("Invalid command - Try again\nin format <command> [userid] [password]\n");
         } else if (client_login == -1) {
            printf("Failed to send login request - Exiting\n");
            return -1; 
         }
      
      } else if (strcmp(tokens[0], "newuser") == 0) {
         /* 
            <newuser> [username] [password]
         */
         printf("Newuser Message Arr: %s\n", message_arr);
         int client_newuser = create_newuser(client_sock_fd, temp_arr);
         // printf("client return: %d\n", client_newuser);
         if (client_newuser == -2){
            printf("[ERROR] Failed to create newuser [UserID should be between 3 and 32 characters]\n");
            continue;
         } else if (client_newuser == -3) {
            printf("[ERROR] Failed to create newuser [Password should be between 4 and 8 characters\n");
            continue;
         } else if (client_newuser == -4) {
            printf("[ERROR] Invalid command (try again: in format <newuser> [userid] [password])\n");
            continue; 
         } else if (client_newuser == -1) {
            printf("[ERROR] Failed to send newuser request - Exiting\n");
         }

      } else if (strcmp(delim_command, "message") == 0) {
         /*
            <message> "message to send"
         */   
      } else if (strcmp(delim_command, "logout") == 0) {
         /*
            <logout>
         */   

      }
   } 

   return 0; 
}