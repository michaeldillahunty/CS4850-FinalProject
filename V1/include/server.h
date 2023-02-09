#define SERVER_PORT 14725 // last 1 + last 4 digits of student ID
#define MAX_PENDING 5
#define MAX_LINE 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Handles the login request recieved from client 
   \return < 0 on error, >= 0 on success
*/
int handle_login(int socket, char*userID, char*password);

/** Handles the new user request recieved from client
   \return < 0 on error, >= 0 on success
*/
int handle_newuser(int socket, char*new_userID, char*new_password);

/** Handles the message recieved from client and sends to other client
   \return < 0 on error, >= 0 on success
*/
int handle_message(int socket, char*message);

/** Handles the logout request recieved from client
   \return < 0 on error, >= 0 on success
*/
int handle_logout_request(int socket);