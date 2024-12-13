# Testing malloc failure without modifying your program source code

---

### 1. Test with a Custom Library

Use a library like libeatmydata or override malloc with a custom implementation that simulates failure. For example, with LD_PRELOAD, you can inject a modified version of malloc that fails after a certain threshold.

Create a simple custom malloc failure:

```bash
gcc -shared -fPIC -o libfailmalloc.so fail_malloc.c
LD_PRELOAD=./libfailmalloc.so ./your_program
```
**Using a custom library to override malloc is the most reliable way to test malloc failure**

---

### 2. Limit the Available Memory for the Program
Use tools like ulimit (on Linux/Unix systems) to restrict the maximum memory the program can allocate:
```bash
ulimit -v 2048 # Set max virtual memory to 2048 KB
./your_program
```
This will cause malloc to fail if the program exceeds the memory limit.

P.S
You can reset ulimit to its default value by running the following command:
```bash
ulimit -v unlimited # Restore to no limit
```
---

### 3. Run the Program in a Low-Memory Environment

Create a virtual machine or a container (e.g., Docker) with limited memory:

```bash
docker run --memory=16m -it your_container
```

---

### 4. Simulate Large Allocations

Run the program on a system already under heavy memory pressure. Alternatively, in another terminal, run a memory-intensive process like:

```bash
yes | dd bs=1M count=100000 of=/dev/null
```

---
