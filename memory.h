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
	string four;
	int sy, one, two, thr, i;
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
	void add_text(int czi, int a, int b, int c, string d, type _a, type _b, type _c);
	void add_label(string s) { label[s] = linenum; }
	void add_data(char c) { store[datanum] = c;datanum++; }
	void add_var(string s) { da[s] = datanum; }
	void change_data(int i, char c) { store[i] = c; }
	int find_label(string s) { return label[s]; }
	int find_data(string s) { return da[s]; }
	symbol& get_line(int i) { return te[i]; }
	char get_data(int i) { return store[i]; }
	int get_data_num() { return datanum; }
	int get_line_num() { return linenum; }
	void align(int k);
	void sp(int n) { for (int i = 0; i < n; ++i) store[datanum++] = '\0'; }
	//void print();
};