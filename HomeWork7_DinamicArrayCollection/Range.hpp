#pragma once

#ifndef Range_HPP
#define Range_HPP

/*!
	\brief Класс объекта типа "диапазон".
	\details Объект этого класса необходим как промежуточное звено, хранящее длину динамического массива для
	корректной работы методов begin() и end() цикла "range based for"
*/
template<typename Type>
class Range {
public:
	Range(const Type* begin, int length) : begin_(begin), length_(length), counter_(0) {}
	~Range() {}
	const Type* begin()const { return begin_; }
	const Type* end()const { return begin_ + length_; }
	int counter_; // Счётчик кол-ва итераций для циклов (публичный для доступа объектов других классов)
private:
	const Type* begin_;
	int length_;	
};

#endif // !Range_HPP