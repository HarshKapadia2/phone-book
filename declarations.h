// Constant definitions
#define BUFFER_LENGTH 100
#define MAX_NO_OF_PARSED_PARAMETERS 6
#define TRUE 1
#define FALSE 0
#define COUNT_BUFFER_LENGTH 3
#define RECORD_STORE_FILE_NAME "phone-book-records.txt"

// Enumerator defintion
enum error_state {
    INCORRECT_COMMAND_PARAMETER = -100,
    COMMAND_PARAMETER_NOT_PASSED = -101,
    MEMORY_NOT_ALLOCATED = -102,
    INSUFFICIENT_PARAMETER_COUNT = -103,
    INCORRECT_FUNCTION_PARAMETER = -104,
    FILE_OPENING_ERROR = -105,
    RECORD_ADDITION_ERROR = -106,
    DUPLICATE_RECORD_ERROR = -107,
    RECORD_DISPLAY_ERROR = -108,
    RECORD_NOT_FOUND = -109,
    FILE_DOES_NOT_EXIST_ERROR = -110
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
int add_record(char **parsed_command);
int find_records(char **parsed_command);
int save_record_to_file(struct record *phone_record);
struct record *get_record_based_on_email(char *email);
struct record *create_record(char **parsed_command);
char **parse_command(char command[]);
int is_record_existing(char *email);
int are_all_parameters_existing(char **parsed_command, int check_start_index,
                                int no_of_parameters);
void print_error(enum error_state err_state, char *expected_string,
                 char *incorrect_string);
void print_record(struct record *phone_record);
void print_help();
