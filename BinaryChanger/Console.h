#pragma once
#include <string>
#include <bitset>

using namespace std;
using Byte = bitset<8>;

class Console
{
	public:
		Console();
		~Console();

	private:
		void ask_input_file();
		void ask_output_file();
		void ask_dec();
		void read_n_write();
		void ask(string& answer);
		void process();
		void show_percentage(int const length, long long const& bytepos, long long const& file_size);
		Byte op(Byte base, int decal) {
			return Byte(base.to_ulong() + decal);
		}
		string m_input_file;
		string m_output_file;
		int16_t dec;
};

