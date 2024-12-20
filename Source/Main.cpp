#include <Resurrect/Resurrect.hpp>

int main()
{
	Resurrect::Window window("Resurrect window", { 800, 600 }, { 100, 100 });
	while (!window.ShouldClose());

	return 0;
}