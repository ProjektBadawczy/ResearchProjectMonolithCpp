#pragma once
#include <string>

using namespace std;

#ifndef linux
#define ADDRESS "127.0.0.1"
#else
#define ADDRESS getenv("INSIDE_DOCKER") ? "0.0.0.0" : "127.0.0.1"
#endif
