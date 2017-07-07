#include"run.h"


void run::runn() {
	base *t;
	reg.storage[29] = 4 * 1024 * 1024;
	i = mem.find_label("main");
	bool fla;
	std::ofstream out("result.txt");
	//std::ofstream out2("textre.txt");
	//int k = mem.get_line_num();
	//for (int j = 0; j < k; ++j) {
	//	symbol a= mem.get_line(j);
	//	out2<<j<<' '<<a.sy<<' '<<a.one<<' '<< a._one<<' '<<a.two
	//		<<' '<<a._two<<' '<<a.thr<<' '<<a._thr<<endl;
	//}
	while (f) {
		fl = true;
		if (!v4.empty()) {
			t = v4.front();
			t->WB();
			v4.pop();
		}
		if (!v3.empty()) {
			t = v3.front();
			t->MA();
			v3.pop();
			v4.push(t);
		}
		if (!v2.empty()) {
			t = v2.front();
			t->EX();
			v2.pop();
			if ( !fl && fla ) v1.pop();
			v3.push(t);
		}
		if (!v1.empty()) {
			t = v1.front();
			if (t->ID()) {
				v1.pop();
				if (t->get_cz() != 39) v2.push(t);
			}
		}
		/*for (int j = 0; j < 34; j++) out << reg.storage[j] << " ";
		out << i<<' '<<endl;*/
		if (i >= mem.get_line_num()) { fla = false;continue; }
		else if (!v1.empty()) continue;
		else fla = true;
		a = mem.get_line(i);
		t = xx[i]; ++i;
		t->IF(a);
		v1.push(t);		
	}
	//cerr << endl;
	cerr << correct << " / " << tot << " = " << (double)correct / tot * 100 << "%" << endl;
}
