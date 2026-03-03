#include <stdio.h>
  int main (void){
  FILE *f ; 
  int i , n;
  f = fopen("test.txt", "rt");
  if (f == NULL ){return 1;}
  for (i=1 ; i<=10 ; i++){
     fscanf(f,"%d",&n);
     printf("%d ", n );
  }
  fclose(f);
   
  return 0;
  }