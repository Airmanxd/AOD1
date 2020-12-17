#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

void multiplyOrder(int p[], int length, int*res)
{
	int n = length - 1;
	int** res_min = new int*[n];
	int** res_max = new int*[n];
	for (int i = 0; i < n; i++)
	{
		res_min[i] = new int[n];
		res_max[i] = new int[n];
	}

	for (int i = 0; i < n; ++i) 
	{
		res_min[i][i] = 0;
		res_max[i][i] = 0;
	}

	for (int l = 1; l < n; ++l) 
	{
		for (int i = 0; i < n - l; ++i) 
		{
			int j = i + l;
			res_min[i][j] = INT_MAX;
			res_max[i][j] = INT_MIN;
			for (int k = i; k < j; ++k)
			{
				res_min[i][j] = min(res_min[i][j], res_min[i][k] + res_min[k + 1][j] + p[i] * p[k + 1] * p[j + 1]);
				res_max[i][j] = max(res_max[i][j], res_max[i][k] + res_max[k + 1][j] + p[i] * p[k + 1] * p[j + 1]);
			}
		}
	}
	res[0] = res_min[0][n - 1];
	res[1] = res_max[0][n - 1];
}

int main()
{
	int test[] = { 5, 10, 3, 12, 5, 50, 6 };
	int length = sizeof(test) / sizeof(test[0]) - 1;
	/*cout << "How many matrices will there be?\n";
	cin >> length;
	int* arr = new int[length];
	cout << "Enter the sizes of the matrices\n";
	for (int i = 0; i < length; i++)
		cin >> arr[i];*/
	int* res = new int;
	multiplyOrder(test, length, res);
	cout << "Minimum calculations: " << res[0];
	cout << "\nMaximum calculations: " << res[1];

}
