#define _CRT_SECURE_NO_WARNINGS
#define SIZE 30
#include<stdio.h>
#include<ctype.h>
#include<string>
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
struct nonterminal {
	char nt;
	int countofRules;
	char rules[SIZE][SIZE];
};
struct followsets {
	char nonterminal;
	string rules;
};
class firstSet {
public:
	int n;
	int NR = 0;
	nonterminal* nt = new nonterminal[SIZE];
	void FindFollow() {
		int i = 0;
		char f;
		bool flag = false;
		for (; i < NR; i++)
		{
			f = nt[i].nt;
			flag = false;
			for (int rules = 0; rules < NR; rules++) {
				
				for (int j = 0; j < nt[rules].countofRules; j++) {
					
					for (int k = 0; k < 12; k++) {

						char comp = nt[rules].rules[j][k];
						if (comp == '\0')
							break;
						if (comp == f) {
							flag = true;
							char nextitem = nt[rules].rules[j][k + 1];
							if (nt[rules].rules[j][k + 1] == '\0')
							{
								printf("\nFollow(%c) is Follow(%c)", f, nt[rules].nt);
								break;
							}
							if (nt[rules].rules[j][k + 1] != '\0') {
								
								if (isupper(nextitem)) {
									recursiveMethod(f, nextitem);
								}
								else {
									printf("\nFollow(%c) is %c", f, nextitem);
								}
							}
						}
					}
				}
			}
			if (flag == false) {
				printf("\nFollow(%c) is {}", f);
			}
		}
	}
	int findIndex(char s) {
		for (int i = 0; i < NR; i++) {
			if (nt[i].nt == s) {
				return i;
			}
		}
		return -1;
	}
	void recursiveMethod(char originalNT, char nonterminal) {
		int l = findIndex(nonterminal);
		char firstletter;
		for (int j = 0; j < nt[l].countofRules; j++) {
			firstletter = nt[l].rules[j][0];
			if (isupper(firstletter)) {
				recursiveMethod(originalNT, firstletter);
			}
			else {
				printf("\nFirst(%c) is %c", originalNT, firstletter);
			}
		}
	}
	void print() {
		printf("Original CFG is\n");
		for (int i = 0; i < NR; i++) {
			printf("%c->", nt[i].nt);
			for (int j = 0; j < nt[i].countofRules; j++) {
				printf("%s", nt[i].rules[j]);
				if (j == nt[i].countofRules - 1) {
					printf("\n");
				}
				else printf("|");
			}

		}
	}
	void makeRules(string prod) {
		if (prod != "\n" || prod != "\0")
		{
			string s = prod;
			string nonterminal = s.substr(0, s.find('-')); //save first letter as nonterminal
			s = s.substr(s.find('>') + 1, s.length()); //now read rules
			int i = 0;
			nt[NR].nt = nonterminal.at(0); //saving nonterminal in struct
			while (s.find('|') != string::npos) {
				char* s2 = convertToarr(s.substr(0, s.find('|'))); //read rule till |
				int l = 0;
				for (; l < SIZE; l++) {
					nt[NR].rules[i][l] = s2[l];
				}
				nt[NR].rules[i][l] = '\0';
				s = s.substr(s.find('|') + 1, s.length());
				i++;
			}

			if (s.length() > 0) { //if still pending rule
				char* s2 = convertToarr(s);
				int l = 0;
				for (; l < s.length(); l++) {
					nt[NR].rules[i][l] = s2[l];
				}
				nt[NR].rules[i][l] = '\0';

				i++;
			}
			nt[NR].countofRules = i;
			NR++;
		}

	}
	char* convertToarr(string s) {
		char* a = (char*)malloc(sizeof(char) * s.length());
		int i = 0;
		for (; i < s.length(); i++) {
			a[i] = s[i];
		}
		a[i] = '\0';
		return a;
	}

	void loadCFGfromFile() {
		ifstream fin;
		fin.open("D:\\CFG.txt");
		string rlist;
		if (fin.is_open())
		{
			while (!fin.eof())
			{
				getline(fin, rlist);

				if (rlist != " " || rlist != "\n" || rlist != "\0")
					makeRules(rlist);

			}
			fin.close();
		}
		else
			cout << "File not found." << endl;
	}

};

int main() {
	firstSet fs = firstSet();
	fs.loadCFGfromFile();
	fs.print();
	fs.FindFollow();

	system("pause");
}

