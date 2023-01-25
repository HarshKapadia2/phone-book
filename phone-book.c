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
        print_error(COMMAND_PARAMETER_NOT_PASSED, "pb", "");
        return;
    }
    // Check if the first string is 'pb'
    if (strcmp(parsed_command[0], "pb") != 0) {
        print_error(INCORRECT_COMMAND_PARAMETER, "pb", parsed_command[0]);
        return;
    }
    // Check if a string exists at the 2nd array position
    if (parsed_command[1] == NULL) {
        print_error(COMMAND_PARAMETER_NOT_PASSED, "<command_type>", "");
        return;
    }

    // Handle command types
    if (strcmp(parsed_command[1], "display") == 0) {
        // Display all records
        printf("Display all records\n");
    } else if (strcmp(parsed_command[1], "add") == 0) {
        add_record(parsed_command); // Add single record
    } else if (strcmp(parsed_command[1], "update") == 0) {
        // Update single record
        printf("Update single record\n");
    } else if (strcmp(parsed_command[1], "delete") == 0) {
        // Delete single record
        printf("Delete single record\n");
    } else if (strcmp(parsed_command[1], "find") == 0) {
        find_records(parsed_command); // Find record(s)
    } else if (strcmp(parsed_command[1], "exit") == 0) {
        // Exit program
        printf("Phone book shut down.\n");
        exit(0);
    } else if (strcmp(parsed_command[1], "help") == 0) {
        print_help(); // Print help
    } else {
        print_error(INCORRECT_COMMAND_PARAMETER, "<command_type>",
                    parsed_command[1]);
    }

    // Free `parsed_command`, as it has now been worked on and is thus not of
    // further use
    free(parsed_command);
}

// Handles creating and adding phone record to file
int add_record(char **parsed_command) {
    struct record *new_record = create_record(parsed_command);

    if (new_record == NULL) {
        print_error(RECORD_ADDITION_ERROR, NULL, NULL);
        return FALSE;
    }

    // Check if e-mail is unique
    if (is_record_existing(new_record->email)) {
        print_error(RECORD_ADDITION_ERROR, NULL, NULL);
        return FALSE;
    }

    // Write record to file
    int is_record_saved = save_record_to_file(new_record);

    if (is_record_saved) {
        printf("Record added to phone book.\n");
        free(new_record); // Free the record structure memory
        return TRUE;
    } else {
        print_error(RECORD_ADDITION_ERROR, NULL, NULL);
        free(new_record); // Free the record structure memory
        return FALSE;
    }
}

// Displays one record based on `email` or multiple records based on
// `first_name` (if present)
int find_records(char **parsed_command) {
    // Check if a string exists at the 3rd array position
    if (parsed_command[2] == NULL) {
        print_error(COMMAND_PARAMETER_NOT_PASSED, "-n/-e", "");
        return FALSE;
    }

    // Handle flags
    if (strcmp(parsed_command[2], "-e") == 0) {
        // Find single record using `email`

        // Check if all parameters exist
        if (!are_all_parameters_existing(parsed_command, 3, 1)) {
            print_error(RECORD_DISPLAY_ERROR, NULL, NULL);
            return FALSE;
        }

        // Get required phone record
        struct record *required_record =
            get_record_based_on_email(parsed_command[3]);

        if (required_record != NULL) {
            print_record(required_record);
            return TRUE;
        } else {
            print_error(RECORD_NOT_FOUND, "e-mail", parsed_command[3]);
            return FALSE;
        }
    } else if (strcmp(parsed_command[2], "-n") == 0) {
        // Find record(s) using `first_name`

        printf("TO DO: Find record(s) using first name.\n");
        return TRUE;
    } else {
        print_error(INCORRECT_COMMAND_PARAMETER, "-n/-e", parsed_command[2]);
        return FALSE;
    }
}

// Appends a phone record to the file
int save_record_to_file(struct record *phone_record) {
    FILE *file = fopen(RECORD_STORE_FILE_NAME, "a"); // Append

    if (file == NULL) {
        print_error(FILE_OPENING_ERROR, NULL, NULL);
        return FALSE;
    }

    // Add data to file
    fprintf(file, "%s %s %s %s\n", phone_record->first_name,
            phone_record->last_name, phone_record->email,
            phone_record->phone_no);

    fclose(file); // Close the file

    return TRUE;
}

// Gets a single record structure based on an e-mail
// `email` is a unique field
struct record *get_record_based_on_email(char *email) {
    FILE *file = fopen(RECORD_STORE_FILE_NAME, "r"); // Read

    if (file == NULL) {
        print_error(FILE_OPENING_ERROR, NULL, NULL);
        return NULL;
    }

    while (!feof(file)) {
        char data_buffer[BUFFER_LENGTH];
        char command_buffer[BUFFER_LENGTH] = "pb add ";

        fgets(data_buffer, sizeof(data_buffer), file);

        // Construct command so that `create_record()` gets required format
        memmove(command_buffer + 7, data_buffer, BUFFER_LENGTH - 7);

        char **parsed_command = parse_command(command_buffer);

        // Check if the e-mails match
        if (strcmp(parsed_command[4], email) == 0) {
            return create_record(parsed_command);
        }
    }

    return NULL;
}

// Creates a new phone record structure
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

            if (i + 1 == MAX_NO_OF_PARSED_PARAMETERS &&
                parsed_command[i][strlen(token) - 1] == '\n') {
                // Remove the '\n' from the last non-null token
                parsed_command[i][strlen(token) - 1] = '\0';
            }
        }
    }

    return parsed_command;
}

// Checks if a record is existing based on whether the e-mail exists in the
// phone book
int is_record_existing(char *email) {
    struct record *phone_record = get_record_based_on_email(email);

    if (phone_record == NULL) {
        return FALSE;
    } else {
        print_error(DUPLICATE_RECORD_ERROR, phone_record->email, NULL);
        return TRUE;
    }
}

// Check if the required number of parameters exist in the entire (or a part of
// the) command Minimum `start_index` value is zero
int are_all_parameters_existing(char **parsed_command, int start_index,
                                int expected_parameter_count) {
    int actual_count = 0;

    // Check input values
    if (start_index < 0) {
        print_error(INCORRECT_FUNCTION_PARAMETER, "are_all_parameters_existing",
                    "start_index");
    }
    if (expected_parameter_count < 0) {
        print_error(INCORRECT_FUNCTION_PARAMETER, "are_all_parameters_existing",
                    "expected_parameter_count");
    }
    if (start_index < 0 || expected_parameter_count < 0) {
        return FALSE;
    }

    for (int i = start_index; i < MAX_NO_OF_PARSED_PARAMETERS; i++) {
        if (actual_count == expected_parameter_count ||
            parsed_command[i] == NULL) {
            break;
        }

        actual_count++;
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
        printf("Incorrect parameter(s) passed. Expected '%s', but got '%s'. "
               "Use 'pb help' for usage.\n",
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
        printf("Insufficient number of parameters passed. Expected %s "
               "parameter(s), but got %s. Use 'pb help' for usage.\n",
               expected_string, incorrect_string);
        break;
    case -104:
        printf("Incorrect parameter '%s' passed to function '%s()'.\n",
               incorrect_string, expected_string);
        break;
    case -105:
        printf("File '%s' could not be opened.\n", RECORD_STORE_FILE_NAME);
        break;
    case -106:
        printf("The phone record could not be added to the phone book.\n");
        break;
    case -107:
        printf(
            "A record with the e-mail '%s' already exists in the phone book.\n",
            expected_string);
        break;
    case -108:
        printf("The phone record(s) could not be displayed.\n");
        break;
    case -109:
        printf("The phone record(s) with the %s '%s' could not be found.\n",
               expected_string, incorrect_string);
        break;
    default:
        printf("Error.\n");
        break;
    }
}

// Prints a phone record
void print_record(struct record *phone_record) {
    printf("First name: %s\n", phone_record->first_name);
    printf("Last name: %s\n", phone_record->last_name);
    printf("e-mail: %s\n", phone_record->email);
    printf("Phone no.: %s\n", phone_record->phone_no);
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
