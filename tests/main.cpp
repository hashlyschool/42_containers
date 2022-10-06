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

#include "../project/Stack.hpp"
#include <stack>
#include <iostream>

/*!
 * @brief function for testing custom stack
 *
 * @return true (testing complete)
 * @return false (testing failed)
 */
bool	testingStack()
{
	ft::stack<int>		myStack;
	std::stack<int>		stdStack;

	stdStack.push(3);
	myStack.push(3);

	std::cout << "Stack = " << stdStack.top() << "\n";
	std::cout << "MyStack = " << myStack.top() << "\n";
	return (0);
}

/// @brief main function for testing custom containers
/// @return int

int	main()
{
	if (testingStack() == 0)
		std::cout << "Stack: OK" << std::endl;
	else
		std::cout << "Stack: KO" << std::endl;
	return (0);
}
