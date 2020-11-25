
#include "TechDemo.hpp"

int main (int argc, char *argv[])
{
	TechDemo* techDemo = new TechDemo();
	techDemo->Initialize();
	techDemo->UpdateAndRender();
	delete techDemo;

	return 0;
}