#include "TF1.h"
#include "TCanvas.h"
//#include <iostream>
//#include <string>

TF1 myFunction(){

	TF1 f("f1", "cos(x)", -5., 5.);
	f.SetLineColor(kBlue+1);
	f.SetTitle("My graph;x;x; cos(x)");

	return f;
}

std::string askFileName(const std::string question, std::istream &in, std::ostream &out){

	std::string filename{};
	out << question;
	in >> filename;
	return filename;
}

void create_pdf(TF1 & func, std::string file_name){

	file_name.append(".pdf");
	const TCanvas c{"c", "Something", 0, 0, 800, 600};
	func.Draw();
	c.Print(file_name.c_str());
};


int main(){

	TF1 f{myFunction()};
	std::string filename{
		askFileName("Please enter pdf filename: ", std::cin, std::cout)};
	create_pdf(f, filename);

	return 0;
}
