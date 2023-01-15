// Enumerator defintion
enum error_state {
    INCORRECT_PARAMETER = -100,
    PARAMETER_NOT_PASSED = -101,
    MEMORY_NOT_ALLOCATED = -102
};

// Function declarations
void run_phone_book();
void handle_command(char command_buffer[]);
char **parse_command(char command[]);
void print_error(enum error_state err_state, char *expected_string, char *incorrect_string);
void print_help();
