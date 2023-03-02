#ifndef SERVER_H
#define SERVER_H

#define MAX_PENDING 5

// last 1 + last 4 digits of student ID
#define SERVER_PORT 14725 

#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

typedef struct user_data{
   bool user_exists;
   char uid[32]; 
   // char password[10]; // don't need a password field since there can be matching passwords
} Users;

/** Handles the login request recieved from client 
   \return < 0 on error, >= 0 on success
*/
int recieve_login(int socket, char*user_id, char*password);

/** Handles the new user request recieved from client
   \return < 0 on error, >= 0 on success
*/
int recieve_newuser(int socket, char*newuser_id, char*new_passwd);

/** Handles the message recieved from client and sends to other client
   \return < 0 on error, >= 0 on success
*/
int recieve_message(int socket, char*message);

/** Handles the logout request recieved from client
   \return < 0 on error, >= 0 on success
*/
int recieve_logout(int socket);

bool compare_users(char*uid);
int add_user(char*uid, char*passwd);


#endif