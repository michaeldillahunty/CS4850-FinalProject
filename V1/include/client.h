#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SERVER_PORT 14725 // last 1 + last 4 digits of student ID
#define MAX_LINE 256

/*
 * Required Functions 
 */

/** Send request, using user information, to join the chat room 
   \return < 0 on error, >= 0 on success
*/
int login_request(int socket, char*userID, char*password); 

/** Send request to server to create new user account
   \return < 0 on error, >= 0 on success
*/
int create_newuser(int socket, char*new_userID, char*new_user_pass);

/** Send a message to server
   \return < 0 on error, >= 0 on success
*/
int send_message(int socket, char*message);


/** Quit the chatroom 
   \return < 0 on error, >= 0 on success
*/
int logout_request(int socket);