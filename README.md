# 🐚 Minishell - 42 School Project

Welcome to **Minishell**! 🎉 This is one of the most comprehensive projects from **Rank 3** at 42 School, where we recreate a functional Unix shell from scratch. This project challenges us to implement command parsing, execution, signal handling, and all the core features that make a shell work.

The goal is to create a shell that behaves like **bash**, handling commands, pipes, redirections, environment variables, and built-in commands! 🚀

---

### 📂 Project Structure

minishell/
├── include/minishell.h    # Header file (.h)  
├── src/                   # Source files (.c)  
│   ├── minishell.c        # Main program entry point  
│   ├── builtins/          # Built-in commands  
│   │   ├── cmd_cd.c       # Change directory  
│   │   ├── cmd_echo.c     # Echo command  
│   │   ├── cmd_env.c      # Environment variables  
│   │   ├── cmd_exit.c     # Exit shell  
│   │   ├── cmd_export.c   # Export variables  
│   │   ├── cmd_pwd.c      # Print working directory  
│   │   └── cmd_unset.c    # Unset variables  
│   ├── parse/             # Command parsing  
│   │   ├── parse_line.c   # Main parsing logic  
│   │   ├── parse_pipeline.c # Pipeline parsing  
│   │   ├── tokenize.c     # Tokenization  
│   │   ├── syntax.c       # Syntax validation  
│   │   ├── expand_variables.c # Variable expansion  
│   │   ├── remove_quotes.c # Quote handling  
│   │   └── token_type.c   # Token classification  
│   ├── execution/         # Command execution  
│   │   ├── execute.c      # Main execution logic  
│   │   ├── execute_builtins.c # Built-in execution  
│   │   ├── execute_command.c # Command execution  
│   │   ├── execute_external.c # External commands  
│   │   ├── get_command.c  # Command resolution  
│   │   └── handle_redirections.c # I/O redirection  
│   ├── env/              # Environment management  
│   └── control/          # Signal and control flow  
├── libft/                # Libft library  
├── .gitignore  
├── Makefile              # Makefile to compile the project  
└── README.md             # This file  

---

### 🚀 Features Implemented

#### 🛠️ Built-in Commands
- **`echo`** - Display text (with -n option support)
- **`cd`** - Change directory (relative and absolute paths)
- **`pwd`** - Print current working directory
- **`export`** - Set environment variables
- **`unset`** - Remove environment variables
- **`env`** - Display environment variables
- **`exit`** - Exit the shell (with exit codes)

#### 🔗 Advanced Shell Features
- **Pipes** (`|`) - Chain commands together
- **Input redirection** (`<`) - Redirect input from files
- **Output redirection** (`>`) - Redirect output to files
- **Append redirection** (`>>`) - Append output to files
- **Here documents** (`<<`) - Multi-line input with delimiters
- **Variable expansion** (`$VAR`, `$?`) - Expand environment variables and exit codes
- **Quote handling** - Single quotes, double quotes, and escaping
- **Signal handling** - Ctrl+C, Ctrl+D, Ctrl+\ behavior
- **Command history** - Navigate through previous commands

---

### 🧠 Core Components

#### 🎯 Parsing Engine
- **Tokenization**: Breaks input into tokens (commands, operators, arguments)
- **Syntax validation**: Checks for proper shell syntax
- **Variable expansion**: Handles `$VAR` and `$?` expansions
- **Quote processing**: Manages single and double quotes
- **Pipeline creation**: Builds command pipeline structures

#### 🔧 Execution Engine
- **Built-in detection**: Identifies and executes built-in commands
- **External commands**: Finds and executes system commands
- **Pipeline execution**: Handles pipes between commands
- **Redirection handling**: Manages input/output redirections
- **Process management**: Forks and manages child processes

#### 🌍 Environment Management
- **Variable storage**: Maintains environment variables
- **Variable expansion**: Expands variables in commands
- **Export/unset**: Manages variable lifecycle
- **Exit code tracking**: Maintains `$?` variable

---

## 🛠️ How to Use

### 📦 Compilation

To compile the shell, run:

```bash
make
```

This will generate the `minishell` executable.

### 🧩 Usage

Launch the shell:

```bash
./minishell
```

You'll see the custom prompt:
```
SMASH -> 
```

### 💡 Usage Examples

#### Basic Commands
```bash
SMASH -> echo "Hello, World!"
Hello, World!

SMASH -> pwd
/home/user/minishell

SMASH -> ls -la
# Lists directory contents

SMASH -> cd ..
SMASH -> pwd
/home/user
```

#### Environment Variables
```bash
SMASH -> export NAME="42 Student"
SMASH -> echo $NAME
42 Student

SMASH -> env | grep NAME
NAME=42 Student

SMASH -> unset NAME
SMASH -> echo $NAME
# (empty output)
```

#### Pipes and Redirections
```bash
# Simple pipe
SMASH -> ls | grep ".c"

# Output redirection
SMASH -> echo "Hello" > output.txt
SMASH -> cat output.txt
Hello

# Input redirection
SMASH -> cat < input.txt

# Append redirection
SMASH -> echo "World" >> output.txt

# Here document
SMASH -> cat << EOF
> Line 1
> Line 2
> EOF
Line 1
Line 2
```

#### Complex Pipelines
```bash
# Multiple pipes
SMASH -> ls -la | grep ".c" | wc -l

# Mixed redirections and pipes
SMASH -> cat file.txt | grep "pattern" > results.txt

# Variable expansion
SMASH -> export PATH_BACKUP=$PATH
SMASH -> echo $PATH_BACKUP
```

---

## 🎯 Key Features Deep Dive

### 🔍 Parsing Process
1. **Tokenization**: Input is split into meaningful tokens
2. **Quote handling**: Processes single/double quotes and escapes
3. **Variable expansion**: Expands `$` variables and `$?` exit codes
4. **Syntax validation**: Checks for syntax errors
5. **AST creation**: Builds abstract syntax tree for execution

### ⚙️ Execution Flow
1. **Built-in check**: Determines if command is built-in
2. **PATH resolution**: Finds executable in system PATH
3. **Process creation**: Forks processes for external commands
4. **Pipe setup**: Creates pipes for command chaining
5. **Redirection**: Sets up file descriptors for I/O redirection
6. **Signal handling**: Manages interrupt signals properly

### 🔒 Signal Handling
- **SIGINT (Ctrl+C)**: Interrupts current command, shows new prompt
- **SIGQUIT (Ctrl+\)**: Ignored in interactive mode
- **EOF (Ctrl+D)**: Exits shell gracefully
- **SIGTERM**: Handles termination signals

---

## ✅ Project Requirements

- ✅ Interactive command prompt
- ✅ Command history with readline
- ✅ Search and launch executables (relative/absolute paths and PATH)
- ✅ Handle quotes (single and double)
- ✅ Implement redirections (`<`, `>`, `>>`, `<<`)
- ✅ Implement pipes (`|`)
- ✅ Handle environment variables (`$VAR`)
- ✅ Handle exit status (`$?`)
- ✅ Handle signals (Ctrl+C, Ctrl+D, Ctrl+\)
- ✅ Implement all required built-ins
- ✅ No memory leaks
- ✅ Error handling similar to bash

---

## 🚨 Error Handling

The shell handles various error conditions:

- **Syntax errors**: Invalid command syntax
- **Command not found**: Non-existent commands
- **Permission denied**: Insufficient permissions
- **File not found**: Missing input files
- **Pipe errors**: Broken pipes
- **Memory allocation**: Out of memory conditions
- **Signal interruption**: Graceful signal handling

---

## 🧪 Testing & Validation

### Basic Functionality Tests
```bash
# Test built-ins
echo "test" | ./minishell
# Input: pwd
# Input: echo $USER
# Input: exit

# Test pipes
echo "ls | grep minishell" | ./minishell

# Test redirections
echo "echo hello > test.txt" | ./minishell
echo "cat < test.txt" | ./minishell
```

### Advanced Tests
```bash
# Test complex pipelines
echo "ls -la | grep minishell | wc -l" | ./minishell

# Test variable expansion
echo 'export TEST="hello world"; echo $TEST' | ./minishell

# Test here documents
./minishell << 'EOF'
cat << END
line 1
line 2
END
exit
EOF
```

### Comparison with Bash
```bash
# Compare outputs
echo "command" | bash
echo "command" | ./minishell
# Outputs should be identical
```

---

## 💡 Key Learning Objectives

- **Shell Internals**: Understanding how shells parse and execute commands
- **Process Management**: Mastering fork, exec, and wait system calls
- **Signal Handling**: Implementing proper signal behavior
- **I/O Redirection**: Managing file descriptors and pipes
- **Memory Management**: Preventing memory leaks in complex programs
- **Error Handling**: Robust error management and recovery
- **Parsing Techniques**: Tokenization and syntax analysis
- **System Programming**: Low-level Unix programming concepts

---

## 🚀 Advanced Features

### Custom Prompt
The shell features a custom colored prompt: `SMASH -> `

### History Support
Uses GNU readline for:
- Command history navigation (↑/↓ arrows)
- Line editing capabilities
- Tab completion (basic)

### Exit Code Tracking
Maintains `$?` variable with the exit status of the last command:
```bash
SMASH -> ls /nonexistent
ls: cannot access '/nonexistent': No such file or directory
SMASH -> echo $?
2
```

---

## 🔍 Debugging Tips

1. **Memory debugging**: Use valgrind to detect memory leaks
2. **Signal testing**: Test all signal combinations
3. **Edge cases**: Test empty commands, multiple spaces, special characters
4. **Comparison testing**: Compare behavior with bash
5. **Stress testing**: Test with complex command combinations

---

## 🏆 Project Challenges

- **Parsing complexity**: Handling quotes, variables, and special characters
- **Signal management**: Proper signal handling in different contexts
- **Memory management**: Preventing leaks in complex data structures
- **Process synchronization**: Managing multiple processes and pipes
- **Error compatibility**: Matching bash error messages and behavior

---

*Made with ❤️ at 42 Madrid*
