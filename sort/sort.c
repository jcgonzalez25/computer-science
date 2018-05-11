#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SELECT "selection"
#define INSERT "insertion"
#define QUICK "quick"
void loadNums(int **numList,int *size){
  int buff;
  while( ( scanf("%d",&buff) ) == 1){
    *numList = *(size) == 1? malloc(sizeof(int) * *(size)): realloc(*numList,sizeof(int) * *(size));
    *(*numList + (*size - 1)) = buff;
    *(size) += 1;  
  }

}
void printList(int *numList, int size){
  int i;
  for(i=0; i < size - 1; i++)
    printf("%d\n",numList[i]);
}
void selectionSort(int *numList, int size){
  int i,minIndex,k,tmp;

  for(i=0;i< size; i++){
    minIndex = i;
    for(k= i + 1;k <size; k++){
      if(numList[k] < numList[minIndex])
        minIndex = k;
    }
    tmp = numList[i];
    numList[i] = numList[minIndex];
    numList[minIndex] = tmp;

  }
}
void insertionSort(int *numList, int size){
  int i,j,key;

  for(i=1;i<size;i++){
    key = numList[i];
    j= i - 1;
    while(j>= 0 && numList[j] > key){
      numList[j+1] = numList[j];
      j -= 1;
    }
    numList[j+1] = key;
  }
}

void quickSort(int *arr,int size){
  
}

int main(int argc, char* argv[]){
  int* numList = 0;
  int size = 1;
  int numBuff;
  loadNums(&numList, &size);
  if(argc == 2){
    if(strcmp(argv[1],SELECT) == 0) {
      printf("youve chosen Selection sort algorithm\n");
      selectionSort(numList,size);
    }else if(strcmp(argv[1],INSERT) == 0){
      insertionSort(numList,size);
      printf("youve chosen insertion sort algorithm\n");
    }else if(strcmp(argv[1],QUICK) == 0){
      printf("Youve Chosen the quick sort algorithm\n");
      quickSort(numList,size);
    }
  }
  printList(numList,size);
}
