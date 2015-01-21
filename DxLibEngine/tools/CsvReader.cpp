#include "stdafx.h"
#include "CsvReader.h"
#include <fstream>
#include <QString>

using namespace std;
CsvReader::CsvReader(void)
{
}


CsvReader::~CsvReader(void)
{
}

vector<string> split(string str, char ch )
{
	using namespace std;
	int begin = 0;
	int end = begin;
	vector<string> words;
	for (uint i=0; i<str.length(); ++i)
	{
		if (str[i] == ch)
		{
			end = i;
			words.push_back(str.substr(begin, end - begin));
			if (str[i+1] == '\r')
				++i;
			begin = i+1;
		}
	}
	end = str.length();
	words.push_back(str.substr(begin, end - begin));
	return words;
}


void CsvReader::FromFile( string fileName )
{
	QString str;
	data.clear();
	ifstream file(fileName);
	string context;
	while(getline(file, context))
	{
		data.push_back(split(context, ','));
	}
	return ;
}
