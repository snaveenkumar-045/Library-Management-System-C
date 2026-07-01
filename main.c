Source Code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Function declarations
int login();
void addBook();
void displayBooks();
void searchBook();
void deleteBook();
void addStudent();
void issueBook();
void returnBook();
void displayTransactions();
// ================= MAIN =================
int main() {
 int choice;
 if (!login()) {
 printf("Access Denied!\n");
 return 0;
 }
 while (1) {
 printf("\n==============================\n");
 printf(" LIBRARY MANAGEMENT SYSTEM\n");
 printf("==============================\n");
 printf("1. Add Book\n");
 printf("2. Display Books\n");
 printf("3. Search Book\n");
 printf("4. Delete Book\n");
 printf("5. Add Student\n");
 printf("6. Issue Book\n");
 printf("7. Return Book\n");
 printf("8. Display Transactions\n");
 printf("9. Exit\n");
 printf("Enter choice: ");
 scanf("%d", &choice);
 switch (choice) {
 case 1: addBook(); break;
 case 2: displayBooks(); break;
 case 3: searchBook(); break;
 case 4: deleteBook(); break;
 case 5: addStudent(); break;
 case 6: issueBook(); break;
 case 7: returnBook(); break;
 case 8: displayTransactions(); break;
 case 9: exit(0);
 default: printf("Invalid choice!\n");
 }
 }
}
// ================= LOGIN =================
int login() {
 char user[20], pass[20];
 printf("Username: ");
 scanf("%s", user);
 printf("Password: ");
 scanf("%s", pass);
 if (strcmp(user, "admin") == 0 && strcmp(pass, "1234") == 0)
 return 1;
 return 0;
}
// ================= ADD BOOK =================
void addBook() {
 FILE *fp = fopen("books.csv", "a");
 int id, qty;
 char name[50], author[50];
 printf("Enter Book ID: ");
 scanf("%d", &id);
 printf("Enter Book Name: ");
 scanf(" %[^\n]", name);
 printf("Enter Author: ");
 scanf(" %[^\n]", author);
 printf("Enter Quantity: ");
 scanf("%d", &qty);
 fprintf(fp, "%d,%s,%s,%d\n", id, name, author, qty);
 fclose(fp);
 printf("Book Added Successfully!\n");
}
// ================= DISPLAY BOOKS =================
void displayBooks() {
 FILE *fp = fopen("books.csv", "r");
 int id, qty;
 char name[50], author[50];
 printf("\nID\tName\t\tAuthor\t\tQty\n");
 printf("---------------------------------------------\n");
 while (fscanf(fp, "%d,%[^,],%[^,],%d\n",&id, name, author, &qty) != EOF) {
 printf("%d\t%s\t\t%s\t\t%d\n", id, name, author, qty);
 }
 fclose(fp);
}
// ================= SEARCH BOOK =================
void searchBook() {
 FILE *fp = fopen("books.csv", "r");
 int id, qty, searchId, found = 0;
 char name[50], author[50];
 printf("Enter Book ID to search: ");
 scanf("%d", &searchId);
 while (fscanf(fp, "%d,%[^,],%[^,],%d\n",&id, name, author, &qty) != EOF) {
 if (id == searchId) {
 printf("\nBook Found!\n");
 printf("ID: %d\nName: %s\nAuthor: %s\nQty: %d\n",
 id, name, author, qty);
 found = 1;
 break;
 }
 }
 if (!found)
 printf("Book not found!\n");
 fclose(fp);
}
// ================= DELETE BOOK =================
void deleteBook() {
 FILE *fp = fopen("books.csv", "r");
 FILE *temp = fopen("temp.csv", "w");
 int id, qty, deleteId, found = 0;
 char name[50], author[50];
 printf("Enter Book ID to delete: ");
 scanf("%d", &deleteId);
 while (fscanf(fp, "%d,%[^,],%[^,],%d\n",&id, name, author, &qty) != EOF) {
 if (id == deleteId) {
 found = 1;
 printf("Book Deleted Successfully!\n");
 continue;
 }
 fprintf(temp, "%d,%s,%s,%d\n", id, name, author, qty);
 }
 fclose(fp);
 fclose(temp);
 remove("books.csv");
 rename("temp.csv", "books.csv");
 if (!found)
 printf("Book not found!\n");
}
// ================= ADD STUDENT =================
void addStudent() {
 FILE *fp = fopen("students.csv", "a");
 int id;
 char name[50];
 printf("Enter Student ID: ");
 scanf("%d", &id);
 printf("Enter Student Name: ");
 scanf(" %[^\n]", name);
 fprintf(fp, "%d,%s\n", id, name);
 fclose(fp);
 printf("Student Added Successfully!\n");
}
// ================= ISSUE BOOK =================
void issueBook() {
 FILE *fp = fopen("transactions.csv", "a");
 int sid, bid;
 char date[20];
 printf("Enter Student ID: ");
 scanf("%d", &sid);
 printf("Enter Book ID: ");
 scanf("%d", &bid);
 printf("Enter Issue Date (DD-MM-YY): ");
 scanf("%s", date);
 fprintf(fp, "%d,%d,%s,NOT_RETURNED\n", sid, bid, date);
 fclose(fp);
 printf("Book Issued Successfully!\n");
}
// ================= RETURN BOOK =================
void returnBook() {
 FILE *fp = fopen("transactions.csv", "r");
 FILE *temp = fopen("temp.csv", "w");
 int sid, bid;
 char rdate[20];
 printf("Enter Student ID: ");
 scanf("%d", &sid);
 printf("Enter Book ID: ");
 scanf("%d", &bid);
 printf("Enter Return Date (DD-MM-YY): ");
 scanf("%s", rdate);
 int s, b;
 char idate[20], ret[20];
 while (fscanf(fp, "%d,%d,%[^,],%s\n",&s, &b, idate, ret) != EOF) {
 if (s == sid && b == bid && strcmp(ret, "NOT_RETURNED") == 0) {
 fprintf(temp, "%d,%d,%s,%s\n", s, b, idate, rdate);
 printf("\nBook Returned Successfully!\n");
 printf("Fine: Rs. 20 (Demo)\n");
 } else {
 fprintf(temp, "%d,%d,%s,%s\n", s, b, idate, ret);
 }
 }
 fclose(fp);
 fclose(temp);
 remove("transactions.csv");
 rename("temp.csv", "transactions.csv");
}
// ================= DISPLAY TRANSACTIONS =================
void displayTransactions() {
 FILE *fp = fopen("transactions.csv", "r");
 int sid, bid;
 char issue[20], ret[20];
 printf("\nStudentID\tBookID\tIssueDate\tReturnDate\n");
 printf("-----------------------------------------------------------\n");
 while (fscanf(fp, "%d,%d,%[^,],%s\n",&sid, &bid, issue, ret) != EOF)
printf("%d\t\t%d\t%s\t\t%s\n", sid, bid, issue, ret);
 }
 fclose(fp);
}