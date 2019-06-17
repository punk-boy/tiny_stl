#include <iostream>
#include <new>
#include <cstddef>
#include <climits>
#include <cstdlib>
/*******************************************************************
							ALLOCATOR
********************************************************************/
namespace MY_ALLOC
{
template <class T>
inline T * _allocate(ptrdiff_t size, T *)
{
	std::set_new_handler(0);
	T * tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
	if(tmp == 0)
	{
		std::cerr << "out of memory" << std::endl;
		exit(0);
	}
	return tmp;
}

template <class T>
inline void _deallocate(T * buffer)
{
	::operator delete(buffer);
}

template <class T1, class T2>
inline void _construct(T1 * p, const T2 & value)
{
	new(p) T1(value);
}

template <class T>
inline void _destroy(T * ptr)
{
	ptr->~T();
}

template <class T>
class allocator
{
public:
	typedef T 					value_type;
	typedef T * 				pointer;
	typedef const T *			const_pointer;
	typedef T & 				reference;
	typedef const T & 			const_reference;
	typedef size_t				size_type;
	typedef ptrdiff_t 			difference_type;

	template <class U>
	struct rebind{
		typedef allocator<U>	other;
	};

	/*
	allocator(){}
	allocator(const allocator &){}
	template<class U>allocator(const allocator<U> &){}
	~alloctator(){}
	*/

	pointer address(reference x) const
	{
		return (pointer)&x;
	}

	const_pointer const_address(const reference x) const
	{
		return (const_pointer)&x;
	}

	pointer allocate(size_type n, const void * hint= 0)
	{
		return _allocate((difference_type)n, (pointer)0);
	}

	void deallocate(pointer p, size_type n)
	{
		_deallocate(p);
	}

	size_type max_type() const
	{
		return size_type(UINT_MAX/sizeof(T));
	}

	void construct(pointer p, const T& value)
	{
		_construct(p, value);
	}

	void destroy(pointer p)
	{
		_destroy(p);
	}
};
}//end of namespace MY_ALLOC



/*******************************************************************
							ITERATOR
********************************************************************/





/*******************************************************************
							VECTOR
********************************************************************/

namespace MY_VECTOR
{

template <class T, class Alloc>
class vector
{
public:
	typedef T 					value_type;
	typedef value_type * 		pointer;
	typedef value_type *		iterator;
	typedef value_type & 		reference;
	typedef size_t 				size_type;
	typedef ptrdiff_t			difference_type;

protected:
	//typedef MY_ALLOC::allocator<T> data_allocator;
	typedef Alloc 				data_allocator;
	iterator start;
	iterator finish;
	iterator end_of_storage;

	void insert_aux(iterator position, const T & x);
	void deallocate(){}
	void fill_initialize(size_type n, const T & value){}


public:
	iterator begin()
	{
		return start;
	}

	iterator end()
	{
		return finish;
	}

	size_type size() const
	{
		return size_type(end() - begin())
	}

	size_type capacity() const
	{
		return size_type(end_of_storage - begin());
	}

	bool empty()
	{
		return begin() == end();
	}

	reference operator[](size_type n)
	{
		return *(begin() + n);
	}





};

}




/*******************************************************************
							SORT
********************************************************************/



/*******************************************************************
							MAIN
********************************************************************/

#include <vector>
#include <algorithm>

int main()
{
	const int len = 5;
	int a[len] = {0, 2, 9, 1, 5};
	std::vector<int, MY_ALLOC::allocator<int> > iv(a, a+len);

	std::sort(iv.begin(), iv.end());

	for(std::vector<int, MY_ALLOC::allocator<int> >::iterator i = iv.begin();
		i != iv.end(); ++i)
	{
		std::cout << *i << std::endl;
	}



	return 0;
}






