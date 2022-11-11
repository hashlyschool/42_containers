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

#include "../project/stack.hpp"
#include "../project/vector.hpp"
#include <stack>
#include <iostream>
#include <vector>
#include <map>

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

template <typename T>
void	printSize(ft::vector<T> const &vct, bool print_content = true)
{
	const std::size_t size = vct.size();
	const std::size_t capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename ft::vector<T>::const_iterator it = vct.begin();
		typename ft::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

bool	testingVector()
{
	ft::vector<int> vct(7);
	ft::vector<int> vct_two(4);
	ft::vector<int> vct_three;
	ft::vector<int> vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;
	printSize(vct);
	printSize(vct_two);

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###" << std::endl;

	printSize(vct);
	printSize(vct_two);
	printSize(vct_three);
	printSize(vct_four);

	vct_four.assign(6, 84);
	printSize(vct_four);

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

	printSize(vct);
	printSize(vct_two);

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
	std::vector<int> vct;
	// vct.assign();
	ft::vector<int>::iterator iter;
	ft::vector<int>::const_iterator const_iter;
	//должно работать
	const_iter = iter;
	//не должно работать
	// iter = const_iter;
	return (0);
}
