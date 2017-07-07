
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

			int j = mem.get_line_num();
			while (s[i] == ' ' || s[i] == ',') ++i;
			instr(i, s, a, _a, c, _c, d);
			while (s[i] == ' ' || s[i] == ',') ++i;
			if (s[i] == '#' || s[i] == '\0') { 
				int czi = bianhao(cz, empty, j);
				if (cz == "mfhi") 
				{
					b = 33; _b = address;
				}
				if (cz == "mflo") { b = 32; _b = address; }
				mem.add_text(czi, a, b, c, d, _a, _b, _c);
				continue; 
			}
			instr(i, s, b, _b, c, _c, d);
			while (s[i] == ' ' || s[i] == ',') ++i;
			if (s[i] == '#' || s[i] == '\0') { 
				int czi = bianhao(cz, empty, j);
				
				mem.add_text(czi, a, b, c, d, _a, _b, _c);
				continue; 
			}
			instr(i, s, c, _c, c, _c, d);
			int czi = bianhao(cz, address, j);
			mem.add_text(czi, a, b, c, d, _a, _b, _c);
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
int text::bianhao(string s, type ty, int i) {

	if (s == "add") { 
		r.xx.push_back( new Add(mem, r.is, r.os, reg));
		return 0; 
	}
	if (s == "addu") { 
		r.xx.push_back( new Addu(mem, r.is, r.os, reg));
		return 1; 
	}
	if (s == "addiu") { 
		r.xx.push_back( new Addiu(mem, r.is, r.os, reg));
		return 2; 
	}
	if (s == "sub") { 
		r.xx.push_back( new Sub(mem, r.is, r.os, reg));
		return 3;
	}
	if (s == "subu") {
		r.xx.push_back( new Subu(mem, r.is, r.os, reg));
		return 4;
	}
	if (s == "mul" && ty != empty) { 
		r.xx.push_back( new Mul(mem, r.is, r.os, reg));
		return 5; 
	}
	if (s == "mulu" && ty != empty) { 
		r.xx.push_back( new Mulu(mem, r.is, r.os, reg));
		return 6; 
	}
	if (s == "mul" && ty == empty) { 
		r.xx.push_back( new Mul2(mem, r.is, r.os, reg));
		return 7; 
	}
	if (s == "mulu" && ty == empty) {
		r.xx.push_back( new Mulu2(mem, r.is, r.os, reg));
		return 8; 
	}
	if (s == "div" && ty != empty) { 
		r.xx.push_back( new Div(mem, r.is, r.os, reg));
		return 9; 
	}
	if (s == "divu" && ty != empty) { 
		r.xx.push_back( new Divu(mem, r.is, r.os, reg));
		return 10; 
	}
	if (s == "div" && ty == empty) { 
		r.xx.push_back( new Div2(mem, r.is, r.os, reg));
		return 11; 
	}
	if (s == "divu" && ty == empty) { 
		r.xx.push_back( new Divu2(mem, r.is, r.os, reg));
		return 12; 
	}
	if (s == "xor") {
		r.xx.push_back( new Xor(mem, r.is, r.os, reg));
		return 13;
	}
	if (s == "xoru") { 
		r.xx.push_back( new Xoru(mem, r.is, r.os, reg));
		return 14; 
	}
	if (s == "neg") { 
		r.xx.push_back( new Neg(mem, r.is, r.os, reg));
		return 15; 
	}
	if (s == "negu") { 
		r.xx.push_back( new Negu(mem, r.is, r.os, reg));
		return 16; 
	}
	if (s == "rem") { 
		r.xx.push_back( new Rem(mem, r.is, r.os, reg));
		return 17;
	}
	if (s == "remu") { 
		r.xx.push_back( new Remu(mem, r.is, r.os, reg));
		return 18;
	}
	if (s == "li") { 
		r.xx.push_back( new li(mem, r.is, r.os, reg));
		return 19; 
	}
	if (s == "seq") { 
		r.xx.push_back( new Seq(mem, r.is, r.os, reg));
		return 20; 
	}
	if (s == "sge") { 
		r.xx.push_back( new Sge(mem, r.is, r.os, reg));
		return 21;
	}
	if (s == "sgt") { 
		r.xx.push_back( new Sgt(mem, r.is, r.os, reg));
		return 22; 
	}
	if (s == "sle") { 
		r.xx.push_back( new Sle(mem, r.is, r.os, reg));
		return 23;
	}
	if (s == "slt") { 
		r.xx.push_back( new Slt(mem, r.is, r.os, reg));
		return 24; 
	}
	if (s == "sne") { 
		r.xx.push_back( new Sne(mem, r.is, r.os, reg));
		return 25; 
	}
	if (s == "b" || s == "j") { 
		r.xx.push_back( new J(mem, r.is, r.os, reg, r));
		return 26; 
	}
	if (s == "beq") { 
		r.xx.push_back( new Beq(mem, r.is, r.os, reg, r));
		return 27;
	}
	if (s == "bne") { 
		r.xx.push_back( new Bne(mem, r.is, r.os, reg, r));
		return 28; 
	}
	if (s == "bge") { 
		r.xx.push_back( new Bge(mem, r.is, r.os, reg, r));
		return 29; 
	}
	if (s == "ble") { 
		r.xx.push_back( new Ble(mem, r.is, r.os, reg, r));
		return 30; 
	}
	if (s == "bgt") { 
		r.xx.push_back( new Bgt(mem, r.is, r.os, reg, r));
		return 31;
	}
	if (s == "blt") { 
		r.xx.push_back( new Blt(mem, r.is, r.os, reg, r));
		return 32;
	}
	if (s == "beqz") { 
		r.xx.push_back( new Beqz(mem, r.is, r.os, reg, r));
		return 33; 
	}
	if (s == "bnez") { 
		r.xx.push_back( new Bnez(mem, r.is, r.os, reg, r));
		return 34; 
	}
	if (s == "blez") { 
		r.xx.push_back( new Blez(mem, r.is, r.os, reg, r));
		return 35; 
	}
	if (s == "bgez") { 
		r.xx.push_back( new Bgez(mem, r.is, r.os, reg, r));
		return 36;
	}
	if (s == "bgtz") { 
		r.xx.push_back( new Bgtz(mem, r.is, r.os, reg, r));
		return 37; 
	}
	if (s == "bltz") { 
		r.xx.push_back( new Bltz(mem, r.is, r.os, reg, r));
		return 38; 
	}
	if (s == "jr") { 
		r.xx.push_back( new Jr(mem, r.is, r.os, reg, r));
		return 39; 
	}
	if (s == "jal") { 
		r.xx.push_back( new Jal(mem, r.is, r.os, reg, r));
		return 40; 
	}
	if (s == "jalr") { 
		r.xx.push_back( new Jalr(mem, r.is, r.os, reg, r));
		return 41; 
	}
	if (s == "la") { 
		r.xx.push_back( new La(mem, r.is, r.os, reg));
		return 42; 
	}
	if (s == "lb") { 
		r.xx.push_back( new Lb(mem, r.is, r.os, reg));
		return 43; 
	}
	if (s == "lh") { 
		r.xx.push_back( new Lh(mem, r.is, r.os, reg));
		return 44; 
	}
	if (s == "lw") { 
		r.xx.push_back( new Lw(mem, r.is, r.os, reg));
		return 45; 
	}
	if (s == "sb") { 
		r.xx.push_back( new Sb(mem, r.is, r.os, reg));
		return 46; 
	}
	if (s == "sh") { 
		r.xx.push_back( new Sh(mem, r.is, r.os, reg));
		return 47; 
	}
	if (s == "sw") { 
		r.xx.push_back( new Sw(mem, r.is, r.os, reg));
		return 48; }
	if (s == "move") { 
		r.xx.push_back( new Move(mem, r.is, r.os, reg));
		return 49; 
	}
	if (s == "mfhi") { 
		r.xx.push_back( new Move(mem, r.is, r.os, reg));
		return 50; 
	}
	if (s == "mflo") { 
		r.xx.push_back( new Move(mem, r.is, r.os, reg));
		return 51; 
	}
	if (s == "syscall") { 
		r.xx.push_back( new syscall(mem, r.is, r.os, reg, r));
		return 52; 
	}
}
