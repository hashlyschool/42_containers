#include "../inc/Stack.hpp"
#include <stack>
#include <iostream>

void	testingStack()
{
	// ft::stack<int>		myStack;
	std::stack<int>		stdStack;

	stdStack.push(3);
	// Mystack.push(3);

	std::cout << "Stack = " << stdStack.top() << "\n";
	// std::cout << "MyStack = " << myStack.top() << "\n";
}

int	main()
{
	testingStack();
	return (0);
}
