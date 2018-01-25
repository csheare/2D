#include <iostream>
void f() {
 static int count = 0;
 int index = 0;
 std::cout << ++count << ++index << std::endl;
}

int main() {
 f();
 f();
}
