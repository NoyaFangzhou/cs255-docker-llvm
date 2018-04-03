#define NA 100
#define NB 100
#define NC  48

void test() {

	int a[NA];

	for (int i = 1; i < NA; ++i)
	{
		a[i] = a[i] + a[i-1];
	}

}

