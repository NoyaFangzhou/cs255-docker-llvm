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

}
