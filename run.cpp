#include "bTree.h"
#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;

int main() {

	string name, surname;
	int birth;
	char gender, option;

	bTree familyTree;
	
	
	
	while(true){
		cout << "\nM E N U: \n|\n"
			 << "1 - Add the first person to the tree\n"
			 << "2 - Add an ancestor to the existing person\n"
			 << "3 - Modify one's personal data\n"
			 << "4 - Show somebody's parents\n"
			 << "5 - Print the whole tree\n"
			 << "6 - Delete the existing person\n"
			 << "7 - Delete the whole tree\n"
			 << "8 - Save the tree to the text file\n"
			 << "9 - Read the tree from the text file\n"
			 << "a - Return the path to somebody in the tree\n"
			 << "|\nO - STOP THE PROGRAM\n";

		option = _getch();
		
		
		
		switch (option) {
		
			case '1':
			{
				cout << "\nADDING THE FIRST PERSON TO THE TREE\n"
					 << "\nType the name, surname, date of birth and gender (F or M): ";
				cin >> name >> surname >> birth >> gender;
				cout << "\n" << name << " " << surname << ", " << birth << "\n";
                
                if (gender != 'f'
                    && gender != 'F'
                    && gender != 'm'
                    && gender != 'M'){
                    
                    cout << "The program is too basic to understand a concept of a non-karyotypical gender\n";
				    break;
				}
                
				person* p = new person;
				p->name = name;
				p->surname = surname;
				p->birth = birth;
				p->gender = gender;

				bool isok;
				isok = familyTree.addRoot(p);
				if (!isok) 
					cout << "\nERROR (code 1): Unspecified memory issue lol\n";
			}
				break;
				
				
				
				
				
				
				
			case '2':
			{
				cout << "\nADDING AN ANCESTOR TO THE EXISTING PERSON\n"
					 << "Type the name, surname and date of birth of the person to whom you will enter the data about their ancestor: ";
				cin >> name >> surname >> birth;

				node* n = familyTree.find(name, surname, birth);
				
				if (!n) {
					cout << "There's no such person in the tree!\n";
					break;
				}

				cout << "\nADD THE ANCESTOR\n"
					 << "\nType the name, surname, date of birth and gender (F or M): ";
				cin >> name >> surname >> birth >> gender;
				cout << "\n" << name << " " << surname << ", " << birth << "\n";

				person* p = new person;
				p->name = name;
				p->surname = surname;
				p->birth = birth;
				p->gender = gender;

				if (gender == 'f' || gender == 'F')
					familyTree.addRightChild(p, n);
				else if (gender == 'm' || gender == 'M')
					familyTree.addLeftChild(p, n);
				else
					cout << "The program is too basic to understand a concept of a non-karyotypical gender\n";
			}
				break;
				
				
				
				
				
				
				
			case '3':
			{
				cout << "\nMODIFYING ONE'S PERSONAL DATA\n"
					 << "Type the name, surname and date of birth: ";
				cin >> name >> surname >> birth;

				node* n = familyTree.find(name, surname, birth);
				if (!n) {
					cout << "There's no such person in the tree!\n";
					break;
				}

				cout << "\nTYPE THE NEW PERSONAL DATA\n"
					 << "Type the name, surname and date of birth: ";
				cin >> name >> surname >> birth;
				
				n->data->name = name;
				n->data->surname = surname;
				n->data->birth = birth;

				cout << "\n" << name << " " << surname << ", " << birth << "\n";
			}
				break;
				
				
				
				
				
				
				
			case '4':
			{
				cout << "\nSHOWING SOMEBODY'S PARENTS\n"
					 << "Type the name, surname and date of birth: ";
				cin >> name >> surname >> birth;

				node* n = familyTree.find(name, surname, birth);
				if (!n) {
					cout << "There's no such person in the tree!\n";
					break;
				}
				if (n->leftChild != NULL || n->rightChild != NULL) {
					cout << "\nThe person has the following parents";
					if (n->leftChild != NULL)
						cout << "Dad: " << n->leftChild->data->name << " "
						<< n->leftChild->data->surname << ", " << n->leftChild->data->birth << "\n";
					if (n->rightChild != NULL)
						cout << "Mom: " << n->rightChild->data->name << " "
						<< n->rightChild->data->surname << ", " << n->rightChild->data->birth << "\n";
				}
				else
					cout << "\nThe person doesn't have any parents :C";
				
			}
				break;
				
				
				
				
				
				
				
			case '5':
			{
				cout << "\nTHE FAMILY TREE:\n";
				familyTree.printData();
			}
				break;
				
				
				
				
				
				
				
			case '6':
			{
				cout << "\nDELETING THE EXISTING PERSON\n"
					 << "Type the name, surname and date of birth: ";
				cin >> name >> surname >> birth;

				node* n = familyTree.find(name, surname, birth);
				if (!n) {
					cout << "There's no such person in the tree!\n";
					break;
				}
				familyTree.deleteNode(n);
			}
				break;
				
				
				
				
				
				
				
			case '7':
			{
				cout << "\nDELETING THE TREE\n";
				familyTree.makeNull();
			}
				break;
				
				
				
				
				
				
				
			case '8':
			{
				cout << "\nSAVING THE TREE\n";
				ofstream output; output.open("ancestorTree.txt");
				node* root = familyTree.getRoot();
				familyTree.writeTreeTXT(root, output);
				output.close();
			}
				break;
				
				
				
				
				
				
				
			case '9':
			{
				cout << "\nLOADING THE TREE\n";
				ifstream input; input.open("ancestorTree.txt");
				familyTree.makeNull();
				familyTree.readTreeTXT(input);
			}
				break;
				
				
				
				
				
				
				
			case 'a': {
				cout << "\nRETURNING THE PATH\n"
					<< "Type the name, surname and date of birth of the specific person: ";
				cin >> name >> surname >> birth;

				node* n = familyTree.find(name, surname, birth);
				if (!n) {
					cout << "There's no such person in the tree!\n";
					break;
				}

				familyTree.traceWantedNode(n);
			}
				break;
				
				
				
				
				
				
				
			case '0':
				return 0;
			
		}
	}


	return 0;
}
