#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_DATA_ENTRIES 5

const char DATA_PATH[] = "./data.csv";
const int DATA_MAX_LINES = 400;

typedef struct Data {
    double value[NB_DATA_ENTRIES];
    double result;
} Data;

int read_data_file(const char *path, Data *data, int max) {
    FILE *file = fopen(path, "r");
    char line[256];
    int n = 0;

    if (file == NULL) {
        perror("Erreur de la lecture du fichier de donnée");
        return EXIT_FAILURE;
    }

    fgets(line, sizeof line, file); // En tête du fichier !!!!!!!!!!
    while (n < max && fgets(line, sizeof line, file) != NULL) {
        Data *d = &data[n];
        if (sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf",
            &d->value[0], &d->value[1], &d->value[2],
            &d->value[3], &d->value[4], &d->result) == 6) {
            n++;
        } else {
            fprintf(stderr, "Ligne ignoree : %s", line);
        }
    }

    fclose(file);
    return n;
}

int main(void) {
    Data *data = malloc(sizeof(Data) * DATA_MAX_LINES);
    const int linesReaded = read_data_file(DATA_PATH, data, DATA_MAX_LINES);
    printf("%d lignes on été lu\n", linesReaded);

    free(data);
    return 0;
}