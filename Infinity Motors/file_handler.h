#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>

#define MAX_ROWS 350
#define MAX_COLUMNS 350
#define MAX_LENGTH 350

struct csv{
    int n_columns, n_rows;
    char ***data;
};

struct log{
    char autor[MAX_LENGTH], fecha[MAX_LENGTH];
    char log_text[MAX_ROWS][MAX_LENGTH];
    int n_rows;
};

struct filenames{
    char names[MAX_ROWS][MAX_LENGTH];
    int n_rows;
};

struct filenames get_filenames (char* path){
    struct filenames filenames;
    DIR *dir;
    struct dirent *ent;

    dir = opendir(path);

    if (dir == NULL) {
        perror("Unable to open directory");
    }

    filenames.n_rows = 0;
    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }
        strcpy(filenames.names[filenames.n_rows], ent->d_name);
        filenames.n_rows++;
    }
    closedir(dir);
    return filenames;
}

int file_exist (char *filename){
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL){
        return 0;
    }
    else{
        return 1;
    }
}

 struct csv read_csv (char *filename){

    struct csv csv_data;
    char *token;
    int row = 0, column = 0, max_n_cols = 0;
    char line[MAX_LENGTH];
    FILE *fp;

    csv_data.data = (char ***)malloc(MAX_ROWS * sizeof(char **));
    for (int i = 0; i < MAX_ROWS; i++){
        csv_data.data[i] = (char **)malloc(MAX_COLUMNS * sizeof(char *));

        for (int j = 0; j < MAX_COLUMNS; j++){
            csv_data.data[i][j] = (char *)malloc(MAX_LENGTH * sizeof(char));
        }
    }

    fp = fopen(filename, "r");

    if (fp == NULL){
        printf("No se puede abrir el archivo %s\n", filename);
        exit(1);
    }

    while (fgets(line, MAX_LENGTH, fp) != NULL){
        token = strtok(line, ",");
        while (token != NULL){
            int len = strlen(token);
            if (token[len - 1] == '\n')
            {
                token[len - 1] = '\0';
            }
            strcpy(csv_data.data[row][column], token);
            column++;
            token = strtok(NULL, ",");
        }
        row++;
        max_n_cols = column;
        column = 0;
    }

    fclose(fp);

    csv_data.n_columns = max_n_cols;
    csv_data.n_rows = row;

    return csv_data;
}

struct log open_log (char *filename){

}

void write_csv (char* filename, struct csv csv){
    FILE* fp;
    fp = fopen(filename, "w");
    int a=0, b=0;
    char sentence[MAX_LENGTH] = "";  // Inicializar "sentence" a cadena vacía

    if (fp == NULL){
        printf("Error al abrir el archivo.");
        exit(1);
    }

    for (a ; a < csv.n_rows ; a++) {
        memset(sentence, 0, sizeof(sentence));
        for (b ; b < csv.n_columns ; b++){
            strcat(sentence, csv.data[a][b]);
            if (b < csv.n_columns-1){
                strcat(sentence, ",");
            }
        }
        b=0;  // Reiniciar "b" a cero
        strcat(sentence, "\n");
        fprintf(fp, "%s", sentence);

        for (int i = 0; i < MAX_LENGTH; i++) {
            sentence[i] = '\0';
        }
    }
    fclose(fp);
}

// Función para actualizar un registro en el archivo CSV
void update_record(char *filename, int id, char sustitute[4][MAX_LENGTH]){
    FILE *fp;
    struct csv csv = read_csv(filename);

    for(int column = 0; column < 4; column++){
        strcpy(csv.data[id-1][column], sustitute[column]);
    }

    write_csv(filename, csv);
}

void delete_record(char *filename, int id){
    FILE *fp;
    struct csv csv = read_csv(filename);
    int a, b;

    for (a=id ; a <= csv.n_rows ; a++){
        csv.data[a-1] = csv.data[a];
    }

    // Eliminar el ultimo elemento
    for (a=0 ; a <= csv.n_rows-1 ; a++){
        csv.data[a] = csv.data[a];
    }

    csv.n_rows -= 1;

    write_csv(filename, csv);
}

void write_log (char *filename, struct log log){
    FILE* fp;
    fp = fopen(filename, "w");

    if (fp == NULL){
        printf("Error al abrir el archivo.");
        exit(1);
    }
    fprintf(fp, "Fecha: %s\n\n", log.fecha);
    fprintf(fp, "Autor: %s\n\n", log.autor);
    fprintf(fp, "Desarrollo:\n");

    for (int i = 0 ; i < log.n_rows ; i++){
        fprintf(fp, "%s\n", log.log_text[i]);
    }
    fclose(fp);
}
