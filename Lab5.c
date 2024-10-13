#include <stdio.h>

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

    for (int i = 0; i < MAX_MONTHS; ++i) {
        if (sales[i].sales < minSales) {
            minSales = sales[i].sales;
        }

        if (sales[i].sales > maxSales) {
            maxSales = sales[i].sales;
        }

        totalSales += sales[i].sales;
    }

    printf("Sales summary:\n");
    printf("Minimum sales: $%.2f (%s)\n", minSales, sales[0].month);
    printf("Maximum sales: $%.2f (%s)\n", maxSales, sales[MAX_MONTHS - 1].month);
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

int main() {
    struct SalesData sales[MAX_MONTHS];

    // Input sales data as an array of digits
    const double salesArray[MAX_MONTHS] = {
        23458.01, 40112.00, 56011.85, 37820.88, 37904.67, 60200.22,
        72400.31, 56210.89, 67230.84, 68233.12, 80950.34, 95225.22
    };

    initializeSalesData(sales, salesArray);

    printSalesReport(sales);
    printSummaryReport(sales);
    printMovingAverage(sales);
    printSortedSalesReport(sales);

    return 0;
}
