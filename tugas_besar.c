#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define RED_TEXT   "\x1b[31m"
#define GREEN_TEXT "\x1b[32m"
#define YELLOW_TEXT "\x1b[33m"
#define BLUE_TEXT  "\x1b[34m"
#define CYAN_TEXT "\x1b[36m"
#define RESET_TEXT "\x1b[0m"
#define FILE_NAME "listTugas.txt"


struct Task {
    char title[50];
    char description[100];
    int isCompleted;
    char deadline[20];
};

void displayMenu() {
    printf(CYAN_TEXT "\n=================================================================================================================\n" RESET_TEXT);
    printf(" 1.");
    printf(YELLOW_TEXT " Tambah Tugas                                                                                             \n" RESET_TEXT);
    printf(CYAN_TEXT "=================================================================================================================\n" RESET_TEXT);
    printf(" 2.");
    printf(YELLOW_TEXT " Tampilkan Tugas                                                                                          \n" RESET_TEXT);
    printf(CYAN_TEXT "=================================================================================================================\n" RESET_TEXT);
    printf(" 3.");
    printf(YELLOW_TEXT " Hapus Tugas                                                                                              \n" RESET_TEXT);
    printf(CYAN_TEXT "=================================================================================================================\n" RESET_TEXT);
    printf(" 4.");
    printf(YELLOW_TEXT " Tandai Selesai                                                                                           \n" RESET_TEXT);
    printf(CYAN_TEXT "=================================================================================================================\n" RESET_TEXT);
    printf(" 5.");
    printf(YELLOW_TEXT " Tampilkan Tugas Selesai                                                                                  \n" RESET_TEXT);
    printf(CYAN_TEXT "=================================================================================================================\n" RESET_TEXT);
    printf(" 6.");
    printf(YELLOW_TEXT " Tampilkan Tugas Berdasarkan Deadline                                                                     \n" RESET_TEXT);
    printf(CYAN_TEXT "=================================================================================================================\n" RESET_TEXT);
    printf(" 7.");
    printf(YELLOW_TEXT " Keluar                                                                                                   \n" RESET_TEXT);
    printf(CYAN_TEXT "=================================================================================================================\n" RESET_TEXT);
}

void displayTask(struct Task task, int taskNumber) {
    printf(" %d.", taskNumber);
    printf(" %s \n", task.isCompleted ? GREEN_TEXT "[Selesai]   " RESET_TEXT : RED_TEXT "[Belum Selesai]" RESET_TEXT);
    printf("    Judul: %s\n", task.title);
    printf("    Deskripsi: %s\n", task.description);
    if (strlen(task.deadline) > 0) {
        printf("    Deadline: %s", task.deadline);
    }
    printf(CYAN_TEXT "\n.................................................................................................................\n" RESET_TEXT);
}

void saveTaskToFile(struct Task task) {
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Error: Gagal membuka file untuk penulisan.\n");
        exit(1);
    }

    fprintf(file, "%d;%s;%s;%s\n", task.isCompleted, task.title, task.description, task.deadline);

    fclose(file);
}

void saveTasksToFile(struct Task tasks[], int totalTasks) {
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Error: Gagal membuka file untuk penulisan.\n");
        exit(1);
    }

    for (int i = 0; i < totalTasks; i++) {
        fprintf(file, "%d;%s;%s;%s\n", tasks[i].isCompleted, tasks[i].title, tasks[i].description, tasks[i].deadline);
    }

    fclose(file);
}

void loadTasksFromFile(struct Task tasks[], int *totalTasks) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        return;
    }

    while (fscanf(file, "%d;%49[^;];%99[^;];%19[^\n]\n", &tasks[*totalTasks].isCompleted, tasks[*totalTasks].title, tasks[*totalTasks].description, tasks[*totalTasks].deadline) == 4) {
        (*totalTasks)++;
        if (*totalTasks >= MAX_TASKS) {
            break;
        }
    }

    fclose(file);
}

int main() {
    struct Task tasks[MAX_TASKS];
    int totalTasks = 0;

    loadTasksFromFile(tasks, &totalTasks);

    printf(YELLOW_TEXT "  _   _   _  ___  _     _____ _____   _    __  ___       _  _    _      _______  _  _____  _   _    _    _  ____       \n");
    printf(" | | | | | ||  _|| |   | ___||  __  || |  /  ||  _|     | || |  | |    |__   __|| ||  _  /| |_| |  | |  | ||  _ |      \n");
    printf(" | |_| |/  ||  _|| |__ | |__ | |__| ||  |/   ||  _|     | ||  |_| |       | |   | || |_| / |   |   | |__| ||  __|      \n");
    printf(" |___/|___/ |___||____||____||______||_|\_/|__||___|     |_||_|  |_|       |_|   |_||____/   |_|    |______||_|         \n" RESET_TEXT);


    while (1) {
        displayMenu();

        int choice;
        printf(YELLOW_TEXT "                                                                                            PILIH MENU (1-7): " RESET_TEXT);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (totalTasks < MAX_TASKS) {
                    printf(CYAN_TEXT "\n................................................." RESET_TEXT);
                    printf(YELLOW_TEXT " [TAMBAH TUGAS] " RESET_TEXT);
                    printf(CYAN_TEXT "................................................\n" RESET_TEXT);
                    printf(" - ");
                    printf(YELLOW_TEXT " Judul: " RESET_TEXT);
                    scanf(" %[^\n]", tasks[totalTasks].title);
                    printf(" - ");
                    printf(YELLOW_TEXT " Deskripsi: " RESET_TEXT);
                    scanf(" %[^\n]", tasks[totalTasks].description);
                    printf(" - ");
                    printf(YELLOW_TEXT " Deadline (dd/mm/yyyy): " RESET_TEXT);
                    scanf("%s", tasks[totalTasks].deadline);
                    tasks[totalTasks].isCompleted = 0;
                    totalTasks++;
                    saveTaskToFile(tasks[totalTasks - 1]);
                    printf(GREEN_TEXT "........................................... Tugas Berhasil Ditambahkan ..........................................\n" RESET_TEXT);
                } else {
                    printf(RED_TEXT ".....................................Maaf, jumlah maksimum tugas telah tercapai....................................\n" RESET_TEXT);
                }
                break;

            case 2:
                if (totalTasks > 0) {
                    printf(CYAN_TEXT "\n................................................." RESET_TEXT);
                    printf(YELLOW_TEXT " [DAFTAR TUGAS] " RESET_TEXT);
                    printf(CYAN_TEXT "................................................\n" RESET_TEXT);
                    for (int i = 0; i < totalTasks; i++) {
                        displayTask(tasks[i], i + 1);
                    }
                } else {
                    printf(RED_TEXT "Tidak ada tugas yang tersedia.\n" RESET_TEXT);
                }
                break;

            case 3:
                if (totalTasks > 0) {
                    printf(CYAN_TEXT "\n................................................." RESET_TEXT);
                    printf(YELLOW_TEXT " [HAPUS TUGAS] " RESET_TEXT);
                    printf(CYAN_TEXT ".................................................\n" RESET_TEXT);
                    printf(" -  ");
                    printf(YELLOW_TEXT "Masukkan nomor tugas yang ingin dihapus: " RESET_TEXT);
                    int taskNumber;
                    scanf("%d", &taskNumber);
                    if (taskNumber >= 1 && taskNumber <= totalTasks) {
                        for (int i = taskNumber - 1; i < totalTasks - 1; i++) {
                            tasks[i] = tasks[i + 1];
                        }
                        totalTasks--;
                        saveTasksToFile(tasks, totalTasks);
                        printf(GREEN_TEXT "\n............................................. Tugas Berhasil Dihapus ............................................\n" RESET_TEXT);
                    } else {
                        printf(RED_TEXT "\n............................................ Nomor tugas tidak valid ............................................\n" RESET_TEXT);
                    }
                } else {
                    printf(RED_TEXT "Tidak ada tugas yang tersedia.\n" RESET_TEXT);
                }
                break;

            case 4:
                if (totalTasks > 0) {
                    int taskNumber;
                    printf(CYAN_TEXT "\n................................................" RESET_TEXT);
                    printf(YELLOW_TEXT " [TANDAI TUGAS] " RESET_TEXT);
                    printf(CYAN_TEXT ".................................................\n" RESET_TEXT);
                    printf(" -  ");
                    printf(YELLOW_TEXT "Masukkan nomor tugas yang ingin ditandai selesai: " RESET_TEXT);
                    scanf("%d", &taskNumber);
                    if (taskNumber >= 1 && taskNumber <= totalTasks) {
                        tasks[taskNumber - 1].isCompleted = 1;
                        saveTasksToFile(tasks, totalTasks);
                        printf(GREEN_TEXT "\n........................................ Tugas berhasil ditandai selesai ........................................\n" RESET_TEXT);
                    } else {
                        printf(RED_TEXT "\n............................................ Nomor tugas tidak valid ............................................\n" RESET_TEXT);
                    }
                } else {
                    printf(RED_TEXT "Tidak ada tugas yang tersedia.\n" RESET_TEXT);
                }
                break;

            case 5:
                if (totalTasks > 0) {
                    printf(CYAN_TEXT "\n................................................" RESET_TEXT);
                    printf(YELLOW_TEXT " [TUGAS SELESAI] " RESET_TEXT);
                    printf(CYAN_TEXT "................................................\n" RESET_TEXT);
                    for (int i = 0; i < totalTasks; i++) {
                        if (tasks[i].isCompleted) {
                            displayTask(tasks[i], i + 1);
                        }
                    }
                } else {
                    printf(RED_TEXT "Tidak ada tugas yang tersedia.\n" RESET_TEXT);
                }
                break;

            case 6:
                if (totalTasks > 0) {
                    char tempDeadline[20];
                    printf(CYAN_TEXT "\n..............................................." RESET_TEXT);
                    printf(YELLOW_TEXT " [DEADLINE TUGAS] " RESET_TEXT);
                    printf(CYAN_TEXT "................................................\n" RESET_TEXT);
                    printf(" -  ");
                    printf(YELLOW_TEXT "Masukkan deadline yang ingin ditampilkan (dd/mm/yyyy): " RESET_TEXT);
                    scanf("%s", tempDeadline);
                    printf(CYAN_TEXT "-----------------------------------------------------------------------------------------------------------------" RESET_TEXT);

                    printf("\n -  ");
                    printf(YELLOW_TEXT "Tugas dengan Deadline: " RESET_TEXT);
                    printf(BLUE_TEXT "%s \n" RESET_TEXT, tempDeadline);
                    for (int i = 0; i < totalTasks; i++) {
                        if (strcmp(tasks[i].deadline, tempDeadline) == 0) {
                            displayTask(tasks[i], i + 1);
                        }
                    }
                } else {
                    printf(RED_TEXT "Tidak ada tugas yang tersedia.\n" RESET_TEXT);
                }
                break;

            case 7:
                printf(YELLOW_TEXT " ___  _   _  ___     ___  _   _  ___  \n");
                printf("|   || |_| ||  _|   |   || |_| ||  _| \n");
                printf("|  <  |   | |  _|   |  <  |   | |  _| \n");
                printf("|___|  |_|  |___|   |___|  |_|  |___| \n" RESET_TEXT);
                exit(0);

            default:
                printf(RED_TEXT "Pilihan tidak valid. Masukkan angka antara 1 dan 7.\n" RESET_TEXT);
        }
    }

    return 0;
}
