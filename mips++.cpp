#include <iostream>
#include "memory.h"
#include "text.h"
#include "registers.h"
#include "run.h"
using namespace std;

int main(int argc, char* argv[])
{

	memory a;
	registers regi;
	run r(a, cin, cout, regi);
	ifstream fin;
	fin.open(argv[1]);
	//fin.open("array_test1-mahaojun.s");
	text b(a, fin, regi, r);
	b.read_all();
	//a.print();
	b.tran();
	//a.print();
	r.runn();

	return r.ret;
}
