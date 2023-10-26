#include<stdio.h>
#include<math.h>
#define EPSILON 0.001
#define MACRO 10

double testpoint(double avgx1,double avgy1,double avgx2,double avgy2){
    double x,y;
    int check;
    do
    {
        check = scanf("%lf %lf", &x, &y);
        if (check != 2)
        {
            return 0;
        }
        //the statement compares distances
        if (sqrt(pow(y - avgy1, 2) + pow(x - avgx1, 2)) < sqrt(pow(y - avgy2, 2) + pow(x - avgx2, 2)))
        {
            printf("class 1, distance = %.1lf \n", sqrt(pow(y - avgy1, 2) + pow(x - avgx1, 2)));
        }
        else
        {
            printf("class 2, distance = %.1lf \n", sqrt(pow(y - avgy2, 2) + pow(x - avgx2, 2)));
        }
    } while (check == 2);
}
int main(){
    int i,j;
    double x,y,sumx,sumy;
    double avgx1,avgy1,avgx2,avgy2;
    double midx,midy,slope;

    //user enters point coordinates for class 1
    for (i = 0; i < MACRO; i++)
    {
        scanf("%lf %lf",&x,&y);
        sumx=sumx+x;
        sumy =sumy+y;
    }
    avgx1 = sumx / MACRO;
    avgy1 = sumy / MACRO;

    //reset variables for class 2  
    x = 0, y = 0, sumy = 0, sumx = 0 ;

    //user enters point coordinates for class 2
    for (j = 0; j < MACRO; j++)
    {
        scanf("%lf %lf", &x, &y);
        sumx = sumx + x;
        sumy = sumy + y;
    }
    //find averages of points
    avgx2 = sumx / MACRO;
    avgy2 = sumy / MACRO;

    midx=(avgx1 + avgx2) / 2;
    midy=(avgy1 + avgy2) / 2;

    //if divider is zero ,adds epsilon
    if(avgy1-avgy2!=0){
        slope = -1/((avgy1 - avgy2) / (avgx1 - avgx2)) ;
    }
    else{
        slope = -1 / ((avgy1 - avgy2+EPSILON) / ((avgx1 - avgx2)));
    }
    printf("midpoint = %.1lf %.1lf\n", midx, midy);
    printf("separating line slope = %.1lf\n", slope);

    testpoint(avgx1,avgy1,avgx2,avgy2);

    return 0;

}