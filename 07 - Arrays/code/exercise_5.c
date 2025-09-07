#include <stdio.h>

void populate_array(int *arr, int len) {
    for (int i = 0; i < len; i++) {
        arr[i] = i +1;
    }
}

int main () {
    int nums[4];
    int size = sizeof(nums) / sizeof(nums[0]);
    populate_array(nums, size);


    printf("------------------------------------------\n");
    printf("Printing using array notation...\n");

    for (int i = 0; i< size; i++) {
        printf("Value at index '%d' is: %d\n",i,nums[i]);
    }

    printf("------------------------------------------\n");
    printf("Printing using pointer notation...\n");
    for (int i = 0; i < size; i++) {
        printf("Value at address '%p' is: %d\n", (void*)(nums + i), *(nums +i));
    }
    return 0;
}