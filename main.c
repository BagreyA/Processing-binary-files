#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct train {
    char destination[50];
    int number;
    int departure_time[2];
};

int main() {
    FILE *fp;
    char filename[50];
    int choice;

    do {
        printf("Выберите действие:\n");
        printf("1. Добавить запись в файл или начать запись нового файла.\n");
        printf("2. Начать обработку существующего файла.\n");
        printf("3. Выйти из программы.\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите имя файла: ");
                scanf("%s", filename);
                fp = fopen(filename, "ab");
                if (fp == NULL) {
                    printf("Ошибка при создании файла\n");
                    return 1;
                }
                struct train new_train;
                printf("Введите данные о новом поезде:\n");
                printf("Название пункта назначения: ");
                scanf("%s", new_train.destination);
                printf("Номер поезда: ");
                scanf("%d", &new_train.number);
                printf("Время отправления в формате ЧЧ ММ: ");
                scanf("%d %d", &new_train.departure_time[0], &new_train.departure_time[1]);
                fwrite(&new_train, sizeof(struct train), 1, fp);
                fclose(fp);
                printf("Запись добавлена в файл.\n");
                break;

            case 2:
                printf("Введите имя файла: ");
                scanf("%s", filename);
                fp = fopen(filename, "rb");
                if (fp == NULL) {
                    printf("Ошибка при открытии файла\n");
                    return 1;
                }
                int input_time[2];
                printf("Введите время в формате ЧЧ ММ: ");
                scanf("%d %d", &input_time[0], &input_time[1]);
                struct train current_train;
                int found_train = 0;
                while (fread(&current_train, sizeof(struct train), 1, fp) != 0) {
                    if (current_train.departure_time[0] > input_time[0] ||
                        (current_train.departure_time[0] == input_time[0] && current_train.departure_time[1] == input_time[1])) {
                        printf("Поезд №%d %s отправляется в %02d:%02d\n", current_train.number,
                               current_train.destination, current_train.departure_time[0], current_train.departure_time[1]);
                        found_train = 1;
                    }
                }
                if (!found_train) {
                    printf("Поезда, отправляющегося после указанного времени, не найдено.\n");
                }
                fclose(fp);
                break;

            case 3:
                printf("До свидания!\n");
                break;

            default:
                printf("Неверный выбор. Попробуйте снова.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
