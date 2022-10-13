#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

const int k = 6; //maximum number of digits of a number
struct list
{
	list(int v, list* n)
	{
		value = v;
		next = n;
	}

	int value;
	list* next;
};

void Menu()
{
	cout << "Menu" << endl;
	cout << "Enter 1 to add an element to the arr" << endl;
	cout << "Enter 2 to remove an element from the array" << endl;
	cout << "Enter 3 to find an element in the array" << endl;
	cout << "Enter 4 to count the number of duplicate elements in the array" << endl;
	cout << "Enter 5 to exit the program" << endl;
}

void FilingArray(int* arr, int amount_of_array)
{
	int variant;
	cout << endl << "Choose how to fill in the array. 1 - Random filling, 2 - fill with pens: ";
	cin >> variant;

	if (variant == 1)
	{
		int cond = pow(10, k);
		for (int i = 0; i < amount_of_array; i++)
		{
			arr[i] = rand() % cond;
		}
	}

	else
	{
		cout << endl;
		for (int i = 0; i < amount_of_array; i++)
		{
			cout << "Element " << i + 1 << ": ";
			cin >> arr[i];
		}
		cout << endl;
	}
}

void PrintArray(int* arr, int amount_of_array)
{
	for (int i = 0; i < amount_of_array; i++)
	{
		cout << arr[i] << " ";
	}	
}

void AddToPocket(list** pocket, int val, int digit)
{
	list* node = new list(val, nullptr);

	if (pocket[digit] == nullptr)
	{
		pocket[digit] = node;
	}

	else
	{
		list* tmp = pocket[digit];
		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
		}
		tmp->next = node;
	}
}

void Sort(int* arr, int amount_of_array)
{
	list* pocket[10]{ nullptr };
	int digit;
	
	for (int i = 1; i <= k; i++)
	{
		int degree = pow(10, i - 1);
		for (int j = 0; j < amount_of_array; j++)
		{
			digit = (arr[j] / degree) % 10;
			AddToPocket(pocket, arr[j], digit);
		}

		int number_in_array = 0;
		for (int j = 0; j < 10; j++)
		{
			while (pocket[j] != nullptr)
			{
				arr[number_in_array] = pocket[j]->value;
				list* tmp = pocket[j];
				pocket[j] = pocket[j]->next;
				number_in_array++;
				delete tmp;
			}
		}
	}
}

void AddElement(int*& val_arr, int& amount_of_elements)
{
	int* new_values_arr = new int[amount_of_elements + 1];

	for (int i = 0; i < amount_of_elements; i++)
	{
		new_values_arr[i] = val_arr[i];
	}

	cout << "Enter the number you want to add to the array: ";
	int new_elem;
	cin >> new_elem;

	new_values_arr[amount_of_elements] = new_elem;

	delete[] val_arr;
	val_arr = new_values_arr;
	amount_of_elements++;
}

void DeleteElement(int*& val_arr, int& amount_of_elements)
{
	int* new_values_arr = new int[amount_of_elements - 1];

	cout << endl << "Enter the number of the item to delete: ";
	int number_to_del;
	cin >> number_to_del;

	if (number_to_del == 1)
	{
		int j = 0;
		for (int i = 1; i < amount_of_elements; i++)
		{
			new_values_arr[j] = val_arr[i];
			j++;
		}
	}

	if (number_to_del == amount_of_elements)
	{
		for (int i = 0; i < amount_of_elements - 1; i++)
		{
			new_values_arr[i] = val_arr[i];
		}
	}

	if (number_to_del != 1 and number_to_del != amount_of_elements)
	{
		int j = 0;
		for (int i = 0; i < amount_of_elements; i++)
		{
			if (i == number_to_del - 1)
			{
				continue;
			}
			new_values_arr[j] = val_arr[i];
			j++;
		}
	}

	delete[] val_arr;
	val_arr = new_values_arr;
	amount_of_elements--;
}

void FindElement(int* val_arr, int amount_of_elements)
{
	cout << endl << "How to find an element. 1 - by position number, 2 - by content: ";
	int variant;
	cin >> variant;
	bool found = false;

	if (variant == 1)
	{
		cout << "Enter the item position number: ";
		int position_number;
		cin >> position_number;
		found = true;
		cout << "Element with a number " << position_number << ": " << val_arr[position_number - 1] << endl;
	}

	else
	{
		cout << "Enter the item you want to find: ";
		int number;
		cin >> number;
		cout << endl;

		for (int i = 0; i < amount_of_elements; i++)
		{
			if (val_arr[i] == number)
			{
				cout << "Element with a number " << i + 1 << ": " << val_arr[i];
				found = true;
			}
		}
	}

	if (found == false)
	{
		cout << "There is no such element" << endl;
	}
}

void CountRepeated(int* val_arr, int amount_of_elements)
{
	int number_to_compare = val_arr[0];
	int duplicate = 0;
	for (int i = 1; i < amount_of_elements; i++)
	{
		if (val_arr[i] == number_to_compare)
		{
			duplicate++;
		}

		else
		{
			number_to_compare = val_arr[i];
		}
	}

	cout << "Number of duplicate elements: " << duplicate << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	cout << "Enter the number of array elements: ";
	int amount_of_elements;
	cin >> amount_of_elements;

	int* values_array = new int[amount_of_elements];
	FilingArray(values_array, amount_of_elements);

	cout << endl << "Source array" << endl;
	PrintArray(values_array, amount_of_elements);

	Sort(values_array, amount_of_elements);

	cout << endl << endl << "Sorted array" << endl;
	PrintArray(values_array, amount_of_elements);

	cout << endl << endl;

	int menu_item = 0;
	while (menu_item != 5)
	{
		Menu();
		cout << endl << "Enter a menu item: ";
		cin >> menu_item;

		switch (menu_item)
		{

		case 1:
		{
			AddElement(values_array, amount_of_elements);

			cout << endl << "New array" << endl;
			PrintArray(values_array, amount_of_elements);

			Sort(values_array, amount_of_elements);

			cout << endl << endl << "New sorted array" << endl;
			PrintArray(values_array, amount_of_elements);
			break;
		}

		case 2:
		{
			DeleteElement(values_array, amount_of_elements);

			cout << endl << "New array" << endl;
			PrintArray(values_array, amount_of_elements);
			break;
		}

		case 3:
		{
			FindElement(values_array, amount_of_elements);
			break;
		}

		case 4:
		{
			CountRepeated(values_array, amount_of_elements);
			break;
		}

		}

		if (menu_item != 5)
		{
			cout << endl << endl;
			system("pause");
			cout << endl;
		}
	}

	cout << endl;
	delete [] values_array;
	return 0;
}