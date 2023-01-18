#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    run_phone_book();
    return 0;
}

// Driver loop for the phone book
void run_phone_book() {
    char command_buffer[BUFFER_LENGTH];

    printf("Phone Book\n\n");
    printf("Use 'pb help' for usage.\n");

    while (1) {
        printf("\n$ ");
        fgets(command_buffer, sizeof(command_buffer), stdin);

        handle_command(command_buffer);
    }
}

// Calls the appropriate command function depending on the command and flag, and
// passes the parsed command to that function
void handle_command(char command[]) {
    char **parsed_command = parse_command(command);

    // Check if `parsed_command` is NULL
    if (parsed_command == NULL) {
        return;
    }
    // Check if a string exists at the 1st array position
    if (parsed_command[0] == NULL) {
        print_error(PARAMETER_NOT_PASSED, "pb", "");
        return;
    }
    // Check if the first string is 'pb'
    if (strcmp(parsed_command[0], "pb") != 0) {
        print_error(INCORRECT_PARAMETER, "pb", parsed_command[0]);
        return;
    }
    // Check if a string exists at the 2nd array position
    if (parsed_command[1] == NULL) {
        print_error(PARAMETER_NOT_PASSED, "<command_type>", "");
        return;
    }

    // Handle command types
    if (strcmp(parsed_command[1], "display") == 0) {
        // Display all records
        printf("Display all records\n");
    } else if (strcmp(parsed_command[1], "add") == 0) {
        // Add single record
        printf("Add single record\n");
    } else if (strcmp(parsed_command[1], "update") == 0) {
        // Update single record
        printf("Update single record\n");
    } else if (strcmp(parsed_command[1], "delete") == 0) {
        // Delete single record
        printf("Delete single record\n");
    } else if (strcmp(parsed_command[1], "find") == 0) {
        // Find record(s)
        printf("Find record(s)\n");

        // Check if a string exists at the 3rd array position
        if (parsed_command[2] == NULL) {
            print_error(PARAMETER_NOT_PASSED, "-n/-e", "");
            return;
        }

        // Handle flags
        if (strcmp(parsed_command[2], "-n") == 0) {
            // Find record(s) using first name
            printf("Find record(s) using first name\n");
        } else if (strcmp(parsed_command[2], "-e") == 0) {
            // Find single record using e-mail
            printf("Find single record using e-mail\n");
        } else {
            print_error(INCORRECT_PARAMETER, "-n/-e", parsed_command[2]);
        }
    } else if (strcmp(parsed_command[1], "exit") == 0) {
        // Exit program
        printf("Phone book shut down.\n");
        exit(0);
    } else if (strcmp(parsed_command[1], "help") == 0) {
        // Print help
        print_help();
    } else {
        print_error(INCORRECT_PARAMETER, "<command_type>", parsed_command[1]);
    }

    // Free `parsed_command`, as it has now been worked on and is thus not of
    // further use
    free(parsed_command);
}

// Creates a new phone record
struct record *create_record(char **parsed_command) {
    struct record *new_record = NULL;

    if (!are_all_parameters_existing(parsed_command, 2, 4)) {
        return NULL;
    }

    new_record = malloc(sizeof(struct record));

    if (new_record == NULL) {
        print_error(MEMORY_NOT_ALLOCATED, NULL, NULL);
        return NULL;
    }

    new_record->first_name = parsed_command[2];
    new_record->last_name = parsed_command[3];
    new_record->email = parsed_command[4];
    new_record->phone_no = parsed_command[5];

    return new_record;
}

// Splits the command string on whitespaces
char **parse_command(char command[]) {
    char *command_ptr = command;
    char **parsed_command =
        malloc(sizeof(char *) * MAX_NO_OF_PARSED_PARAMETERS);
    char delimiter = ' '; // Whitespace

    // Check if memory was allocated
    if (parsed_command == NULL) {
        print_error(MEMORY_NOT_ALLOCATED, NULL, NULL);
        return NULL;
    }

    for (int i = 0; i < MAX_NO_OF_PARSED_PARAMETERS; i++) {
        char *token = strsep(&command_ptr, &delimiter);

        if (token == NULL) {
            // The command string is completely parsed
            parsed_command[i] =
                NULL; // Making a Character Pointer (char *) null

            if (parsed_command[i - 1] != NULL) {
                // Remove the '\n' from the last non-null token
                token = parsed_command[i - 1];
                parsed_command[i - 1][strlen(token) - 1] = '\0';

                if (strlen(parsed_command[i - 1]) == 0) {
                    // Edge case for inputs like 'find ' (A single Whitespace at
                    // the end of the command string)
                    parsed_command[i - 1] = NULL;
                }
            }
        } else {
            parsed_command[i] = malloc(sizeof(char *) * BUFFER_LENGTH);

            // Check if memory was allocated
            if (parsed_command[i] == NULL) {
                print_error(MEMORY_NOT_ALLOCATED, NULL, NULL);
                free(parsed_command); // Remove previously allocated memory as
                                      // it is now useless

                return NULL;
            }

            parsed_command[i] = token;
        }
    }

    return parsed_command;
}

// Check if the required number of parameters exist in the entire (or a part of
// the) command Minimum `start_index` value is zero
int are_all_parameters_existing(char **parsed_command, int start_index,
                                int expected_parameter_count) {
    int actual_count = 0;

    // Check input values
    if (start_index < 0 || expected_parameter_count < 0) {
        return FALSE;
    }

    for (int i = start_index; i < MAX_NO_OF_PARSED_PARAMETERS; i++) {
        if (parsed_command[i] != NULL) {
            actual_count++;
        }
    }

    if (actual_count == expected_parameter_count) {
        return TRUE;
    } else {
        char expected_parameter_count_buffer[COUNT_BUFFER_LENGTH];
        char actual_count_buffer[COUNT_BUFFER_LENGTH];

        snprintf(expected_parameter_count_buffer, COUNT_BUFFER_LENGTH, "%d",
                 expected_parameter_count);
        snprintf(actual_count_buffer, COUNT_BUFFER_LENGTH, "%d", actual_count);

        print_error(INSUFFICIENT_PARAMETER_COUNT,
                    expected_parameter_count_buffer, actual_count_buffer);

        return FALSE;
    }
}

// Prints error
void print_error(enum error_state err_state, char *expected_string,
                 char *incorrect_string) {
    switch (err_state) {
    case -100:
        printf(
            "Incorrect parameter passed. Expected '%s', but got '%s'. Use 'pb "
            "help' for usage.\n",
            expected_string, incorrect_string);
        break;
    case -101:
        printf(
            "Parameter not passed. Expected '%s', but got '%s'. Use 'pb help' "
            "for usage.\n",
            expected_string, incorrect_string);
        break;
    case -102:
        printf("Memory could not be allocated. Try again.\n");
        break;
    case -103:
        printf(
            "Insufficient number of parameters passed. Expected %s parameters, "
            "but got %s. Use 'pb help' for usage.\n",
            expected_string, incorrect_string);
        break;
    default:
        printf("Error.\n");
        break;
    }
}

// Prints command help
void print_help() {
    printf("Usage: pb [TYPE] [FLAG]... [DATA]...\n");
    printf("Use the phone book to add, update, delete or find records.\n\n");
    printf("Actions:\n");
    printf("- To display all records: pb display\n");
    printf("- To add a record: pb add <first_name> <last_name> <unique_email> "
           "<phone_number>\n");
    printf("- To update a record: pb update <first_name> <last_name> "
           "<email_of_record_to_update> <phone_number>\n");
    printf("- To delete a record: pb delete <email_of_record_to_delete>\n");
    printf("- To find record(s) using a first name: pb find -n "
           "<first_name_of_records_to_find>\n");
    printf("- To find a record using an e-mail: pb find -e "
           "<email_of_record_to_find>\n");
    printf("- To exit: pb exit\n");
    printf("- To display command help: pb help\n");
    printf("\nEg: pb add selena gomez sg@selenagomez.com +1(xxx)xxx-xxxx\n");
}
