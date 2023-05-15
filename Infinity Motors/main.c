#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "file_handler.h"

#define SLEEP_TIME 2
#define MAX_ROWS 350
#define MAX_COLUMNS 350
#define MAX_LENGTH 350

void gotoxy(int x, int y){
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

void logo (){

    gotoxy(34, 6);
    printf("      OOOOOOOOOOO                   OOOOOOOOOOO");
    gotoxy(34, 7);
    printf("    OOOOOOOOOOOOOOOO             OOOOOOOOOOOOOOOOO");
    gotoxy(34, 8);
    printf("  OOOOO        .OOOOO           OOOOO        .OOOOO");
    gotoxy(34, 9);
    printf(" OOO              .OOOO       OOOO              .OOO");
    gotoxy(34, 10);
    printf("OO                  .OOOO   OOOO                  .OO");
    gotoxy(34, 11);
    printf("OO                    .OOOOOOO                     OO");
    gotoxy(34, 12);
    printf("OO                     OOOOOOO                     OO");
    gotoxy(34, 13);
    printf("OO                   OOOO . OOOO                   OO");
    gotoxy(34, 14);
    printf(".OOO               OOOO     . OOOO               OOO");
    gotoxy(34, 15);
    printf(" .OOOOO         OOOOO         . OOOOO         OOOOO");
    gotoxy(34, 16);
    printf("   .OOOOOOOOOOOOOOOO            .OOOOOOOOOOOOOOOOO");
    gotoxy(34, 17);
    printf("     .OOOOOOOOOOO                 . OOOOOOOOOOO");
    gotoxy(34, 18);
    printf("       .........                    ..........");
    gotoxy(34, 20);
    printf("                 - A u t o S o f t -");
    gotoxy(0, 24);
    sleep(SLEEP_TIME);

}

void presentation (){
    sleep(SLEEP_TIME);
    gotoxy(47, 11);
    printf("Somos Infinity Motors");
    gotoxy(47, 12);
    printf("Version: 1.0.0");
    gotoxy(47, 13);
    printf("By Alan Ricardo Alvarado Ahedo");
    gotoxy(47, 14);
    printf("Ingeneria en Computacion");
    gotoxy(47, 15);
    printf("Programacion Estructurada");
    sleep(SLEEP_TIME);
}

int validate_user (char user[30], char password[30]){
    char filename[] = "sources/employees/users.csv";
    struct csv csv = read_csv(filename);

    for (int i = 0 ; i < csv.n_rows ; i++){
        if ((strcmp(user, csv.data[i][1]) == 0) && (strcmp(password, csv.data[i][2]) == 0)){
            return atoi(csv.data[i][0]);
        }
    }
    return 0;
}

int login (){
    char user[30], password[30];
    int user_id;

    gotoxy(53, 12);
    printf("Iniciemos sesion\n");

    do{
        gotoxy(53, 13);
        printf("Usuario: ");
        scanf("%s", &user);
        gotoxy(53, 14);
        printf("Contrasena: ");
        scanf("%s", &password);
        system("cls");
        gotoxy(53, 12);
        printf("Usuario y/o contrasena erroneo\n");

        user_id = validate_user(user, password);
    }
    while (user_id == 0);

    system("cls");
    gotoxy(50, 13);
    printf("Inicio de sesion exitoso\n");
    gotoxy(50, 14);
    printf("ID de usuario: %i", user_id);
    sleep(SLEEP_TIME);
    system("cls");

    return 1;
}

int main(){
    /*char user_type;

    logo();
    system("cls");

    presentation();
    system("cls");

    user_type = login();

    if (user_type == 1){
            menu(user_type);
    }*/

    menu(1);

    return 0;
}

void menu (){
    char choice = 'a';

    do{
        gotoxy(50, 10);
        printf("Menu: ");
        gotoxy(50, 11);
        printf("A. Consultar inventario");

        gotoxy(50, 12);
        printf("B. Consultar bitacoras");

        gotoxy(50, 13);
        printf("C. Salir");

        gotoxy(50, 15);
        printf("Eleccion: ");
        scanf("%s", &choice);
        choice = tolower(choice);
        getchar();

        if (choice < 'a'  || choice > 'e'){
            gotoxy(50, 14);
            printf("Elige una opcion valida");
            sleep(SLEEP_TIME-1);
            system("cls");
        }

        else{
        switch (choice){
            case 'a':
                system("cls");
                gotoxy(50, 12);
                printf("Yendo a consultar inventario");
                system("cls");
                inventory_menu();
                break;

            case 'b':
                system("cls");
                gotoxy(50, 12);
                printf("Yendo a bitacoras");
                system("cls");
                log_menu();
                break;

            case 'c':
                system("cls");
                gotoxy(58, 13);
                printf("Saliendo");
                sleep(SLEEP_TIME);
                system("cls");
                exit(1);
                break;
        }}

    }
    while(choice < 'a'  || choice > 'e');
}

// CRUD: Create, Read, Update, Delete
void inventory_menu (){
    char path[MAX_LENGTH] = "";
    char choice;
    char brand[MAX_LENGTH];

    do{
        gotoxy(50, 11);
        printf("A. Inventario de cabeza");

        gotoxy(50, 12);
        printf("B. Inventario de monoblock");

        gotoxy(50, 13);
        printf("C. Regresar al menu principal");

        gotoxy(50, 14);
        printf("Eleccion: ");
        scanf("%s", &choice);

        if (choice < 'a'  || choice > 'd'){
            gotoxy(50, 14);
            printf("Elige una opcion valida");
            sleep(SLEEP_TIME-1);
            system("cls");
        }

        else{
            switch (choice){
                case 'a':
                    system("cls");
                    do{
                        gotoxy(47, 14);
                        printf("Inventario de cabeza:");

                        gotoxy(47, 15);
                        printf("Que marca necesitas consultar?: ");
                        scanf("%s", &brand);
                        getchar();

                        path[0] = '\0';
                        strcat(path, "sources/inventory/cabeza/");
                        strcat(path, brand);
                        strcat(path, ".csv");

                        system("cls");
                        gotoxy(47, 11);
                        printf("Esta marca no esta registrada");
                        gotoxy(47, 12);
                        printf("Prueba de nuevo");
                        gotoxy(47, 13);
                        printf("%s, %d", path, file_exist(path));
                    }
                    while(!(file_exist(path)));
                    inventory_consult(path);
                    break;

                case 'b':
                    system("cls");
                    gotoxy(47, 12);
                    printf("Inventario de monoblock:");

                    gotoxy(47, 13);
                    printf("Que marca necesitas consultar?: ");
                    scanf("%s", &brand);
                    getchar();

                    inventory_consult("monoblock/", brand);
                    break;

                case 'c':
                    system("cls");
                    gotoxy(47, 12);
                    printf("Regresando al menu principal");
                    sleep(SLEEP_TIME);
                    system("cls");
                    break;
            }
        choice = 'a';
        }
    }
    while (choice < 'a'  || choice > 'd');
}

void inventory_consult (char *path){
    char choice;
    int padx = 27, pady=5, i;

    struct csv csv = read_csv(path);

    do{
        system("cls");

        gotoxy(padx+0, pady+1);
        printf("Inventario:");

        gotoxy(padx+0, pady+3);
        printf("ID");

        gotoxy(padx+5, pady+3);
        printf("| NOMBRE DE PIEZA");

        gotoxy(padx+30, pady+3);
        printf("| MODELO");

        gotoxy(padx+50, pady+3);
        printf("| CANTIDAD DISPONIBLE");

        gotoxy(padx+0, pady+4);
        for (int i = 0 ; i <= 71 ; i++){
            printf("-");
        }

        for ( i = 0 ; i < csv.n_rows ; i++){
            gotoxy(padx+0, pady+i+5);
            printf("%s", csv.data[i][0]);

            gotoxy(padx+5, pady+i+5);
            printf("| %s", csv.data[i][1]);

            gotoxy(padx+30, pady+i+5);
            printf("| %s", csv.data[i][2]);

            gotoxy(padx+50, pady+i+5);
            printf("| %s", csv.data[i][3]);
        }
        gotoxy(padx, pady+i+7);
        printf("A. Reabastecer este inventario");
        gotoxy(padx, pady+i+8);
        printf("B. Eliminar producto");
        gotoxy(padx, pady+i+9);
        printf("C. Modificar datos (nombre, modelo y cantidad)");
        gotoxy(padx, pady+i+10);
        printf("D. Regresar al menu");
        gotoxy(padx, pady+i+11);
        printf("Respuesta: ");
        scanf("%c", &choice);

        if (choice < 'a'  || choice > 'd'){
                gotoxy(50, 14);
                printf("Elige una opcion valida");
                sleep(SLEEP_TIME-1);
                system("cls");
        }

        else{
            switch (choice){
                case 'a':
                    restock_inventory(path, csv.n_rows);
                    break;
                case 'b':
                    delete_inventory(path, csv.n_rows);
                    break;
                case 'c':
                    modify_invetory(path, csv.n_rows);
                    break;
                case 'd':
                    system("cls");
                    gotoxy(47, 12);
                    printf("Regresando al menu anterior");
                    sleep(SLEEP_TIME);
                    system("cls");
                    break;
            }
        }
        choice = 'a';
    }
    while(choice < 'a'  || choice > 'd');
}

void modify_invetory (char *filename, int max_id){
    char id[5];
    char sustitute[4][MAX_LENGTH];
    int num_id;

    system("cls");
    gotoxy(20, 13);
    printf("Dime el ID de la pieza que quieres modificar (1 al %i): (NUMERO) ", max_id);
    scanf("%s", &id);
    getchar();

    strcpy(sustitute[0], id);

    gotoxy(20, 14);
    printf("Nuevo nombre de la pieza que quieres modificar: (TEXTO) ");
    scanf("%[^\n]", &sustitute[1]);
    getchar();

    gotoxy(20, 15);
    printf("Nuevo nombre del modelo de la pieza que quieres modificar: (TEXTO) ");
    scanf("%[^\n]", &sustitute[2]);
    getchar();

    gotoxy(20, 16);
    printf("Dime la cantidad de piezas en inventario: (NUMERO) ");
    scanf("%s", &sustitute[3]);
    getchar();

    num_id = atoi(id);

    update_record(filename, num_id, sustitute);
}

void delete_inventory (char *filename, int max_id){
    char id[5];
    int num_id;

    system("cls");
    gotoxy(25, 13);
    printf("Dime el ID de la pieza que quieres eliminar (1 al %i): (NUMERO) ", max_id);
    scanf("%s", &id);
    getchar();

    num_id = atoi(id);

    delete_record(filename, num_id);
}

void restock_inventory (char *filename, int max_id){
    FILE *fp;
    struct csv csv = read_csv(filename);
    int i=0, ids_length=0;
    char quantities[MAX_ROWS][MAX_LENGTH], quantity[MAX_LENGTH], ids[MAX_ROWS][MAX_LENGTH];

    system("cls");
    gotoxy(20, 13);
    printf("Escribe el ID (1 al %i) y los ejemplares separados por un espacio, ejemplo: 2 234\n", max_id);
    gotoxy(20, 14);
    printf("Para salir solo escribe \"1 /cancelar\"\n");
    gotoxy(20, 15);
    printf("Para terminar solo escribe \"2 /terminado\"\n");
    while(TRUE){
        gotoxy(25, i+16);
        printf("Elemento %i: ", i+1);
        scanf("%s %s", &ids[i], &quantity);
        getchar();

        if (ids[i][0]=='1' && strcmp(quantity, "/cancelar")==0){
            break;
        }

        else if (ids[i][0]=='2' && strcmp(quantity, "/terminado")==0){
            gotoxy(0,0);
            printf("Guardando datos%i\n", ids_length);

            for(int a = 0; a < ids_length; a++){
                printf("array %s, %s\n", ids[a], quantities[a]);
                for (int b = 0 ;  b < csv.n_rows ; b++){
                    printf("    csv %s\n", csv.data[b][0]);
                    if (strcmp(ids[a], csv.data[b][0])==0){
                        strcpy(csv.data[b][3], quantities[a]);
                        b = csv.n_rows+1;
                    }
                }
            }

            write_csv(filename, csv);
            break;
        }
        else{
            gotoxy(25, i+17);
            strcpy(quantities[i], quantity);
            ids_length += 1;
        }
        i++;
    }
}

void log_menu (){
    char choice = 'a';
    char path[MAX_LENGTH] = "sources/history/";

    do{
        gotoxy(50, 10);
        printf("Menu: ");
        gotoxy(50, 11);
        printf("A. Crear bitacora");

        gotoxy(50, 12);
        printf("B. Consultar bitacora");

        gotoxy(50, 13);
        printf("C. Borrar bitacora");

        gotoxy(50, 14);
        printf("D. Regresar");

        gotoxy(50, 15);
        printf("Eleccion: ");
        scanf("%s", &choice);
        choice = tolower(choice);
        getchar();

        if (choice < 'a'  || choice > 'e'){
            gotoxy(50, 14);
            printf("Elige una opcion valida");
            sleep(SLEEP_TIME-1);
            system("cls");
        }

        else{
        switch (choice){
            case 'a':
                system("cls");
                gotoxy(50, 12);
                printf("Crear bitacora");
                system("cls");
                create_log(path);
                break;

            case 'b':
                system("cls");
                gotoxy(50, 12);
                printf("Consultar bitacora");
                system("cls");
                read_log();
                break;

            case 'c':
                system("cls");
                gotoxy(50, 12);
                printf("Borrar bitacora");
                system("cls");
                break;

            case 'd':
                system("cls");
                gotoxy(58, 13);
                printf("Saliendo");
                sleep(SLEEP_TIME);
                system("cls");
                exit(1);
                break;
        }}

    }
    while(choice < 'a'  || choice > 'e');
}

void create_log (char* path){
    char filename[MAX_LENGTH];
    struct log log;
    char line_text[MAX_LENGTH];

    printf("Este es el desarrollo de la bitácora\n");
    printf("Para finalizar de escribir, escribe en una linea blanca \"/finalizar\"");
    gotoxy(0, 3);
    printf("Nombre de bitacora: ");
    scanf("%[^\n]", filename);
    getchar();

    gotoxy(0, 5);
    printf("Autor: ");
    scanf("%[^\n]", log.autor);
    getchar();

    gotoxy(0, 7);
    printf("Fecha: ");
    scanf("%[^\n]", log.fecha);
    getchar();
    gotoxy(0, 9);
    printf("Desarrollo:\n");
    log.n_rows = 0;
    while(true){
        scanf("%[^\n]", line_text);
        getchar();

        if (strcmp(line_text, "/finalizar")==0){
            strcat(path, filename);
            strcat(path, ".txt");
            printf("%s", path);
            write_log(path, log);
            break;
        }
        else{
            strcpy(log.log_text[log.n_rows], line_text);
            log.n_rows++;
        }
    }

}

void read_log (){
    char path[MAX_LENGTH] = "sources/history/";
    struct filenames files = get_filenames(path);
    int padx = 27, pady=5;

    gotoxy(padx, pady);
    printf("Estos son los archivos disponibles, cual deseas abrir?");
    gotoxy(padx+1, pady);

    for (int i = 0 ; i < files.n_rows ; i++){
        gotoxy(padx+4, pady+1+i);
        printf("%i. %s", i+1, files.names[i]);
    }
}
