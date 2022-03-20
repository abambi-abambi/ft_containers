/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abambi <abambi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:12:38 by abambi            #+#    #+#             */
/*   Updated: 2022/02/10 15:51:58 by abambi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <stdexcept>

// #include <cstring>
// #include <limits>
// #include <algorithm>

#include "iterator.hpp"

namespace ft
{
	template <typename T, class Allocator = std::allocator<T> >
	class vector
	{
	private:
		Allocator											v_alloc;
		T*													v_ptr;
		size_t												v_capacity;
		size_t												v_size;

	public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef size_t										size_type;
		typedef ptrdiff_t									difference_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef vector_iterator<pointer>					iterator;
		typedef vector_iterator<const_pointer>				const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

/*
** Constructors
*/

// 1
		// vector();

// 2 +
		explicit vector(const allocator_type &alloc = allocator_type())
		{
			this->v_alloc = alloc;
			this->v_ptr = this->v_alloc.allocate(0);
			this->v_capacity = 0;
			this->v_size = 0;
		}

// 3 +
		explicit vector(size_type num, const_reference value = value_type(), \
				const allocator_type &alloc = allocator_type())
		{
			this->v_alloc = alloc;
			this->v_ptr = NULL;
			this->v_capacity = 0;
			this->v_size = 0;
			if (num == 0)
			{
				this->v_ptr = this->v_alloc.allocate(0);
				return ;
			}
			this->assign(num, value);
		}

// 4 +
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, \
				const allocator_type &alloc = allocator_type(),
				typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
		{
			this->v_alloc = alloc;
			this->v_ptr = this->v_alloc.allocate(0);
			this->v_capacity = 0;
			this->v_size = 0;
			this->assign(first, last);
		}

// 5
		vector(vector const &src)
		{
			this->v_alloc = src.v_alloc;
			this->v_ptr = this->v_alloc.allocate(src.v_size);
			this->v_capacity = src.v_capacity;
			this->v_size = src.v_size;
			for (size_type i = 0; i < src.v_size; ++i)
				this->v_alloc.construct(this->v_ptr + i, *(src.v_ptr + i));
		}

		vector		&operator=(const vector &src)
		{
			if (this == &src)
				return (*this);
			clear();
			insert(begin(), src.begin(), src.end());
			return (*this);
		};

// alternative variant
		// vector			&operator=(vector const &src)
		// {
		// 	if (this == &src)
		// 		return (*this);
		// 	this->clear();
		// 	this->reserve_without_copying(src.v_capacity);
		// 	memcpy(static_cast<void *>(this->v_ptr), static_cast<void *>(src.v_ptr), src.v_size * sizeof(value_type));
		// 	this->v_size = src.v_size;
		// 	return (*this);
		// }

		~vector()
		{
			this->clear();
			this->v_alloc.deallocate(this->v_ptr, this->v_capacity);
		}

/*
** assign: range of elements
*/

		template <class InputIterator>
		void			assign(InputIterator first, InputIterator last, \
							typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
		{
			clear();
			insert(begin(), first, last);
		}

/*
** assign: number of elements
*/

		void			assign(size_type num, const value_type &value)
		{
			clear();
			insert(begin(), num, value);
		}

		allocator_type	get_allocator() const
		{
			return this->v_alloc;
		}

/*
** Element access
*/
		reference		at(size_type x)
		{
			if (x >= this->v_size)
				throw std::out_of_range("x is out of range");
			return (this->v_ptr[x]);
		}

		const_reference	at(size_type x) const
		{
			if (x >= this->v_size)
				throw std::out_of_range("x is out of range");
			return (this->v_ptr[x]);
		}

		reference				operator[](size_type x)			{ return (this->v_ptr[x]); }
		const_reference			operator[](size_type x) const	{ return (this->v_ptr[x]); }
		reference				front(void)						{ return (this->v_ptr[0]); }
		const_reference			front(void) const				{ return (this->v_ptr[0]); }
		reference				back(void)						{ return (this->v_ptr[this->v_size - 1]); }
		const_reference			back(void) const				{ return (this->v_ptr[this->v_size - 1]); }

/*
** Iterators
*/
		iterator				begin(void)						{ return (iterator(this->v_ptr)); }
		const_iterator	 		begin(void) const				{ return (const_iterator(this->v_ptr)); }
		iterator				end(void)						{ return (iterator(this->v_ptr + this->v_size)); }
		const_iterator			end(void) const					{ return (const_iterator(this->v_ptr + this->v_size)); }
		reverse_iterator		rbegin(void)					{ return (reverse_iterator(this->end())); }
		const_reverse_iterator	rbegin(void) const				{ return (const_reverse_iterator(this->end())); }
		reverse_iterator		rend(void)						{ return (reverse_iterator(this->begin())); }
		const_reverse_iterator	rend(void) const				{ return (const_reverse_iterator(this->begin())); }

/*
** Capacity
*/

		bool					empty(void) const				{ return (this->v_size == 0); }
		size_type				size(void) const				{ return (this->v_size); }
		size_type				max_size(void) const			{ return (this->v_alloc.max_size()); }
		size_type				capacity(void) const			{ return (this->v_capacity); }
		void					reserve(size_type n)
		{
			if (n > v_alloc.max_size())
				throw std::length_error("vector - reserve()");
			if (n > this->v_capacity)
			{
				// if (n < this->v_capacity)
				// if (n < this->v_capacity * 2)
				// if (n < this->v_capacity * 2)
					// n = this->v_capacity;
					// n = this->v_capacity * 2;
				pointer	new_ptr = v_alloc.allocate(n);

				for (size_type i = 0; i < this->v_size; i++)
				{
					v_alloc.construct(new_ptr + i, this->v_ptr[i]);
					v_alloc.destroy(v_ptr + i);
				}
				v_alloc.deallocate(this->v_ptr, this->v_capacity);
				this->v_ptr = new_ptr;
				this->v_capacity = n;				
			}
		}

	private:
		void		reserve_without_copying(size_type n)
		{
			if (n > v_alloc.max_size())
				throw std::length_error("vector - reserve()");
			if (n > this->v_capacity)
			{
				if (n < this->v_capacity * 2)
					n = this->v_capacity * 2;
				pointer	new_ptr = v_alloc.allocate(n);
				for (size_type i = 0; i < this->v_size; i++)
				{
					v_alloc.destroy(v_ptr + i);
				}
				this->v_alloc.deallocate(this->v_ptr, this->v_capacity);
				this->v_ptr = new_ptr;
				this->v_capacity = n;
				this->v_size = 0;
			}
		}

		public:

/*
** Modifiers
*/

		void		clear()
		{
			while (this->v_size != 0)
				this->v_alloc.destroy(&this->v_ptr[--this->v_size]);
			this->v_alloc.deallocate(this->v_ptr, this->v_capacity);
			this->v_ptr = this->v_alloc.allocate(0);
			this->v_capacity = 0;
		}

/*
** insert: one element
*/

		iterator	insert(iterator position, const value_type &value)
		{
			size_type	pos = position.asIndex(this->v_ptr);

			if ((this->v_size + 1) == 1)
				this->reserve(1);
			else if ((this->v_size + 1) > this->v_capacity)
				this->reserve(this->v_capacity * 2);
			for (size_t i = this->v_size; i > pos; i--)
				this->v_alloc.construct(&this->v_ptr[i], this->v_ptr[i - 1]);
			this->v_alloc.construct(&this->v_ptr[pos], value);
			this->v_size++;
			return iterator(this->v_ptr + pos);
		}

/*
** insert: number of elements
*/

		void		insert(iterator position, size_type num, const value_type &value)
		{
			while (num--)
			{
				position = insert(position, value);
			}
		}

/*
** insert: range of elements
*/

		template <class InputIterator>
		void		insert(iterator position, InputIterator first, InputIterator last, \
						typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
		{
			while (first != last)
			{
				position = insert(position, *first++);
				++position;
			}
		}

/*
** erase: one element
*/

		iterator	erase(iterator position)
		{
			if (!this->v_size)
				return (position);
			size_type	i = position.asIndex(this->v_ptr);

			if (i >= this->v_size)
				return (position);
			while (i < this->v_size - 1)
			{
				this->v_alloc.destroy(&this->v_ptr[i]);
				this->v_alloc.construct(&this->v_ptr[i], this->v_ptr[i + 1]);
				i++;
			}
			if (!--this->v_size)
				return (this->end());
			return (position);
		}

/*
** erase: the range of elements
*/

		iterator	erase(iterator first, iterator last)
		{
			for ( ; first != last; )
				erase(--last);
			return (last);
		}

		void		push_back(value_type value)
		{
			insert(end(), value);
		}

		void		pop_back()
		{
			erase(--end());
		}

		void		resize(size_type n, value_type value = value_type())
		{
			if (n > this->v_size)
				for (size_type i = this->v_size; i < n; ++i)
					this->push_back(value);
			else if (n < this->v_size)
				for (size_type i = n; i < this->v_size; ++i)
					this->pop_back();
			else
				return ;
			this->v_size = n;
		}

		void		swap(vector &src)
		{
			std::swap(this->v_ptr,		src.v_ptr);
			std::swap(this->v_size,		src.v_size);
			std::swap(this->v_capacity,	src.v_capacity);
			std::swap(this->v_alloc,	src.v_alloc);
		}
	};

	template <typename T, class Allocator>
	void swap(vector<T, Allocator> &x, vector<T, Allocator> &y)
	{
		x.swap(y);
	}

	template <typename T, class Allocator>
	bool operator==(vector<T, Allocator> const &left, vector<T, Allocator> const &right)
	{
		if (left.size() != right.size())
			return (false);
		return (ft::equal(left.begin(), left.end(), right.begin(), right.end()));
	}

	template <typename T, class Allocator>
	bool operator<(vector<T, Allocator> const &left, vector<T, Allocator> const &right)
	{
		return (ft::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()));
	}

	template <typename T, class Allocator>
	bool operator!=(vector<T, Allocator> const &left, vector<T, Allocator> const &right)	{ return (!(left == right)); }

	template <typename T, class Allocator>
	bool operator<=(vector<T, Allocator> const &left, vector<T, Allocator> const &right)	{ return (!(right < left)); }

	template <typename T, class Allocator>
	bool operator>(vector<T, Allocator> const &left, vector<T, Allocator> const &right)		{ return (right < left); }

	template <typename T, class Allocator>
	bool operator>=(vector<T, Allocator> const &left, vector<T, Allocator> const &right)	{ return (!(left < right)); }

}

#endif
