#include <iostream>
#include <fstream>
#include <queue>
#include <string>
using namespace std;

struct Customer {
	string name;
	bool hasCard;
	int tokenNumber;
	string cardNumber;
};
fstream file;

struct Counter {
	string counterName;
	queue<Customer> customers;
};

void enqueueCustomer(Counter& counter, const Customer& customer) {
	counter.customers.push(customer);
}

void dequeueCustomer(Counter& counter) {
	counter.customers.pop();
}

void displayCounterQueue(const Counter& counter) {
	queue<Customer> tempQueue = counter.customers;

	while (!tempQueue.empty()) {
		Customer customer = tempQueue.front();
		cout << "Token Number: " << customer.tokenNumber << " | Name: " << customer.name << " | Card Number: " << customer.cardNumber << endl;
		tempQueue.pop();
	}
}

void saveCounterQueueToFile(const Counter& counter, const string& filename) {
	ofstream outFile(filename);

	if (!outFile) {
		cout << "Error opening the file " << filename << endl;
		return;
	}

	queue<Customer> tempQueue = counter.customers;

	while (!tempQueue.empty()) {
		Customer customer = tempQueue.front();
		outFile << customer.tokenNumber << " " << customer.name << " " << customer.cardNumber << endl;
		tempQueue.pop();
	}

	outFile.close();
}

void loadCounterQueueFromFile(Counter& counter, const string& filename) {
	ifstream inFile(filename);

	if (!inFile) {
		cout << "Error opening the file " << filename << endl;
		return;
	}

	Customer customer;
	while (inFile >> customer.tokenNumber >> customer.name >> customer.cardNumber) {
		enqueueCustomer(counter, customer);
	}

	inFile.close();
}

void rearrangeCounterQueue(Counter& counter) {
	queue<Customer> tempQueue;
	while (!counter.customers.empty()) {
		tempQueue.push(counter.customers.front());
		counter.customers.pop();
	}

	while (!tempQueue.empty()) {
		Customer currentCustomer = tempQueue.front();
		bool inserted = false;

		while (!counter.customers.empty()) {
			Customer frontCustomer = counter.customers.front();

			if (currentCustomer.cardNumber.compare(0, 1, "p") == 0 && frontCustomer.cardNumber.compare(0, 1, "p") != 0) {
				counter.customers.push(currentCustomer);
				inserted = true;
				break;
			}
			else if (currentCustomer.cardNumber.compare(0, 1, "g") == 0 && (frontCustomer.cardNumber.compare(0, 1, "p") == 0 || frontCustomer.cardNumber.compare(0, 1, "s") == 0)) {
				counter.customers.push(currentCustomer);
				inserted = true;
				break;
			}
			else if (currentCustomer.cardNumber.compare(0, 1, "s") == 0) {
				counter.customers.push(currentCustomer);
				inserted = true;
				break;
			}

			counter.customers.pop();
		}

		if (!inserted) {
			counter.customers.push(currentCustomer);
		}

		tempQueue.pop();
	}
}
void deposit()
{
	int n, b, num;
	string l;
	cout << "Enter Account No: ";
	cin >> n;

	file.open(std::to_string(n) + ".txt", ios::in);
	if (file)
	{
		while (!file.eof()) {
			getline(file, l);
			file.close();
		}
		std::string str = l;
		num = std::stoi(str);
		cout << "Enter the amount to Deposit : ";
		cin >> b;
		num = num + b;
		cout << "Amount Deposited successfully.\nNew Balance : " << num << endl;
		file.open(std::to_string(n) + ".txt", ios::app);
		file << "After Making Deposit :\nNew Balance :" << endl;
		file << num;
		file.close();
		return;
	}
	else {
		cout << "Invalid Account No.\n";

	}
	cout << endl;
}
void withdraw()
{
	int n, b, num;
	string l;
	cout << "Enter Account No: ";
	cin >> n;
	file.open(std::to_string(n) + ".txt", ios::in);
	while (true) {
		if (file) {
			while (!file.eof()) {
				getline(file, l);
				file.close();
			}std::string str = l;
			num = std::stoi(str);
			do {
				cout << "Enter the amount to Withdraw : ";
				cin >> b;
				if (b <= num) {
					num = num - b;
					cout << "Amount Withdrawn successfully.\nNew Balance : " << num << endl;
					file.open(std::to_string(n) + ".txt", ios::app);
					file << "After Withdrawing :\nNew Balance :" << endl;
					file << num;
					file.close();
					return;
				}
			} while (b <= num);
		}
		else
		{
			cout << "Invalid Account No.\n";
		}
	}
	cout << endl;
}

void cheque()
{
	int n, b, num;
	string l;
	cout << "Enter Account No: ";
	cin >> n;
	file.open(std::to_string(n) + ".txt", ios::in);
	do {
		if (file) {
			while (!file.eof()) {
				getline(file, l);
				file.close();
			}
			std::string str = l;
			num = std::stoi(str);
			do {
				cout << "Enter the amount on Cheque : ";
				cin >> b;
				if (b <= num) {
					num = num - b;
					cout << "Cheque Cashed Successfully " << endl;
					file.open(std::to_string(n) + ".txt", ios::app);
					file << "After Withdrawing :\nNew Balance :" << endl;
					file << num;
					file.close();
					return;
				}
			} while (b <= num);
			break;
		}
		else {
			cout << "Invalid Account No.\n";
		}
	} while (file);
	cout << endl;
}

void Util_Fees() {
	float amnt;
	string m, n;
	cout << "Enter the Utility Company or Educational Institute Name : ";
	cin >> n;
	cout << "Enter the Bill/Fee Challan Number : ";
	cin >> m;
	cout << "Enter the Amount to be paid : ";
	cin >> amnt;
	cout << "Amount " << amnt << " Paid Successfully to " << n << " on Bill/Challan Number " << m << endl;
	cout << endl;
}

void service() {
	while (true) {
		cout << "1. To Deposit\n2. For Withdrawal\n3. To Pay Utility Bill/Fees\n4. To Cash a Cheque\n5. Exit" << endl;
		int c;
		cin >> c;
		if (c == 1) {
			deposit();
		}
		else if (c == 2) {
			withdraw();
		}
		else if (c == 3) {
			Util_Fees();
		}
		else if (c == 4) {
			cheque();
		}
		else if (c == 5) {
			break;
		}
		else {
			cout << "Invalid choice. Please try again." << endl;
		}
		cout << endl;
	}
}

int main() {
	Counter counter1, counter2;
	counter1.counterName = "Counter 1";
	counter2.counterName = "Counter 2";

	// Load queues from files (if they exist)
	loadCounterQueueFromFile(counter1, "counter1_queue.txt");
	loadCounterQueueFromFile(counter2, "counter2_queue.txt");

	int token = 1; // Starting token number

	while (true) {
		cout << "1. New customer\n2. Serve customer from Counter 1\n3. Serve customer from Counter 2\n4. Exit" << endl;
		int choice;
		cin >> choice;

		if (choice == 1) {
			Customer newCustomer;
			cout << "Customer Name: ";
			cin >> newCustomer.name;
			cout << "Do you have a card? (1 for Yes, 0 for No): ";
			cin >> newCustomer.hasCard;

			newCustomer.tokenNumber = token++;
			if (newCustomer.hasCard) {
				cout << "Enter customer card number: ";
				cin >> newCustomer.cardNumber;
				if (newCustomer.cardNumber.compare(0, 1, "p") == 0 || newCustomer.cardNumber.compare(0, 1, "g") == 0 || newCustomer.cardNumber.compare(0, 1, "s") == 0) {
					enqueueCustomer(counter2, newCustomer);
					rearrangeCounterQueue(counter2);
				}
				else {
					enqueueCustomer(counter1, newCustomer);
				}
			}
			else {
				enqueueCustomer(counter1, newCustomer);
			}

			// Save queues to files
			saveCounterQueueToFile(counter1, "counter1_queue.txt");
			saveCounterQueueToFile(counter2, "counter2_queue.txt");
		}
		else if (choice == 2) {
			if (!counter1.customers.empty()) {
				Customer servingCustomer = counter1.customers.front();
				cout << "Serving customer from " << counter1.counterName << ":" << endl;
				cout << "Token Number: " << servingCustomer.tokenNumber << " | Name: " << servingCustomer.name /*<< " | Card Number: " << servingCustomer.cardNumber */ << endl;
				dequeueCustomer(counter1);
				// Save updated queue to file
				saveCounterQueueToFile(counter1, "counter1_queue.txt");
				service();
			}
			else {
				cout << "No customers in " << counter1.counterName << " queue." << endl;
			}
		}
		else if (choice == 3) {
			if (!counter2.customers.empty()) {
				Customer servingCustomer = counter2.customers.front();
				cout << "Serving customer from " << counter2.counterName << ":" << endl;
				cout << "Token Number: " << servingCustomer.tokenNumber << " | Name: " << servingCustomer.name << " | Card Number: " << servingCustomer.cardNumber << endl;
				dequeueCustomer(counter2);
				// Save updated queue to file
				saveCounterQueueToFile(counter2, "counter2_queue.txt");
				service();
			}
			else {
				cout << "No customers in " << counter2.counterName << " queue." << endl;
			}
		}
		else if (choice == 4) {
			break;
		}
		else {
			cout << "Invalid choice. Please try again." << endl;
		}

		cout << endl;
	}

	system("pause");
}
