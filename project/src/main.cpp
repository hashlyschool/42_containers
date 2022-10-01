/*!
 * @file main.cpp
 * @author hashly (ilya12-141998@mail.ru)
 * @brief file for testing custom containers
 * @version 1.0
 * @date 2022-10-01
 *
 * @copyright Flex copyright (c) 2022
 *
 */

#include "../inc/Stack.hpp"
#include <stack>
#include <iostream>

/// @brief function for testing custom stack
void	testingStack()
{
	// ft::stack<int>		myStack;
	std::stack<int>		stdStack;

	stdStack.push(3);
	// Mystack.push(3);

	std::cout << "Stack = " << stdStack.top() << "\n";
	// std::cout << "MyStack = " << myStack.top() << "\n";
}

/// @brief main function for testing custom containers
/// @return int
int	main()
{
	testingStack();
	return (0);
}
