//name the file using your student ID
//e.g 012345678.cpp


// do not change the declaration section !
#include <iostream>

using namespace std;

class Node
{
public:
	Node(int value, Node* nextptr = nullptr, Node* prevptr = nullptr,
		int currentpriority = 0);

	int getVal(void);

	Node* getNext(void);

	Node* getPrev(void);

	void setVal(int value);

	void setPrev(Node* prevptr);

	void setNext(Node* nextptr);

	int getPriority(void);

	void setPriority(int priority);


private:
	Node* next;
	Node* prev;
	int priority;
	int value;
};

class Stack
{
public:
	Stack(void);

	~Stack(void);

	void Push(int value);

	Node* NodePop(void);

	int Pop(void);

private:

	Node* top;
};

class Queue
{
public:
	Queue(void);

	~Queue(void);

	void Enqueue(int i, int priority = 0);

	int Dequeue(void);

protected:

	Node* back;
	Node* front;

private:

	virtual Node* NodeDequeue(void);
};


class Scheduler : public Queue
{
public:
	//you can only overide PUBLIC methods from the Queue class
	void Enqueue(int i, int priority = 0);

	int Dequeue(void);

private:
	//you can add private methods and attributes
	Node* NodeDequeue(void);
};

//-------------------------------YOUR implementation goes here!!!-----------------------

Node::Node(int value, Node* nextptr, Node* prevptr, int currentpriority) 
{
	this->value = value;
	this->next = nextptr;
	this->prev = prevptr;
	this->priority = currentpriority;
}


int Node::getVal(void) 
{
	return value;
}

Node* Node::getNext(void)
{
	return next;
}


Node* Node::getPrev(void) 
{
	return prev;
}

void Node::setVal(int value) 
{
	this->value = value;
}


void Node::setPrev(Node* prevptr) 
{
	this->prev = prevptr;
}

void Node::setNext(Node* nextptr) 
{
	this->next = nextptr;
}


int Node::getPriority(void) 
{
	return priority;
};

void Node::setPriority(int priority) 
{
	this->priority = priority;
};

Stack::Stack(void) 
{
	top = nullptr;
}

Stack::~Stack(void) 
{
	while (top != nullptr)
	{
		Pop();
	}
}

void Stack::Push(int value) 
{
	Node* tmp = new Node(value, top);
	top = tmp;
}

Node* Stack::NodePop(void) 
{
	Node* tmp = top;

	if (top != nullptr)
	{
		top = top->getNext();
	}

	return tmp;
}

int Stack::Pop(void) 
{
	Node* tmp = NodePop();

	int ret = 0;

	if (tmp != nullptr)
	{
		ret = tmp->getVal();
		
	}
	else
	{
		throw "Stack Empty";
	}

	delete tmp;
	return ret;
}


Queue::Queue(void) 
{
	front = back = nullptr;
}


Queue::~Queue(void) 
{
	while (front != nullptr)
	{
		delete NodeDequeue();
	}
}

void Queue::Enqueue(int i, int priority)
{
	Node* tmp = new Node(i, back, nullptr);
	back = tmp;
	if (front == nullptr)
	{
		front = back;
	}
	else
	{
		tmp = back->getNext();
		tmp->setPrev(back);
	}
}

int Queue::Dequeue(void) 
{
	Node* tmp = NodeDequeue();
	int ret = 0;
	if (tmp != nullptr)
	{
		ret = tmp->getVal();
	}
	else
	{
		throw "Queue Empty";
	}
	if (front == nullptr)
	{
		back = front;
	}
	delete tmp;
	return ret;
}

Node* Queue::NodeDequeue(void) 
{
	Node* tmp = front;
	if (front != nullptr)
	{
		front = front->getPrev();
		if (front != nullptr)
		{
			front->setNext(nullptr);
		}
	}
	return tmp;
}



// ************************** Scheduler ***************************************
// 
// depending on your implementation you may overide any PUBLIC methods INHERITED from the Queue class
// as well as add ANY private methods in Scheduler class

void Scheduler::Enqueue(int i, int priority)
{
	//Out of range handling
	if (priority > 10 || priority < 0)
	{
		throw "Out of range priority!";
	}

	Node* newNode = new Node(i, nullptr, nullptr, priority);

	if (front == nullptr)
	{
		front = back = newNode;
		return;
	}

	// Insert node based on its priority
	Node* current = front;
	Node* previous = nullptr;

	while (current != nullptr && current->getPriority() >= priority) // Linear search
	{
		previous = current;
		current = current->getNext();
	}

	if (current == nullptr) // Lowest priority, add to the end
	{
		back->setNext(newNode);
		newNode->setPrev(back);
		back = newNode;
	}
	else if (current == front) // Add to front highest priority
	{
		newNode->setNext(front);
		front->setPrev(newNode);
		front = newNode;
	}
	else // Insert in the middle
	{
		previous->setNext(newNode);
		newNode->setPrev(previous);
		newNode->setNext(current);
		current->setPrev(newNode);
	}
}

int Scheduler::Dequeue(void)
{
	if (front == nullptr) // Empty queue
	{
		throw "Scheduler Empty";
	}

	Node* tmp = NodeDequeue();
	int ret = tmp->getVal();

	return ret;
}

Node* Scheduler::NodeDequeue(void) 
{
	if (front == nullptr) // Queue is empty
	{
		return nullptr;
	}

	// Dequeue the highest-priority node
	Node* tmp = front;
	front = front->getNext();

	Node* current = front;

	while (current != nullptr)
	{
		current->setPriority(current->getPriority() + 1);
		current = current->getNext();
	}

	if (front != nullptr)
	{
		front->setPrev(nullptr);
	}
	else // Queue becomes empty
	{
		back = nullptr;
	}

	return tmp;
}


//-------------------------------YOUR implementation ends here!!!!-----------------------



//----------------------------- YOUR code testing --------------------------
// comment out or delete this section AFTER you finished your testing

#include <time.h>       /* time */
#include <chrono>

using namespace std::chrono;


int main(void) 
{
	int const COUNT = 20;
	int input[COUNT] = { 1,2,3,4,5,9,8,7,6,10, 1,2,3,4,5,9,8,7,6,10 };

	cout << "01. STACK BASIC TEST\n";

	Stack myStack;
	cout << "Push: \n";
	for (int i = 0; i < COUNT; i++) 
	{
		cout << input[i] << " ";
		myStack.Push(input[i]);
	}
	cout << "\nPop:  \n";
	for (int i = 0; i < COUNT; i++) 
	{
		cout << myStack.Pop();
		cout << " ";
	}
	cout << "\n\n02. EMPTY STACK EXCEPTION TEST\n";
	myStack.Push(1);
	try 
	{
		myStack.Pop();
		myStack.Pop();
	}
	catch (const char* msg) 
	{
		cout << msg << endl;
	}

	cout << "\n\n03. QUEUE BASIC TEST\n";
	Queue myQueue;
	cout << "Enqueue: \n";
	for (int i = 0; i < COUNT; i++) 
	{
		cout << input[i] << " ";
		myQueue.Enqueue(input[i]);

	}
	cout << "\nDequeue: \n";
	for (int i = 0; i < COUNT; i++) 
	{
		cout << myQueue.Dequeue();
		cout << " ";
	}

	cout << "\n\n04. EMPTY QUEUE EXCEPTION TEST\n";
	myQueue.Enqueue(1);
	try 
	{
		myQueue.Dequeue();
		myQueue.Dequeue();
	}
	catch (const char* msg) 
	{
		cout << msg << endl;
	}

	cout << "\n\n05. SCHEDULER BASIC TEST\n";
	Scheduler myScheduler;
	cout << "Enqueue: \n";
	for (int i = 0; i < COUNT; i++) 
	{
		cout << input[i] << " ";
		myScheduler.Enqueue(input[i], input[i]);

	}
	cout << "\nDequeue: \n";
	for (int i = 0; i < COUNT; i++) 
	{
		cout << myScheduler.Dequeue();
		cout << " ";
	}

	cout << "\n\n06. EMPTY SCHEDULER EXCEPTION TEST\n";
	myScheduler.Enqueue(1, 1);
	try 
	{
		myScheduler.Dequeue();
		myScheduler.Dequeue();
	}
	catch (const char* msg) 
	{
		cout << msg << endl;
	}

	cout << "\n\n07. SCHEDULER PRIORITY RANGE TEST\n";
	cout << "Enqueue(1,11): ";
	try 
	{
		myScheduler.Enqueue(1, 11);
		cout << myScheduler.Dequeue();
	}
	catch (const char* msg) 
	{
		cout << msg << endl;
	}

	cout << "\n\n08. SCHEDULER BLOCKING TEST\n";
	cout << "Enqueue: \n";
	for (int i = 0; i < COUNT; i++) 
	{
		myScheduler.Enqueue(input[i], input[i]);
		cout << input[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 100; i++)
	{
		cout << "\rEnqueue: 10 ";
		myScheduler.Enqueue(10, 10);
		cout << "  Dequeue: ";
		cout << myScheduler.Dequeue();
		cout << " ";
	}
	cout << "\nBlocked items: \n";
	for (int i = 0; i < COUNT; i++) 
	{
		cout << myScheduler.Dequeue() << " ";
	}


	cout << "\n\n09. SCHEDULER PERFOMANCE TEST\n";
	int qSize = 1000000;
	int duration1 = 0;
	int duration2 = 0;
	int x = 0;

	Scheduler myScheduler1;
	for (int i = 0; i < qSize; i++) 
	{
		for (int i = 0; i < COUNT; i++) 
		{
			myScheduler1.Enqueue(input[i], input[i]);
			//cout << input[i] << " ";
		}
	}

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	myScheduler1.Enqueue(10, 10);
	x = myScheduler1.Dequeue();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration1 = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	cout << "\nDequeue = " << x << " Time used : " << duration1 << " microseconds." << endl << endl;

	Scheduler myScheduler2;
	qSize = 2 * qSize;
	for (int i = 0; i < qSize; i++) 
	{
		for (int i = 0; i < COUNT; i++) 
		{
			myScheduler2.Enqueue(input[i], input[i]);
			//cout << input[i] << " ";
		}
	}


	t1 = high_resolution_clock::now();
	myScheduler2.Enqueue(10, 10);
	x = myScheduler2.Dequeue();
	t2 = high_resolution_clock::now();
	duration2 = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	cout << "\nDequeue = " << x << " Time used : " << duration2 << " microseconds." << endl << endl;

	double ratio = (double)duration2 / duration1;
	std::cout << "ratio: " << ratio;


	getchar();
}

