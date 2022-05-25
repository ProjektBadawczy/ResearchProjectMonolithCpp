#include "BFSResult.h"

BFSResult::BFSResult(int* parents, bool success)
{
	this->parents = parents;
	this->success = success;
}
BFSResult::~BFSResult()
{
	delete[] parents;
}
int* BFSResult::getParents()
{
	return parents;
}
bool BFSResult::getSuccess()
{
	return success;
}