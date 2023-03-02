#include "../include/server.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define UNUSED(x) (void)(x)
/** References: 
   

*/


int recieve_login(int socket, char*user_id, char*password){
   // UNUSED(socket);
   // UNUSED(user_id);
   // UNUSED(password);
   if (socket && user_id && password){
      
   }
   return -1; 
}

int recieve_newuser(int socket, char*newuser_id, char*new_passwd){
   // UNUSED(socket);
   // UNUSED(newuser_id);
   // UNUSED(new_passwd);
   if (!socket || !newuser_id || !new_passwd){
      return -1; 
   }
   
   if (strlen(newuser_id) < 3 || strlen(newuser_id) > 32){ // verify valid userid length
      return -2; 
   } 
   if (strlen(new_passwd) < 4 || strlen(new_passwd) > 8){ // verify valid password length
      return -3;
   }
   
   int add_newuser = add_user(newuser_id, new_passwd);
   if (add_newuser == 1){ // if the requested newuser ID already exists 
      return 1;
   } else if (add_newuser < 0) {
      return -1; 
   }
   return 0; // if successfully created new user
}

bool compare_users(char*uid){
   FILE*fp = fopen("users.txt", "r");
   if (fp == NULL){
      return NULL;
   }
   char users_arr[32];
   while (fscanf(fp, "(%[^,], %*s\n", users_arr) == 1){
      int is_match = strcmp(users_arr, uid);
      if (is_match == 0) { // if the given user matches one already in the file
         fclose(fp);
         return true; // given user already exists
      }
   }
   fclose(fp); 
   return false;  // if no userid's were found that match the given userid
}

int add_user(char*uid, char*passwd){
   FILE*fp = fopen("users.txt", "r+");
   if (!fp){   // if failed to open file
      return -1; 
   }

   if (compare_users(uid) == false){ // if the user already exists
      return 1;
   } 

   int new_user = fprintf(fp, "(%s, %s)", uid, passwd);
   if (new_user > 0){ 
      fclose(fp);
      return 0; // succesfully added new user to users.txt 
   }
   return -1; 
}

int recieve_message(int socket, char*message){
   UNUSED(socket);
   UNUSED(message);
   return -1;
}

int recieve_logout(int socket){
   UNUSED(socket);
   return -1;
}

// int get_user_id(Users*user_id){
   

// }