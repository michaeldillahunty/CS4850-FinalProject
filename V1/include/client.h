#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 14725 // last 1 + last 4 digits of student ID
#define MAX_SIZE 256

/*
 * Required Functions 
 */

/** Send request, using user information, to join the chat room 
   \return < 0 on error, >= 0 on success
*/
int login(int socket, char*input); 

/** Send request to server to create new user account
   \return < 0 on error, >= 0 on success
*/
int create_newuser(int socket, char*input);

/** Send a message to server
   \return < 0 on error, >= 0 on success
*/
int send_message(int socket, char*message);


/** Quit the chatroom 
   \return < 0 on error, >= 0 on success
*/
int logout(int socket);

