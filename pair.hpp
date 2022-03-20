#ifndef UT_HPP
# define UT_HPP

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		public:
		typedef	T1		first_type;
		typedef	T2		second_type;
		first_type		first;
		second_type		second;

		pair(void) :
			first(first_type()),
			second(second_type())
		{}
		template <class U, class V>
			pair(const pair<U,V> &pr) :
				first(pr.first),
				second(pr.second)
			{}
		pair(const first_type &a, const second_type &b) :
			first(a),
			second(b)
		{}
		pair	&operator=(const pair &pr)
		{
			if (*this == pr)
				return (*this);
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}
	};

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	template <class T1, class T2>
	bool operator==(const pair<T1,T2> &left, const pair<T1,T2> &right)
	{
		return (left.first == right.first && \
				left.second == right.second);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1,T2> &left, const pair<T1,T2> &right)
	{
		return (left.first < right.first || \
				(left.first == right.first && left.second < right.second));
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1,T2> &left, const pair<T1,T2> &right)
	{
		return (!(left == right));
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1,T2> &left, const pair<T1,T2> &right)
	{
		return (!(right < left));
	}

	template <class T1, class T2>
	bool operator>(const pair<T1,T2> &left, const pair<T1,T2> &right)
	{
		return (right < left);
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1,T2> &left, const pair<T1,T2> &right)
	{
		return (!(left < right));
	}
}

# endif