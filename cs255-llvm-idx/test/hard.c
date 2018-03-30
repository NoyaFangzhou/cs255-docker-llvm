#define NA 100
#define NB 100
#define NC  48

void hardbench(int* a, int* b, int* c) {
   int temp, val;
   int i, j, k, t = 0;

   for (t = 0; t < NA; ++t)
   {
      val = t * 2 + 3;
      a[t] = val;
   }
 
   for (i = 1; i < NA; ++i)
   {
      a[i] = a[i-1] * 2;
   }

   for (j = 0; j < NB; ++j)
   {
      b[j] = a[(NB-1)-j]  - a[j]; // you can output 99 - j for index of a[(NB-1)-j]
   }

   for (k = 2; k < NC; ++k)
   {
      c[k] = c[k*2-3] + b[k-1];
   }

}
