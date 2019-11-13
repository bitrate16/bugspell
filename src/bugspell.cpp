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
		     if (resc == 34) c = L' ';
		else if (resc == 35) c = L'.';
		else if (resc == 36) c = L',';
		else if (resc == 37) c = L'?';
		else if (resc == 38) c = L'!';
		else if (resc == 39) c = L'+';
		else if (resc == 40) c = L'=';
		else if (resc == 41) c = L'-';
		else if (resc == 42) c = L'_';
		else if (resc == 43) c = L')';
		else if (resc == 44) c = L'(';
		else if (resc == 45) c = L'[';
		else if (resc == 46) c = L']';
		else if (resc == 47) c = L'{';
		else if (resc == 48) c = L'}';
		else if (resc == 49) c = L'<';
		else if (resc == 50) c = L'>';
		else if (resc == 51) c = L'0';
		else if (resc == 52) c = L'1';
		else if (resc == 53) c = L'2';
		else if (resc == 54) c = L'3';
		else if (resc == 55) c = L'4';
		else if (resc == 56) c = L'5';
		else if (resc == 57) c = L'6';
		else if (resc == 58) c = L'7';
		else if (resc == 59) c = L'8';
		else if (resc == 60) c = L'9';
		else if (resc == 61) c = L'~';
		else if (resc == 62) c = L':';
		else if (resc == 63) c = L';';
		else if (resc < 33)  c = (wchar_t) resc + L'а';
		
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
		     if (s[i] == L' ') charnum = 34;
		else if (s[i] == L'.') charnum = 35;
		else if (s[i] == L',') charnum = 36;
		else if (s[i] == L'?') charnum = 37;
		else if (s[i] == L'!') charnum = 38;
		else if (s[i] == L'+') charnum = 39;
		else if (s[i] == L'=') charnum = 40;
		else if (s[i] == L'-') charnum = 41;
		else if (s[i] == L'_') charnum = 42;
		else if (s[i] == L')') charnum = 43;
		else if (s[i] == L'(') charnum = 44;
		else if (s[i] == L'[') charnum = 45;
		else if (s[i] == L']') charnum = 46;
		else if (s[i] == L'{') charnum = 47;
		else if (s[i] == L'}') charnum = 48;
		else if (s[i] == L'<') charnum = 49;
		else if (s[i] == L'>') charnum = 50;
		else if (s[i] == L'0') charnum = 51;
		else if (s[i] == L'1') charnum = 52;
		else if (s[i] == L'2') charnum = 53;
		else if (s[i] == L'3') charnum = 54;
		else if (s[i] == L'4') charnum = 55;
		else if (s[i] == L'5') charnum = 56;
		else if (s[i] == L'6') charnum = 57;
		else if (s[i] == L'7') charnum = 58;
		else if (s[i] == L'8') charnum = 59;
		else if (s[i] == L'9') charnum = 60;
		else if (s[i] == L'~') charnum = 61;
		else if (s[i] == L':') charnum = 62;
		else if (s[i] == L';') charnum = 63;
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

// bash c.sh "" src/bugspell

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