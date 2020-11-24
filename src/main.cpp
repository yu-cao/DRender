
#include "../include/TechDemo.h"

int main (int argc, char *argv[])
{
	TechDemo* techDemo = new TechDemo();
	techDemo->Initialize();
	techDemo->UpdateAndRun();
	delete techDemo;

	return 0;
}