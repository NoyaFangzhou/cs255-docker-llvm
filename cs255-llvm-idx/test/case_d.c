#define NA 100
#define NB 100
#define NC  48

void test() {

   int a[NA], b[NB];
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
