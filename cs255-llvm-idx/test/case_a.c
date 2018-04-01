#define NA 100
#define NB 100
#define NC  48

void test(int* a) {
   int temp, last;
   int i = 0;

   for (i = 0; i < NA; ++i)
   {
      last = NA - 1- i;
      temp = a[i];
      a[i] = a[last];
      a[last] = temp; 
   }

}
