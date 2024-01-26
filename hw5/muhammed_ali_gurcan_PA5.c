#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARB_CAL_1G 4    /* Number of calories in 1g carbohydrate */
#define PROTEIN_CAL_1G 4 /* Number of calories in 1g protein */
#define FAT_CAL_1G 9     /* Number of calories in 1g fat */
#define WATER_CAL_1G 0   /* Number of calories in 1g water */

typedef struct cals
{
    double carb;
    double protein;
    double fat;
} cals;

void getandparse(char parts[][30], int *n_p, char *name);
int definite(char *name);
void f(char *name, cals *ca, double *total_weight);
double getamount(char *name);
void final(cals *ca, double *total_weight);

int main()
{
    cals meal;
    char name[30];
    double total_weight = 0.0;
    meal.carb = 0.0;
    meal.protein = 0.0;
    meal.fat = 0.0;

    printf("What is the meal?\n");
    scanf("%s", name);
    f(name, &meal, &total_weight);
    final(&meal, &total_weight);
    
    return 0;
}

int definite(char *name)
{
    int length = strlen(name);
    if (length > 0 && name[length - 1] == ')')
    {
        return 1; // Return 1 if the last character is ')'
    }
    else
    {
        return 0;
    }
}
void getandparse(char parts[][30], int *n_p, char *name)
{
    int count = 0;
    // If the current character is not a space,move it to index 'count++'.
    for (int j = 0; name[j]; j++)
        if (name[j] != ' ')
            name[count++] = name[j]; // here count is incremented
    name[count] = '\0';

    char *token;
    char delimiters[] = ",";
    int i = 0;

    token = strtok(name, delimiters);

    while (token != NULL && i < 20)
    {
        strcpy(parts[i], token);
        (*n_p)++;
        token = strtok(NULL, delimiters);
        i++;
    }
}

void f(char *name, cals *ca, double *total_weight)
{
    // 20*30 and commas
    char nutrients[700];

    // for the first iteration.
    strcpy(nutrients, name);
    int n_p = 0;
    char parts[20][30];
    cals temp;
    if (definite(nutrients))
    {
        cals base;
        double amount;
        amount = getamount(nutrients);
        *total_weight += amount;
        printf("List the amount macro nutrients in %s\n", nutrients);
        scanf("%lf %lf %lf", &base.carb, &base.protein, &base.fat);
        ca->carb = amount * (base.carb / 100) * CARB_CAL_1G;
        ca->protein = amount * (base.protein / 100) * PROTEIN_CAL_1G;
        ca->fat = amount * (base.fat / 100) * FAT_CAL_1G;
        return;
    }
    else
    {
        printf("What is %s?\n", nutrients);
        // reads until end of line
        scanf(" %[^\n]", nutrients);
    }

    getandparse(parts, &n_p, nutrients);

    for (int i = 0; i < n_p; i++)
    {
        f(parts[i], &temp, total_weight);
        ca->carb += temp.carb;
        ca->protein += temp.protein;
        ca->fat += temp.fat;
    }
}

double getamount(char *name)
{
    double amount;
    //  Scan the string to extract the amount
    sscanf(name, "%*[^0-9]%lf", &amount);
    return amount;
}

void final(cals *ca, double *total_weight)
{
    double A, B, C, D, E;
    A = ((ca->carb) + (ca->protein) + (ca->fat));
    B = *total_weight;
    C = (ca->carb / (ca->carb + ca->protein + ca->fat) * 100);
    D = (ca->protein / (ca->carb + ca->protein + ca->fat) * 100);
    E = (ca->fat / (ca->carb + ca->protein + ca->fat) * 100);
    printf("Total calories is %.1lf in %.1lfg Hamburger. ", A, B);
    printf("%%%.1lf calories from carbs, ", C);
    printf("%%%.1lf from proteins, ", D);
    printf("%%%.1lf from fats.\n", E);

//495 sum of hws
}