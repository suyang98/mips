
#include"text.h"

void text::read_all() {
	string s="";
	char c;
	getline(is, s, '.');
	c = get_char();
	s = "";
	while (c && c <='z'&&c>='a') {
		s = s + c;
		c = get_char();
	}
	if (s == "text") text::read_text();
	if (s == "data") text::read_data();
	reg.storage[29] = mem.get_data_num();
}
void text::read_data() {
	string s;
	while(!is.eof()) {
		getline(is,s);
		string cz = "";
		int i = 0;
		while (s[i] == ' ') ++i;
		if (s[i] == '#') continue;
		if ((s[i] <= 'z' && s[i] >= 'a')||(s[i] <= 'Z' && s[i] >= 'A')||s[i]=='_'||(s[i] <= '9' && s[i] >= '0')){
			string var = "";
			while ((s[i] <= 'z' && s[i] >= 'a') || (s[i] <= 'Z' && s[i] >= 'A') || s[i] == '_'||(s[i] <= '9' && s[i] >= '0')) {
				var = var + s[i];
				++i;
			}
			mem.add_var(var);
		}
		while (s[i] != '\0' && s[i] != '.') ++i;
		if (s[i] == '\0') continue;
		++i;
		while(s[i] <= 'z' && s[i] >= 'a') {
			cz = cz + s[i];
			++i;
		}
		if (cz == "data") { read_data(); continue; }
		if (cz == "text") { read_text(); continue; }
		if (cz == "ascii") {
			while (s[i] != '"')++i;
			++i;
			while (s[i] != '"') { 
				if (s[i] == '\\')
				{
					++i;
					if (s[i] == '\'') mem.add_data('\'');
					if (s[i] == '\"') mem.add_data('\"');
					if (s[i] == 'f') mem.add_data('\f');
					if (s[i] == 'n') mem.add_data('\n');
					if (s[i] == 'r') mem.add_data('\r');
					if (s[i] == 't') mem.add_data('\t');
					if (s[i] == 'v') mem.add_data('\v');
					if (s[i] == '\\') mem.add_data('\\');
					if (s[i] == '\?') mem.add_data('\?');
					if (s[i] == '0') mem.add_data('\0');
				}
				else mem.add_data(s[i]);++i; 
			}
		}
		if (cz == "asciiz") {
			while (s[i] != '"')++i;
			++i;
			while (s[i] != '"') { 
				if (s[i] == '\\')
				{
					++i;
					if (s[i] == '\'') mem.add_data('\'');
					if (s[i] == '\"') mem.add_data('\"');
					if (s[i] == 'f') mem.add_data('\f');
					if (s[i] == 'n') mem.add_data('\n');
					if (s[i] == 'r') mem.add_data('\r');
					if (s[i] == 't') mem.add_data('\t');
					if (s[i] == 'v') mem.add_data('\v');
					if (s[i] == '\\') mem.add_data('\\');
					if (s[i] == '\?') mem.add_data('\?');
					if (s[i] == '0') mem.add_data('\0');
				}
				else mem.add_data(s[i]);++i;
			}
			mem.add_data('\0');
		}
		if (cz == "align") {
			int num = 0, k;
			while (s[i] == ' ')++i;
			while (s[i] > '9' || s[i] < '0') ++i;
			while (s[i] >= '0' && s[i] <= '9') {
				num = num * 10 + s[i]- '0';
				++i;
			}
			k = 1 << num;
			mem.align(k);
		}
		if (cz == "space") { 
			int n = 0;
			while (s[i] == ' ')++i;
			while (s[i] > '9' || s[i] < '0') ++i;
			while (s[i] >= '0' && s[i] <= '9') {
				n = n * 10 + s[i] - '0';
				++i;
			}
			mem.sp(n);
		}
		if (cz == "byte") {
			while (s[i] == ' ')++i;
			while (s[i] != '#'&& s[i] != '\0') {
				bool flag = true;
				if (s[i] == '-') { flag = false;++i; }
				if (s[i] >= '0' && s[i] <= '9') {
					int num = 0;
					while (s[i] >= '0' && s[i] <= '9') {
						num = num * 10 + s[i] - '0';
						++i;
					}
					if (!flag) num = -num;
					mem.add_data(char(num)); continue;
				}
				++i;
			}
		}
		if (cz == "half") {
			while (s[i] == ' ')++i;
			while (s[i] != '#'&& s[i] != '\0') {
				bool flag = true;
				if (s[i] == '-') { flag = false;++i; }
				if (s[i] >= '0' && s[i] <= '9') {
					int num = 0, num1 = 0, num2 = 0;
					while (s[i] >= '0' && s[i] <= '9') {
						num = num * 10 + s[i] - '0';
						++i;
					}
					if (!flag) num = -num;
					num1 = num & 255; 
					num2 = (num >> 8) & 255; 
					mem.add_data(char(num1));
					mem.add_data(char(num2)); continue;

				}
				++i;
			}
		}
		if (cz == "word") {
			while (s[i] == ' ')++i;
			while (s[i] != '#'&& s[i] != '\0') {
				bool flag = true;
				if (s[i] == '-') { flag = false;++i; }
				if (s[i] >= '0' && s[i] <= '9') {
					int num = 0, num1 = 0, num2 = 0, num3 = 0, num4 = 0;
					while (s[i] >= '0' && s[i] <= '9') {
						num = num * 10 + s[i] - '0';
						++i;
					}
					if (!flag) num = -num;
					num1 = num & 255;
					num2 = (num >> 8) & 255;
					num3 = (num >> 16) & 255;
					num4 = (num >> 24) & 255;
					mem.add_data(char(num1));
					mem.add_data(char(num2));
					mem.add_data(char(num3));
					mem.add_data(char(num4)); continue;
				}
				++i;
			}
		}

	}
}
void text::read_text() {
	string s;
	while (!is.eof()) {
		getline(is, s);
		int i = 0;
		while (s[i] == ' '|| s[i] == '\t') ++i;
		if (s[i] == '.') {
			++i;
			if (s[i] == 'd') read_data();
			if (s[i] == 't') read_text();
			continue;
		}
		if (s[i] == '#') continue;
		if ((s[i]<='z' && s[i]>='a')||(s[i]<='Z' && s[i]>='A')||s[i]=='_'||(s[i] <= '9' && s[i] >= '0')) {
			string cz = "";
			while ((s[i]<='z' && s[i]>='a')||(s[i]<='Z' && s[i]>='A')||s[i]=='_'||(s[i] <= '9' && s[i] >= '0')) {
				cz = cz + s[i];
				++i;
			}
			if (s[i] == ':') { mem.add_label(cz);continue; }
			int a, b, c;string d = "";
			type _a, _b, _c;
			a = b = c = 0; 
			_a = _b = _c = empty;

			while (s[i] == ' ' || s[i] == ',') ++i;
			instr(i, s, a, _a, c, _c, d);
			while (s[i] == ' ' || s[i] == ',') ++i;
			if (s[i] == '#' || s[i] == '\0') { mem.add_text(cz, a, b, c, d, _a, _b, _c);continue; }
			instr(i, s, b, _b, c, _c, d);
			while (s[i] == ' ' || s[i] == ',') ++i;
			if (s[i] == '#' || s[i] == '\0') { mem.add_text(cz, a, b, c, d, _a, _b, _c);continue; }
			instr(i, s, c, _c, c, _c, d);

			mem.add_text(cz, a, b, c, d, _a, _b, _c);
		}
	}
}
char text::get_char() {
	char ch;
	if ((ch = is.get()) == EOF) return NULL;
	return ch;
}
void text::instr(int &i, string s, int &a, type &_a, int &b, type &_b, string &d) {
	bool flag = true;
	if (s[i] == '$') {
		_a = address;
		++i;
		string re = "";
		while ((s[i]<='z'&&s[i]>='a')||(s[i]<='9'&&s[i]>='0')) re = re + s[i++];
		a = reg.m[re];
	}
	if (s[i] == '-') { flag = false;++i; }
	if (s[i] <= '9'&&s[i] >= '0') {
		int num = 0;
		while (s[i] <= '9' && s[i] >= '0') { num = num * 10 + s[i] - '0';++i; }
		if (!flag) num = -num;
		if (s[i] == '(') {
			i += 2;
			_a = address;
			string re = "";
			while ((s[i] <= 'z'&&s[i] >= 'a') || (s[i] <= '9'&&s[i] >= '0')) re = re + s[i++];
			a = reg.m[re];
			b = num; _b = add;
		}
		else _a = number, a = num;
	}
	if ((s[i] <= 'z' && s[i] >= 'a') || (s[i] <= 'Z' && s[i] >= 'A') || s[i] == '_'|| (s[i] <= '9' && s[i] >= '0')) {
		while ((s[i] <= 'z' && s[i] >= 'a') || (s[i] <= 'Z' && s[i] >= 'A') || s[i] == '_'|| (s[i] <= '9' && s[i] >= '0')) {
			d = d + s[i]; ++i;
		}
		_a = empty;
	}
}
void text::tran() {
	int maxline;
	symbol *a;
	maxline = mem.get_line_num();
	for (int i = 0; i < maxline; ++i) {
		a = &mem.get_line(i);
		if (a->four != "") {
			if (a->sy == 26 || a->sy == 40) { a->_one = address; a->one = mem.find_label(a->four);a->four = ""; }
			else if (a->sy >= 33 && a->sy <=38)
				{a->_two = address; a->two = mem.find_label(a->four);a->four = "";}
			else if (a->sy >= 27 && a->sy <=32)
				{a->_thr = address; a->thr = mem.find_label(a->four);a->four = "";}
			else { a->_two = address; a->two = mem.find_data(a->four);a->four = ""; }
		}
	}
		
}