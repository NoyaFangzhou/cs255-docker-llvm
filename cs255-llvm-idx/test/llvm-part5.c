void
test()
{
	//  int *a, int* b, int* c, int* d, int * e, int *f, int *g
	int a[100], b[100], c[100], d[100], e[100], f[100], g[100], h[100], m[100], n[100], o[100], p[100];
    
    
    // CASE 1: test for different reference
    // No Dependence
	for (int i = 1; i < 100; ++i)
	{
		a[i+1] = b[i] + 1;
	}

    // CASE 2: test for wz-siv
    // <c[i], c[1]>
    //  Distance Vector:   0    (=)
    // <c[i], c[100]>
    //  No Dependence
	for (int i = 1; i < 100; ++i)
	{
		c[i] = c[1] + c[100];
	}

    // CASE 3: test for default
    // <d[i], d[i]>
    //  Distance Vector:   0    (=)
    // <d[i], d[i-1]>
    //  Distance Vector:   1    (<)
	for (int i = 1; i < 100; ++i)
	{
		d[i] = d[i] + d[i-1];
	}
    
    // CASE 4: test for wc-siv
    // <e[i], e[100-i]>
    //  Distance Vector:    100-2i  (<) if i < 50
    //                      0       (=) if i = 50
    //                      100-2i  (<) if i > 50
	for (int i = 1; i < 100; ++i)
	{
		e[i] = e[100-i];
	}

    // CASE 5: test for wc-siv
    // No Dependence
	for (int i = 1; i < 50; ++i)
	{
		f[i] = f[101-i];
	}
    
    // CASE 6: test for ziv
    // No Dependence
	for (int i = 1; i < 100; i+=2) {
		g[3] = g[5] + 1;
	}
    
    // CASE 7: test for mixing dependence
    // <h[i], h[i+1]>
    //  Distance Vector:   1    (<)
    // <m[i], m[10]>
    //  Distance Vector:   0    (=)
    for (int i = 0; i < 98; i++) {
        h[i] = m[10];
        m[i] = h[i+1] + 7;
    }
    
    // CASE 8: test for loop-indep dependence
    // <p[100-i], h[100-i]>
    //  Distance Vector:   0    (=)
    for (int i = 1; i < 50; i+=5) {
        p[100-i] = p[100-i] - 6;
    }
    
    // CASE 9: test for mixing multi-types dependencies
    // <o[i], o[i+1]>
    //  Distance Vector:   1    (<)
    // <o[i], o[100-i]>
    //  Distance Vector:   0    (=)
    // <o[i], o[10]>
    //  Distance Vector:   0    (=)
    for (int i = 50; i >= 1; i--)
    {
        o[i] = o[i+1] + o[100-i] + o[10];
    }
    
    
    
}
