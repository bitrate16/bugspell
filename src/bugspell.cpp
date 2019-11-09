#include <algorithm>
#include <wctype.h>
#include <iostream>
#include <iostream>
#include <locale>
#include <string>
#include <string.h>
#include <codecvt>
#include <cstdlib>

#define CH_1 L'ж'
#define CH_2 L'В'
#define CH_3 L'Ж'
#define CH_4 L'в'

int rand_range(int min, int max) {
	return min + (rand() % static_cast<int>(max - min + 1));
};

std::wstring deconvert_pj(const std::wstring& s) {
	std::wstring out;
	
	// 1. 00 -> CH_1
	// 2. 11 -> CH_2
	// 3. 01 -> CH_3
	// 4. 10 -> CH_4
	
	for (int i = 0; i < s.size();) {
		while (i < s.size() && s[i] != CH_1 && s[i] != CH_2 && s[i] != CH_3 && s[i] != CH_4)
			++i;
		if (i >= s.size())
			break;
		int ch0 = s[i]; 
		// std::wcout << s[i];
		++i;
		
		while (i < s.size() && s[i] != CH_1 && s[i] != CH_2 && s[i] != CH_3 && s[i] != CH_4)
			++i;
		if (i >= s.size())
			break;
		int ch1 = s[i];
		// std::wcout << s[i];
		++i;
		
		while (i < s.size() && s[i] != CH_1 && s[i] != CH_2 && s[i] != CH_3 && s[i] != CH_4)
			++i;
		if (i >= s.size())
			break;
		
		int ch2 = s[i];
		// std::wcout << s[i] << ' ';
		++i;
		
		int resc = 0;
		     if (ch0 == CH_1) /* { */ resc |= 0b000000; /* std::wcout << "00"; } */
		else if (ch0 == CH_2) /* { */ resc |= 0b000011; /* std::wcout << "11"; } */
		else if (ch0 == CH_3) /* { */ resc |= 0b000001; /* std::wcout << "01"; } */
		else if (ch0 == CH_4) /* { */ resc |= 0b000010; /* std::wcout << "10"; } */
		
		     if (ch1 == CH_1) /* { */ resc |= 0b000000; /* std::wcout << "00"; } */
		else if (ch1 == CH_2) /* { */ resc |= 0b001100; /* std::wcout << "11"; } */
		else if (ch1 == CH_3) /* { */ resc |= 0b000100; /* std::wcout << "01"; } */
		else if (ch1 == CH_4) /* { */ resc |= 0b001000; /* std::wcout << "10"; } */
		
		     if (ch2 == CH_1) /* { */ resc |= 0b000000; /* std::wcout << "00"; } */
		else if (ch2 == CH_2) /* { */ resc |= 0b110000; /* std::wcout << "11"; } */
		else if (ch2 == CH_3) /* { */ resc |= 0b010000; /* std::wcout << "01"; } */
		else if (ch2 == CH_4) /* { */ resc |= 0b100000; /* std::wcout << "10"; } */
		
		wchar_t c = 0;
		if (resc == 34)
			c = ' ';
		else if (resc == 35)
			c == '.';
		else if (resc == 36)
			c == ',';
		else if (resc < 33)
			c = (wchar_t) resc + L'а';
		
		out += c;
		// std :: wcout << " '" << c << "'" << std::endl;
	}
	
	return out;
};

std::wstring convert_pj(const std::wstring& s) {
	std::wstring out;
	
	// 1. 00 -> CH_1
	// 2. 11 -> CH_2
	// 3. 01 -> CH_3
	// 4. 10 -> CH_4
	
	int word_length = 0;
	int char_count = 0;
	int bitnum = 0;
	
	for (int i = 0; i < s.size(); ++i) {
		int charnum;
		// std::wcout << std::endl << "'" << s[i] << "'";
		if (s[i] == L' ')
			charnum = 34;
		else if (s[i] == L'.')
			charnum = 35;
		else if (s[i] == L',')
			charnum = 36;
		else if (L'а' <= s[i] && s[i] <= L'я')
			charnum = s[i] - L'а';
		else if (L'А' <= s[i] && s[i] <= L'Я')
			charnum = s[i] - L'А';
		else 
			continue;
		
		for (int j = 0; j < 6; j += 2) {
			int bit0 = (charnum >> (j + 1)) & 1;
			//if (bitnum % 3)
			//	bit0 ^= 1;
			//++bitnum;
			int bit1 = (charnum >> (j + 0)) & 1;
			//if (bitnum % 3)
			//	bit1 ^= 1;
			//++bitnum;
			
			// std::wcout << bit0 << bit1;
			
			if (bit0)
				if (bit1)
					out += CH_2;
				else
					out += CH_4;
			else
				if (bit1)
					out += CH_3;
				else
					out += CH_1;
			++char_count;
			++word_length;
			
			if ((word_length > 2) && (char_count < s.size() * 3 - 2) && rand_range(0, 1) && rand_range(0, 1)) {
				out += ' ';
				word_length = 0;
			}
		}
	}
	
	// std::wcout << std::endl;
	
	return out;
};

// bash c.sh "" src/bugspell "фывфыаыфв"

// Отображает русский текст (с пробелами, всеми буквами) в последовательность 
//  ВжВжЖ (по правилу из функции, делит рандомными пробелами.
int main(int argc, char** argv) {
	// bugspell
	// bugspell "text"
	// bugspell -d "text"
	
	if (argc < 2) {
	
		std::ios_base::sync_with_stdio(false);

		std::locale utf8( std::locale(), new std::codecvt_utf8_utf16<wchar_t> );
		std::wcout.imbue(utf8);
		std::wcin.imbue(utf8);
		
		std::wstring input;
		std::wstring output;
		
		std::getline(std::wcin, input);
		
		output = convert_pj(input);
		
		std::wcout << output << std::endl;
		
		output = deconvert_pj(input);
		
		std::wcout << output << std::endl;
		
	} else if (argc == 2) {
	
		std::ios_base::sync_with_stdio(false);

		std::locale utf8( std::locale(), new std::codecvt_utf8_utf16<wchar_t> );
		std::wcout.imbue(utf8);
		std::wcin.imbue(utf8);
		
		std::string inputc(argv[1]);
		std::wstring input(inputc.begin(), inputc.end());
		std::wstring output;
		
		output = convert_pj(input);
		
		std::wcout << output << std::endl;
	} else if (argc >= 3 && strcmp(argv[1], "-d") == 0) {
	
		std::ios_base::sync_with_stdio(false);

		std::locale utf8( std::locale(), new std::codecvt_utf8_utf16<wchar_t> );
		std::wcout.imbue(utf8);
		std::wcin.imbue(utf8);
		
		std::string inputc(argv[2]);
		std::wstring input(inputc.begin(), inputc.end());
		std::wstring output;
		
		output = convert_pj(input);
		
		std::wcout << output << std::endl;
	}
	
	return 0;
};