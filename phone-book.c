#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_LENGTH 100
#define MAX_NO_OF_PARSED_PARAMETERS 5

// Function declarations
void runPhoneBook();
void handleCommand(char command_buffer[]);
char **parseCommand(char command[]);
void printInstructions();

int main() {
    runPhoneBook();
    
    return 0;
}

// Driver loop for the phone book
void runPhoneBook() {
    char command_buffer[BUFFER_LENGTH];

    printf("----------------------\n");
    printf("\nPhone Book\n\n");
    printf("----------------------\n");

    while(1) {
        int choice = 0;

        printInstructions();

        printf("\nPlease enter choice: ");
        fgets(command_buffer, sizeof(command_buffer), stdin);
        printf("\n");

        handleCommand(command_buffer);

        printf("\n----------------------\n");
    }
}

// Calls the appropriate command function depending on the command and flag, and passes the parsed command to that function
void handleCommand(char command[]) {
    char **parsedCommand = parseCommand(command);

    if(strcmp(parsedCommand[0], "display") == 0) { // Display all records
        printf("\nDisplay all records\n");
    }
    else if(strcmp(parsedCommand[0], "add") == 0) { // Add single record
        printf("\nAdd single record\n");
    }
    else if(strcmp(parsedCommand[0], "update") == 0) { // Update single record
        printf("\nUpdate single record\n");
    }
    else if(strcmp(parsedCommand[0], "delete") == 0) { // Delete single record
        printf("\nDelete single record\n");
    }
    else if(strcmp(parsedCommand[0], "find") == 0) { // Find record(s)
        printf("\nFind record(s)\n");

        if(strcmp(parsedCommand[1], "-n") == 0) { // Find record(s) using first name
            printf("\nFind record(s) using first name\n");
        }
        else if(strcmp(parsedCommand[1], "-e") == 0) { // Find single record using e-mail
            printf("\nFind single record using e-mail\n");
        }
        else {
            printf("\nIncorrect flag to 'find' command. Please try again.\n");
        }
    }
    else if(strcmp(parsedCommand[0], "exit") == 0) { // Exit program
        printf("\nBye!\n");
        exit(0);
    }
    else {
        printf("\nIncorrect command. Please try again.\n");
    }
}

// Splits the command string on whitespaces
char **parseCommand(char command[]) {
    char *command_ptr = command;
    char **parsedCommand = malloc(sizeof(char *) * MAX_NO_OF_PARSED_PARAMETERS);
    char delimiter = ' ';
    char *token = NULL;
    int position = 0;

    while(1) {
        token = strsep(&command_ptr, &delimiter);

        if (token == NULL) { // The command string is completely parsed
            // Remove the '\n' from the last token
            position--;
            token = parsedCommand[position];
            parsedCommand[position][strlen(token) - 1] = '\0';

            // Break the loop as the command string is completely parsed
            break;
        }

        parsedCommand[position] = malloc(sizeof(char *) * BUFFER_LENGTH);
        parsedCommand[position] = token;

        position++;
    }

    return parsedCommand;
}

// Prints user instructions
void printInstructions() {
    printf("\nInstructions:\n");
    printf("- To display all records: display\n");
    printf("- To add a record: add <first_name> <last_name> <unique_email> <phone_number>\n");
    printf("- To update a record: update <first_name> <last_name> <email_of_record_to_update> <phone_number>\n");
    printf("- To delete a record: delete <email_of_record_to_delete>\n");
    printf("- To find record(s) using a first name: find -n <first_name_of_records_to_find>\n");
    printf("- To find a record using an e-mail: find -e <email_of_record_to_find>\n");
    printf("- To exit: exit\n");
    printf("\nEg: add selena gomez sg@selenagomez.com +1(xxx)xxx-xxxx\n");
}
