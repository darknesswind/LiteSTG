#ifndef CSVREADER_H
#define CSVREADER_H
#pragma once
#include <string>
#include <vector>

class CsvReader
{
	CsvReader(void);
public:	
	~CsvReader(void);

	void FromFile(std::string fileName);

	std::vector<std::vector<std::string>> data;
};

#endif