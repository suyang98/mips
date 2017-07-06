#include "memory.h"



void memory::add_text(string s, int a, int b, int c, string d, type _a, type _b, type _c) {
	symbol sym;
	sym.sy = bianhao(s, _c);sym.i = linenum;
	sym.one = a; sym.two = b; sym.thr = c; sym.four = d;
	sym._one = _a; sym._two = _b; sym._thr = _c;
	te.push_back(sym); linenum++;
}

void memory::align(int k) {
	int i = datanum % k, tmp = datanum;
	if (datanum == 0) datanum = k;
	else if (i == 0) return;
	else datanum = (1 + datanum / k) * k;
	for (int i = tmp; i < datanum; ++i) store[i] = '\0';
}

int memory::bianhao(string s, type ty) {
		
		if (s == "add") {return 0;}
		if (s == "addu") { return 1; }
		if (s == "addiu") { return 2; }
		if (s == "sub") { return 3; }
		if (s == "subu") { return 4; }
		if (s == "mul" && ty != empty) { return 5; }
		if (s == "mulu" && ty != empty) { return 6; }
		if (s == "mul" && ty == empty) { return 7; }
		if (s == "mulu" && ty == empty) { return 8; }
		if (s == "div" && ty != empty) { return 9; }
		if (s == "divu" && ty != empty) { return 10; }
		if (s == "div" && ty == empty) { return 11; }
		if (s == "divu" && ty == empty) { return 12; }
		if (s == "xor") { return 13; }
		if (s == "xoru") { return 14; }
		if (s == "neg") { return 15; }
		if (s == "negu") { return 16; }
		if (s == "rem") { return 17; }
		if (s == "remu") { return 18; }
		if (s == "li") { return 19; }
		if (s == "seq") { return 20; }
		if (s == "sge") { return 21; }
		if (s == "sgt") { return 22; }
		if (s == "sle") { return 23; }
		if (s == "slt") { return 24; }
		if (s == "sne") { return 25; }
		if (s == "b" || s == "j") { return 26; }
		if (s == "beq") { return 27; }
		if (s == "bne") { return 28; }
		if (s == "bge") { return 29; }
		if (s == "ble") { return 30; }
		if (s == "bgt") { return 31; }
		if (s == "blt") { return 32; }
		if (s == "beqz") { return 33; }
		if (s == "bnez") { return 34; }
		if (s == "blez") { return 35; }
		if (s == "bgez") { return 36; }
		if (s == "bgtz") { return 37; }
		if (s == "bltz") { return 38; }
		if (s == "jr") { return 39; }
		if (s == "jal") { return 40; }
		if (s == "jalr") { return 41; }
		if (s == "la") { return 42; }
		if (s == "lb") { return 43; }
		if (s == "lh") { return 44; }
		if (s == "lw") { return 45; }
		if (s == "sb") { return 46; }
		if (s == "sh") { return 47; }
		if (s == "sw") { return 48; }
		if (s == "move") { return 49; }
		if (s == "mfhi") { return 50; }
		if (s == "mflo") { return 51; }
		if (s == "syscall") { return 52; }
}


//
//void print() {
//	cout << datanum << endl;
//	for (int i = 0; i < datanum; ++i) cout << store[i];
//	for (int i = 0; i < linenum; ++i) cout << te[i].sy << ' ' << te[i].i << ' ' << te[i].one << ' ' << te[i]._one << ' ' << te[i].two << ' ' << te[i]._two << ' ' << te[i].thr << ' ' << te[i]._thr << ' ' << te[i].four << endl;
//	map<string, int>::iterator mapi;
//	for (mapi = da.begin(); mapi != da.end();++mapi) cout << mapi->first << ' ' << mapi->second << endl;
//	for (mapi = label.begin();mapi != label.end();++mapi) cout << mapi->first << ' ' << mapi->second << endl;
//}
