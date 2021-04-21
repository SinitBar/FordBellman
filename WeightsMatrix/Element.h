#pragma once
#include <iostream>
using namespace std;
template <class Key_Type, class Value_Type>
class Element
{
	Element<Key_Type, Value_Type>* next;
	Value_Type data;
	Key_Type key;
	void set_next(Element<Key_Type, Value_Type>* new_element) { next = new_element; }
	void set_data(Value_Type new_data) { data = new_data; }
	void set_key(Key_Type new_key) { key = new_key; }

public:
	Element() { }
	Element<Key_Type, Value_Type>* get_next() { return next; }
	Value_Type get_data() { return data; }
	Key_Type get_key() { return key; }
	~Element() {}
	template <class Key_Type, class Value_Type> friend class Queue;
};