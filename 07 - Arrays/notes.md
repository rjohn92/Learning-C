It's important to remember that when we try to get the elements of an array what happens. They decay to a pointer to the first element in the array. This means to reference it we should do this:

```c
int arr[4] = {1,2,3,4}// we can have this to declare the array
int *ptr = arr; 

```

This means that '*ptr' now stores the address. This 