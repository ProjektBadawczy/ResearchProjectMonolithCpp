#pragma once
class BFSResult
{
public:
	BFSResult(int* parents, bool success);
	~BFSResult();
	int* getParents();
	bool getSuccess();
private:
	int* parents;
	bool success;
};