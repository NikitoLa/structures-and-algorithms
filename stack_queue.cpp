#include <iostream>
#include <ctime>

using namespace std;

struct Task
{
	Task(int ty, int d, int ti)
	{
		type = ty;
		duration = d;
		time = ti;
	}

	int type;
	int duration;
	int time;

	void SetTask(Task* values)
	{
		type = values->type;
		duration = values->duration;
		time = values->time;
	}

	void Info()
	{
		cout << "Time of receipt of the task: " << time << '\t';
		cout << "Task type: " << type << '\t';
		cout << "Task cycles: " << duration << endl;
	}

};

struct TaskList
{
	TaskList(Task* T, TaskList* n)
	{
		TaskValues = T;
		next = n;
	}

	Task* TaskValues;
	TaskList* next;
};

bool TaskListIsEmpty(TaskList* head)
{
	return (head == nullptr);
}

void TaskGenerator(TaskList*& head, int time, const int amount_of_tasks)
{
	int type;
	int duration;
	

	if (time <= amount_of_tasks / 2)
	{
		cout << endl << "Enter the task type " << time << " (0,1,2): ";
		cin >> type;
		cout << "Enter the task execution time " << time << " (1, 2, 3): ";
		cin >> duration;

		Task* new_task = new Task(type, duration, time);
		TaskList* node = new TaskList(new_task, nullptr);

		if (TaskListIsEmpty(head))
		{
			head = node;
		}
		
		else
		{
			TaskList* tmp = head;
			while (tmp->next != nullptr)
			{
				tmp = tmp->next;
			}
			tmp->next = node;
		}
	}

	else
	{
		type = rand() % 3;
		duration = (rand() % 3) + 1;
		cout << endl << "Task type " << time << ": " << type << endl;
		cout << "Task completion time " << time << ": " << duration << endl;

		Task* new_task = new Task(type, duration, time);
		TaskList* node = new TaskList(new_task, nullptr);

		if (TaskListIsEmpty(head))
		{
			head = node;
		}

		else
		{
			TaskList* tmp = head;
			while (tmp->next != nullptr)
			{
				tmp = tmp->next;
			}
			tmp->next = node;
		}
	}
}

void DeleteTask(TaskList*& head)
{
	head = head->next;
}

void ChangeQueue(Task** queue, const int length_of_queue)
{
	int first = 0;
	for (int i = first; i < length_of_queue - 1; i++)
	{
		queue[i] = queue[i + 1];
	}

	queue[length_of_queue - 1] = nullptr;
}

void AddToQueue(Task** queue, TaskList*& head_of_incoming_tasks, const int length_of_queue, bool& queue_is_full)
{
	if (queue[length_of_queue - 1] != nullptr)
	{
		cout << "The queue is completely full, the task is not placed in the queue" << endl << endl;
		queue_is_full = true;
		return;
	}

	else
	{
		int nomber_in_queue = 0;
		while (queue[nomber_in_queue] != nullptr)
		{
			nomber_in_queue++;
		}
		queue[nomber_in_queue] = head_of_incoming_tasks->TaskValues;
		DeleteTask(head_of_incoming_tasks);
	}

}

void AddToStack(TaskList*& top, Task* values)
{
	TaskList* new_task = new TaskList(values, nullptr);
	if (TaskListIsEmpty(top))
	{
		top = new_task;
	}

	else
	{
		new_task->next = top;
		top = new_task;
	}
}

void TaskAllocator(Task* first_task_from_queue, Task& P0, Task& P1, Task& P2, TaskList*& head_of_stack)
{
	int first = 0;

	switch (first_task_from_queue->type)
	{
	case 0:
		if (P0.duration == 0)
		{
			P0.SetTask(first_task_from_queue);
		}
		
		else
		{
			AddToStack(head_of_stack, first_task_from_queue);
		}
		break;

	case 1:
		if (P1.duration == 0)
		{
			P1.SetTask(first_task_from_queue);
		}

		else
		{
			AddToStack(head_of_stack, first_task_from_queue);
		}
		break;

	case 2:
		if (P2.duration == 0)
		{
			P2.SetTask(first_task_from_queue);
		}

		else
		{
			AddToStack(head_of_stack, first_task_from_queue);
		}
		break;
	}
}

void PrintTasks(TaskList* head_of_tasks)
{
	TaskList* tmp = head_of_tasks;
	while (tmp->next != nullptr)
	{
		tmp->TaskValues->Info();
		tmp = tmp->next;
	}
	tmp->TaskValues->Info();
}

void PrintQueue(Task** queue, const int length_of_queue)
{
	for (int i = 0; i < length_of_queue; i++)
	{
		if (queue[i] == nullptr)
		{
			break;
		}
		queue[i]->Info();
	}
}

void InfoAboutProcessors(Task P0, Task P1, Task P2)
{

	switch (P0.duration)
	{
	case 0:
		cout << "Processor type 0: free" << endl;
		break;

	default:
		cout << "Processor type 0: ";
		P0.Info();
	}

	switch (P1.duration)
	{
	case 0:
		cout << "Processor type 1: free" << endl;
		break;

	default:
		cout << "Processor type 1: ";
		P1.Info();
	}

	switch (P2.duration)
	{
	case 0:
		cout << "Processor type 2: free" << endl;
		break;

	default:
		cout << "Processor type 2: ";
		P2.Info();
	}
}

void AddTaskFromStack(Task& P0, Task& P1, Task& P2, TaskList*& head_of_stack)
{
	TaskList* tmp = head_of_stack;

	switch (head_of_stack->TaskValues->type)
	{
	case 0:
		if (P0.duration == 0)
		{
			P0.SetTask(head_of_stack->TaskValues);
			head_of_stack = head_of_stack->next;
			delete tmp;
		}
		break;

	case 1:
		if (P1.duration == 0)
		{
			P1.SetTask(head_of_stack->TaskValues);
			head_of_stack = head_of_stack->next;
			delete tmp;
		}
		break;

	case 2:
		if (P2.duration == 0)
		{
			P2.SetTask(head_of_stack->TaskValues);
			head_of_stack = head_of_stack->next;
			delete tmp;
		}
		break;
	}
}

int main()
{
	srand(time(NULL));

	TaskList* head_of_incoming_tasks = nullptr;
	TaskList* head_of_stack = nullptr;
	Task processor0(0, 0, 0);
	Task processor1(1, 0, 0);
	Task processor2(2, 0, 0);
	
	int amount_of_tasks;
	cout << "Enter the number of incoming tasks: ";
	cin >> amount_of_tasks;
	const int length_of_queue = 3;
	int first_in_queue = 0;

	for (int i = 1; i <= amount_of_tasks; i++)
	{
		TaskGenerator(head_of_incoming_tasks, i, amount_of_tasks);
	}
	Task* queue[length_of_queue]{ nullptr };

	int tacts = 1;
	cout << endl;

	while (head_of_incoming_tasks != nullptr || processor0.duration != 0 || processor1.duration != 0 || processor2.duration != 0 || head_of_stack != nullptr)
	{
		cout << "-------------------------------------------------------------------------------";
		cout << endl << "There is a tact " << tacts << endl << endl;

		bool queue_is_full = false;
		while (!queue_is_full && !TaskListIsEmpty(head_of_incoming_tasks))
		{
			AddToQueue(queue, head_of_incoming_tasks, length_of_queue, queue_is_full);
		}
		
		if (queue[first_in_queue] != nullptr)
		{
			TaskAllocator(queue[first_in_queue], processor0, processor1, processor2, head_of_stack);
			ChangeQueue(queue, length_of_queue);
		}

		if (head_of_incoming_tasks != nullptr)
		{
			cout << "Input tasks" << endl;
			PrintTasks(head_of_incoming_tasks);
			cout << endl;
		}

		if (queue[first_in_queue] != nullptr)
		{
			cout << "Queue Contents" << endl;
			PrintQueue(queue, length_of_queue);
			cout << endl;
		}

		InfoAboutProcessors(processor0, processor1, processor2);
		cout << endl;

		if (head_of_stack != nullptr)
		{
			cout  << "Stack Contents" << endl;
			PrintTasks(head_of_stack);
			cout << endl;
		}

		if (processor0.duration != 0)
		{
			processor0.duration -= 1;
		}

		if (processor1.duration != 0)
		{
			processor1.duration -= 1;
		}

		if (processor2.duration != 0)
		{
			processor2.duration -= 1;
		}
		

		if (queue[first_in_queue] == nullptr && head_of_incoming_tasks == nullptr && head_of_stack != nullptr)
		{
			AddTaskFromStack(processor0, processor1, processor2, head_of_stack);
		}

		tacts++;
	}

	return 0;
}