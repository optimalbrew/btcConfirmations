/*
 * This C++ source file was generated by the Gradle 'init' task.
 */

#include "app.h"
#include <cassert>

int main() {
    attack::Greeter greeter;
    assert(greeter.userinput("Hello, World!").compare("Hello, World!") == 0);
    return 0;
}
