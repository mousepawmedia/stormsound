#include "stormsound/dummy.hpp"

void Dummy::speak() { channel << "Hello, world!" << IOCtrl::endl; }
