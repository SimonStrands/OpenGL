#include "fileConverter.h"

int main()
{
	std::cout << "What file do you wanna convert to OEM?" << std::endl;
	std::string CurrentFile;
	std::cin >> CurrentFile;
	std::string NewFile;
	std::cout << "wanna give the file a new name? ('n' = no, other name be the file name)" << std::endl;
	std::cin >> NewFile;
	if(NewFile == "n"){
		NewFile = "";
	}

	if(!convert(CurrentFile, NewFile)){
		std::cout << "something went wrong" << std::endl;
	}
	else{
		std::cout << "Done!" << std::endl;
	}

	std::cout << "press enter to close program" << std::endl;
	getchar();
	return 0;
}