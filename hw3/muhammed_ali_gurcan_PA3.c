#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_VALUE 100
#define MAX_POLY_LENGTH 1000

double evaluate_polynomial(char *poly, double value)
{
    double result = 0.0;
    // Length of polynomial string
    int len = strlen(poly);
    printf("%d",len);
    int i = 0;

    while (i < len)
    {
        int sign = 1;
        double coefficient = 0.0;
        double decimal = 0.0;
        int power = 0;

        if (poly[i] == '-')
        {
            // If the term is negative, that updates the sign
            sign = -1;
            i++;
        }
        else if (poly[i] == '+')
        {
            // If the term is positive, that moves to next character
            i++;
        }

        // Finding coefficient
        while (poly[i] >= '0' && poly[i] <= '9')
        {
            coefficient = coefficient * 10 + (poly[i] - '0');
            i++;
        }

        // Checking point in the coefficient
        if (poly[i] == '.')
        {
            i++;
            while (poly[i] >= '0' && poly[i] <= '9')
            {
                decimal = decimal * 10 + (poly[i] - '0');
                i++;
            }
            decimal = 0.1 * decimal;
        }

        // If there is no coefficient ,set as 1
        if (coefficient == 0.0)
        {
            coefficient = 1.0;
        }
        coefficient = coefficient + decimal;
        // Check for 'x'
        if (poly[i] == 'x')
        {
            // If the term is x, that moves to next character
            i++;
            if (poly[i] == '^')
            {
                // If the term is ^, that moves to next character
                i++;
                while (poly[i] >= '0' && poly[i] <= '9')
                {
                    power = power * 10 + (poly[i] - '0');
                    i++;
                }
            }
            else
            {
                // If the term x has no exponential ,power set as 1
                power = 1;
            }
        }

        // Calculating the term and add it to the result
        result += sign * coefficient * pow(value, power);

        // That moves to the next term until find the next + or - character
        while (i < len && poly[i] != '+' && poly[i] != '-')
        {
            i++;
        }
    }
    return result;
}

int main()
{
    FILE *fp1 = fopen("values.txt", "r");
    FILE *fp2 = fopen("polynomials.txt", "r");
    FILE *fp3 = fopen("evaluations.txt", "w");

    if (fp1 == NULL || fp2 == NULL || fp3 == NULL)
    {
        printf("Error opening files.\n");
        return 1;
    }

    char polynomial[MAX_POLY_LENGTH];
    double values[MAX_VALUE];

    int values_count = 0;

    while (fscanf(fp1, "%lf", &values[values_count]) != EOF && values_count < MAX_VALUE)
    {
        values_count++;
    }

    while (fgets(polynomial, MAX_POLY_LENGTH, fp2) != NULL)
    {
        for (int i = 0; i < values_count; i++)
        {
            double result = evaluate_polynomial(polynomial, values[i]);
            fprintf(fp3, "%.2lf ", result);
        }
        fprintf(fp3, "\n");
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    return 0;
}
