For Exercise #1:
We just declared an array of 5 variables of int type with:
int nums[5];

Pretty simple. But it was empty. So what we did was loop through it and fill it out with multiples of 10. 
Next we wanted to print out the variables. But we also wanted to get the addresses of each 'box' in the array that held my numbers.

So what we did was create a second loop. This second loop would go through the array 'nums'. And it would create a *ptr that would point at the current position in the nums array. We would print that index number. Then print the value at that index. Then we would also pritn the address of that index.

Everything worked as expected. Also, since we know each int value is 4 bytes in size that our total amount of memory used for this array would be 20 bytes. 
So if we looked at index '0' as the base. Then (inclusively counting) the index '4' would be a total of +16 bytes from the starting point in the array.


---

For Exercise # 2:


---

For Exercise #6
We print the numbers in bounds first. Then we get reliable/reasonable output. It gives us even numbers for the indexes 0 through 4. That's what we expected. 

However, when we try to look out of bounds we get some weird output:

1st Run
```c
------------------------------------------
Printing using array notation...
Value at index '0' is: 2
Value at index '1' is: 4
Value at index '2' is: 6
Value at index '3' is: 8
Value at index '4' is: 10
Attempting to print out of bounds values:
Value at index '5' is: 32766
Value at index '6' is: -2029767424
```
------------------------------------------

2nd Run
```c
Printing using array notation...
Value at index '0' is: 2
Value at index '1' is: 4
Value at index '2' is: 6
Value at index '3' is: 8
Value at index '4' is: 10
Attempting to print out of bounds values:
Value at index '5' is: 32764
Value at index '6' is: 1608803840
```

```c
------------------------------------------
Printing using array notation...
Value at index '0' is: 2
Value at index '1' is: 4
Value at index '2' is: 6
Value at index '3' is: 8
Value at index '4' is: 10
Attempting to print out of bounds values:
Value at index '5' is: 32764
Value at index '6' is: 990807808
```

