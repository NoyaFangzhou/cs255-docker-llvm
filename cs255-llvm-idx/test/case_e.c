#define NA 100
#define NB 100
#define NC  48

void test(int* a, int* b, int* c) {
	
   int i, j = 0;

   for (i = 0; i < NA; ++i)
   {
   	j = i;
      b[i] = -a[j];
   }

   int n = NA;

   while (n > 0)
   {
      if (n > NA/2) 
      {
         c[n] = c[n+1] + c[n];
      }
      else 
      {
         c[n] = c[n+1] - c[n];
      }
      n--;
   }

}
