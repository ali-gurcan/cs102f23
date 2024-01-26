#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define NUMBER_OF_CHAR 27

void dissimilarity(int gramsX[][NUMBER_OF_CHAR], int gramsY[][NUMBER_OF_CHAR]);
void read(FILE *lang, int grams[][NUMBER_OF_CHAR], char *alphabet);
float sum(int grams[][NUMBER_OF_CHAR]);
int wspace(char c);

int main()
{
    FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fpx;

    int gramsX[NUMBER_OF_CHAR][NUMBER_OF_CHAR];
    int gramsY[NUMBER_OF_CHAR][NUMBER_OF_CHAR];
    char *alphabet = "abcdefghijklmnopqrstuvwxyz ";

    memset(gramsX, 0, sizeof(gramsX));
    memset(gramsY, 0, sizeof(gramsY));

    fpx = fopen("language_x.txt", "r");
    read(fpx, gramsX, alphabet);
    fclose(fpx);

    fp1 = fopen("language_1.txt", "r");
    read(fp1, gramsY, alphabet);
    fclose(fp1);
    dissimilarity(gramsX, gramsY);
    memset(gramsY, 0, sizeof(gramsY));

    fp2 = fopen("language_2.txt", "r");
    read(fp2, gramsY, alphabet);
    fclose(fp2);
    dissimilarity(gramsX, gramsY);
    memset(gramsY, 0, sizeof(gramsY));

    fp3 = fopen("language_3.txt", "r");
    read(fp3, gramsY, alphabet);
    fclose(fp3);
    dissimilarity(gramsX, gramsY);
    memset(gramsY, 0, sizeof(gramsY));

    fp4 = fopen("language_4.txt", "r");
    read(fp4, gramsY, alphabet);
    fclose(fp4);
    dissimilarity(gramsX, gramsY);
    memset(gramsY, 0, sizeof(gramsY));

    fp5 = fopen("language_5.txt", "r");
    read(fp5, gramsY, alphabet);
    fclose(fp5);
    dissimilarity(gramsX, gramsY);
    memset(gramsY, 0, sizeof(gramsY));

    memset(gramsX, 0, sizeof(gramsX));

    return 0;
}
int wspace(char c)
{
    // it checks whether whitespace
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

float sum(int grams[][NUMBER_OF_CHAR])
{
    float sum = 0.0;
    for (int i = 0; i < NUMBER_OF_CHAR; i++)
    {
        for (int j = 0; j < NUMBER_OF_CHAR; j++)
        {
            sum += grams[i][j];
        }
    }
    return sum;
}

void dissimilarity(int gramsX[][NUMBER_OF_CHAR], int gramsY[][NUMBER_OF_CHAR])
{
    float diss = 0.0;
    float sumX = 0.0, sumY = 0.0;
    // finds sum
    sumX = sum(gramsX);
    sumY = sum(gramsY);
    // calculate dissimilarity
    for (int i = 0; i < NUMBER_OF_CHAR; i++)
    {
        for (int j = 0; j < NUMBER_OF_CHAR; j++)
        {
            diss += fabs((gramsX[i][j] / sumX) - (gramsY[i][j] / sumY));
        }
    }
    printf("%f\n", diss);
}

void read(FILE *lang, int grams[][NUMBER_OF_CHAR], char *alphabet)
{
    char prev, current;

    if (fscanf(lang, "%c", &prev) == 1)
    {
        while (fscanf(lang, "%c", &current) == 1)
        {
            if (wspace(prev))
                prev = ' ';
            if (wspace(current))
                current = ' ';
            for (int i = 0; i < NUMBER_OF_CHAR; i++)
            {
                for (int j = 0; j < NUMBER_OF_CHAR; j++)
                {
                    if (alphabet[i] == prev && alphabet[j] == current && !(i == NUMBER_OF_CHAR - 1 && j == NUMBER_OF_CHAR - 1))
                    {
                        // does not count if there are two consecutive spaces
                        grams[i][j]++;
                        break;
                    }
                }
            }
            prev = current; // update prev for the next iteration
        }
    }
}
