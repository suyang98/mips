#include "memory.h"



void memory::add_text(int czi, int a, int b, int c, string d, type _a, type _b, type _c) {
	symbol sym;
	sym.sy = czi;sym.i = linenum;
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



//
//void print() {
//	cout << datanum << endl;
//	for (int i = 0; i < datanum; ++i) cout << store[i];
//	for (int i = 0; i < linenum; ++i) cout << te[i].sy << ' ' << te[i].i << ' ' << te[i].one << ' ' << te[i]._one << ' ' << te[i].two << ' ' << te[i]._two << ' ' << te[i].thr << ' ' << te[i]._thr << ' ' << te[i].four << endl;
//	map<string, int>::iterator mapi;
//	for (mapi = da.begin(); mapi != da.end();++mapi) cout << mapi->first << ' ' << mapi->second << endl;
//	for (mapi = label.begin();mapi != label.end();++mapi) cout << mapi->first << ' ' << mapi->second << endl;
//}
