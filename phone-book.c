#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "declarations.h"

#define BUFFER_LENGTH 100
#define MAX_NO_OF_PARSED_PARAMETERS 6

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
        printf("\n$ ");
        fgets(command_buffer, sizeof(command_buffer), stdin);

        handleCommand(command_buffer);
    }
}

// Calls the appropriate command function depending on the command and flag, and passes the parsed command to that function
void handleCommand(char command[]) {
    char **parsed_command = parseCommand(command);

    // Check if `parsed_command` is NULL
    if(parsed_command == NULL) {
        return;
    }
    // Check if a string exists at the 1st array position
    if(parsed_command[0] == NULL) {
        printError(PARAMETER_NOT_PASSED, "pb", "");
        return;
    }
    // Check if the first string is 'pb'
    if(strcmp(parsed_command[0], "pb") != 0) {
        printError(INCORRECT_PARAMETER, "pb", parsed_command[0]);
        return;
    }
    // Check if a string exists at the 2nd array position
    if(parsed_command[1] == NULL) {
        printError(PARAMETER_NOT_PASSED, "<command_type>", "");
        return;
    }

    // Handle command types
    if(strcmp(parsed_command[1], "display") == 0) { // Display all records
        printf("Display all records\n");
    }
    else if(strcmp(parsed_command[1], "add") == 0) { // Add single record
        printf("Add single record\n");
    }
    else if(strcmp(parsed_command[1], "update") == 0) { // Update single record
        printf("Update single record\n");
    }
    else if(strcmp(parsed_command[1], "delete") == 0) { // Delete single record
        printf("Delete single record\n");
    }
    else if(strcmp(parsed_command[1], "find") == 0) { // Find record(s)
        printf("Find record(s)\n");

        // Check if a string exists at the 3rd array position
        if(parsed_command[2] == NULL) {
            printError(PARAMETER_NOT_PASSED, "-n/-e", "");
            return;
        }

        // Handle flags
        if(strcmp(parsed_command[2], "-n") == 0) { // Find record(s) using first name
            printf("Find record(s) using first name\n");
        }
        else if(strcmp(parsed_command[2], "-e") == 0) { // Find single record using e-mail
            printf("Find single record using e-mail\n");
        }
        else {
            printError(INCORRECT_PARAMETER, "-n/-e", parsed_command[2]);
        }
    }
    else if(strcmp(parsed_command[1], "exit") == 0) { // Exit program
        printf("Phone book shut down.\n");
        exit(0);
    }
    else if(strcmp(parsed_command[1], "help") == 0) { // Print help
        printHelp();
    }
    else {
        printError(INCORRECT_PARAMETER, "<command_type>", parsed_command[1]);
    }

    // Free `parsed_command`, as it has now been worked on and is thus not of further use
    free(parsed_command);
}

// Splits the command string on whitespaces
char **parseCommand(char command[]) {
    char *command_ptr = command;
    char **parsed_command = malloc(sizeof(char *) * MAX_NO_OF_PARSED_PARAMETERS);
    char delimiter = ' '; // Whitespace

    // Check if memory was allocated
    if (parsed_command == NULL) {
        printError(MEMORY_NOT_ALLOCATED, NULL, NULL);
        return NULL;
    }

    for (int i = 0; i < MAX_NO_OF_PARSED_PARAMETERS; i++) {
        char *token = strsep(&command_ptr, &delimiter);

        if (token == NULL) { // The command string is completely parsed
            parsed_command[i] = NULL; // Making a Character Pointer (char *) null
            
            if(parsed_command[i - 1] != NULL) {
                // Remove the '\n' from the last non-null token
                token = parsed_command[i - 1];
                parsed_command[i - 1][strlen(token) - 1] = '\0';
                
                if(strlen(parsed_command[i - 1]) == 0) {
                    // Edge case for inputs like 'find ' (A single Whitespace at the end of the command string)
                    parsed_command[i - 1] = NULL;
                }
            }
        }
        else {
            parsed_command[i] = malloc(sizeof(char *) * BUFFER_LENGTH);

            // Check if memory was allocated
            if (parsed_command[i] == NULL) {
                printError(MEMORY_NOT_ALLOCATED, NULL, NULL);
                free(parsed_command); // Remove previously allocated memory as it is now useless

                return NULL;
            }

            parsed_command[i] = token;
        }
    }

    return parsed_command;
}

// Prints error
void printError(enum error_state err_state, char *expected_string, char *incorrect_string) {
    switch (err_state) {
        case -100:
            printf("Incorrect parameter passed. Expected '%s', but got '%s'. Use 'pb help' for usage.\n", expected_string, incorrect_string);
            break;
        case -101:
            printf("Parameter not passed. Expected '%s', but got '%s'. Use 'pb help' for usage.\n", expected_string, incorrect_string);
            break;
        case -102:
            printf("Memory could not be allocated. Try again.\n");
            break;
        default:
            printf("Error.\n");
            break;
    }
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
