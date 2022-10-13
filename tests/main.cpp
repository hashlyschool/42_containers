/*!
 * @file main.cpp
 * @author hashly (ilya12-141998@mail.ru)
 * @brief file for testing custom containers
 * @version 1.0
 * @date 2022-10-09
 *
 * @copyright Flex copyright (c) 2022
 *
 */

#include "../project/Stack.hpp"
#include "../project/Vector.hpp"
#include <stack>
#include <iostream>
#include <vector>

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

bool	testingVector()
{
	std::vector<int>	stdVector;
	ft::vector<int>		myVector;

	stdVector.push_back(3);
	myVector.push_back(3);

	std::cout << "Vector = " << stdVector[0] << "\n";
	std::cout << "MyVector = " << myVector[0] << "\n";
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

	testingVector();
	return (0);
}
