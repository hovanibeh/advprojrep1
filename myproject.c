// hovanibeh.c
// Simple student-style passenger system with login, files, linked list, and report
// Updated for 4 passengers: Hovan Ibeh, Martin Hynes, Tai Davies, Clinton Imade
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // getch() for password masking
// ---- Login structure ----
typedef struct {
    char username[20];
    char password[20];
} Login;
Login logins[3]; // we have 3 login records in login.txt
// ---- Passenger node (linked list) ----
typedef struct Passenger {
    int pps;                // PPS number
    char fname[30];         // first name
    char lname[30];         // last name
    int year;               // year born
    char email[50];         // email
    char area[20];          // area travelled from
    char tclass[20];        // travel class
    char trips[40];         // trips per year
    struct Passenger* next; // pointer to next node
} Passenger;
Passenger* head = NULL; // start of linked list
// ---- EXPLANATION COMMENTS ----
// strcmp(a,b) = compares two strings, returns 0 if same
// malloc(n) = allocates memory, must free later
// free(ptr) = frees memory
// p->next = pointer to next element in struct
// fopen/fprintf/fclose = file I/O functions
// ----------------- LOGIN FUNCTIONS -----------------
void loadLogins() { /* same as before */ }
int login() { /* same as before */ }
// ----------------- FILE LOAD / SAVE -----------------
void loadPassengers() {
    // Load 4 passengers from passenger.txt
    // Hovan Ibeh, Martin Hynes, Tai Davies, Clinton Imade
    FILE* f = fopen("passenger.txt", "r");
    if (!f) return;
    while (1) {
        Passenger* p = malloc(sizeof(Passenger));
        int r = fscanf(f, "%d %29s %29s %d %49s %19s %19s %39s",
            &p->pps, p->fname, p->lname, &p->year,
            p->email, p->area, p->tclass, p->trips);
        if (r == 8) {
            p->next = head;
            head = p;
        }
        else {
            free(p);
            break;
        }
    }
    fclose(f);
}
void savePassengers() { /* same as before */ }
// ----------------- LIST FUNCTIONS -----------------
void addPassenger() { /* same as before */ }
void displayAll() { /* same as before */ }
Passenger* findPassenger(int pps) { /* same as before */ }
void updatePassenger() { /* same as before */ }
void deletePassenger() { /* same as before */ }
// ----------------- STATISTICS -----------------
void stats() {
    // Shows % of passengers from each area
    int d = 0, l = 0, cnt = 0, u = 0, m = 0, tot = 0;
    Passenger* t = head;
    while (t) {
        if (strcmp(t->area, "Dublin") == 0) d++;
        else if (strcmp(t->area, "Leinster") == 0) l++;
        else if (strcmp(t->area, "Connacht") == 0) cnt++;
        else if (strcmp(t->area, "Ulster") == 0) u++;
        else if (strcmp(t->area, "Munster") == 0) m++;
        tot++;
        t = t->next;
    }
    if (tot == 0) { printf("No data\n"); return; }
    printf("Dublin: %.1f%%\n", d * 100.0 / tot);
    printf("Leinster: %.1f%%\n", l * 100.0 / tot);
    printf("Connacht: %.1f%%\n", cnt * 100.0 / tot);
    printf("Ulster: %.1f%%\n", u * 100.0 / tot);
    printf("Munster: %.1f%%\n", m * 100.0 / tot);
}
// ----------------- REPORT -----------------
void printReport() {
    // Generates report.txt with all 4 passengers
    FILE* f = fopen("report.txt", "w");
    if (!f) { printf("Could not open report.txt\n"); return; }
    fprintf(f, "Rail Ireland Passenger Report\n");
    fprintf(f, "=============================\n\n");
    if (!head) { fprintf(f, "No passengers.\n"); fclose(f); return; }
    Passenger* t = head;
    int total = 0;
    while (t) {
        fprintf(f, "PPS: %d | %s %s | YOB: %d | %s | From: %s | Class: %s | Trips: %s\n",
            t->pps, t->fname, t->lname, t->year,
            t->email, t->area, t->tclass, t->trips);
        total++;
        t = t->next;
    }
    fprintf(f, "\nTotal passengers: %d\n\n", total);
    // statistics by area
    int d = 0, l = 0, cnt = 0, u = 0, m = 0;
    t = head;
    while (t) {
        if (strcmp(t->area, "Dublin") == 0)d++;
        else if (strcmp(t->area, "Leinster") == 0)l++;
        else if (strcmp(t->area, "Connacht") == 0)cnt++;
        else if (strcmp(t->area, "Ulster") == 0)u++;
        else if (strcmp(t->area, "Munster") == 0)m++;
        t = t->next;
    }
    if (total > 0) {
        fprintf(f, "Statistics (by area):\n");
        fprintf(f, "Dublin: %.1f%%\n", d * 100.0 / total);
        fprintf(f, "Leinster: %.1f%%\n", l * 100.0 / total);
        fprintf(f, "Connacht: %.1f%%\n", cnt * 100.0 / total);
        fprintf(f, "Ulster: %.1f%%\n", u * 100.0 / total);
        fprintf(f, "Munster: %.1f%%\n", m * 100.0 / total);
    }
    fclose(f);
    printf("Report written to report.txt\n");
}
// ----------------- MAIN -----------------
int main() {
    loadLogins();
    if (!login()) return 0;
    loadPassengers();
    int ch;
    do {
        printf("\n1.Add 2.Display 3.Update 4.Delete 5.Stats 6.PrintReport 0.Exit\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1)addPassenger();
        else if (ch == 2)displayAll();
        else if (ch == 3)updatePassenger();
        else if (ch == 4)deletePassenger();
        else if (ch == 5)stats();
        else if (ch == 6)printReport();
    } while (ch != 0);
    savePassengers(); // save before exit
    return 0;
}