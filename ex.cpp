#include <string>
#include <cstdlib>
using namespace std;

void visualize() {
    system("dot -Tpng -o digraph.png digraph.txt");
    system("start digraph.png");
}

int main()
{
    visualize();
    return 0;
}
