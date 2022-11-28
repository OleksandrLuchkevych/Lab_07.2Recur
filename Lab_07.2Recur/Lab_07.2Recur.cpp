#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Change(int** a, int index_min, int index_max, int j);
int Min(int** a, const int k, const int n, int& minmin, int j0, int i, int j);
void MinMax(int** a, const int k, const int n, int& min, int& max, int row, int& index_min,
    int& index_max, bool& umova, int j, int q);


void Create(int** a, const int k, const int n, const int Low, const int High, int i, int j)
{
    a[i][j] = Low + rand() % (High - Low + 1);
    if (j < n - 1)
        Create(a, k, n, Low, High, i, j + 1);
    else
        if (i < k - 1)
            Create(a, k, n, Low, High, i + 1, 0);
        else 
            return;
}
void Print(int** a, const int k, const int n, int i, int j)
{
    cout << setw(4) << a[i][j];
    if (j < n - 1)
        Print(a, k, n, i, j + 1);
    else
        if (i < n - 1)
        {
            cout << endl;
            Print(a, k, n, i + 1, 0);
        }
        else
            cout << endl << endl;
}
void Change(int** a, int index_min, int index_max, int j)
{
        int tmp = a[j][index_min];
        a[j][index_min] = a[j][index_max];
        a[j][index_max] = tmp;
}
int Min(int** a, const int k, const int n, int& minmin, int j0, int i, int j)
{
    
    if (a[i][j] < minmin)
    {
        minmin = a[i][j];
        j0 = j;

    }
    if (j < n - 1)
        Min(a, k, n, minmin, j0, i, j + 1);
    else
        if (i < k - 1)
            Min(a, k, n, minmin, j0, i + 1, 0);
        else 
            return minmin;

}
int main()
{
    srand((unsigned)time(NULL));
    int Low = -50;
    int High = 50;
    int n, k;
    cout << "k = "; cin >> k;
    cout << "n = "; cin >> n;
    int** a = new int* [k];
    for (int i = 0; i < k; i++)
        a[i] = new int[n];

    int i = 0;
    int j = 0;
    int index_min = 0;
    int index_max = 0;
    bool umova = false;

    Create(a, k, n, Low, High, i, j);
    Print(a, k, n, i, j);

    int minmin = a[0][0];
    int row = 0;
    int min = a[row][0];
    int max = a[row][0];

    int q = 0;
    MinMax(a, k, n, min, max, row, index_min, index_max, umova, j, q);
    Print(a, k, n, i, j);

    for (int i = 0; i < k; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}


void MinMax(int** a, const int k, const int n, int& min, int& max, int row, int& index_min, 
                                                    int& index_max, bool& umova, int j, int q)
{
    if (row < k)
    {
        if (umova)
        {
            min = a[row][0];
            max = a[row][0];
            umova = false;
        }

        if (j < n)
        {
            if (a[row][j] <= min)
            {
                min = a[row][j];
                index_min = j;

            }
            MinMax(a, k, n, min, max, row, index_min, index_max, umova, j + 1, q);
        }
        else
            if (q < n)
            {
                if (a[row][q] >= max)
                {
                    max = a[row][q];
                    index_max = q;
                }
                MinMax(a, k, n, min, max, row, index_min, index_max, umova, j, q + 1);
            }
            else
            {
                umova = true;
                Change(a, index_min, index_max, row);
                MinMax(a, k, n, min, max, row + 1, index_min, index_max, umova, 0, 0);
            }
    }
    else
        return;
}