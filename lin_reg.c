#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float ypredit(float a, float b, float x) {
    return a * x + b;
}

float erreur(float *tabx, float *taby, int n, float a, float b) {
    float s = 0;
    for (int i = 0; i < n; i++) {
        float Y = ypredit(a, b, tabx[i]);
        s += (Y - taby[i]) * (Y - taby[i]);
    }
    return s / (float) n;
}

void gradient(float *a, float *b, float *tabx, float *taby, int n, float alpha) {
    float da = 0, db = 0;
    for (int i = 0; i < n; i++) {
        float Y = ypredit(*a, *b, tabx[i]);
        da += (Y - taby[i]) * tabx[i];
        db += (Y - taby[i]);
    }
    da = (2 * da) / (float)n;
    db = (2 * db) / (float) n;
    *a -= alpha * da;
    *b -= alpha * db;

}

int main() {
    int n;
    do {
        printf("Donner le nombre de points: ");
        scanf("%d", &n);
    } while (n <= 0);

    float *tabx = (float *)malloc(n * sizeof(float));
    float *taby = (float *)malloc(n * sizeof(float));

    if (tabx == NULL || taby == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("tabx[%d] = ", i);
        scanf("%f", &tabx[i]);
        printf("taby[%d] = ", i);
        scanf("%f", &taby[i]);
    }
    srand(time(0));
    float a = ((float)rand() / RAND_MAX) * 2 - 1;
    float b = ((float)rand() / RAND_MAX) * 2 - 1;

    printf("Valeurs initiales : a = %f, b = %f\n", a, b);

    float s = erreur(tabx, taby, n, a, b);
    float alpha = 0.001;

    while (s > 0.000001) {
        gradient(&a, &b, tabx, taby, n, alpha);
        s = erreur(tabx, taby, n, a, b);
    }

    printf("Resultats finaux :\n");
    printf("Pente (a) = %f\n", a);
    printf("Ordonnee a l'origine (b) = %f\n", b);
    printf("Erreur finale = %f\n", s);

    free(tabx);
    free(taby);

    return 0;
}
