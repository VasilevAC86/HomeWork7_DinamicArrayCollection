#pragma once

#include<cstdlib>
#include<ctime>
#include"Range.hpp"

#ifndef DinamicArrray_HPP
#define DinamicArrray_HPP

/*! 
	\brief Шаблонный класс для создания объекта - очереди динамического массива	 
	Каждый элемент очереди - объект типа данных Type
*/
template<typename Type>
class DinamicArray {
public:
	/// \brief Конструктор по умолчанию
	DinamicArray() :data_(nullptr), size_(0){}
	/// \brief Конструктор копирования
	DinamicArray(const DinamicArray& other);
	/// \brief Конструктор переноса
	DinamicArray(DinamicArray&& other);
	~DinamicArray() {
		if (data_)
			delete[]data_;
	}	
	/*!
		\brief Метод добавления элемента в коллекцию
		\details Если в коллекции ещё ничего нет, то создаём колекцию размером в один элемент, в который записываем переданное значение.
		Если в коллекции есть элементы, то в зависимости от выбора пользователя новый элемент добавляем либо в конец очереди, либо в элемент \
		коллекции, указанной пользователем путём создания нового массива с увеличенным на 1	размером, перезаписи в новый массив данных из старого \
		массива, последний элемент нового массива = переданному значению.
		После формирования нового массива, старый удаляем, указатель перенаправляем на новый массив.
	*/
	void AddElement();
	/*!
		\brief Метод удаления выбранного пользователем элемента из коллекции
		\details Если в коллекции больше одного элемента, т.е. после удаления элемента она не будет пустой, то создаём новый массив разром на \
		один элемент меньше, чем исходный массив. В новый массив перезаписываем все элементы исходного, индексы которых не совпадают с \
		переданным в метод индексом.				
		После формирования нового массива, старый удаляем, указатель перенаправляем на новый массив
	*/
	void PopElement(int position);
	/*!
		\brief Метод изменения значения выбранного пользователем элемента из коллекции
		\details Просто презаписывается переданное пользователем значение value по индексу num
	*/
	void ChangeElement(int position, Type value) { data_[position] = value; }	
	/// \brief Сэттэр для установки размера коллекции
	void SetSize(int n) { this->size_ = n; }
	/// \brief Сэттэр для выделения памяти под коллекцию размером size_
	void SetAdress() { this->data_ = new Type[size_]; }	
	/*!
		\brief Сэттэр для рандомного заполнения коллекции в зависимости от типа данных объекта
		\details В зависимости от переданного в метод типа данных Type коллукция заполняется рандомными значениями
		Метод может работать со следующими типами данных: int, double, float, char, bool.
		При необходимости, метод можно дописать другими типами данных
	*/
	void SetValue();	
	/*! 
		\brief Гэттэр для получения размера коллекции
		\details Метод написан для корректной работы стандартной функции std::size()
	*/
	int size()const { return size_; }	
	/// \brief Гэттэр для получения значения i-того элемента коллекции
	Type GetValue(int i)const { return data_[i]; }
	/// \brief Гэттэр для получения адреса коллекции
	Type* GetAdress()const { return data_; }	
	int GetSize()const { return size_; }	
private:
	Type* data_; ///< Указатель на динамический массив элементов типа Type                
	int size_; ///< Размер динамического массива			
};

template<typename Type>
inline DinamicArray<Type>::DinamicArray(const DinamicArray& other) {
	size_ = other.size_;
	data_ = new Type[size_];
	for (int i = 0; i < size_; ++i)
		data_[i] = other.data_[i];
}

template<typename Type>
inline DinamicArray<Type>::DinamicArray(DinamicArray&& other) {
	this->size_ = 0;
	this->data_ = nullptr;
	std::swap(data_, other.data_);
	std::swap(size_, other.size_);
}

template<typename Type>
inline void DinamicArray<Type>::PopElement(int position) {
	if (size_ - 1) { // Если после удаления элемента в коллекции что-то остаётся, то
		Type* tmp = new Type[size_ - 1];		
		Range<Type> R(data_, size_); // Создаём объект класса Range для возможности использования цикла range based for	
		bool key = false;
		for (Type element : R) {
			if (R.counter_ < position) 
				tmp[R.counter_] = element;							
			if (R.counter_ == position)
				if (key) 
					tmp[R.counter_] = element;
				else {
					key = true;					
					continue;
				}			
			if (R.counter_ > position) 
				tmp[R.counter_] = element;							
			++R.counter_;
		}		
		this->size_ -= 1;
		delete[]data_; // Чисти память от старого массива
		this->data_ = tmp; // Перенаправляем указатель на новый массив
		R.~Range(); // Удаляем объект класса Range
		return;
	}	
	this->size_ = 0;
	delete[]data_;
	data_ = nullptr;
}

template<typename Type>
inline void DinamicArray<Type>::SetValue() {
	srand(time(NULL));
	if (typeid(Type) == typeid(int))
		for (int i = 0; i < size_; ++i)
			data_[i] = rand() % (200) - 100;
	if (typeid(Type) == typeid(double) || typeid(Type) == typeid(float))
		for (int i = 0; i < size_; ++i)
			data_[i] = rand() * Type(100) / RAND_MAX;
	if (typeid(Type) == typeid(char))
		for (int i = 0; i < size_; ++i)
			data_[i] = rand() % 256;
	if (typeid(Type) == typeid(bool))
		for (int i = 0; i < size_; ++i)
			data_[i] = rand() % 2;
}

template<typename Type>
inline void DinamicArray<Type>::AddElement() {
	std::cout << "Enter a value of the new element -> ";
	Type value;
	std::cin >> value;
	if (!data_) { // Если в коллекции ещё ничего нет
		data_ = new Type[1]{ value };
		++size_;
		return;
	}	
	Type* tmp = new Type[size_ + 1];
	Range<Type> R(data_, size_); // Создаём объект класса Range для возможности использования цикла range based for	
	std::cout << "\033[93mDo you want to add a new element to the end of the collection?\033[0m" << std::endl << \
		"Press \033[91m1\033[0m for yes \033[4mor\033[0m press \033[91many other key\033[0m if you want to add the new elelment to a specific location\nYour choice -> ";
	char my_Choice;
	std::cin >> my_Choice;
	if (my_Choice == '1') {
		for (Type element : R) {
			tmp[R.counter_] = element;
			++R.counter_;
		}
		tmp[size_] = value;
	}
	else {
		std::cout << "Enter a position to add the new element -> ";
		int position;
		std::cin >> position;
		try {
			if (position > size_ || position <= 0)
				throw std::exception("\033[91mInput error! The element's number can not be more than the size of collection or negative or equal to zero!\033[0m");
		}
		catch (const std::exception& ex) {
			std::cout << ex.what() << std::endl;
			while (position > size_ || position <= 0) {
				std::cout << "Enter the number of element one more time -> ";
				std::cin >> position;
			}
		}
		position--; // для приведения порядкового номера элемента коллекции к индексу массива		
		for (Type element : R) {
			if (R.counter_ < position)
				tmp[R.counter_] = element;
			if (R.counter_ == position) {
				tmp[R.counter_] = value;
				tmp[R.counter_ + 1] = element;
			}
			if (R.counter_ > position)
				tmp[R.counter_ + 1] = element;
			++R.counter_;
		}		
	}
	delete[]data_; // Чистим память от старого массива
	++size_; // Увеличиваем размер коллекции на один элемент
	this->data_ = tmp; // Перенаправляем указатель на участок памяти с новым массивом
	R.~Range(); // Удаляем объект класса Range
}

#endif // !DinamicArrray_HPP


