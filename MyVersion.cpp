#include<iostream>
#include<conio.h>
#include<string>
#include <fstream>

using namespace std;

//structs

struct position {
	int positionNumber;
	position* next;
};
struct node {
	int repetitions;
	int index;
	string word;
	node* next;
	position* FIRSTPOSITION = NULL;
	position* LASTPOSITION =  NULL;
};

//globals
int TOTALWORDS = 0;
int POSITION = 0;
int INDEX = 0;
node* FIRST = NULL;
node* LAST = NULL;


//definitions
void addNode(string);
void display();
void indexString(string);

char toLowercase(char);
void showIndexes();
string getIndexes();
string readFromFile();
void decrypt(string);
string getWord(int);
void organizedDisplay();
void testDisplay();
void menu();
void showTranslatedText();


//main
void main()
{	
	string test;
	int choice = 10;
	cout << "******************** START **********************" << endl;
	menu();
	while (choice != 0) {
		
		cin >> choice;
		if (choice == 1) {
			test = readFromFile();
			cout << readFromFile();
		}
		else if (choice == 2) {
			indexString(test);
			display();
		}
		else if (choice == 3) {
			showTranslatedText();
		}
		else if (choice == 4) {
			organizedDisplay();
		}
	}
	
}
void indexString(string x) {
	string temp = "";
	for (int i = 0; i < x.length(); i++) {
		if(x[i] == ' ' || x[i] == ',' || x[i] == '.'){
			if (x[i] == ',') {
				addNode(temp);
				addNode(",");
				temp = "";
			}
			else if (x[i] == '.') {
				addNode(temp);
				addNode(".");
				temp = "";
			}
				
			addNode(temp);
			temp = "";
		}
		else {
			x[i]=toLowercase(x[i]);
			temp.push_back(x[i]);
		}
	}
	if (temp != "") {
		addNode(temp);
		temp = "";
	}
}

void addNode(string x) {
	
	if (x != "") {
		TOTALWORDS++; 
		bool found = false;
		node* p;
		p = FIRST;
		position* currPosition = new position;
		currPosition->next = NULL;
		POSITION++;
		currPosition->positionNumber = POSITION;
		
		while (p != NULL) {
			if (p->word == x) {
				found = true;
				p->repetitions++;
				p->LASTPOSITION->next = currPosition;
				p->LASTPOSITION = currPosition;
				break;
			}
			p = p->next;
		}
		if (!found) {
			INDEX++;
			node* curr = new node;
			curr->word = x;
			curr->repetitions = 1;
			curr->next = NULL;
			if (FIRST == NULL) {
				curr->index = 0;
				FIRST = curr;
				LAST = curr;
			}
			else {
				LAST->next = curr;
				LAST = curr;
				curr->index = INDEX;
			}
			curr->FIRSTPOSITION = currPosition;
			curr->LASTPOSITION = currPosition;
			
		}
		
	}
}
void display() {
	cout << endl;
	cout << "TOTAL WORDS = " << TOTALWORDS << endl;
	node* p;
	p = FIRST;
	while (p != NULL) {
		position* pPosition = p->FIRSTPOSITION;
		cout << p->word << "   index : " << p->index << " TIMES REPEATED = "<< p->repetitions <<endl;
		cout << "POSITIONS : ";
		while (pPosition != NULL) {
			cout << pPosition->positionNumber << ", " ;
			pPosition = pPosition->next;
		}
		cout << endl;
		p = p->next;
	}
}

char toLowercase(char in) {
	if (in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
}
void showTranslatedText() {
	cout << endl;
	for (int i = 0; i < TOTALWORDS; i++) {
		node* p = FIRST;
		while (p != NULL) {
			position* pPosition = p->FIRSTPOSITION;
			while (pPosition != NULL) {
				if (pPosition->positionNumber == i) {
					cout << p->index << " ";
				}
				pPosition = pPosition->next;
			}

			p = p->next;
		}
	}
}
void showIndexes() {
	string text = "";
	node* p;
	p = FIRST;
	while (p != NULL) {
		cout << p->index <<" ";
		p = p->next;
	}
}

string readFromFile() {
	string text = "";
	string para = "";
	ifstream inFile;

	inFile.open("test.txt");
	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}

	while (getline(inFile, text)) {
		para += text;
	} 
	inFile.close();
	return para;
}

void decrypt(string input) {
	string s = "";
	for (int i = 0; i < input.length(); i++) {
		if (input[i] != ' ')
			s += input[i];
			
		if (input[i] == ' ') {
			cout << getWord(stoi(s)) << " ";
			s = "";
			}
	 }
		
}
string getWord(int index) {
	node* p;
	p = FIRST;
	while (p != NULL) {
		if (p->index == index) {
			return p->word;
			break;
		}
		p = p->next;
		}
		
}
string getIndexes() {
	string text = "";
	node* p;
	p = FIRST;
	while (p != NULL) {
		text = text + to_string(p->index) + " ";
		//cout << p->index;
		p = p->next;
	}
	return text;
}

void organizedDisplay() {
	cout << endl;
	for (int i = 0; i < TOTALWORDS; i++) {
		node* p = FIRST;
		while (p != NULL) {
			position* pPosition = p->FIRSTPOSITION;
			while (pPosition != NULL) {
				if (pPosition->positionNumber == i) {
					cout << p->word << " ";
				}
				pPosition = pPosition->next;
			}
			
			p = p->next;
		}
	}
}
void testDisplay() {
	node* p = FIRST;
	position* q = p->FIRSTPOSITION;
	while (q != NULL) {
		cout << q->positionNumber << endl;
		q = q->next;
	}
}
void menu() {
	cout << "1) Read String From File" << endl;
	cout << "2) Index Given String and Display" << endl;
	cout << "3) Encrypt String and Literal display " << endl;
	cout << "4) Decrypt String and show output" << endl;
	cout << "" << endl;
}