# Libfail
### Custom Fail Function Library
This library provides a way to simulate failures in common system calls (e.g., fork, pthread_create, pipe, etc.) using the LD_PRELOAD mechanism. It is useful for testing error-handling code paths in your programs.

## Features

- Simulates failures in key system calls:
  - `malloc`, `fork`, `pthread_create`, `pipe`, `dup2`, `execve`, `waitpid`, `read`, `write`, and `open`.
- Configurable failure scenarios for robust testing.
- Minimal overhead and easy integration.

---

## Usage

### 1. Clone the Repository

```bash
git clone https://github.com/RychkovIurii/Libfail.git
cd Libfail
```

### 2. Compile the Shared Libraries

Each file simulates failures for a specific system call. Compile the desired files:
```bash
gcc -shared -fPIC -o libfailfork.so fail_fork.c -ldl
gcc -shared -fPIC -o libfailpthread.so fail_pthread.c -ldl
gcc -shared -fPIC -o libfailpipe.so fail_pipe.c -ldl
gcc -shared -fPIC -o libfaildup2.so fail_dup2.c -ldl
gcc -shared -fPIC -o libfailexecve.so fail_execve.c -ldl
gcc -shared -fPIC -o libfailwaitpid.so fail_waitpid.c -ldl
```

### 3. Preload the Library

Run your program with the custom library to simulate failures:
```bash
LD_PRELOAD=./libfailfork.so ./your_program
LD_PRELOAD=./libfailpthread.so ./your_program
LD_PRELOAD=./libfailpipe.so ./your_program
```

If you want to test it with `valgrind`:
``` bash
LD_PRELOAD=./libfailfunction.so valgrind ./your_program
LD_PRELOAD=./libfail_malloc.so valgrind ./your_program
```

### 4.  Test Failure Scenarios

`fork`: Fails every other call.  
`pthread_create`: Fails after a configurable number of threads.  
`pipe`: Fails every 3rd call.  
`dup2`: Fails for specific file descriptors.  
`execve`: Fails for specific executables.  
`waitpid`: Fails for specific process IDs.  

**Customization**

Edit the source files (e.g., fail_fork.c, fail_pipe.c) to modify failure conditions, such as the number of successful calls before failure.

Example:
```
static int fail_after = 3; // Change the failure threshold
```
Example Output
```
$ LD_PRELOAD=./libfailpipe.so ./test_program
Error: pipe failed with EMFILE
```
**Notes**
Use only for testing and debugging.
Works only with dynamically linked executables.
Reset failure conditions in the code as needed.

Feel free to extend or combine the functions into a single shared library for convenience.
