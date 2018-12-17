#include "pch.h"
#include "Console.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;
using Byte = bitset<8>;

Console::Console() {
	string ascii_art =
		"|\n|	                /$$$$$$         \n"
		"|	               /$$__  $$        \n"
		"|	 /$$$$$$/$$$$ | $$  \\__//$$$$$$$\n"
		"|	| $$_  $$_  $$| $$$$   /$$_____/	minot0r file converter\n"
		"|	| $$ \\ $$ \\ $$| $$_/  | $$		github.com/minot0r\n"
		"|	| $$ | $$ | $$| $$    | $$      \n"
		"|	| $$ | $$ | $$| $$    |  $$$$$$$\n"
		"|	|__/ |__/ |__/|__/     \\_______/\n|";

	cout << ascii_art << endl << endl;

	bool _continue = true;
	while (_continue) {
		process();
		string ans;
		cout << "Recommencer ? (y/n)";
		ask(ans);
		(ans != "y") ? _continue = false : 0;
	}
	
}


Console::~Console() {
}

void Console::process() {
	ask_input_file();
	ask_output_file();
	ask_dec();

	ifstream input_file;
	input_file.open(this->m_input_file.c_str(), ios::binary);
	input_file.seekg(0, ios::end);
	long long file_size = input_file.tellg();
	input_file.seekg(0);

	ofstream output_file;
	output_file.open(this->m_output_file.c_str(), ios::binary);

	long long on_byte = 1;


	if (input_file.is_open()) {
		if (output_file.is_open()) {

			while (!input_file.eof()) {
				Byte oc = input_file.get();
				if (on_byte % (1024 * 1024 * 50) == 0) // Every 50mB
					show_percentage(20, on_byte, file_size);
				output_file << static_cast<char>(op(oc, this->dec).to_ulong());
				on_byte++;
			}

			input_file.close();
			output_file.close();
			cout << "Travail termine !\t\t\t" << endl;
		}
		else {
			cout << "Impossible d'ouvrir le fichier de sortie !";
		}

	}
	else {
		cout << "Impossible d'ouvrir le fichier d'entree !";
	}
}

void Console::show_percentage(int const length, long long const& bytepos, long long const& file_size) {
	int perthous = bytepos * 20 / file_size;
	cout << "[";
	for (int i = 0; i < perthous; i++)
		cout << '/';
	for (int i = 0; i <= 20 - perthous; i++)
		cout << '.';
	cout << "] " << bytepos * 100 / file_size << "% (" << bytepos / (1024 * 1024) << " Mb) \r";

}

void Console::ask_input_file() {
	cout << "Chemin du fichier d'entree";
	ask(this->m_input_file);
}

void Console::ask_output_file() {
	cout << "Chemin du fichier de sortie";
	ask(this->m_output_file);
}

void Console::ask_dec() {
	cout << "Decalage en bits";
	string ans;
	string::size_type st;
	ask(ans);
	this->dec = stoi(ans, &st);
}

void Console::read_n_write() {

}

void Console::ask(string& answer) {
	cout << " > ";
	getline(cin, answer);
}
