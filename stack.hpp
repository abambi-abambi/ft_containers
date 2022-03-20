/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abambi <abambi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:12:23 by abambi            #+#    #+#             */
/*   Updated: 2022/02/09 23:47:39 by abambi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

// # include <vector>
# include "vector.hpp"

namespace ft
{
	template <typename T, class Container = ft::vector<T> >
	class stack
	{
		protected:
			Container			c;
		public:
			typedef T			value_type;
			typedef	Container	container_type;

			explicit	stack(const Container &src = Container())	: c(src) {};
			stack		&operator=(const stack &src)				{ this->c = src.c; return (*this); };
						stack(const stack &src)						{ *this = src; };
						~stack() {}

			value_type			&top(void)							{ return (this->c.back()); };
			const value_type	&top(void) const					{ return (this->c.back()); };
			void				push(value_type &value)				{ this->c.push_back(value); };
			void				pop(void)							{ this->c.pop_back(); };
			bool				empty(void) const					{ return (this->c.empty()); };
			size_t				size(void) const					{ return (this->c.size()); };

		protected:
			template<typename Tt, class Cont>
			friend bool			operator==(const stack<Tt,Cont> &left, const stack<Tt,Cont> &right);

			template<typename Tt, class Cont>
			friend bool			operator!=(const stack<Tt,Cont> &left, const stack<Tt,Cont> &right);

			template<typename Tt, class Cont>
			friend bool			operator<(const stack<Tt,Cont> &left, const stack<Tt,Cont> &right);

			template<typename Tt, class Cont>
			friend bool			operator<=(const stack<Tt,Cont> &left, const stack<Tt,Cont> &right);

			template<typename Tt, class Cont>
			friend bool			operator>(const stack<Tt,Cont> &left, const stack<Tt,Cont> &right);

			template<typename Tt, class Cont>
			friend bool			operator>=(const stack<Tt,Cont> &left, const stack<Tt,Cont> &right);
	};

	template <typename T, class Container>
	bool	operator==(const stack<T,Container> &left, const stack<T,Container> &right) { return (left.c == right.c); };

	template <typename T, class Container>
	bool	operator!=(const stack<T,Container> &left, const stack<T,Container> &right) { return (left.c != right.c); };

	template <typename T, class Container>
	bool	operator<(const stack<T,Container> &left, const stack<T,Container> &right) { return (left.c < right.c); };

	template <typename T, class Container>
	bool	operator<=(const stack<T,Container> &left, const stack<T,Container> &right) { return (right.c <= left.c); };

	template <typename T, class Container>
	bool	operator>(const stack<T,Container> &left, const stack<T,Container> &right) { return (right.c > left.c); };

	template <typename T, class Container>
	bool	operator>=(const stack<T,Container> &left, const stack<T,Container> &right) { return (left.c >= right.c); };
};

#endif
