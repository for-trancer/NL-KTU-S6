## Changing Port Number After Each Execution

In this repository, we have streamlined the code by removing error handlers to reduce the number of lines of code. This may occasionally result in address bind issues upon execution. To mitigate this problem, it is advisable to change the port number after each execution.

### Why Change the Port Number?

Removing error handlers helps in reducing the code complexity, but it might cause address bind issues if the port is still in use from a previous execution. Changing the port number ensures that your application runs smoothly without encountering binding conflicts.

### How to Change the Port Number

In your C program, the port number is defined using a preprocessor directive. Follow these steps to change the port number:

1. **Locate the Port Definition:**
   Find the line in your source code where the port number is defined. It typically looks like this:

   ```c
   #define PORT 8080
