#include <stdio.h>

int cube(int number) {
	return number*number*number;
}

int add (int a, int b) {
	return a +b;
}

int multiply (int a, int b) {
	return a * b;
}

int squared_sum(int a, int b) {
	return (a*a) + (b*b);
}

int max_of_two(int no_one, int no_two) {
	if (no_one>no_two) return no_one;
	else if(no_one<no_two) return no_two;
}

void greet(const char *name) {
	printf("Hello, %s!\n", name);
}

int sum_to_n(int number){
	if (number<=1) return 1;//base case
	return number+sum_to_n(number-1);
}
int main() {
	printf("Cube function:%d\n", cube(5)); //prints 125
	printf("Max of two function: %d\n", max_of_two(10, 5)); //prints 10
	printf("Squared sum function: %d\n", squared_sum(3,2));
	printf("Mulitply function: %d\n", multiply(4,9));
	greet("You");
	printf("Add function: %d\n",add(3,2));
	printf("Sum to N function: %d\n", sum_to_n(100)); //should print 5050
	return 0;
}
