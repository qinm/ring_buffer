#ifndef MY_RING_BUFFER_H
#define MY_RING_BUFFER_H

#include <iostream>
using namespace std;

template <class Type>
class ring_buffer{	
public:
	typedef ring_buffer<Type> this_type;
	typedef typename Type value_type;
	typedef typename ptrdiff_t  difference_type;
	typedef typename Type* pointer;
	typedef typename Type& reference;
	typedef typename ptrdiff_t size_type;

	ring_buffer():m_buf(0),m_end(0),m_first(0),m_last(0),m_size(0){}//create an empty ring_buffer with zero capacity
	ring_buffer(size_type n):m_size(0){
		m_begin=new value_type[n];
		m_first=m_last=m_begin;
		m_end=m_begin+n;
	}
	ring_buffer(size_type n,value_type item):m_size(n){	
		m_begin=new value_type[n];
		m_first=m_last=m_begin;
		for(size_t i=0;i<m_size;i++)
			*m_last++=item;
		m_end=m_begin+n;
	}
	ring_buffer(ring_buffer& dest):m_size(dest.m_size ){
		m_begin=new value_type[dest.capacity()];
		m_end=m_begin+dest.capacity();
		m_first=m_last=m_begin;
		for(int i=0;i<dest.size();i++)
		{
			*m_last=*(dest.m_begin+i);
			m_last++;
			if(m_last==m_end)
				m_last=m_begin;
		}
	}
	bool full(){return m_size==capacity();}
	bool empty(){return m_size==0;}
	size_type capacity() const{ return m_end - m_begin; }
	size_type size() const{ return m_size; }
	value_type sum(){
		int index=0;
		value_type sum=0;
		for(index;index<m_size;index++)
			sum+=m_begin[index];
		return sum;
	}
	value_type operator[](int index){
		if(m_size==0||index>m_size||index<0)
			return -1;
		pointer tmp=m_first;
		for(int i=0;i<index;i++)
		{
			tmp++;
			if(tmp==m_end)
				tmp=m_begin;
		}
		return *tmp;
	}
	void push_back(value_type item){
		if(full())
		{	
		if(empty())
			return;
		*m_last=item;
		if(++m_last==m_end)
			m_last=m_begin;
		m_first=m_last;

		}
		else
		{
		*m_last=item;
		m_size++;
		m_last++;
		if(m_last==m_end)
			m_last=m_begin;
		}
	}
	void pop_front(){
	if(empty())
		return;
	cout<<"pop front:"<<*m_first<<endl;
	if(++m_first==m_end)
	{
		m_first=m_begin;
	}
		m_size--;
}
	~ring_buffer(){
		delete [] m_begin;
	}
private:
	pointer m_begin;
	pointer m_end;
	pointer m_first;
	pointer m_last;
	size_type m_size;
};
#endif