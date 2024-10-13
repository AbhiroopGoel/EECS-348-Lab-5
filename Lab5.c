#include <stdio.h>
#include <stdlib.h>

#define MAX_MONTHS 12

struct SalesData {
    char month[15];
    double sales;
};

const char *monthNames[MAX_MONTHS] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

void initializeSalesData(struct SalesData sales[MAX_MONTHS], const double salesArray[MAX_MONTHS]) {
    for (int i = 0; i < MAX_MONTHS; ++i) {
        sales[i].sales = salesArray[i];
        sprintf(sales[i].month, "%s", monthNames[i]);
    }
}

void printSalesReport(struct SalesData sales[MAX_MONTHS]) {
    printf("Monthly sales report for 2022:\n");
    printf("Month\t\tSales\n");

    for (int i = 0; i < MAX_MONTHS; ++i) {
        printf("%s\t$%.2f\n", sales[i].month, sales[i].sales);
    }

    printf("\n");
}

void printSummaryReport(struct SalesData sales[MAX_MONTHS]) {
    double minSales = sales[0].sales, maxSales = sales[0].sales, totalSales = 0;
    int minIndex = 0, maxIndex = 0;

    for (int i = 0; i < MAX_MONTHS; ++i) {
        if (sales[i].sales < minSales) {
            minSales = sales[i].sales;
            minIndex = i;
        }

        if (sales[i].sales > maxSales) {
            maxSales = sales[i].sales;
            maxIndex = i;
        }

        totalSales += sales[i].sales;
    }

    printf("Sales summary:\n");
    printf("Minimum sales: $%.2f (%s)\n", minSales, sales[minIndex].month);
    printf("Maximum sales: $%.2f (%s)\n", maxSales, sales[maxIndex].month);
    printf("Average sales: $%.2f\n\n", totalSales / MAX_MONTHS);
}

void printMovingAverage(struct SalesData sales[MAX_MONTHS]) {
    printf("Six-Month Moving Average Report:\n");

    for (int i = 0; i <= MAX_MONTHS - 6; ++i) {
        double sum = 0;
        for (int j = i; j < i + 6; ++j) {
            sum += sales[j].sales;
        }

        printf("%s - %s $%.2f\n", sales[i].month, sales[i + 5].month, sum / 6);
    }

    printf("\n");
}

void printSortedSalesReport(struct SalesData sales[MAX_MONTHS]) {
    printf("Sales Report (Highest to Lowest):\n");
    printf("Month\t\tSales\n");

    // Sorting sales data in descending order
    for (int i = 0; i < MAX_MONTHS - 1; ++i) {
        for (int j = 0; j < MAX_MONTHS - i - 1; ++j) {
            if (sales[j].sales < sales[j + 1].sales) {
                // Swap the elements if they are in the wrong order
                struct SalesData temp = sales[j];
                sales[j] = sales[j + 1];
                sales[j + 1] = temp;
            }
        }
    }

    // Print the sorted sales report
    for (int i = 0; i < MAX_MONTHS; ++i) {
        printf("%s\t$%.2f\n", sales[i].month, sales[i].sales);
    }

    printf("\n");
}

void readSalesDataFromFile(struct SalesData sales[MAX_MONTHS], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    double salesArray[MAX_MONTHS];
    for (int i = 0; i < MAX_MONTHS; ++i) {
        fscanf(file, "%lf", &salesArray[i]);
    }

    fclose(file);
    initializeSalesData(sales, salesArray);
}

int main() {
    struct SalesData sales[MAX_MONTHS];
    char filename[100];

    // Ask the user to provide the input file name
    printf("Enter the input file name: ");
    scanf("%s", filename);

    // Read sales data from file
    readSalesDataFromFile(sales, filename);

    printSalesReport(sales);
    printSummaryReport(sales);
    printMovingAverage(sales);
    printSortedSalesReport(sales);

    return 0;
}
