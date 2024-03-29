
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forword_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forword_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};


template <class Category, class T, class Distance = ptrdiff_t,
class Pointer = T *, class Reference = T &>
struct iterator
{
	typedef Category 		iterator_category;
	typedef T 				value_type;
	typedef Distance		difference_type;
	typedef Pointer			pointer;
	typedef Reference 		Reference;
};

template <class Iterator>
struct iterator_traits
{
	typedef typename Iterator::iterator_category	iterator_category;
	typedef typename Iterator::value_type 			value_type;
	typedef typename Iterator::difference_type 		difference_type;
	typedef typename Iterator::pointer  			pointer;
	typedef typename Iterator::reference 			reference;
};

//designed for native pointer
template <class T>
struct iterator_traits<T*>
{
	typedef random_access_iterator_tag 				iterator_category;
	typedef T 										value_type;
	typedef ptrdiff_t 								difference_type;
	typedef T * 									pointer;
	typedef T & 									reference;
}




