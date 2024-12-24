#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793
#define N 1000 


double f(double x) {
    return -0.5 * log(1 - 2 * x * cos(PI / 3) + x * x);
}


int isExtremum(double prev, double curr, double next) {
    return ((curr > prev && curr > next) || (curr < prev && curr < next));
}


double integrate(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += f(x);
    }

    return sum * h;
}

int main() {
    double a = -1.0, b = 1.0; 
    double h = (b - a) / N;  

    FILE* file = fopen("output.txt", "w");
    if (!file) {
        perror("File opening error");
        return 1;
    }

    fprintf(file, "Tabulation function:\n");
    fprintf(file, "x\t\tf(x)\t\tComment\n");

    double prev = f(a); 
    for (int i = 1; i <= N; i++) {
        double x = a + i * h;
        double curr = f(x);
        double next = f(x + h);

        fprintf(file, "%.5f\t%.5f", x, curr);

        if (i > 1 && i < N && isExtremum(prev, curr, next)) {
            fprintf(file, "\tExtremum");
        }

        fprintf(file, "\n");
        prev = curr;
    }

    
    double integral = integrate(a, b, N);

    fprintf(file, "\nThe integral of a function on [%.2f, %.2f]: %.5f\n", a, b, integral);

    fclose(file);

    printf("The results are saved to a file output.txt\n");

    return 0;
}
