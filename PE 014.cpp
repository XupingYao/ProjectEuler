#include <iostream>
#include <Windows.h>
#include <array>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
	LARGE_INTEGER start, finish, frequence;
	QueryPerformanceFrequency(&frequence);
	QueryPerformanceCounter(&start);

	constexpr int N = 1000000 + 1;
	int i, t;
	unsigned long int j;
	array<int, N> *A = new array<int, N>;
	(*A).fill(0);
	(*A).at(1) = 1;
	for (i = 2; i < N; i++)
	{
		j = i;
		t = 0;
		while (j >= i)
		{
			t++;
			if (j % 2)
			{
				j = 3 * j + 1;
			}
			else
			{
				j = j / 2;
			}
		}
		(*A).at(i) = t + (*A).at(j);
	}
	cout << distance((*A).cbegin(), max_element((*A).cbegin(), (*A).cend())) << endl;
	QueryPerformanceCounter(&finish);
	cout << "Elapsed time is " << (finish.QuadPart - start.QuadPart) * 1000.0 / frequence.QuadPart << " ms" << endl;
	system("pause");
	return 0;
}