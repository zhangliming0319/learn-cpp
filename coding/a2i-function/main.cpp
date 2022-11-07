#include <iostream>
#include <sstream>

int main(int argc, char** argv) {
  std::stringstream ss;
  std::cout.precision(10);
	int n1;
	double n2;
	std::string n3, n4;
	// auto s = "123.00009";
	// ss << s;         // 类似 cout
	// ss >> n2;        // 类似 cin
	// //std::cout.precision(10);
	// std::cout << "string \"" << s << "\" to double object "
	// 	<< n2 << std::endl;
	// string 转 int / double

	ss.clear();
	ss<<"123";
	ss>>n1;
	
  ss.clear();
	ss<<"456.789";
	ss>>n2;
	
	// int / double 转string
	ss.clear(); 
	ss<<114514;
	ss>>n3;
	
	ss.clear();
	ss<<1919.81;
	ss>>n4;
	
	std::cout<<n1<<" "<<n2<<" "<<n3<<" "<<n4<<std::endl;
	
	return 0;
}