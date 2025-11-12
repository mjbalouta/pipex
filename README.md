# Pipex
## UNIX mechanism

This project allows you to explore a UNIX mechanism in detail. 

### How to use:
1) Inside the directory you want: `git clone https://github.com/mjbalouta/pipex.git`

2) Type `make` to compile the project

3) Type `./pipex` followed by a prompt that follows this model `infile cmd1 cmd2 outfile`

**For Bonus:**

1) Type `make bonus`

2) Type `./pipex` followed by a prompt that follows this model `infile cmd1 cmd2 cmd3 (...) outfile`

### Requirements

1) It must take 4 arguments:
- file1 and file2 are file names.
- cmd1 and cmd2 are shell commands with their parameters.

2) It must behave exactly like the following shell command:
```
< file1 cmd1 | cmd2 > file2
```

### Some notes from my Notebook:

**1) access()**:
- used to check if a command is executable before calling execve()

**2) dup2()**:
- redirects one file descriptor to another

**3) execve()**:
- replaces the current process with a new program (it does not return, unless there's an error).

**4) pipe()**:
- creates a pipe - fd[0] for reading, fd[1] for writing.

**5) fork()**:
- used to create separate processes for cmd1 and cmd2.

**6) waitpid()**:
- waits for the child processes to finish.

**UNDERSTANDING KEY CONCEPTS AND DEFINING STRATEGY**

**1) Processes:**
- A process is an instance of a running program;
- You need to create child processes using fork();

**2) File Descriptors:**
- File descriptors are integers that represent open files or standard streams.

**3) Pipes:**
- A pipe is used to pass data from one process to another.

**4) Command Execution:**
- Use execve() to replace the current process with a new one;
- You must split command string and find the path to the binary.

**5) Environment Path:**
- Commands like ls or grep are binaries stored in directories from the PATH environment variable;
- You must parse envp[] to find the full path.