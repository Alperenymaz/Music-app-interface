
#include <iostream>
#include"LinkedList.h"
#include "LQueue.h"

using namespace std;

struct Data
{
	string name;
	Queue<string> songs;
	Data(string xname ="Def", string xsong = "Def") {
		name = xname;
		if(xsong != "Def")
			songs.add(xsong);
	}
	bool operator==(const Data& asd) {
		return (name == asd.name);
	}
	friend ostream& operator<<(ostream& out, const Data& asd) {
		Queue<string> xsongsLike;
		xsongsLike = asd.songs;
		while (!xsongsLike.isEmpty())
		{
			out << xsongsLike.front() << endl;
			xsongsLike.remove();
		}
		return out;
	}
};
int main()
{
	LinkedList<Data> Head[100];
	LinkedList<string> names;
	string namesArr[100];
	LinkedList<string> songArr[100];
	LinkedList<string> songs;
	LLNode<Data>* info;

	char comm;
	int doesFinish = 0;
	int num = 0;
	string name, songname;
	bool ext;

	while (doesFinish == 0)
	{
		cout << "\nC-c to Add user \nS-s to Set song name \nL-l to List song names \nE-e to Erase song name \nN-n to List all names \nM-m to List all songs \nQ-q to Quit" << endl;
		cin >> comm;

		switch (comm)
		{

		case 'C':
		case 'c':

			ext = true;
			cout << "Enter name: ";
			cin >> name;

			for (int i = 0; i < num; i++)
			{
				if (namesArr[i] == name) {
					ext = false;
					break;
				}
			}
			if (ext) {
				names.insertFirst(" " + name);
				Head[num].insertFirst(Data(name));
				namesArr[num] = name;
				num++;
			}
			else
			{
				cout << "Wrong name!\n";
			}
			break;

		case 'S':
		case 's':
			cout << "Enter name: ";
			cin >> name;

			for (int i = 0; i < num; i++)
			{
				info =  Head[i].search(namesArr[i]);

				if (info->data.name == name) {

					cout << "Enter song name: ";
					cin >> songname;
					if (!songArr[i].search(songname)) {
						songArr[i].insertFirst(songname);
						songs.insertFirst(" " + songname);
						info->data.songs.add(songname);
					}
					else
					{
						cout << "Wrong name\n";
					}
				}
			}
			break;

		case 'L':
		case 'l':

			cout << "Enter name: ";
			cin >> name;

			for (int i = 0; i < num; i++)
			{
				info = Head[i].search(namesArr[i]);

				if (info->data.name == name) {

					cout << info->data;
				}
			}
			break;

		case 'E':
		case 'e':
			cout << "Enter name: ";
			cin >> name;

			for (int i = 0; i < num; i++)
			{
				info = Head[i].search(namesArr[i]);

				if (info->data.name == name) {

					//Head[i].clearList();
				}
			}
			break;

		case 'N':
		case 'n':
			cout << "Names: \n";
			names.reversePrint();
			break;

		case 'M':
		case 'm':
			cout << "Songs: \n";
			songs.reversePrint();
			break;

		case 'Q':
		case 'q':
			cout << "\nEnd!" << endl;
			doesFinish = 1;
			break;
		default:
			cout << "\nWrong input!" << endl;
			break;
		}
	}

}


