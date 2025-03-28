#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_DEPT 30

#define RESET  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define RED    "\x1B[31m"
#define CYAN   "\x1B[36m"
#define YELLOW "\x1B[33m"

typedef struct {
    int id;
    char name[50];
    int age;
    char department[30];
} Student;

void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

void mainMenu() {
    int choice;
    while (1) {
        printf(CYAN "\n=============================================\n");
        printf("      STUDENT MANAGEMENT SYSTEM\n");
        printf("=============================================\n" RESET);
        printf(YELLOW "1. Add Student\n" RESET);
        printf(YELLOW "2. View All Students\n" RESET);
        printf(YELLOW "3. Search Student by ID\n" RESET);
        printf(YELLOW "4. Update Student\n" RESET);
        printf(YELLOW "5. Delete Student\n" RESET);
        printf(YELLOW "6. Exit\n" RESET);
        printf(CYAN "=============================================\n" RESET);
        printf(YELLOW "Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline buffer

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: 
                printf(GREEN "\n✅  Exiting program. Goodbye!\n" RESET);
                exit(0);
            default: 
                printf(RED "\n❌  Invalid choice! Please enter a number between 1-6.\n" RESET);
        }
    }
}

int main() {
    mainMenu();
    return 0;
}


void addStudent() {
    FILE *file = fopen("students.txt", "a"); // Open file in append mode
    if (file == NULL) {
        printf(RED "❌ Error opening file!\n" RESET);
        return;
    }

    Student s;
    printf(CYAN"\n=============================================\n");
    printf("               ADD NEW STUDENT               \n");
    printf(CYAN"=============================================\n");

    printf(YELLOW "Enter Student ID: ");
    scanf("%d", &s.id);
    getchar(); // Consume newline left by scanf

    printf(YELLOW "Enter Student Name: ");
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; // Remove newline

    printf(YELLOW "Enter Age: ");
    scanf("%d", &s.age);
    getchar(); 

    printf(YELLOW "Enter Department: ");
    fgets(s.department, MAX_DEPT, stdin);
    s.department[strcspn(s.department, "\n")] = '\0';

    // Write student data to file
    fprintf(file, "%d,%s,%d,%s\n", s.id, s.name, s.age, s.department);
    fclose(file); // Close file after writing

    printf(GREEN "\n✅ Student added successfully!\n" RESET);
}

void viewStudents() {
    FILE *file = fopen("students.txt", "r"); // Open file in read mode
    if (file == NULL) {
        printf(RED "❌ Error: No student records found!\n" RESET);
        return;
    }

    Student s;
    int found = 0; // Flag to check if records exist

    printf(CYAN"\n=============================================\n");
    printf("              STUDENT LIST                   \n");
    printf(CYAN"=============================================\n");
    printf("| %-5s | %-20s | %-5s | %-15s |\n", "ID", "Name", "Age", "Department");
    printf("--------------------------------------------------------\n");

    while (fscanf(file, "%d,%49[^,],%d,%29[^\n]\n", &s.id, s.name, &s.age, s.department) != EOF) {
        printf("| %-5d | %-20s | %-5d | %-15s |\n", s.id, s.name, s.age, s.department);
        found = 1;
    }

    fclose(file); // Close file after reading

    if (!found) {
        printf(RED "❌ No student records available.\n" RESET);
    }
}

void searchStudent() {
    FILE *file = fopen("students.txt", "r"); // Open file in read mode
    if (file == NULL) {
        printf(RED "❌ Error: No student records found!\n" RESET);
        return;
    }

    int searchId, found = 0;
    Student s;

    printf(CYAN"\n=============================================\n");
    printf("             SEARCH STUDENT                  \n");
    printf(CYAN"=============================================\n");
    printf(YELLOW "Enter Student ID to search: ");
    scanf("%d", &searchId);

    while (fscanf(file, "%d,%49[^,],%d,%29[^\n]\n", &s.id, s.name, &s.age, s.department) != EOF) {
        if (s.id == searchId) {
            printf(GREEN "\n✅ Student Found!\n" RESET);
            printf("------------------------------------------------\n");
            printf("| ID    : %-5d                                 |\n", s.id);
            printf("| Name  : %-20s                     |\n", s.name);
            printf("| Age   : %-5d                                 |\n", s.age);
            printf("| Dept  : %-15s                    |\n", s.department);
            printf("------------------------------------------------\n");
            found = 1;
            break;
        }
    }

    fclose(file); // Close file after reading

    if (!found) {
        printf(RED "\n❌  Student with ID %d not found!\n" RESET, searchId);
    }
}

void deleteStudent() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf(RED "❌  Error: No student records found!\n" RESET);
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf(RED "❌ Error opening temporary file!\n" RESET);
        fclose(file);
        return;
    }

    int deleteId, found = 0;
    Student s;

    printf(CYAN"\n=============================================\n");
    printf("             DELETE STUDENT                  \n");
    printf(CYAN"=============================================\n");
    printf(YELLOW "Enter Student ID to delete: ");
    scanf("%d", &deleteId);

    while (fscanf(file, "%d,%49[^,],%d,%29[^\n]\n", &s.id, s.name, &s.age, s.department) != EOF) {
        if (s.id == deleteId) {
            found = 1;
            continue; // Skip writing this student to the new file (delete it)
        }
        fprintf(tempFile, "%d,%s,%d,%s\n", s.id, s.name, s.age, s.department);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("students.txt");         // Delete old file
        rename("temp.txt", "students.txt"); // Rename temp file to original name
        printf(GREEN "\n✅ Student with ID %d deleted successfully!\n" RESET, deleteId);
    } else {
        remove("temp.txt"); // Remove temp file if no changes were made
        printf(RED "\n❌ Student with ID %d not found!\n" RESET, deleteId);
    }
}

void updateStudent() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf(RED "❌ Error: No student records found!\n" RESET);
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf(RED "❌ Error opening temporary file!\n" RESET);
        fclose(file);
        return;
    }

    int updateId, found = 0;
    Student s;

    printf(CYAN"\n=============================================\n");
    printf("             UPDATE STUDENT                  \n");
    printf(CYAN"=============================================\n");
    printf(YELLOW "Enter Student ID to update: ");
    scanf("%d", &updateId);
    getchar(); // Clear newline character from buffer

    while (fscanf(file, "%d,%49[^,],%d,%29[^\n]\n", &s.id, s.name, &s.age, s.department) != EOF) {
        if (s.id == updateId) {
            found = 1;

            // Get new details
            printf(YELLOW "Enter new Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = 0; // Remove newline character

            printf(YELLOW "Enter new Age: ");
            scanf("%d", &s.age);
            getchar(); // Clear newline buffer

            printf(YELLOW "Enter new Department: ");
            fgets(s.department, sizeof(s.department), stdin);
            s.department[strcspn(s.department, "\n")] = 0; // Remove newline character

            fprintf(tempFile, "%d,%s,%d,%s\n", s.id, s.name, s.age, s.department);
            printf(GREEN "\n✅  Student with ID %d updated successfully!\n" RESET, updateId);
        } else {
            fprintf(tempFile, "%d,%s,%d,%s\n", s.id, s.name, s.age, s.department);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("students.txt");
        rename("temp.txt", "students.txt");
    } else {
        remove("temp.txt");
        printf(RED "\n❌  Student with ID %d not found!\n" RESET, updateId);
    }
}
