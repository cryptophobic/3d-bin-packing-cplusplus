#include "main.h"

int main() {

	std::string file = "D:\\newlog.txt";

	Stat::Logger* lg = new Stat::Logger(file);
	lg->Clear();
	lg->Append("one");
	lg->Append("two");
	lg->Append("three");
	lg->Append("four");

}