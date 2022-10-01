/*!
 * @file Stack.hpp
 * @author hashly (ilya12-141998@mail.ru)
 * @brief custom std::stack
 * @version 1.0
 * @date 2022-10-01
 *
 * @copyright Flex copyright (c) 2022
 *
 */

#ifndef STACK_HPP
# define STACK_HPP

# include <deque>

/// @brief custom namespace for school project's
namespace ft
{

	/// @brief custom implementation std::stack
	/// @tparam T
	/// @tparam Container
	template <class T, class Container = std::deque<T> >
	class stack
	{
		protected:
			/// @brief base containers
			Container	_container;
		public:

			/// @brief Construct a new stack object
			/// @param c
			explicit stack(const Container &c) : _container(c) {};

			/// @brief Copy constructor
			/// @param other
			stack(const stack &other): _container(other._container) {}

			/// @brief operator =
			/// @param other
			/// @return stack&
			stack& operator=(const stack& other)
			{
				_container = other._container;
				return (*this);
			}
	};

} // namespace ft

#endif
