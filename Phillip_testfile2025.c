#include "Phillip_libFS2025.h"
#include <ctype.h>  // For tolower()
#include <string.h>  // For memset()

// Function to display the menu
void displayMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Create a file\n");
    printf("2. Open a file\n");
    printf("3. Write to a file\n");
    printf("4. Read from a file\n");
    printf("5. Close a file\n");
    printf("6. Delete a file\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

// Function to wait for user input to continue
void waitForUser() {
    printf("\nPress Enter to continue...");
    getchar();  // Wait for Enter key
    getchar();  // Clear the newline character from the buffer
}

int main() {
    char filename[MAX_FILENAME];
    char introduction[] = "Hello, my name is Phillip Ho.\n\n"
                          "I am a computer science student with a strong interest in systems "
                          "programming. My goal is to build "
                          "reliable and efficient software systems.\n\n"
                          "This project demonstrates a simple file system library in C that "
                          "provides basic file operations. I hope you find my implementation "
                          "useful and educational!";
    int file_index = -1;  // Track the currently open file
    int choice;
    char buffer[MAX_FILE_SIZE];

    while (1) {
        displayMenu();
        scanf("%d", &choice);  // Get user choice
        getchar();  // Clear the newline character from the buffer

        switch (choice) {
            case 1:  // Create a file
                printf("Enter the filename to create: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileCreate(filename) != 0) {
                    printf("Error creating file.\n");
                }
                waitForUser();
                break;

            case 2:  // Open a file
                printf("Enter the filename to open: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                file_index = fileOpen(filename);
                if (file_index == -1) {
                    printf("Error opening file.\n");
                }
                waitForUser();
                break;

            case 3:  // Write to a file
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("Writing introduction to file '%s'...\n", filename);
                    if (fileWrite(file_index, introduction) != 0) {
                        printf("Error writing to file.\n");
                    }
                }
                waitForUser();
                break;

            case 4:  // Read from a file 
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    // Clear buffer before reading
                    memset(buffer, 0, MAX_FILE_SIZE);
                    
                    // Read file contents into buffer
                    int bytes_read = fileRead(file_index, buffer, MAX_FILE_SIZE);
                    
                    if (bytes_read == -1) {
                        printf("Error reading from file.\n");
                    } else if (bytes_read == 0) {
                        printf("File '%s' is empty.\n", filename);
                    } else {
                        printf("\n--- Contents of file '%s' ---\n", filename);
                        printf("%s\n", buffer);
                        printf("--- End of file ---\n");
                        printf("Read %d bytes from file.\n", bytes_read);
                    }
                }
                waitForUser();
                break;

            case 5:  // Close a file
                if (file_index == -1) {
                    printf("Error: No file is currently open.\n");
                } else {
                    if (fileClose(file_index) == 0) {
                        printf("File closed successfully.\n");
                        file_index = -1;  // Reset file index after closing
                    } else {
                        printf("Error closing file.\n");
                    }
                }
                waitForUser();
                break;

            case 6:  // Delete a file
                printf("Enter the filename to delete: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileDelete(filename) != 0) {
                    printf("Error deleting file.\n");
                }
                waitForUser();
                break;

            case 7:  // Exit
                printf("Exiting the program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                waitForUser();
                break;
        }
    }

    return 0;
}