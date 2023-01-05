#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_LENGTH 100
#define MAX_NO_OF_PARSED_PARAMETERS 6

// Function declarations
void runPhoneBook();
void handleCommand(char command_buffer[]);
char **parseCommand(char command[]);
void printHelp();

int main() {
    runPhoneBook();
    
    return 0;
}

// Driver loop for the phone book
void runPhoneBook() {
    char command_buffer[BUFFER_LENGTH];

    printf("Phone Book\n\n");
    printf("Use 'pb help' for usage.\n");

    while(1) {
        int choice = 0;

        printf("\n$ ");
        fgets(command_buffer, sizeof(command_buffer), stdin);

        handleCommand(command_buffer);
    }
}

// Calls the appropriate command function depending on the command and flag, and passes the parsed command to that function
void handleCommand(char command[]) {
    char **parsedCommand = parseCommand(command);

    // Check if a string exists at the 1st array position
    if(parsedCommand[0] == NULL) {
        printf("Use 'pb help' for usage.\n");
        return;
    }
    // Check if the first string is 'pb'
    if(strcmp(parsedCommand[0], "pb") != 0) {
        printf("Command should start with 'pb'. Use 'pb help' for usage.\n");
        return;
    }
    // Check if a string exists at the 2nd array position
    if(parsedCommand[1] == NULL) {
        printf("Command type/option not passed. Use 'pb help' for usage.\n");
        return;
    }

    // Handle command types
    if(strcmp(parsedCommand[1], "display") == 0) { // Display all records
        printf("Display all records\n");
    }
    else if(strcmp(parsedCommand[1], "add") == 0) { // Add single record
        printf("Add single record\n");
    }
    else if(strcmp(parsedCommand[1], "update") == 0) { // Update single record
        printf("Update single record\n");
    }
    else if(strcmp(parsedCommand[1], "delete") == 0) { // Delete single record
        printf("Delete single record\n");
    }
    else if(strcmp(parsedCommand[1], "find") == 0) { // Find record(s)
        printf("Find record(s)\n");

        // Check if a string exists at the 3rd array position
        if(parsedCommand[2] == NULL) {
            printf("Flag to 'find' command not passed. Use 'pb help' for usage.\n");
            return;
        }

        // Handle flags
        if(strcmp(parsedCommand[2], "-n") == 0) { // Find record(s) using first name
        printf("Find record(s) using first name\n");
        }
        else if(strcmp(parsedCommand[2], "-e") == 0) { // Find single record using e-mail
            printf("Find single record using e-mail\n");
        }
        else {
            printf("Incorrect flag to 'find' command. Use 'pb help' for usage.\n");
        }
    }
    else if(strcmp(parsedCommand[1], "exit") == 0) { // Exit program
        printf("Phone book shut down.\n");
        exit(0);
    }
    else if(strcmp(parsedCommand[1], "help") == 0) { // Print help
        printHelp();
    }
    else {
        printf("Incorrect command type. Use 'pb help' for usage.\n");
    }
}

// Splits the command string on whitespaces
char **parseCommand(char command[]) {
    char *command_ptr = command;
    char **parsedCommand = malloc(sizeof(char *) * MAX_NO_OF_PARSED_PARAMETERS);
    char delimiter = ' ';

    for (int i = 0; i < MAX_NO_OF_PARSED_PARAMETERS; i++) {
        char *token = strsep(&command_ptr, &delimiter);

        if (token == NULL) { // The command string is completely parsed
            parsedCommand[i] = NULL; // Making a Character Pointer (char *) null
            
            if(parsedCommand[i - 1] != NULL) {
                // Remove the '\n' from the last non-null token
                token = parsedCommand[i - 1];
                parsedCommand[i - 1][strlen(token) - 1] = '\0';
                
                if(strlen(parsedCommand[i - 1]) == 0) {
                    // Edge case for inputs like 'find ' (whitespace at end)
                    parsedCommand[i - 1] = NULL;
                }
            }
        }
        else {
            parsedCommand[i] = malloc(sizeof(char *) * BUFFER_LENGTH);
            parsedCommand[i] = token;
        }
    }

    return parsedCommand;
}

// Prints command help
void printHelp() {
    printf("Usage: pb [TYPE] [FLAG]... [DATA]...\n");
    printf("Use the phone book to add, update, delete or find records.\n\n");
    printf("Actions:\n");
    printf("- To display all records: pb display\n");
    printf("- To add a record: pb add <first_name> <last_name> <unique_email> <phone_number>\n");
    printf("- To update a record: pb update <first_name> <last_name> <email_of_record_to_update> <phone_number>\n");
    printf("- To delete a record: pb delete <email_of_record_to_delete>\n");
    printf("- To find record(s) using a first name: pb find -n <first_name_of_records_to_find>\n");
    printf("- To find a record using an e-mail: pb find -e <email_of_record_to_find>\n");
    printf("- To exit: pb exit\n");
    printf("- To display command help: pb help\n");
    printf("\nEg: pb add selena gomez sg@selenagomez.com +1(xxx)xxx-xxxx\n");
}
