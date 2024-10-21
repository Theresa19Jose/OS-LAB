#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int parent_to_child[2];  // Pipe for parent to child communication
    int child_to_parent[2];  // Pipe for child to parent communication
    pid_t pid;
    char parent_msg[100], child_msg[100];
    char buffer[100];

    // Create the pipes
    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // Fork the process to create a child
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {  // Parent process
        close(parent_to_child[0]);  // Close unused read end of parent-to-child pipe
        close(child_to_parent[1]);  // Close unused write end of child-to-parent pipe

        // Parent sends a message to child
        printf("Parent passes value to child\n");
        printf("Enter data for child: ");
        fgets(parent_msg, 100, stdin);
        write(parent_to_child[1], parent_msg, strlen(parent_msg) + 1);
        close(parent_to_child[1]);  // Close the write end after sending data

        // Parent reads the reply from the child
        read(child_to_parent[0], buffer, sizeof(buffer));
        printf("Parent receives from child: %s\n", buffer);
        close(child_to_parent[0]);  // Close the read end after reading
    } 
    else {  // Child process
        close(parent_to_child[1]);  // Close unused write end of parent-to-child pipe
        close(child_to_parent[0]);  // Close unused read end of child-to-parent pipe

        // Child reads the message from the parent
        read(parent_to_child[0], buffer, sizeof(buffer));
        printf("Child receives from parent: %s", buffer);
        close(parent_to_child[0]);  // Close the read end after reading

        // Child sends a reply to the parent
        printf("Enter reply to parent: ");
        fgets(child_msg, 100, stdin);
        write(child_to_parent[1], child_msg, strlen(child_msg) + 1);
        close(child_to_parent[1]);  // Close the write end after sending data
    }

    return 0;
}


