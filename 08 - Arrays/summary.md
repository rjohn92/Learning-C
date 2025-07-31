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

