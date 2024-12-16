#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Student {
    char soyad[15];
    char ad[15];
    int il;
    char qrup[10];
    struct Student *next;
} Student;

Student *readFromFile(const char *filename);
void writeToFile(const char *filename, Student *head);
Student *addStudent(Student *head);
Student *deleteStudent(Student *head);
void displayStudents(Student *head);
void displayByGroup(Student *head);
void freeList(Student *head);
int getSize(Student *head);

int main() {
    Student *head = NULL;
    head = readFromFile("students.txt");

    int choice;
    while (true) {
        printf("\n===============================\n");
        printf("1. Yeni tələbə əlavə et\n");
        printf("2. Tələbəni sil\n");
        printf("3. Qrupa görə tələbələri göstər\n");
        printf("4. Siyahını fayla yaz\n");
        printf("5. Çıxış\n");
        printf("===============================\n");
        printf("Seçiminizi daxil edin: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                head = addStudent(head);
                break;
            case 2:
                head = deleteStudent(head);
                break;
            case 3:
                displayByGroup(head);
                break;
            case 4:
                writeToFile("students.txt", head);
                break;
            case 5:
                freeList(head);
                printf("Proqram bitdi.\n");
                return 0;
            default:
                printf("Yanlış seçim!\n");
        }
    }
}

Student *readFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Fayl açılmadı. Yeni siyahı yaradılacaq.\n");
        return NULL;
    }

    Student *head = NULL, *current = NULL;
    while (true) {
        Student *newStudent = malloc(sizeof(Student));
        if (!newStudent) {
            printf("Yaddaş ayrılmadı!\n");
            return head;
        }
        if (fscanf(file, "%s %s %d %s", newStudent->soyad, newStudent->ad, &newStudent->il, newStudent->qrup) == EOF) {
            free(newStudent);
            break;
        }
        newStudent->next = NULL;
        if (!head) {
            head = newStudent;
        } else {
            current->next = newStudent;
        }
        current = newStudent;
    }
    fclose(file);
    return head;
}

void writeToFile(const char *filename, Student *head) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Fayla yazılarkən xəta baş verdi!\n");
        return;
    }
    Student *current = head;
    while (current) {
        fprintf(file, "%s %s %d %s\n", current->soyad, current->ad, current->il, current->qrup);
        current = current->next;
    }
    fclose(file);
    printf("Fayla yazıldı.\n");
}

Student *addStudent(Student *head) {
    Student *newStudent = malloc(sizeof(Student));
    if (!newStudent) {
        printf("Yaddaş ayrılmadı!\n");
        return head;
    }

    printf("Tələbənin melumatlarını daxil edin (Soyad Ad İl Qrup): ");
    scanf("%s %s %d %s", newStudent->soyad, newStudent->ad, &newStudent->il, newStudent->qrup);
    newStudent->next = head;

    printf("Tələbə siyahıya əlavə edildi.\n");
    return newStudent;
}

Student *deleteStudent(Student *head) {
    if (!head) {
        printf("Siyahı boşdur.\n");
        return NULL;
    }

    char soyad[15], ad[15];
    printf("Silinəcək tələbənin Soyadını və Adını daxil edin: ");
    scanf("%s %s", soyad, ad);

    Student *current = head, *previous = NULL;
    while (current) {
        if (strcmp(current->soyad, soyad) == 0 && strcmp(current->ad, ad) == 0) {
            if (previous) {
                previous->next = current->next;
            } else {
                head = current->next;
            }
            free(current);
            printf("Tələbə silindi.\n");
            return head;
        }
        previous = current;
        current = current->next;
    }
    printf("Belə bir tələbə tapılmadı.\n");
    return head;
}

void displayStudents(Student *head) {
    if (!head) {
        printf("Siyahı boşdur.\n");
        return;
    }
    printf("\nTələbə siyahısı:\n");
    Student *current = head;
    while (current) {
        printf("%s %s %d %s\n", current->soyad, current->ad, current->il, current->qrup);
        current = current->next;
    }
}

void displayByGroup(Student *head) {
    if (!head) {
        printf("Siyahı boşdur.\n");
        return;
    }

    char group[10];
    printf("Qrup nömrəsini daxil edin: ");
    scanf("%s", group);

    printf("\n%s qrupundakı tələbələr:\n", group);
    Student *current = head;
    bool found = false;
    while (current) {
        if (strcmp(current->qrup, group) == 0) {
            printf("%s %s %d %s\n", current->soyad, current->ad, current->il, current->qrup);
            found = true;
        }
        current = current->next;
    }
    if (!found) {
        printf("Bu qrupda tələbə yoxdur.\n");
    }
}

void freeList(Student *head) {
    while (head) {
        Student *temp = head;
        head = head->next;
        free(temp);
    }
}
