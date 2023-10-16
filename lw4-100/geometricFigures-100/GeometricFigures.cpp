#include "pch.h"
#include "CCommandHandler.h"
#include "IShape.h"

using namespace std;

int main(int argc, char argv[])
{
	try
	{
		CCommandHandler ch(cin, cout);
		while (!cin.eof() && !cin.fail())
		{
			cout << "> ";

			if (!ch.HandleCommand())
			{
				cout << "Unknown command!\nUsage: Circle, Trinagle, Rectangle or LineSegment with parameters" << endl;
			}
		}
		ch.PrintShapeWithMinPerimetr();
		ch.PrintShapeWithMaxArea();
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
		return 1;
	}

	return 0;
}
