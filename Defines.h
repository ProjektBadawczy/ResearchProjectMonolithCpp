#pragma once
#include <string>

using namespace std;

// defines for paths to files which contains graphs of certain type
// should be given to GraphRepository constructor
#define BIG_DENSE		"graphs/big_dense_set.json"
#define BIG_SPARSE		"graphs/big_sparse_set.json"
#define RANDOM			"graphs/random_set.json"
#define SMALL_DENSE		"graphs/small_dense_set.json"
#define SMALL_SPARSE	"graphs/small_sparse_set.json"

#ifndef linux
#define ADDRESS "127.0.0.1"
#else
#define ADDRESS getenv("INSIDE_DOCKER") ? "0.0.0.0" : "127.0.0.1"
#endif
