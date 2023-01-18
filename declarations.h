// Constant definitions
#define BUFFER_LENGTH 100
#define MAX_NO_OF_PARSED_PARAMETERS 6
#define TRUE 1
#define FALSE 0
#define COUNT_BUFFER_LENGTH 3

// Enumerator defintion
enum error_state {
  INCORRECT_PARAMETER = -100,
  PARAMETER_NOT_PASSED = -101,
  MEMORY_NOT_ALLOCATED = -102,
  INSUFFICIENT_PARAMETER_COUNT = -103
};

// Structure definition
struct record {
  char *first_name;
  char *last_name;
  char *email; // Unique
  char *phone_no;
};

// Function declarations
void run_phone_book();
void handle_command(char command_buffer[]);
struct record *create_record(char **parsed_command);
char **parse_command(char command[]);
int are_all_parameters_existing(char **parsed_command, int check_start_index,
                                int no_of_parameters);
void print_error(enum error_state err_state, char *expected_string,
                 char *incorrect_string);
void print_help();
