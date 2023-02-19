#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CONTACTS 100
// Structure to hold contact information
struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};
// Function to add a new contact to the file
void addContact(struct Contact* contacts, int* numContacts) {
    // Get the new contact's information
    printf("Enter name: ");
    scanf("%s", contacts[*numContacts].name);
    printf("Enter phone number: ");
    scanf("%s", contacts[*numContacts].phone);
    printf("Enter email: ");
    scanf("%s", contacts[*numContacts].email);
    // Increment the number of contacts
    (*numContacts)++;
    // Write the new contact's information to the file
    FILE* file = fopen("contacts.txt", "a");
    fprintf(file, "%s,%s,%s\n", contacts[*numContacts-1].name, contacts[*numContacts-1].phone, contacts[*numContacts-1].email);
    fclose(file);
}
// Function to search for a contact in the file
void searchContact(struct Contact* contacts, int numContacts) {
    char name[50];
    printf("Enter name to search: ");
    scanf("%s", name);
    // Search for the contact in the file
    FILE* file = fopen("contacts.txt", "r");
    while (!feof(file)) {
        char line[150];
        fgets(line, 150, file);
        char* token = strtok(line, ",");
        if (strcmp(token, name) == 0) {
            printf("Name: %s\n", token);
            token = strtok(NULL, ",");
            printf("Phone: %s\n", token);
            token = strtok(NULL, ",");
            printf("Email: %s", token);
            break;
        }
    }
    fclose(file);
}
// Function to list all contacts in the file
void listContacts(struct Contact* contacts, int numContacts) {
    // Open the file for reading
    FILE* file = fopen("contacts.txt", "r");
    // Print the header for the contact list
    printf("\nName\t\tPhone\t\tEmail\n");
    printf("----\t\t-----\t\t-----\n");
    // Read each line of the file and print the contact information
    while (!feof(file)) {
        char line[150];
        fgets(line, 150, file);
        char* token = strtok(line, ",");
        char* token1 = strtok(NULL, ",");
        char* token2 = strtok(NULL, ",");
        if (token != NULL && token1 != NULL && token2 != NULL) {
            printf("%s\t", token);
//            token = strtok(NULL, ",");
            printf("%s\t", token1);
//            token = strtok(NULL, ",");
            printf("%s", token2);
          
        }
    }
    printf("\n");
    // Close the file
    fclose(file);
}
// Function to delete a contact from the file
void deleteContact(struct Contact* contacts, int* numContacts) {
    char name[50];
    printf("Enter name to delete: ");
    scanf("%s", name);

    // Delete the contact from the file
    FILE* file = fopen("contacts.txt", "r");
    FILE* tempFile = fopen("temp.txt", "w");
    while (!feof(file)) {
        char line[150];
        fgets(line, 150, file);

        char* token = strtok(line, ",");
        if (strcmp(token, name) != 0) {
            fprintf(tempFile, "%s", line);
        }
    }
    fclose(file);
    fclose(tempFile);
    remove("contacts.txt");
    rename("temp.txt", "contacts.txt");
}
int main() {
    struct Contact contacts[MAX_CONTACTS];
    int numContacts = 0;
    int choice;
do {
    printf("1. Add Contact\n");
    printf("2. Search Contact\n");
    printf("3. Delete Contact\n");
    printf("4. List Contacts\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            addContact(contacts, &numContacts);
            break;
        case 2:
            searchContact(contacts, numContacts);
            break;
        case 3:
            deleteContact(contacts, &numContacts);
            break;
        case 4:
    		listContacts(contacts, numContacts);
   			break;
        case 5:
            break;
        default:
            printf("Invalid choice\n");
    }
} while (choice != 5);
return 0;
}
    
