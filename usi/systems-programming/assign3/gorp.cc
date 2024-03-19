#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"      // working from gcc 13
/* Author: Jeferson Morales Mariciano
 * runtime_stack based program execution
 * if it's not a keyword, it's pushed into the runtime_stack
 * from INPUT command, you can get an empty input by pressing ENTER, which is pushed into the runtime_stack
 * as "" (empty string)
 *
 * Using natural recursion to execute the program
 *
 * IDEAS:
 * a piece of block, i.e. a codeblock in the stack is a string which can either represent:
 * - a keyword
 * - a literal
 * - a piece of code (a function) enclosed in curly braces
 *
 * Stack underflow:
 * indentation ignored.
 * find equal number of open and closed braces
 * WHILE pop 2 block, a block of instructions and a condition.
 *
 * another way to provide a program:
 * ./gorp -- the program code
 */
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>

#define FALSE ""
#define TRUE to_string(true)
#define INLINE "--"
#define CURLY_OPEN "{"
#define CURLY_CLOSE "}"
#define CONCATENATION "."
#define LESS_THAN "<"
#define GREATER_THAN ">"
#define EQUAL "=="
#define NOT_EQUAL "!="
#define LESS_THAN_EQUAL "<="
#define GREATER_THAN_EQUAL ">="
#define PLUS "+"
#define MINUS "-"
#define MULTIPLY "*"
#define DIVIDE "/"
#define LOAD "load"
#define STORE "store"
#define INPUT "input"
#define OUTPUT "output"
#define IF "if"
#define IF_ELSE "ifelse"
#define WHILE "while"
#define DUP "dup"

using namespace std;


stack<string> runtime_stack;
unordered_map<string, string> variables;

#pragma region PRIMITIVES
/**
 * @brief Check if the string is representing the false condition.
 * @param elem the string to be checked
 * @return true if the string is representing the false condition "", false otherwise
 */
bool is_false(string& elem) {
    return elem.empty();
}

/**
 * @brief Check if the string is representing a codeblock start.
 * @param elem the string to be checked
 * @return true if the string is representing a codeblock " { ", false otherwise
 */
bool is_codeblock_start(string& elem) {
    return elem == CURLY_OPEN;
}

/**
 * @brief Check if the string is representing a codeblock end.
 * @param elem the string to be checked
 * @return true if the string is representing a codeblock " } ", false otherwise
 */
bool is_codeblock_end(string& elem) {
    return elem == CURLY_CLOSE;
}

/**
 * @brief Give a string from the stack element.
 * @throw underflow_error stack underflow.
 * @return the string from the stack element
 */
string get_stack_elem() {
    if (runtime_stack.empty()) throw underflow_error("Stack underflow");

    string elem = runtime_stack.top();
    runtime_stack.pop();
    return elem;
}

 /**
  * @brief Pops 2 blocks strings from the runtime_stack, interpret them as integers.
  * Throws exception if the top of the runtime_stack is not an integer.
  * @return pair of integers from the top of the runtime_stack
  */
pair<int, int> stack_two_nums() {
    try {
        int b = stoi(get_stack_elem());
        int a = stoi(get_stack_elem());
        return make_pair(a, b);
    } catch (invalid_argument& e) {
        cerr << "Error " << e.what() << ": one of the arguments is invalid." << endl;
        throw;
    } catch (out_of_range& e) {
        cerr << "Error " << e.what() << ": out of range argument found." << endl;
        throw;
    }
}
#pragma endregion

#pragma region CONCATENATION
/**
 * @brief Check if the string is representing a concatenation.
 * @param elem  the string to be checked
 * @return  true if the string is representing a concatenation " . ", false otherwise
 */
bool is_concatenation(string& elem) {
    return elem == CONCATENATION;
}

/**
 * @brief Concatenate two strings and push it onto the stack.
 */
void concatenation() {
    string b = get_stack_elem();
    string a = get_stack_elem();
    runtime_stack.push(a + b);
}
#pragma endregion

#pragma region DUPLICATION
/**
 * @brief Check if the string is representing a duplication.
 * @param keyword the string to be checked
 * @return true if the string is representing a duplication " dup ", false otherwise
 */
bool is_duplication(string& keyword) {
    return keyword == DUP;
}

/**
 * @brief Duplicate the top of the stack.
 */
void duplication() {
    string elem = get_stack_elem();
    runtime_stack.push(elem);
    runtime_stack.push(elem);
}
#pragma endregion

#pragma region IO OPERATIONS
unordered_set<string> io_operators = {INPUT, OUTPUT };

/**
 * @brief Check if the string is representing an IO operation.
 * @param keyword the string to be checked
 * @return true if the string is representing an IO operation, false otherwise
 */
bool is_io_operation(string& keyword) {
    return io_operators.find(keyword) != io_operators.end();
}

/**
 * Push the input into the runtime_stack if it's not a keyword
 * Please do not insert keywords as input.
 */
void input() {
    string input;
    cin >> input;
    runtime_stack.push(input);
}

/**
 * Pops a string from the runtime_stack and prints it in the standard output.
 */
void output() {
    cout << get_stack_elem() << endl;
}

unordered_map<string, void (*)()> io_operations = {
    { INPUT, input },
    { OUTPUT, output }
};
#pragma endregion

#pragma region MATH OPERATIONS
unordered_set<string> math_operators = {PLUS, MINUS, MULTIPLY, DIVIDE};

/**
 * Check if the given keyword is math sign operation.
 * @param keyword the keyword to be checked.
 * @return true if the keyword is a math sign operation, false otherwise.
 */
bool is_math_operation(string& keyword) {
    return math_operators.find(keyword) != math_operators.end();
}

/**
 * Pushes the summation result of two integers as string into the stack.
 */
void summation() {
    const auto& [a, b] = stack_two_nums();
    runtime_stack.emplace(to_string(a + b));
}

/**
 * Pushes the subtraction result of two integers as string into the stack.
 */
void subtraction() {
    const auto& [a, b] = stack_two_nums();
    runtime_stack.emplace(to_string(a - b));
}

/**
 * Pushes the multiplication result of two integers as string into the stack.
 */
void multiplication() {
    const auto& [a, b] = stack_two_nums();
    runtime_stack.emplace(to_string(a * b));
}

/**
 * Pushes the division result of two integers as string into the stack.
 * Cast to int the result.
 */
void division() {
    try {
        const auto& [a, b] = stack_two_nums();
        if (b == 0) throw domain_error("Division by zero");
        runtime_stack.emplace(to_string(a / b));
    } catch (const exception& e) {
        cerr << "Error " << e.what() << endl;
        throw;
    }
}

unordered_map<string, void (*)()> math_operations = {
        {PLUS,     summation},
        {MINUS,    subtraction},
        {MULTIPLY, multiplication},
        {DIVIDE,   division}
};
#pragma endregion

#pragma region COMPARISON OPERATIONS
// used only for numbers
unordered_set<string> comparison_operators = {
        LESS_THAN, GREATER_THAN, EQUAL, NOT_EQUAL, LESS_THAN_EQUAL, GREATER_THAN_EQUAL
};

/**
 * Check if the given keyword is a comparison operation.
 * @param keyword the keyword to be checked.
 * @return true if the keyword is a comparison operation, false otherwise.
 */
bool is_comparison_operation(string& keyword) {
    return comparison_operators.find(keyword) != comparison_operators.end();
}

/**
 * Pushes the result of the less than comparison of two integers as string into the stack.
 */
void less_than() {
    const auto& [a, b] = stack_two_nums();
    runtime_stack.emplace(a < b ? TRUE : FALSE);
}

/**
 * Pushes the result of the less than equals comparison of two integers as string into the stack.
 */
void less_than_equal() {
    const auto& [a, b] = stack_two_nums();
    runtime_stack.emplace(a <= b ? TRUE : FALSE);
}

/**
 * Pushes the result of the greater than comparison of two integers as string into the stack.
 */
void greater_than() {
    const auto& [a, b] = stack_two_nums();
    runtime_stack.emplace(a > b ? TRUE : FALSE);
}

/**
 * Pushes the result of the greater than equals comparison of two integers as string into the stack.
 */
void greater_than_equal() {
    const auto& [a, b] = stack_two_nums();
    runtime_stack.emplace(a >= b ? TRUE : FALSE);
}

/**
 * Pushes the result of the equals comparison of two integers as string into the stack.
 */
void equal() {
    const auto& [a, b] = stack_two_nums();
    runtime_stack.emplace(a == b ? TRUE : FALSE);
}

/**
 * Pushes the result of the not equals comparison of two integers as string into the stack.
 */
void not_equal() {
    const auto& [a, b] = stack_two_nums();
    runtime_stack.emplace(a != b ? TRUE : FALSE);
}
unordered_map<string, void (*)()> comparison_operations = {
        {LESS_THAN, less_than},
        {LESS_THAN_EQUAL, less_than_equal},
        {EQUAL, equal},
        {NOT_EQUAL, not_equal},
        {GREATER_THAN, greater_than},
        {GREATER_THAN_EQUAL, greater_than_equal}
};
#pragma endregion

void execute_line(istream& buffer, string& line);

#pragma region CONDITIONAL OPERATIONS
unordered_set<string> conditional_operators = {IF, IF_ELSE};

/**
 * Check if the given keyword is a conditional operation.
 * @param keyword the string to be checked.
 * @return true if the keyword is a conditional operation, false otherwise.
 */
bool is_conditional_operation(string& keyword) {
    return conditional_operators.find(keyword) != conditional_operators.end();
}

/**
 * Execute the if statement.
 */
void if_condition() {
    string block = get_stack_elem();
    block = block.substr(2, block.size() - 4);
    string cond =  get_stack_elem();
    if (is_false(cond)) return;

    // otherwise execute_program the cond block
    istringstream block_buffer(""); // empty
    execute_line(block_buffer, block);
}

/**
 * Execute the if else statement.
 */
void if_else_condition() {
    string else_block = get_stack_elem();
    else_block = else_block.substr(2, else_block.size() - 4);
    string if_block = get_stack_elem();
    if_block = if_block.substr(2, if_block.size() - 4);
    string cond =  get_stack_elem();
    istringstream block_buffer(""); // empty
    if (is_false(cond)) {
        // execute_program else block
        execute_line(block_buffer, else_block);
    } else {
        // execute_program if block
        execute_line(block_buffer, if_block);
    }
}

unordered_map<string, void (*)()> conditional_operations = {
        {IF,      if_condition},
        {IF_ELSE, if_else_condition}
};
#pragma endregion

#pragma region LOOP OPERATIONS
/**
 * Check if the given keyword is a loop operation.
 * @param keyword the string to be checked.
 * @return true if the keyword is a loop operation, false otherwise.
 */
bool is_while(string& keyword) {
    return keyword == WHILE;
}

/**
 * Execute the while loop.
 */
void while_loop() {
    string block = get_stack_elem();
    block = block.substr(2, block.size() - 4);
    istringstream block_buffer(FALSE); // empty
    // execute_program block until cond is false
    for (string cond = get_stack_elem(); !is_false(cond); cond = get_stack_elem()) {
        // execute_program the block
        execute_line(block_buffer, block);
    }
}
#pragma endregion

#pragma region LOAD STORE
unordered_set<string> variable_operators = {LOAD, STORE};

/**
 * Check if the given keyword is a variable operation.
 * @param elem the string to be checked.
 * @return true if the keyword is a variable operation load or store, false otherwise.
 */
bool is_variable_operation(string& elem) {
    return variable_operators.find(elem) != variable_operators.end();
}

/**
 * Load the value of the variable into the stack.
 */
void load() {
    string var_name = get_stack_elem();
    if (variables.find(var_name) == variables.end()) {
        throw invalid_argument("Variable not found");
    }
    runtime_stack.push(variables[var_name]);
}

/**
 * Store the value of the top of the stack with a name.
 */
void store() {
    string var_name = get_stack_elem();
    string value = get_stack_elem();
    variables[var_name] = value;
}

unordered_map<string, void (*)()> variable_operations = {
        {LOAD, load},
        {STORE, store}
};
#pragma endregion

// done
#pragma region FILE READING
/**
 * @brief check if a file is provided by looking at argc, then if the filename is valid
 * @param argc number of arguments
 * @param argv array of arguments
 * @return true if a file is provided and valid, false otherwise
 */
bool is_file_provided(int argc, char* argv[]) {
    if (argc <= 1) return false;

    string filename = argv[1];
    if (filename.find(".gorp") == string::npos)
        throw invalid_argument("invalid file extension");

#ifdef DEBUG
    cout << "file provided: " << filename << endl;
#endif
    return true;
}

/**
 * Read and execute_program code from file
 * @param argv array of arguments
 */
ifstream read_file(char* argv[]) {
    string filename = argv[1];
    ifstream filestream(filename);
    if (!filestream.is_open())
        throw invalid_argument("filestream not found.");
    return filestream;
}
#pragma endregion


/**
 * @brief Check if the program is in the given line of code in argv.
 * @param argc number of arguments
 * @param argv array of arguments
 * @return return true if the program is inline in argv.
 */
bool is_program_inline(int argc, char* argv[]) {
    if (argc <= 1) return false;
    string token_inline = argv[1];
    return token_inline == INLINE;
}

/**
 * @brief check if the string elem is a keyword.
 * @param elem  the string to be checked.
 * @return  true if the string is a keyword, false otherwise.
 */
bool is_keyword(string& elem) {
    return is_concatenation(elem) || is_math_operation(elem)
           || is_comparison_operation(elem) || is_duplication(elem)
           || is_variable_operation(elem) || is_conditional_operation(elem)
           || is_io_operation(elem) || is_while(elem);
}

vector<pair<string, void (*)()>> get_keyword_operations() {
    vector<pair<string, void (*)()> > operations;
    operations.emplace_back(CONCATENATION, concatenation);
    operations.emplace_back(DUP, duplication);
    for (const auto& [k, v] : io_operations) operations.emplace_back(k, v);
    for (const auto& [k, v] : math_operations) operations.emplace_back(k, v);
    for (const auto& [k, v] : comparison_operations) operations.emplace_back(k, v);
    for (const auto& [k, v] : conditional_operations) operations.emplace_back(k, v);
    operations.emplace_back(WHILE, while_loop);
    for (const auto& [k, v] : variable_operations) operations.emplace_back(k, v);
    return operations;
}

vector<pair<string, void (*)()>> range = get_keyword_operations();
unordered_map<string, void (*)()> keyword_operations(range.begin(), range.end());


/**
 * @brief Execute the line string passed as a program.
 * @param buffer the buffer to be read if line finished.
 * @param line the line to be executed containing code.
 */
void execute_line(istream& buffer, string& line) {
    stringstream ss(line);
    string elem;
    while (ss >> elem) {
        if (is_keyword(elem)) {
            // execute_program keyword
            keyword_operations[elem]();
        } else if (is_codeblock_start(elem)) {
            // execute_program codeblock
            string codeblock = elem;
            // finish getting from current line
            int count = 1;
            while (count) {
                // get string from new line if finished
                if (! (ss >> elem)) {
                    if (! (getline(buffer, line))) {
                        throw invalid_argument("codeblock not closed");
                    }
                    ss = stringstream(line);
                    ss >> elem;
                }
                codeblock += " " + elem;

                if (is_codeblock_start(elem)) {
                    count++;
                } else if (is_codeblock_end(elem)) {
                    count--;
                }
            }

            runtime_stack.push(codeblock);
        } else {
            // literal
            runtime_stack.push(elem);
        }
    }
}

/**
 * Runtime execution of the code.
 * Invoked after parsing.
 */
void execute_program(istream& buffer) {
    string line;
    while (getline(buffer, line))
        execute_line(buffer, line);
}

#pragma region MAIN
int main(int argc, char* argv[]) {
    try {

        // if provided, read from file, otherwise execute_program code from cin - interactive mode
        if (is_program_inline(argc, argv)) {
            string line;
            for (int i = 2; i < argc; i++)
                line += argv[i] + string(" ");
            istringstream block_buffer(FALSE); // empty
            execute_line(block_buffer, line);
        } else if (is_file_provided(argc, argv)) {
            ifstream filestream = read_file(argv);
            execute_program(filestream);
        } else {
            execute_program(cin);
        }

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}
#pragma endregion

#pragma GCC diagnostic pop

/*

instructions:
ouput
ouput

could make the program crash
*/
