#pragma once
#ifndef _memory_h
#endif _memory_h
#include<map>
#include<deque>
#include<string>
#include<vector>
#include<iostream>
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

enum type { address, number, empty, add };
struct symbol {
	string sy, four;
	int one, two, thr, i;
	type _one, _two, _thr;
};
class memory {
private:
	map<string, int> da, label;
	char *store;
	vector<symbol> te;
	int linenum, datanum;

public:
	memory() { linenum = 0; datanum = 0; store = new char[4 * 1024 * 1024]; }
	~memory() { delete[] store; }
	void add_text(string s, int a, int b, int c, string d, type _a, type _b, type _c) {
		symbol sym;
		sym.sy = s;sym.i = linenum;
		sym.one = a; sym.two = b; sym.thr = c; sym.four = d;
		sym._one = _a; sym._two = _b; sym._thr = _c;
		te.push_back(sym); linenum++;
	}
	void add_label(string s) { label[s] = linenum; }
	void add_data(char c) { store[datanum] = c;datanum++; }
	void add_var(string s) { da[s] = datanum; }
	symbol& get_line(int i) { return te[i]; }
	char get_data(int i) { return store[i]; }
	int get_data_num() { return datanum; }
	int get_line_num() { return linenum; }
	void align(int k) {
		int i = datanum % k, tmp = datanum;
		if (datanum == 0) datanum = k;
		else if (i == 0) return;
		else datanum = (1 + datanum / k) * k;
		for (int i = tmp; i < datanum; ++i) store[i] = '\0';
	}
	void sp(int n) { for (int i = 0; i < n; ++i) store[datanum++] = '\0'; }
	void print() {
		cout << datanum << endl;
		//for (int i = 0; i < datanum; ++i) cout << store[i];
		for (int i = 0; i < linenum; ++i) cout << te[i].sy << ' ' << te[i].i << ' ' << te[i].one << ' ' << te[i]._one << ' ' << te[i].two << ' ' << te[i]._two << ' ' << te[i].thr << ' ' << te[i]._thr << ' ' << te[i].four << endl;
		map<string, int>::iterator mapi;
		for (mapi = da.begin(); mapi != da.end();++mapi) cout << mapi->first << ' ' << mapi->second << endl;
		for (mapi = label.begin();mapi != label.end();++mapi) cout << mapi->first << ' ' << mapi->second << endl;
	}
	int find_label(string s) { return label[s]; }
	int find_data(string s) { return da[s]; }
	void change_data(int i, char c) { store[i] = c; }
};