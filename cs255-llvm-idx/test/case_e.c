#define NA 100
#define NB 100
#define NC  48

void test(int* a, int* b, int* c) {

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
