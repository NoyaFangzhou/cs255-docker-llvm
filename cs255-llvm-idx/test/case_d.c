#define NA 100
#define NB 100
#define NC  48

void case(int* a, int* b) {
	
   int i, j = 0;

   for (i = 0; i < NA; ++i)
   {
   	  j = i;
      b[i] = -a[j];
   }

   int n = NA;

   for (n = NA-2; n >= 1; n--)
   {
   	  a[n] = a[n-1] + a[n+1];
   }

   int x = 1;
   for (x = 1; x < NB; x++)
   {
   	  a[x] = b[NB] - a[x-1];
   }

}
