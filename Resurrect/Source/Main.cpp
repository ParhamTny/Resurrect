#include <Resurrect/Resurrect.hpp>

int main()
{
	Resurrect::Window window("Resurrect window", { 800, 600 }, { 100, 100 });
	Resurrect::Instance instance("Resurrect application", { 1, 0 });
	while (!window.ShouldClose());

	return 0;
}