#include <stdio.h>
#include <stdlib.h> // for malloc() and free()

// Structure to hold the details of an employee
typedef struct employee {
    int empId;
    char Name[100];
    char Designation[100];
    char Dept[10];
} employee_t;

/* Read the employee details using scanf */
void readData(int n, employee_t *s) {
    for (int i = 0; i < n; i++) {
        printf("Enter the ID, Name, Designation and Department of Employee %d:\n", i + 1);
        scanf("%d", &s[i].empId);
        scanf(" %[^\n]%*c", s[i].Name);  //// Read string with spaces until \n and consume it
        scanf(" %[^\n]%*c", s[i].Designation);
        scanf(" %[^\n]%*c", s[i].Dept);
        printf("\n");
    }
}

/* Function to print the employee details */
void display(int n, employee_t *s) {
    for (int i = 0; i < n; i++) {
        printf("\nEmployee %d:\n", i + 1);
        printf("Employee ID: %d\n", s->empId);
        printf("Name: %s\n", s->Name);
        printf("Designation: %s\n", s->Designation);
        printf("Department: %s\n", s->Dept);
        printf("\n");

        s++; // Move to the next employee structure in the array
    }
}

/*----------Main Program--------*/
int main() {
    int n;
    employee_t *employees; // _t to show that the identifier is a type

    printf("Enter the number of employees: ");
    scanf("%d", &n);
    printf("\n");

    // Allocate memory for 'n' employees
    employees = (employee_t *) malloc(n * sizeof(employee_t));
    if (employees == NULL) {
        printf("Memory allocation failed\n");
        return 1; // Exit the program if memory allocation fails
    }

    // Read employee details
    readData(n, employees);

    // Print employee details
    display(n, employees);

    // Free the allocated memory
    free(employees);

    return 0;
}
