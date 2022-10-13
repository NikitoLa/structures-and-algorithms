#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

const int size_of_spreadsheet = 100;
const int size_of_key = 9;
int k = 0;

void Menu()
{
	cout << "Menu:" << endl;
	cout << "Press 1 to check the hash function collision distribution." << endl;
	cout << "Press 2 to fill in the hash table." << endl;
	cout << "Press 3 to display the contents of the hash table." << endl;
	cout << "Press 4 to completely clear the hash table." << endl;
	cout << "Press 5 to add the key to the hash table." << endl;
	cout << "Press 6 to remove the key from the hash table." << endl;
	cout << "Press 7 to find the item in the hash table." << endl;
	cout << "Press 8 to exit the program." << endl;
}

string KeyGenerator()
{
	string key = "";
	string str_k = to_string(k);

	key += "0";

	int second = (rand() % 9) + 1;
	string str_second = to_string(second);

	key += str_second;
	key += "-";

	for (int i = 0; i < 6 - str_k.length(); i++)
	{
		key += "0";
	}
	key += str_k;

	k++;

	return key;
}

int HashFunction(string key)
{
	unsigned int hash = 0;
	unsigned int kod = 0;
	for (int i = 1; i <= size_of_key; i++)
	{
		kod = int(key[i])*(i*99);
		hash += 11*(pow(kod, 3));
	}
	hash %= size_of_spreadsheet;
	return hash;
}

void PrintCollisionsToFile(int* array_for_collisions)
{
	string path = "C:\\Users\\Виталя\\Documents\\ВУЗ домашки\\структуры и алгоритмы, 3й сем\\лаба4\\hash\\hash\\collisions.txt";
	ofstream fout;
	fout.open(path);
	if (fout.is_open())
	{
		for (int i = 0; i < size_of_spreadsheet - 1; i++)
		{
			fout << array_for_collisions[i] << '\n';
		}
		fout << array_for_collisions[size_of_spreadsheet - 1];
	}

	else
	{
		cout << "could not open the file" << endl;
	}
	fout.close();
}

bool FillHashSpreadsheet(string* value, string key, int hashed_key)
{
	bool key_setted = false;
	if (value[hashed_key] == "\0" or value[hashed_key] == "delete")
	{
		value[hashed_key] = key;
		key_setted = true;
	}

	else
	{
		for (int i = hashed_key + 1; i < size_of_spreadsheet; i++)
		{
			if (value[i] == "\0" or value[hashed_key] == "delete")
			{
				value[i] = key;
				key_setted = true;
				break;
			}
		}

		if (key_setted == false)
		{
			for (int i = 0; i < hashed_key; i++)
			{
				if (value[i] == "\0" or value[hashed_key] == "delete")
				{
					value[i] = key;
					key_setted = true;
					break;
				}
			}
		}
	}

	if (key_setted == false)
	{
		cout << "The table is completely full, no new element has been added" << endl << endl;
	}

	return key_setted;
}

void PrintHashSpreadsheet(string* value)
{
	for (int i = 0; i < size_of_spreadsheet; i++)
	{
		cout << "Segment " << i + 1 << ": " << value[i] << endl;
	}
}

void ClearHashSpreadsheet(string* value)
{
	for (int i = 0; i < size_of_spreadsheet; i++)
	{
		value[i] = "\0";
	}
}

string ChekKey(string text)
{
	while (true)
	{
		cout << endl << text;
		string key;
		cin >> key;
		bool incorrect = false;
		if (cin.get() != '\n' or key.length() > 6)
		{
			cin.ignore(32767, '\n');
			cout << "Incorrect input, please repeat" << endl;
			continue;
		}
		
		else
		{
			int i = 0;
			while (key[i] != '\0')
			{
				if (i == 0 or i == 5)
				{
					if (key[i] < '0' or key[i] > '9')
					{
						cout << "Incorrect input, please repeat" << endl;
						incorrect = true;
						break;
					}
				}

				else
				{
					if (key[i] < 'A' or key[i] > 'Z')
					{
						cout << "Incorrect input, please repeat" << endl;
						incorrect = true;
						break;
					}
				}
				i++;
			}
		}

		if (incorrect)
		{
			continue;
		}

		else
		{
			return key;
		}
	}
}

void DeleteKey(string* value, string key, int hashed_key)
{
	int variant;
	cout << endl << "Choose how to delete the item. 1 - by segment number, 2 - by key: ";
	cin >> variant;

	if (variant == 1)
	{
		int number;
		cout << "Enter the segment number: ";
		cin >> number;
		if (value[number - 1] == "\0" or value[number - 1] == "delete")
		{
			cout << endl << "This segment is already empty" << endl;
			return;
		}
		value[number - 1] = "delete";
		cout << endl << "Data successfully deleted" << endl;
		return;
	}

	else
	{
		key = ChekKey("Enter the key . The key has the form cBBBBc, where c is a digit, B is a capital letter of the Latin alphabet: ");
		hashed_key = HashFunction(key);
		if (value[hashed_key] == key)
		{
			value[hashed_key] = "delete";
			cout << endl << "Data successfully deleted" << endl;
			return;
		}

		else
		{
			for (int i = hashed_key + 1; i < size_of_spreadsheet; i++)
			{
				if (value[i] == "\0")
				{
					cout << "This key is not in the table" << endl;
					return;
				}

				if (value[i] == key)
				{
					value[i] = "delete";
					cout << endl << "Data successfully deleted" << endl;
					return;
				}
			}

			for (int i = 0; i < hashed_key; i++)
			{
				if (value[i] == "\0")
				{
					cout << "This key is not in the table" << endl;
					return;
				}

				if (value[i] == key)
				{
					value[i] = "delete";
					cout << endl << "Data successfully deleted" << endl;
					return;
				}
			}
		}
	}
	cout << "This key is not in the table" << endl;
}

void FindKey(string* value, string key, int hashed_key)
{
	int variant;
	cout << endl << "Choose how to find the item. 1 - by segment number, 2 - by key: ";
	cin >> variant;

	if (variant == 1)
	{
		int number;
		cout << "Enter the segment number: ";
		cin >> number;
		if (value[number - 1] == "\0" or value[number - 1] == "delete")
		{
			cout << "Segment " << number << " free";
			return;
		}
		cout << "Segment " << number << ": " << value[number - 1];
		return;
	}

	else
	{
		key = ChekKey("Enter the key . The key has the form cBBBBc, where c is a digit, B is a capital letter of the Latin alphabet: ");
		hashed_key = HashFunction(key);
		if (value[hashed_key] == key)
		{
			cout << endl << "Segment number: " << hashed_key + 1 << '\t' << "Data: " << value[hashed_key] << endl;
			return;
		}

		else
		{
			for (int i = hashed_key + 1; i < size_of_spreadsheet; i++)
			{
				if (value[i] == "\0")
				{
					cout << "This key is not in the table" << endl;
					return;
				}

				if (value[i] == key)
				{
					cout << endl << "Segment number: " << i + 1 << '\t' << "Data: " << value[i] << endl;
					return;
				}
			}

			for (int i = 0; i < hashed_key; i++)
			{
				if (value[i] == "\0")
				{
					cout << "This key is not in the table" << endl;
					return;
				}

				if (value[i] == key)
				{
					cout << endl << "Segment number: " << i + 1 << '\t' << "Data: " << value[i] << endl;
					return;
				}
			}
		}
	}

	cout << "This key is not in the table" << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	system("mode con cols=160 lines=2100");


	string* values_array = new string[size_of_spreadsheet]{ "\0" };
	string key;
	int hashed_key = 0;

	int menu_item = 0;
	while (menu_item != 8)
	{
		Menu();
		cout << endl << "Enter a menu item: ";
		cin >> menu_item;
		bool key_added;
		switch (menu_item)
		{

		case 1:

		{
			int array_for_collision[size_of_spreadsheet]{ 0 };
			int amount_of_keys;

			cout << endl << "Enter the number of keys to create: ";
			cin >> amount_of_keys;

			for (int i = 0; i < amount_of_keys; i++)
			{
				key = KeyGenerator();
				hashed_key = HashFunction(key);
				array_for_collision[hashed_key]++;
			}

			PrintCollisionsToFile(array_for_collision);
			cout << "The data has been successfully added to the file" << endl;
			break;
		}

		case 2:

		{
			int number_of_keys;
			cout << endl << "Enter the number of keys to create: ";
			cin >> number_of_keys;

			for (int i = 0; i < number_of_keys; i++)
			{
				key = KeyGenerator();
				hashed_key = HashFunction(key);
				FillHashSpreadsheet(values_array, key, hashed_key);
			}
			cout << "Hash table has been filled in successfully" << endl;
			break;
		}

		case 3:

		{
			PrintHashSpreadsheet(values_array);
			break;
		}

		case 4:
		{
			ClearHashSpreadsheet(values_array);
			cout << "Hash table cleared successfully" << endl;
			break;
		}

		case 5:

		{
			
			key = ChekKey("Enter the key . The key has the form cBBBBc, where c is a digit, B is a capital letter of the Latin alphabet: ");
			hashed_key = HashFunction(key);
			key_added = FillHashSpreadsheet(values_array, key, hashed_key);
			if (key_added)
			{
				cout << "Key added" << endl;
			}
			break;
		}

		case 6:

		{
			DeleteKey(values_array, key, hashed_key);
			break;
		}

		case 7:

		{
			FindKey(values_array, key, hashed_key);
			break;
		}
		}

		if (menu_item != 8)
		{
			cout << endl;
			system("pause");
			system("cls");
		}
	}

	delete[] values_array;
	return 0;
}
