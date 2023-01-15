// Enumerator defintion
enum error_state {
    INCORRECT_PARAMETER = -100,
    PARAMETER_NOT_PASSED = -101,
    MEMORY_NOT_ALLOCATED = -102
};

// Function declarations
void runPhoneBook();
void handleCommand(char command_buffer[]);
char **parseCommand(char command[]);
void printError(enum error_state err_state, char *expected_string, char *incorrect_string);
void printHelp();
