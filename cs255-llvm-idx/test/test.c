void
test()
{
	//  int *a, int* b, int* c, int* d, int * e, int *f, int *g
	int a[100], b[100], c[100], d[100], e[100], f[100], g[100];
	// test for different reference
	for (int i = 1; i < 100; ++i)
	{
		a[i+1] = b[i] + 1;
	}

	// test for wz-siv
	for (int i = 1; i < 100; ++i)
	{
		c[i] = c[1] + c[100];
	}

	// test for default
	for (int i = 1; i < 100; ++i)
	{
		d[i] = d[i] + d[i-1];
	}
	// test for wc-siv
	for (int i = 1; i < 100; ++i)
	{
		e[i] = e[100-i];
	}

	// test for wc-siv
	for (int i = 1; i < 100; ++i)
	{
		f[i] = f[100-i+1];
	}
	for (int i = 1; i < 100; i++) {
		g[3] = g[5] + 1;
	}
}
