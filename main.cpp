#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<vector>
#include<string>
#include<fstream>
#include<Windows.h>

using namespace std;

class ADMIN;
class CUSTOMER;
class node;
class Item;
class Basket;
class USER;

void menuAction(int action);
void displayItem();
void mergeSort(node** start);
node* SortedMerge(node* a, node* b);
void split(node* head, node** front, node** back);

class ADMIN
{
public:
	void Admin();
	void addItem();
	friend void displayItem();
	void modifyItem();
	void removeItem();
	void customerList();
	void removeCustomer();
};

class CUSTOMER
{
public:
	Basket* basket = NULL;
	void Customer();
	friend void displayItem();
	void searchItem();
	void sortPrice();
	void viewCart();
	void checkout();
	void addToBasket(node* p, int amount);
};

class node
{
	string name;
	double price;
	int quantity;


public:
	static int count;
	int id;
	node* next;

	node() {}

	node(int ID, string name, double price, int quantity)
		:id(ID), name(name), price(price), quantity(quantity), next(NULL) {
	}
	node(node* p)
		:id(p->id), name(p->getName()), price(p->getPrice()), quantity(p->getQuantity()), next(NULL) {}

	node(node& p)
		:id(p.id), name(p.getName()), price(p.getPrice()), quantity(p.getQuantity()), next(NULL) {}

	~node()
	{

	}

	void display()
	{
		cout << id << "\t\t" << name << "\t\t\t" << price << "\t\t" << quantity;
	}
	string getName()
	{
		return this->name;
	}
	double getPrice()
	{
		return this->price;
	}
	int getQuantity()
	{
		return this->quantity;
	}

	void decrease(int q)
	{
		this->quantity -= q;
	}

	void setData(int newID, string name, double price, int quantity)
	{
		this->id = newID;
		this->name = name;
		this->price = price;
		this->quantity = quantity;
		cout << "\nThe product is updated";
	}

}*mainroot = NULL;

int node::count = 0;

class Item
{
	string name;
	double price;
	int quantity;
public:

	Item(string name, double price, int quantity)
		:name(name), price(price), quantity(quantity) {}
	void display()
	{
		cout << name << "\t\t\t" << price << "\t\t" << quantity;
	}
	double getPrice()
	{
		return this->price;
	}
	int getQuantitiy()
	{
		return this->quantity;
	}
};

class Basket
{
public:
	Item item;
	Basket* next;

	Basket(Item item)
		:item(item), next(NULL) {}
};

class USER :public ADMIN, public CUSTOMER
{
protected:
	string username;
	string password;
public:

	USER() {}

	string getUsername()
	{
		return this->username;
	}
	string getPassword()
	{
		return this->password;
	}

	USER(string name, string pass)
	{
		this->username = name;
		this->password = pass;
		this->basket = NULL;
	}
};

node temp;
USER tempuser;
USER user;
node tempnode;

//===============ADMIN FUNCTIONS

void addNode(node* temp)
{
	if (temp == NULL)
	{
		cout << "node not found";
		return;
	}
	else if (mainroot == NULL)
	{
		mainroot = temp;
		cout << "\nitem added in the store.";
	}
	else
	{
		node* p = mainroot;
		while (p->next != NULL)
			p = p->next;
		p->next = temp;
		cout << "\nitem added in the store.";
	}
}

void ADMIN::Admin()
{
	int adminMenuChoise = 0;

	while (adminMenuChoise != 7)
	{
		system("cls");

		cout << "------------------------------------------------------------" << endl;
		cout << "\t\tADMINISTATOR PORTAL" << endl;
		cout << "------------------------------------------------------------" << endl;

		cout << "\t\t1 for ADD a new product" << endl;
		cout << "\t\t2 to display all products" << endl;
		cout << "\t\t3 for MODIFY Existing product" << endl;
		cout << "\t\t4 for Delete a particular product item" << endl;
		cout << "\t\t5 for Customers List" << endl;
		cout << "\t\t6 for Customer Edit" << endl;
		cout << "\t\t7 for Main menu" << endl;
		cout << "\t\t0 for Exit" << endl;

		cout << "\nEnter Your choice ==>";   cin >> adminMenuChoise;

		switch (adminMenuChoise)
		{
		case 1:
			addItem();
			break;
		case 2:
			displayItem();
			_getch();
			break;
		case 3:
			modifyItem();
			break;
		case 4:
			removeItem();
			break;
		case 5:
			customerList();
			break;
		case 6:
			removeCustomer();
			break;
		case 7://takes back to menu;
			break;
		case 0:
			exit(0);
			break;
		default:cout << "\nEnter a valid choice";
			break;
		}
	}
}


void ADMIN::addItem()
{
	system("cls");

	int productID, productQuantity;
	string productName;
	double productPrice;
	char choice;
	bool flag = true;

	fstream fptr("items.dat", ios::binary | ios::app);


	cout << "------------------------------------------------------------" << endl;
	cout << "\t\tADD ITEM TO THE STORE" << endl;
	cout << "------------------------------------------------------------" << endl;

	while (flag)
	{
		cout << "Enter product ID\n==>";
		cin >> productID;
		cout << "Enter product Name\n==>";
		cin >> productName;
		cout << "Enter product price\n==>";
		cin >> productPrice;
		cout << "Enter product quantity\n==>";
		cin >> productQuantity;

		node* item = new node(productID, productName, productPrice, productQuantity);
		temp.setData(item->id, item->getName(), item->getPrice(), item->getQuantity());
		fptr.write((char*)&temp, sizeof(temp));
		addNode(item);
		node::count++;

		cout << "\nDo you want to add more items (Y/N)\n==> ";
		cin >> choice;
		if (choice == 'N' || choice == 'n')
		{
			fptr.close();
			flag = false;
		}
	}
}

void displayItem()
{
	system("cls");
	if (mainroot == NULL)
	{
		cout << "\nSorry curently we are out of stocks";
		return;
	}
	else {
		node* p = mainroot;
		cout << "Existing products are:\n";
		cout << "ID\t\tProduct Name\t\tPrice\t\tQuantity\n";
		cout << "============================================================================\n";
		while (p != NULL)
		{
			p->display();
			p = p->next;
			cout << endl;
		}
	}
	cout << "\nTotal items in the store are : " << node::count;
}

void ADMIN::modifyItem()
{
	system("cls");

	int oldID, newID;
	string name;
	double price;
	int quantity;

	cout << "------------------------------------------------------------" << endl;
	cout << "\t\tMODIFY ITEM IN THE STORE" << endl;
	cout << "------------------------------------------------------------" << endl;
	cout << "\nEnter the id of the item to modify\n==>";
	cin >> oldID;
	cout << "Enter the new product id\n==>";
	cin >> newID;
	cout << "\nEnter the new product name\n==>";
	cin >> name;
	cout << "\n Enter the price of the new item\n==>";
	cin >> price;
	cout << "\nEnter the quantity of the new product\n==>";
	cin >> quantity;

	node* p = mainroot;

	while (p->id != oldID && p)
	{
		p = p->next;
	}
	if (p == NULL)
	{
		cout << "\nThe item not found please check the id of the product";
		return;
	}
	else {
		ifstream in("items.dat", ios::binary);
		ofstream out("temp.dat", ios::binary);



		p->setData(newID, name, price, quantity);

		while (in.read((char*)&tempnode, sizeof(tempnode)))
		{
			if (tempnode.id == oldID)
			{
				tempnode.setData(p->id, p->getName(), p->getPrice(), p->getQuantity());;
				tempnode.next = NULL;
			}
			out.write((char*)&tempnode, sizeof(tempnode));
		}

		in.close();
		out.close();

		remove("items.dat");
		rename("temp.dat", "items.dat");

		cout << "\nThe item is modified";
		displayItem();
	}
}

void ADMIN::removeItem()
{
	int removeID;

	ifstream in("items.dat", ios::binary);
	ofstream out("temp.dat", ios::binary);

	while (1)
	{
		system("cls");

		cout << "------------------------------------------------------------" << endl;
		cout << "\t\tREMOVE ITEM FROM THE STORE" << endl;
		cout << "------------------------------------------------------------" << endl;

		displayItem();

		cout << "\nEnter the id of the item to remove\n==>";
		cin >> removeID;

		if (mainroot != NULL && mainroot->id == removeID)
		{
			if (mainroot->next != NULL)
			{
				node* temp = mainroot;
				mainroot = mainroot->next;
				delete(temp);
			}
			else {
				node* temp = mainroot;
				mainroot = NULL;
				delete(temp);
			}
		}
		else {
			node* p = mainroot;
			node* q = NULL;
			while (p->id != removeID && p)
			{
				q = p;
				p = p->next;
			}
			if (p->next != NULL)
			{
				node* temp = p->next;
				p->next = p->next->next;
				delete(temp);
			}
			else {
				q->next = NULL;
				delete(p);
			}
		}

		while (in.read((char*)&tempnode, sizeof(tempnode)))
		{
			if (tempnode.id != removeID)
			{
				out.write((char*)&tempnode, sizeof(tempnode));
			}
		}
		node::count--;
		cout << "\nThe item is removed from store";
		cout << "\nDo you want to remove more items (Y/N)";
		char ch;
		cin >> ch;
		if (ch == 'n' || ch == 'N')
		{
			in.close();
			out.close();

			remove("items.dat");
			rename("temp.dat", "items.dat");

			break;
		}
	}
}

void ADMIN::customerList()
{
	system("cls");
	ifstream fptr("users.dat", ios::binary | ios::app);


	cout << "Customer Name\n";
	cout << "=======================\n";
	while (fptr.read((char*)&tempuser, sizeof(tempuser)))
	{
		cout << tempuser.getUsername() << endl;
	}
	fptr.close();
	_getch();
}

void ADMIN::removeCustomer()
{
	char name[30];
	bool found = false;
	ifstream in("users.dat", ios::binary);
	ofstream out("temp.dat", ios::binary);

	system("cls");

	cout << "---------------------------------------------";
	cout << "\n\t\t	REMOVE THE CUSTOMER\n";
	cout << "---------------------------------------------\n";
	cout << " ENTER THE CUSTOMER NAME TO BE REMOVED\n";
	cout << "==> ";
	cin >> name;

	while (in.read((char*)&tempuser, sizeof(tempuser)))
	{
		if (tempuser.getUsername() != name)
		{
			out.write((char*)&tempuser, sizeof(tempuser));
		}
		else {
			found = true;
		}
	}

	if (!found)
	{
		cout << "\nUSER NOT FOUND";
		in.close();
		out.close();
	}
	else {
		cout << "\nUSER DELETED";

		in.close();
		remove("users.dat");

		out.close();
		rename("temp.dat", "users.dat");

	}



	_getch();
}

//=========================CUSTOMER FUNCTIONS

void CUSTOMER::Customer()
{

	int customerMenuChoise = 0;
	while (customerMenuChoise != 6)
	{
		system("cls");

		cout << "------------------------------------------------------------" << endl;
		cout << "\t\tCUSTOMER PORTAL" << endl;
		cout << "------------------------------------------------------------" << endl;

		cout << "\t\t1 to display all products" << endl;
		cout << "\t\t2 to search and buy items from shop" << endl;
		cout << "\t\t3 sort products by price" << endl;
		cout << "\t\t4 to view cart" << endl;
		cout << "\t\t5 checkout" << endl;
		cout << "\t\t6 for Main menu" << endl;
		cout << "\t\t0 for Exit" << endl;


		cout << "\nEnter Your choice ==>";   cin >> customerMenuChoise;

		switch (customerMenuChoise)
		{
		case 1:
			displayItem();
			_getch();
			break;
		case 2:
			searchItem();
			break;
		case 3:
			sortPrice();
			break;
		case 4:
			viewCart();
			break;
		case 5:
			checkout();
			break;
		case 6://takes back to menu
			break;
		case 0:
			exit(0);
			break;
		default:cout << "\nEnter a valid choice";
			break;
		}
	}
}

void decreaseItemStock(node* p, int amount) {
	node* t = mainroot;
	while (t && t->id != p->id)
	{
		t = t->next;
	}
	if (t)
	{
		t->decrease(amount);
	}
}

void CUSTOMER::addToBasket(node* p, int amount)
{
	Basket* b = this->basket;

	if (!b)
	{
		Item itemToAdd(p->getName(), p->getPrice(), amount);
		basket = new Basket(itemToAdd);
		cout << "\nItem added to the basket";
		decreaseItemStock(p, amount);
	}
	else {
		while (b->next != NULL)
		{
			b = b->next;
		}
		Item itemToAdd(p->getName(), p->getPrice(), amount);
		Basket* t = new Basket(itemToAdd);
		b->next = t;
		cout << "\nItem added to the basket";
		decreaseItemStock(p, amount);
	}
}

void CUSTOMER::searchItem()
{

	string search;
	bool flag = 1;
	while (flag)
	{
		system("cls");

		cout << "------------------------------------------------------------" << endl;
		cout << "\t\tSEARCH ITEM IN THE STORE" << endl;
		cout << "------------------------------------------------------------" << endl;

		displayItem();

		cout << "\nEnter the name of the product to search\n==>";
		cin >> search;
		node* p = mainroot;
		while (p && p->getName() != search)
		{
			p = p->next;
		}
		if (p == NULL)
		{
			cout << "\nThe item not found please try another item";
			cout << "\nDo you want to search more (Y/N)";
			char ch;
			cin >> ch;
			if (ch == 'n' || ch == 'N')
			{
				flag = 0;
				break;
			}
		}
		else {
			cout << "ID\t\tProduct Name\t\tPrice\t\tQuantity\n";
			cout << "============================================================================\n";
			p->display();
			cout << "\nWant to add the item in the basket(Y/N)\n==>";
			char ch;
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
			{
				int amount;
				cout << "enter the amount of item to add\n==>";
				cin >> amount;
				addToBasket(p, amount);
				cout << "\nDo you want to search more (Y/N)";
				cin >> ch;
				if (ch == 'n' || ch == 'N')
				{
					flag = 0;
					break;
				}
			}
			else {
				cout << "\nDo you want to search more (Y/N)";
				cin >> ch;
				if (ch == 'n' || ch == 'N')
				{
					flag = 0;
					break;
				}
			}
		}
	}
}

void CUSTOMER::sortPrice()
{
	node* sorted = NULL;
	node* p = mainroot;
	node* q = sorted, * temp;

	while (p)
	{
		if (sorted == NULL) {
			temp = new node(p);
			sorted = temp;
			p = p->next;
			q = sorted;
		}
		else {
			temp = new node(p);
			q->next = temp;
			p = p->next;
			q = q->next;
		}
	}

	mergeSort(&sorted);

	system("cls");
	if (sorted == NULL)
	{
		cout << "\nSorry curently we are out of stocks";
		_getch();
		return;
	}
	else {
		node* p = sorted;
		cout << "Existing products are:\n";
		cout << "ID\t\tProduct Name\t\tPrice\t\tQuantity\n";
		cout << "============================================================================\n";
		while (p != NULL)
		{
			p->display();
			p = p->next;
			cout << endl;
		}
	}
	cout << "\nTotal items in the store are : " << node::count;
	_getch();
}

void mergeSort(node** start)
{
	node* head = *start;
	node* a;
	node* b;
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}
	split(head, &a, &b);

	mergeSort(&a);
	mergeSort(&b);

	*start = SortedMerge(a, b);

}

node* SortedMerge(node* a, node* b)
{
	node* result = NULL;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

	if (a->getPrice() <= b->getPrice()) {
		result = a;
		result->next = SortedMerge(a->next, b);
	}
	else {
		result = b;
		result->next = SortedMerge(a, b->next);
	}
	return (result);
}

void split(node* head, node** front, node** back)
{
	node* slow = head;
	node* fast = head->next;

	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*front = head;
	*back = slow->next;
	slow->next = NULL;
}

void CUSTOMER::viewCart()
{
	system("cls");
	if (basket == NULL)
	{
		cout << "\nCurrently your basket is empty.\nCheck out the available items to find the product of your choise.";
		_getch();
		return;
	}
	else {
		Basket* b = basket;
		cout << "Your selected items are products are:\n\n";
		cout << "Product Name\t\tPrice\t\tQuantity\n";
		cout << "============================================================================\n";
		while (b != NULL)
		{
			b->item.display();
			b = b->next;
			cout << endl;
		}
	}
	_getch();
}

void CUSTOMER::checkout()
{
	system("cls");

	if (basket == NULL)
	{
		cout << "\nCurrently your basket is empty.\nCheck out the available items to find the product of your choise.";
		_getch();
		return;
	}
	else {
		Basket* b = basket;
		double billAmount = 0;

		cout << "Your selected items are products are:\n\n";
		cout << "Product Name\t\tPrice\t\tQuantity\n";
		cout << "============================================================================\n";
		while (b != NULL)
		{
			b->item.display();
			billAmount += ((b->item.getPrice()) * (b->item.getQuantitiy()));
			b = b->next;
			cout << endl;
		}
		Basket* temp;
		temp = basket;
		basket = NULL;
		while (temp)
		{
			Basket* bt = temp;
			temp = temp->next;
			delete(bt);
		}
		cout << "\nYour total billing amount is: " << billAmount;
		_getch();
	}

}

//===================================================================  AUTH functions

void signUp()
{
	system("cls");

	cout << "---------------------------------------------";
	cout << "\n\t\tSIGN UP ZONE\n";
	cout << "---------------------------------------------";

	bool flag = 1, validUname = 1;
	string utemp, temp1, temp2, errorChoise;

	ifstream fptr("users.dat", ios::binary | ios::app);


	while (flag)
	{
		cout << "\nENTER THE USERNAME\n==> ";
		cin >> utemp;
		cout << "\nENTER THE PASSWORD\n==> ";
		cin >> temp1;
		cout << "\nCONFIRM THE PASSWORD\n==> ";
		cin >> temp2;
		if (temp1 != temp2)
		{
			cout << "\nPASWARD DID NOT MATCH";
			cout << "\nWANA TRY AGAIN \n(Y/N)\n==> ";
			cin >> errorChoise;
			if (errorChoise == "N" || errorChoise == "n")
			{
				fptr.close();
				exit(0);
			}
		}
		else {
			validUname = 1;
			while (fptr.read((char*)&tempuser, sizeof(tempuser)))
			{
				if (tempuser.getUsername() == utemp)
				{
					validUname = 0;
					break;
				}
			}
			if (validUname)
			{
				USER temp(utemp, temp1);
				fptr.close();
				ofstream ptr("users.dat", ios::binary | ios::app);
				ptr.seekp(0, ios::end);
				ptr.write((char*)&temp, sizeof(temp));
				ptr.close();
				flag = 0;
			}
			else
			{
				cout << "\n THE USERNAME ALREADY EXISTS";
				cout << "\nWANA TRY AGAIN \n(Y/N)\n==> ";
				cin >> errorChoise;
				if (errorChoise == "N" || errorChoise == "n")
				{
					fptr.close();
					flag = 0;
				}
			}
		}
	}
}

void login()
{
	bool flag = 0, loopFlag = 1;
	string loginUsername, loginPassword, errorChoise;
	ifstream fptr("users.dat", ios::binary | ios::app);


	while (loopFlag)
	{
		system("cls");

		cout << "---------------------------------------------";
		cout << "\n\t\t LOGIN PAGE\n";
		cout << "---------------------------------------------\n";
		cout << " ENTER THE USERNAME\n";
		cout << "==> ";
		cin >> loginUsername;
		cout << " ENTER PASSWARD\n";
		cout << "==> ";
		cin >> loginPassword;

		if (loginUsername == "admin" && loginPassword == "admin")
		{
			loopFlag = 0;
			fptr.close();
			tempuser.Admin();
			break;
		}

		while (fptr.read((char*)&tempuser, sizeof(tempuser)))
		{
			if (loginUsername == tempuser.getUsername() && loginPassword == tempuser.getPassword())
			{
				flag = 1;
				fptr.close();
				break;
			}
		}

		if (flag)
		{
			loopFlag = 0;
			tempuser.Customer();
			break;
		}
		else {
			cout << "\n THE USERNAME OR PASWORD DID NOT MATCH";
			cout << "\nWANA TRY AGAIN \n(Y/N)\n==> ";
			cin >> errorChoise;
			if (errorChoise == "N" || errorChoise == "n")
			{
				fptr.close();
				exit(0);
			}
		}
	}
}

//=============================================================     menu

void menu()
{
	int menuChoise = 0;
	while (menuChoise != 3)
	{
		system("cls");
		cout << "------------------------------------------------------------";
		cout << "\n\t\tWELCOME TO THE SHOPER STOP.";
		cout << "\n\t\t\tMENU" << endl;
		cout << "------------------------------------------------------------";
		cout << "\n\t\t1)SIGN UP (new user)";
		cout << "\n\t\t2)LOGIN (existing user)";
		cout << "\n\t\t3)Exit";
		cout << "\n==> ";
		cin >> menuChoise;
		menuAction(menuChoise);
	}
}

void menuAction(int action)
{
	switch (action)
	{
	case 1: signUp();
		break;
	case 2: login();
		break;
	case 3:exit(0);
		break;
	default:cout << "\nenter the valid choise";
		return;
	}
}

void initializeShop()
{
	ifstream fptr("items.dat", ios::binary);
	while (fptr.read((char*)&temp, sizeof(temp)))
	{
		addNode(new node(temp));
		node::count++;
	}
	fptr.close();
}

int main()
{
	initializeShop();
	//program execution begins;
	menu();

	return 0;
}