# include <iostream>
#include"DinamicArray.hpp"
#include"Range.hpp"

/// \brief Прототип шаьлонной функции для вывода в консоль коллекции
template<typename Type>
void PrintCollection(const DinamicArray<Type>&obj);

int main() {
	// ------------------- Заполнение коллекции исходными данными -----------------------
	DinamicArray<float> darr;
	int size;
	std::cout << "\033[91mStep 1. Filling the collection with source data\033[0m\nEnter the length of the collection -> ";
	std::cin >> size;	
	try {
		if (size < 0)
			throw std::exception("\033[91mInput error! The collection's size can not be negative!\033[0m");
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		while (size < 0) {
			std::cout << "Enter the collection's one more time -> ";
			std::cin >> size;
		}
	}
	if (size) {
		darr.SetSize(size);
		darr.SetAdress();
		darr.SetValue();
	}
	PrintCollection(darr);	
			
	// ------------------- Добавление к коллекции элемента -----------------------	
	std::cout << std::endl << "\033[91mStep 2. Adding an item to a collection\033[0m" << std::endl; 
	darr.AddElement();	
	std::cout << "\033[92mThe new element has been successfully added!\033[0m";
	PrintCollection(darr);

	// ------------------- Удаление элемента из коллекции -----------------------
	std::cout << std::endl << "\033[91mStep 3. Deleting an element from a collection\033[0m\nEnter a number of the element you want to delete -> ";
	int position;
	std::cin >> position;
	try {
		if (position > std::size(darr) || position <= 0)
			throw std::exception("\033[91mInput error! The element's number can not be more than the size of collection or negative or equal to zero!\033[0m");
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		while (position > std::size(darr) || position <= 0) {
			std::cout << "Enter the number of element one more time -> ";
			std::cin >> position;
		}
	}
	darr.PopElement(position - 1);
	std::cout << "\033[92mThe element number \033[0m" << position << "\033[92m has been successfully deleted!\033[0m";
	PrintCollection(darr);
	 
	// ------------------- Доступ к элементу коллекции -----------------------
	std::cout << std::endl << "\033[91mStep 4. Access to a collection element\033[0m\nEnter a number of the element you want to see -> ";
	std::cin >> position;
	try {
		if (position > std::size(darr) || position <= 0)
			throw std::exception("\033[91mInput error! The element's number can not be more than the size of collection or negative or equal to zero!\033[0m");
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		while (position > std::size(darr) || position <= 0) {
			std::cout << "Enter the number of element one more time -> ";
			std::cin >> position;
		}
	}
	std::cout << "You have selected an element number \033[92m" << position << "\033[0m with the value \033[92m" << darr.GetValue(position - 1) << "\033[0m" << std::endl \
		<< "\033[93mDo you want to change this element? \033[0m" << std::endl << "Press \033[91m1\033[0m to yes \033[4mor\033[0m press \033[91many other key\033[0m for no"\
		<< std::endl << "Your choice -> ";
	char my_Choice;
	float new_item;
	std::cin >> my_Choice;
	if (my_Choice == '1') {
		std::cout << "Enter a new value -> ";
		std::cin >> new_item;
		darr.ChangeElement(position - 1, new_item);
		PrintCollection(darr);
	}
	//darr.~DinamicArray();

	return 0;
}

template<typename Type>
void PrintCollection(const DinamicArray<Type>& obj) {
	if (std::size(obj)) {
		std::cout << std::endl << "\033[93mThe data type of collection is\033[0m \033[92m" << typeid(Type).name() << "\033[0m" << std::endl << \
			"The collection consists of the following elements: ";				
		Range<Type> R(obj.GetAdress(), std::size(obj));
		for (Type element : R)
			std::cout << "\033[92m" << element << "\033[0m, ";		
		std::cout << "\b\b." << std::endl;
		R.~Range();
		return;
	}
	std::cout << std::endl << "\033[93mThe collection is empty!\033[0m" << std::endl;	
}
