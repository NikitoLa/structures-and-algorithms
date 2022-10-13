#include <cstddef>
#include <iostream>
#include <cmath>

using namespace std;

struct Node
{
	int val;
	int count;
	Node* next;

	Node(int x, int c, Node* t)
	{
		val = x;
		count = c;
		next = t;
	}
};

bool empty(Node* first)
{
	return (first != nullptr);
}

void input_elem(Node*& first, int value, int couter)
{
	Node* new_elem = new Node(value, couter, NULL);

	if (empty(first) == 0)
		first = new_elem;
	else
	{
		Node* tmp = first;

		while (tmp->next != NULL)
			tmp = tmp->next;

		tmp->next = new_elem;
	}
}

Node* erase_first(Node*& first)
{
	if (empty(first) != 0)
	{
		if (first->next == NULL)
			first = nullptr;
		else
		{
			Node* elem = first;
			first = first->next;
			delete elem;
		}
	}

	return first;
}

Node* erase_elem(Node*& first, int elem)
{
	if (empty(first) == 0)
		return first;
	else
		if (first->val == elem)
		{
			erase_first(first);
			return first;
		}
		else
		{
			Node* one = first;
			Node* second = first->next;
			while (second->next != NULL && second->val != elem)
			{
				second = second->next;
				one = one->next;
			}
			if (second->next == NULL && second->val != elem)
			{
				cout << "this item is not in the list.";
				return first;
			}
			one->next = second->next;
			delete second;
		}
	return first;
}

void print_list(Node* first, char* word)
{
	if (empty(first) == 0)
	{
		cout << "The search list is empty" << endl;
		return;
	}

	else
	{
		Node* tmp = first;

		cout << word << endl;
		while (tmp->next != NULL)
		{	
			cout << tmp->val << ' ';
			tmp = tmp->next;
		}
		cout << tmp->val << endl;
	}
}

Node* find_max(Node* first, Node*& max)
{
	Node* tmp = first;
	max = tmp;

	if (empty(first) != 0)
	{
		tmp = first;
		max = tmp;

		while (tmp->next != NULL)
		{
			if (tmp->count > max->count)
				max = tmp;

			tmp = tmp->next;
		}
		if (tmp->count > max->count)
			max = tmp;
	}

	return max;
}

int find_elem(Node*& first, int value)
{
	int cout = 0;

	if (empty(first) != 0)
	{
		Node* tmp = first;

		while (tmp->next != NULL)
		{
			if (tmp->val == value)
				cout++;

			tmp = tmp->next;
		}
		if (tmp->val == value)
			cout++;
	}
	cout++;
	return cout;
}

int main()
{
	setlocale(LC_ALL, "rus");
	Node* first = nullptr;
	int value;
	int kol_elem;
	int appear;
	cout << "Enter the number of items in the list: ";
	cin >> kol_elem;
	for (int i = 0; i < kol_elem; i++)
	{
		
		cout << "Enter the element: ";
		cin >> value;
		appear = find_elem(first, value);
		input_elem(first, value, appear);
		
	}
	print_list(first, (char*)"Initial list: ");
	/**/
	cout << endl << endl;
	Node* second = nullptr;
	Node* maximum = nullptr;

	maximum = find_max(first, maximum);
	while (maximum->count > 1)
	{
		value = maximum->val;
		appear = maximum->count;
		input_elem(second, value, appear);

		for (int i = 0; i < maximum->count; i++)
		{
			first = erase_elem(first, maximum->val);
		}

		maximum = find_max(first, maximum);
	}

	print_list(second, (char*)"second list: ");
}

