#include <stdio.h>
#include <stdlib.h>

struct DynamicArray {
    int *data;
    int size; 
    int capacity;
};

int insertAt(struct DynamicArray *dArray, int index, int value) {
     if (dArray == NULL) {
        return 0;
    }
    
    if (index < 0 || index >= dArray->size) {
        printf("Index out of bounds.\n");
        return 0;
    }
   
    if (dArray->size == dArray->capacity) {
        int newCapacity = dArray->capacity * 2;
        int *temp = realloc(dArray->data, sizeof(int) * newCapacity);
        
        if (temp == NULL) {
            printf("Memory reallocation failed.\n");
            return 0;
        }
        
        dArray->data = temp;
        dArray->capacity = newCapacity;
    }
     
    for (int i = dArray->size; i > index; i--) {
        dArray->data[i] = dArray->data[i-1];
        
    }
    
    dArray->data[index] = value;
    dArray->size++;
    return 1;
}

int set(struct DynamicArray *dArray, int index, int replace) {
    if (dArray == NULL) {
        return 0;
    }
    
    if (index < 0 || index >= dArray->size) {
        printf("Index out of bounds.\n");
        return 0;
    }
    
    dArray->data[index] = replace;
    return 1;
}

int get(struct DynamicArray *dArray, int index, int *result) {
    if (dArray == NULL || result == NULL) {
        return 0;
    }
    
    if (index < 0 || index >= dArray->size) {
        printf("Index out of bounds.\n");
        return 0;
    }
    
    *result = dArray->data[index];
    return 1;
}

int removeAt(struct DynamicArray *dArray, int index) {
    if (dArray == NULL) {
        return 0;
    }
    if (index < 0 || index >= dArray->size) {
        printf("Index out of bounds.\n");
        return 0;
    }
    
    for (int i = index; i < dArray->size - 1; i++) {
        dArray->data[i] = dArray->data[i + 1];
    }
   
    dArray->size--;
    
    return 1;
}

int append(struct DynamicArray *dArray, int newData) {
    if (dArray == NULL) {
        return 0;
    }
    if (dArray->size == dArray->capacity) {
        int newCapacity = dArray->capacity * 2;
        int *temp = realloc(dArray->data, sizeof(int) * newCapacity);
        
        if (temp == NULL) {
            printf("Memory reallocation failed.\n");
            return 0;
        }
        
        dArray->data = temp;
        dArray->capacity = newCapacity;
    }
    dArray->data[dArray->size] = newData;
    dArray->size++; 
    return 1;
}

int main(void)
{
   //int *numbers = malloc(sizeof(int) * 5);
   
   struct DynamicArray numbers; 
   
   numbers.data = malloc(sizeof(int) * 5);
   numbers.size = 0;
   numbers.capacity = 5;
  
   if (numbers.data == NULL) {
       printf("Memory allocation failed.\n");
       return 1;
   }
   
   int counter = 10;
   
   for (int i = 0; i < 10; i++) {
       if (!append(&numbers, counter)) {
           printf("Dynamic array append failed.\n");
           free(numbers.data);
           return 1;
       }
       counter +=10;
   }
  
   
  // int *temp = realloc(numbers, sizeof(int) * 10);
  /* 
   if (temp == NULL) {
       printf("Memory reallocation failed.\n");
       free(numbers);
       return 1;
   }
   numbers = temp;
   
   for (int i = 5; i < 10; i++) {
       numbers[i] = counter;
       counter += 10;
   }
   */
   for (int i = 0; i < numbers.size; i++) {
       printf("Value: %d Address: %p \n", *(numbers.data + i), (void *)(numbers.data + i));
      }
      
    if(!removeAt(&numbers, 3)) {
        printf("Remove at failed!\n");
        free(numbers.data);
        return 1;
    }
    for (int i = 0; i < numbers.size; i++) {
       printf("Value: %d Address: %p \n", *(numbers.data + i), (void *)(numbers.data + i));
      }
    int value;
    if(get(&numbers, 3, &value)) {
        printf("The value at index %d is %d\n", 3, value);
    }
    
    int replaceVal = 69420;
    if(set(&numbers, 3, replaceVal)){
        if(get(&numbers, 3, &value)) {
            printf("The value at index %d is %d\n", 3, value);
        }
    }
    int spyNet = 420;
    if (insertAt(&numbers, 3, spyNet)){
        if(get(&numbers, 3, &value)) {
            printf("The value at index %d is %d\n", 3, value);
        }
        for (int i = 0; i < numbers.size; i++) {
       printf("Index: %d Value: %d Address: %p \n", i, *(numbers.data + i), (void *)(numbers.data + i));
      }
    }
   free(numbers.data);

    return 0;
}
