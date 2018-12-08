#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctype.h>
#include <string.h>

struct phone_num {
	char *phonenum;
	char *phonetype;
	phone_num *next;
};

struct phone_record {
	char *name;
	phone_num *num_head;
	phone_record *next;
	phone_record *previous;
};

struct user_record {
	char name[999];
	char phonenum[99];
	char phonetype[999];
};



struct datastr {
	phone_record *head, *tail;
	int nodecount;
	void create();
	void add_person(user_record *);
	void list();
	void exit();
	int search(char[]);
	void remove_person(int recordnum);
	bool add_number(user_record *);
	void remove_number(int, int);
	void update_person(int, char[]);
	void update_number(user_record *, int, int);
};

using namespace std;
datastr list;

void print_menu();
bool operation(char);
void add_person();
void delete_record();
void search_record();
void update_person();
void update_number();
void add_number();
void delete_number();

int main() {
	list.create();

	bool flag = false;
	char choice;
	while (!flag) {
		print_menu();
		cin >> choice;
		flag = operation(choice);
	}
	list.exit();
	return 0;
}

bool operation(char choice) {
	bool terminate = false;
	switch (choice) {
	case 'S': case 's':
		search_record();
		break;
	case 'A': case 'a':
		add_person();
		break;
	case 'N': case 'n':
		add_number();
		break;
	case 'U': case 'u':
		update_person();
		break;
	case 'V': case 'v':
		update_number();
		break;
	case 'D': case 'd':
		delete_record();
		break;
	case 'R': case 'r':
		delete_number();
		break;

	case 'E': case 'e':
		cout << "Are you sure you want to exit the program? (Y/N):";
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
			terminate = true;
		break;
	case 'L': case 'l':
		list.list();
		break;
	default:
		cout << "Error: You have entered an invalid choice" << endl;
		cout << "Please try again {S, A, N, U, V, D, R, L, E}:";
		cin >> choice;
		terminate = operation(choice);
		break;
	}
	return terminate;
}

void print_menu() {
	//system("clear"); 
	cout << endl;
	cout << "Phone list Application" << endl;
	cout << "Choose an operation" << endl;
	cout << "S: Record Search" << endl;
	cout << "A: Person Add" << endl;
	cout << "N: Number Add" << endl;
	cout << "U: Update Name" << endl;
	cout << "V: Update Number" << endl;
	cout << "D: Record Delete" << endl;
	cout << "R: Number Delete" << endl;
	cout << "L: List Records" << endl;
	cout << "E: Exit" << endl;
	cout << endl;
	cout << "Enter a choice {S, A, N, U, D, R, L, E}: ";
}

void datastr::create() {
	head = NULL;
	tail = NULL;
	nodecount = 0;
}

void datastr::exit() {
	phone_record *record;
	phone_num *num_traverse;
	bool flag = false;
	while (head->next) {
		record = head;
		num_traverse = record->num_head;
		while (num_traverse) {
			record->num_head = num_traverse->next;
			delete num_traverse;
			num_traverse = record->num_head;
		}
		if (head == tail)
			flag = true;
		head = head->next;
		delete record;
		if (flag)
			break;
	}
	nodecount = 0;
}

void datastr::add_person(user_record *toadd) {
	phone_record *record, *traverse;
	traverse = head;
	record = new phone_record;
	record->name = new char[strlen(toadd->name)];
	record->num_head = NULL;
	strcpy(record->name, toadd->name);
	record->next = NULL;
	record->previous = NULL;
	if (head == NULL) {
		head = record;
		tail = record;
		record->next = record;
		record->previous = record;
		nodecount++;
		return;
	}

	if (strcmp(record->name, head->name) < 0) {
		record->next = head;
		head = record;
		(record->next)->previous = record;
		head->previous = tail;
		tail->next = head;
		nodecount++;
		return;
	}

	while ((strcmp(record->name, traverse->name) > 0)) {
		traverse = traverse->next;
		if (traverse == head) break;

	}
	if (traverse != head) {
		record->next = traverse;
		(traverse->previous)->next = record;
		record->previous = traverse->previous;
		traverse->previous = record;

	}
	else {
		record->next = head;
		tail->next = record;
		record->previous = tail;
		head->previous = record;
		tail = record;
	}
	head->previous = tail;
	tail->next = head;
	nodecount++;
	return;
}

bool datastr::add_number(user_record *toadd) {
	phone_record *traverse;
	phone_num *num_record, *num_traverse;
	traverse = head;
	num_traverse = traverse->num_head;
	bool found = false;
	while (true) {
		if (strcmp(toadd->name, traverse->name) == 0) {
			found = true;
			num_record = new phone_num;
			num_record->phonetype = new char[strlen(toadd->phonetype)];
			num_record->phonenum = new char[strlen(toadd->phonenum)];
			strcpy(num_record->phonetype, toadd->phonetype);
			strcpy(num_record->phonenum, toadd->phonenum);

			if (traverse->num_head == NULL) {
				traverse->num_head = num_record;
				num_record->next = NULL;
			}
			else {
				while (num_traverse->next) {
					num_traverse = num_traverse->next;
				}
				num_traverse->next = num_record;
				num_record->next = NULL;
			}
		}
		if (traverse == tail)
			break;
		traverse = traverse->next;
		num_traverse = traverse->num_head;
	}

	if (found)
		return true;
	else
		return false;
	
}


int datastr::search(char searchee[]) {
	phone_record *traverse;
	phone_num *num_traverse;
	int counter = 0;
	int found = 0;
	traverse = head;
	bool all = false;
	bool flag = false;
	if (strcmp(searchee, "*") == 0) {
		datastr::list();
		return 1;
	}

	while (traverse) {
		num_traverse = traverse->num_head;
		int counter2 = 1;
		counter++;
		if (all) {
			cout << counter << "." << traverse->name << endl;
			while (num_traverse) {
				cout << "\t" << counter2 << ". " << num_traverse->phonetype << " " << num_traverse->phonenum << endl;
				num_traverse = num_traverse->next;
				counter2++;
			}
			found++;
		}
		else if (_strnicmp(traverse->name, searchee, strlen(searchee)) == 0) {
			found++;
			cout << counter << "." << traverse->name << endl;
			while (num_traverse) {
				cout << "\t" << counter2 << ". " << num_traverse->phonetype << " " << num_traverse->phonenum << endl;
				num_traverse = num_traverse->next;
				counter2++;
			}
			flag = true;
		}
		if (flag && _strnicmp((traverse->next)->name, searchee, strlen(searchee)) != 0)
			break;
		traverse = traverse->next;

		if (traverse == head)
			break;
	}

	return found;
}

void datastr::remove_number(int choice1, int choice2) {
	phone_record *traverse;
	phone_num *num_traverse, *num_tminus1;
	bool type_found = false;
	int counter1 = 1, counter2 = 1;
	traverse = head;
	if (choice1 <= 0) {
		cout << "Invalid record order number.\n";
		return;
	}

	while (true) {
		if (counter1 == choice1) {
			num_traverse = traverse->num_head;
			if (choice2 == 1) {
				type_found = true;
				traverse->num_head = num_traverse->next;
				delete num_traverse;
				return;
			}
			while (num_traverse) {
				num_tminus1 = num_traverse;
				num_traverse = num_traverse->next;
				counter2++;
				if (counter2 == choice2) {
					type_found = true;
					num_tminus1->next = num_traverse->next;
					delete num_traverse;
					return;
				}
			}
		}
		if (traverse == tail) break;

		counter1++;
		traverse = traverse->next;
	}

	if (!type_found) cout << "Record or Number Type is not found!";
}

void datastr::remove_person(int recordnum) {
	phone_record *traverse;
	phone_num *num_traverse;
	int counter = 1;
	traverse = head;
	if (recordnum <= 0) {
		cout << "Invalid record order number.\n";
		return;
	}
	if (recordnum == 1) {
		num_traverse = traverse->num_head;
		while (num_traverse) {
			traverse->num_head = num_traverse->next;
			delete num_traverse;
			num_traverse = traverse->num_head;
		}
		if (nodecount == 1) {
			head->next = NULL;
			head->previous = NULL;
			head = NULL;
			tail->next = NULL;
			tail->previous = NULL;
			tail = NULL;
			return;
		}
		head = head->next;
		tail->next = head;
		head->previous = tail;
		delete traverse;
		nodecount--;
		return;
	}
	while ((traverse != tail) &&
		(counter < recordnum)) {
		traverse = traverse->next;
		num_traverse = traverse->num_head;
		counter++;
	}
	if (counter < recordnum) {
		cout << "Could not find record to delete.\n";
	}
	else { // record found
		(traverse->previous)->next = traverse->next;
		(traverse->next)->previous = traverse->previous;
		if (traverse == tail) tail = traverse->previous;

		num_traverse = traverse->num_head;

		while (num_traverse) {
			traverse->num_head = num_traverse->next;
			delete num_traverse;
			num_traverse = traverse->num_head;
		}
		delete traverse;
		nodecount--;
	}
}

void datastr::list() {
	int counter = 1;
	phone_record *traverse = head;
	phone_num *num_traverse;
	while (true) {
		if (head == NULL) break;
		int counter2 = 1;
		cout << counter << "." << traverse->name << endl;
		num_traverse = traverse->num_head;
		while (num_traverse) {
			cout << "\t" << counter2 << ". " << num_traverse->phonetype << " " << num_traverse->phonenum << endl;
			num_traverse = num_traverse->next;
			counter2++;
		}
		counter++;
		if (traverse == tail)
			break;
		traverse = traverse->next;
	}

}

void datastr::update_person(int choice, char arr[]) {
	phone_record *traverse, *traverse2;
	int counter = 1;
	traverse = head;
	if (choice <= 0) {
		cout << "Invalid record order number.\n";
		return;
	}
	if (nodecount == 1) {
		traverse->name = new char[strlen(arr)];
		strcpy(traverse->name, arr);
		return;
	}
	if (choice == 1) {
		head = head->next;
		tail->next = head;
		head->previous = tail;
	}
	while ((traverse != tail) &&
		(counter < choice)) {
		traverse = traverse->next;
		counter++;
	}
	if (counter < choice && choice != 1) {
		cout << "Could not find record to delete.\n";
	}
	else if (choice != 1) { // record found
		(traverse->previous)->next = traverse->next;
		(traverse->next)->previous = traverse->previous;
		if (traverse == tail) tail = traverse->previous;
	}
	
	traverse->name = new char[strlen(arr)];
	strcpy(traverse->name, arr);
	traverse2 = head;

	if (strcmp(traverse->name, head->name) < 0) {
		traverse->next = head;
		head = traverse;
		(traverse->next)->previous = traverse;
		head->previous = tail;
		tail->next = head;
		return;
	}

	while ((strcmp(traverse->name, traverse2->name) > 0)) {
		traverse2 = traverse2->next;
		if (traverse2 == head) break;

	}
	if (traverse2 != head) {
		traverse->next = traverse2;
		(traverse2->previous)->next = traverse;
		traverse->previous = traverse2->previous;
		traverse2->previous = traverse;

	}
	else {
		traverse->next = head;
		tail->next = traverse;
		traverse->previous = tail;
		head->previous = traverse;
		tail = traverse;
	}
	head->previous = tail;
	tail->next = head;
}

void datastr::update_number(user_record *toadd, int choice1, int choice2){
	datastr::remove_number(choice1, choice2);

	phone_record *traverse;
	bool rec_found = false;
	int counter1 = 1;
	traverse = head;
	if (choice1 <= 0) {
		cout << "Invalid record order number.\n";
		return;
	}
	while (true){
		if (choice1 == counter1){
			rec_found = true;
			strcpy(toadd->name, traverse->name);
			break;
		}
		traverse = traverse->next;
		counter1++;
		if (traverse == head) break;

	}
	if (!rec_found) cout << "Record or Number Type is not found!";

	if (rec_found){
		datastr::add_number(toadd);
		cout << "Number updated" << endl;
	}
}

void add_person() {
	user_record newrecord;
	cout << "Please enter contact information you want to add" << endl;
	cout << "Name: ";
	cin.ignore(1000, '\n');
	cin.getline(newrecord.name, 999);
	list.add_person(&newrecord);
	cout << endl << "Record added" << endl;
};

void add_number() {
	user_record newrecord;
	cout << "Please enter the name you want to add a number" << endl;
	cin.ignore(1000, '\n');
	cin.getline(newrecord.name, 999);
	cout << "Phone number type: ";
	cin >> setw(99) >> newrecord.phonetype;
	cout << "Phone number: ";
	cin >> setw(99) >> newrecord.phonenum;
	if(list.add_number(&newrecord))
		cout << endl << "Number added" << endl;
	else
		cout << "Name is not found." << endl;
	return;
}

void delete_number() {
	char name[30];
	int choice1, choice2;
	cout << "Please enter the name of the person whose number you want to delete (press '* 'for full  list):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(name, 30);
	int personcount = list.search(name);
	if (personcount == 0) {
		cout << "Could not find a record matching your search criteria" << endl;
	}
	else {
		if (personcount == 1) {
			cout << "Record found." << endl;
			cout << "If you want to delete a number from this record, please enter its number (Enter -1 to exit without performing any operations): ";
		}
		else
			cout << "Enter the number of the record you want to delete a number from (Enter -1 to exit without performing any operations): ";
		cin >> choice1;
		if (choice1 == -1) return;
		cout << "Enter the number of the phone number type (Enter -1 to exit without performing any operations): ";
		cin >> choice2;
		if (choice1 == -1 || choice2 == -1) return;
		list.remove_number(choice1, choice2);
		cout << "Record deleted" << endl;
	}
	return;
}


void delete_record() {
	char name[30];
	int choice;
	cout << "Please enter the name of the person whose record you want to delete (press '* 'for full  list):" << endl;
	cin.ignore(1000, '\n');
	cin.getline(name, 30);
	int personcount = list.search(name);
	if (personcount == 0) {
		cout << "Could not find a record matching your search criteria" << endl;
	}
	else {
		if (personcount == 1) {
			cout << "Record found." << endl;
			cout << "If you want to delete this record, please enter its number (Enter -1 to exit without performing any operations): ";
		}
		else
			cout << "Enter the number of the record you want to delete (Enter -1 to exit without performing any operations): ";
		cin >> choice;
		if (choice == -1) return;
		list.remove_person(choice);
		cout << "Record deleted" << endl;
	}
}

void search_record() {
	char name[30];
	cout << "Please enter the name of the person you want to search for (press '*' for full list): " << endl;
	cin.ignore(1000, '\n');
	cin.getline(name, 30);
	if (list.search(name) == 0) {
		cout << "Could not find a record matching your search criteria" << endl;
	}
};

void update_person() {
	char name[30];
	int choice;
	cout << "Please enter the name of the person whose record you want to update (press '* 'for full  list): " << endl;
	cin.ignore(1000, '\n');
	cin.getline(name, 30);
	int personcount = list.search(name);
	if (personcount == 0) {
		cout << "Could not find a record matching your search criteria" << endl;
	}
	else {
		if (personcount == 1) {
			cout << "Record found." << endl;
			cout << "If you want to update this record, please enter its number (Enter -1 to exit without performing any operations): ";
		}
		else
			cout << "Enter the number of the record you want to update (Enter -1 to exit without performing any operations): ";
		cin >> choice;

		if (choice == -1) return;


		cout << "Please enter contact information you want to change" << endl;
		cout << "Name: ";
		cin.ignore(1000, '\n');
		cin.getline(name, 30);
		list.update_person(choice, name);
		cout << "Record updated" << endl;
	}
}

void update_number() {
	char name[30];
	user_record *newrecord;
	newrecord = new user_record;
	int choice1, choice2;
	cout << "Please enter the name of the person whose number you want to update (press '* 'for full  list): " << endl;
	cin.ignore(1000, '\n');
	cin.getline(name, 30);
	int personcount = list.search(name);
	if (personcount == 0) {
		cout << "Could not find a record matching your search criteria" << endl;
	}
	else {
		if (personcount == 1) {
			cout << "Record found." << endl;
			cout << "If you want to update a number from this record, please enter its number (Enter -1 to exit without performing any operations): ";
		}
		else
			cout << "Enter the number of the record you want to update a number from (Enter -1 to exit without performing any operations): ";
		cin >> choice1;
		if (choice1 == -1) return;
		cout << "Enter the number of the phone number type (Enter -1 to exit without performing any operations): ";
		cin >> choice2;
		if (choice1 == -1 || choice2 == -1) return;
		cout << "Please enter contact information you want to change" << endl;
		cout << "Phone type: ";
		cin.ignore(1000, '\n');
		cin.getline(newrecord->phonetype, 30);
		cout << "Phone number: ";
		cin.getline(newrecord->phonenum, 30);
		list.update_number(newrecord, choice1, choice2);
	}
	return;
}
