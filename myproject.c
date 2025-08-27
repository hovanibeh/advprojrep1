#include <stdio.h>		// Standard I/O
#include <stdlib.h>
#include <string.h>		// String library
#include <ctype.h>// Character type functions
#include <conio.h>//
} Passenger;


// Login s
typedef struct Login {
	char username[20]; //added username field
	char password[10]; //added password field
	struct Login* next;// pointer to next login
} Login;


Passenger* head = NULL;
Login* loginHead = NULL;


// these are my named fuctions 
void loadPassengers();// Load passenger file
void savePassengers();
void addPassenger();
void displayAll();
void displayOne();
void updatePassenger();
void deletePassenger();
void generateStats();
void report();
void listByYear();
int login();


// Helper validation
int validateEmail(const char* email) {
	return (strstr(email, "@") && strstr(email, ".") && strstr(email, ".com"));
}


// Password masking input
void getPassword(char* pass, int size) {
	int i = 0;
	char ch;
	while (i < size - 1) {
		ch = getch();
		if (ch == '\n' || ch == '\r') break;
		if (ch == '\b' && i > 0) {
			i--;
			printf("\b \b");
			continue;
		}
		if (isprint(ch)) {
			pass[i++] = ch;
			printf("*");
		}
	}
	pass[i] = '\0';
}


// Load login file
void loadLogins() {
	FILE* fp = fopen("login.txt", "r");
	if (!fp) {
		fp = fopen("login.txt", "w");
		fprintf(fp, "admin secret\nmanager qwerty\nuser01 abc123\n");
		fclose(fp);
		fp = fopen("login.txt", "r");
	}
	Login* temp, * last = NULL;
	while (!feof(fp)) {
		temp = (Login*)malloc(sizeof(Login));
		if (fscanf(fp, "%s %s", temp->username, temp->password) == 2) {
			temp->next = NULL;
			if (!loginHead) loginHead = temp;
			else last->next = temp;
			last = temp;
		}
		else free(temp);
	}
	fclose(fp);
}
