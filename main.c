#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define LONGITUDE 6 /* j */
#define LATITUDE  5 /* i */

void open_map (int rows, int columns, int map[LATITUDE][LONGITUDE], FILE* f) {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            fscanf(f, "%d", &map[i][j]);
        }
    }
}

// Считает все двойки и заменяет их нулями
int calculate_area (int rows, int columns, int map[LATITUDE][LONGITUDE]) {

    int count = 0;

    for (int x = 0; x < rows; x++) {

        for (int y = 0; y < columns; y++) {

            if (map[x][y] == 2) {

                count++;

                map[x][y] = 0;
            }

            /*for (int i = 0; i < LATITUDE; i++) {
                printf("\n");
                for (int j = 0; j < LONGITUDE; j++) {
                    printf("%d ", map[i][j]);
                }
            }
            printf("\n");/*/

        }
    }

    return count;
}


// находит связные куски суши и делает их двойками
int detect_area(int rows, int columns, int map[LATITUDE][LONGITUDE]) {

    int flag = 0;  // Нужна для случаев когда у нас единица площади

    int flag2 = 0;

    int is_over = 0;

    for (int x = 0; x < rows; x++) {

        for (int y = 0; y < columns; y++) {

            if ((map[x][y] == 1)) {   // Находим первую единичку острова и превращаем её в 2;
                map[x][y] = 2;
                flag = 1;
                break;      
            }
        }

        if (flag == 1) {
            break;
        }

    }   

    // Цикл заполняет двойками остров
    while (is_over != 1) {

        flag2 = 0;

        for (int x = 0; x < rows; x++) {

            for (int y = 0; y < columns; y++) {
                
                // Находим двойку
                if ((map[x][y] == 2)) {
                    
                    // Превращаем все единиицы рядом с двойкой в двойки
                    if (map[x + 1][y] == 1) {
                        map[x + 1][y] = 2;
                        flag2 = 1;
                    }

                    if (map[x - 1][y] == 1) {
                        map[x - 1][y] = 2;
                        flag2 = 1;
                    }
                    
                    if (map[x][y + 1] == 1) {
                        map[x][y + 1] = 2;                  
                        flag2 = 1;
                    }                

                    if (map[x][y - 1] == 1) {
                        map[x][y - 1] = 2;
                        flag2 = 1;
                    }  
                }
            }
        }

        // Если не попали ни в одно из условий выше, значит весь остров уже заполнен двойками
        if (flag2 != 1) {
            is_over = 1;
        }
    }

    // Если пришла хотя бы одна единица, то подсчитываем двойки и выводим
    if ((flag == 1)) {
        printf("\nArea of Island = %d\n", calculate_area(rows, columns, map));
        return 1;
    }

    // Иначе все площади уже посчитаны
    else {
        return 0;
    }

}


void main(void) {

    FILE *f;

    int map[LATITUDE][LONGITUDE];
 
    f = fopen("map.txt", "r");

    open_map(LATITUDE, LONGITUDE, map, f);

    while (detect_area(LATITUDE, LONGITUDE, map) != 0);

    fclose(f);

}