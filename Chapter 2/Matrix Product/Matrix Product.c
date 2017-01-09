#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    double time_spent;
    int i, j, k, a, b, c;
    scanf("%d %d %d", &a, &b, &c);
	int **m1 = malloc(sizeof *m1 * a);
	if(m1)
	{
		for(i = 0; i < a; i++)
		{
			m1[i] = malloc(sizeof * m1[i]*b);
		}
	}
	int **m2 = malloc(sizeof *m2 * b);
	if(m2)
	{
		for(i = 0; i < b; i++)
		{
			m2[i] = malloc(sizeof * m2[i]*c);
		}
	}
	int **m3 = malloc(sizeof *m3 * a);
	if(m3)
	{
		for(i = 0; i < a; i++)
		{
			m3[i] = malloc(sizeof * m3[i]*c);
		}
	}
    for(i = 0; i < a; i++)
    {
        for(j = 0; j < b; j++)
        {
            m1[i][j] = 1;
        }
    }
    for(i = 0; i < b; i++)
    {
        for(j = 0; j < c; j++)
        {
            m2[i][j] = 1;
        }
    }
	for(i = 0; i < a; i++)
    {
        for(j = 0; j < c; j++)
        {
            m3[i][j] = 0;
        }
    }
    clock_t begin = clock();
    for(i = 0; i < a; i++)
    {
        for(j = 0; j < c; j++)
        {
            for(k = 0; k < b; k++)
            {
                m3[i][j] += (m1[i][k] * m2[k][j]);
            }
        }
    }
    clock_t end = clock();
    time_spent = (double)(end-begin) /CLOCKS_PER_SEC;
    printf("%d, %f\n", m3[0][0],time_spent);

    return 0;
}
