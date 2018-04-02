#define NA 100
#define NB 100
#define NC  48

void test() {

	int a[NA], b[NB];
	int i, j = 0;

	for (i = 0; i < NA; ++i)
	{
		j = i;
		b[i] = -a[j];
	}

}
