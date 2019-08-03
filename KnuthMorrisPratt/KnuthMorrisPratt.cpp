// KnuthMorrisPratt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <iostream>

using namespace std;

///
/// Reference: http://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm#.22Partial_match.22_table_.28also_known_as_.22failure_function.22.29
///

int kmp_search(char *s, char *w);
void kmp_table(char *w, int T[]);


int _tmain(int argc, _TCHAR* argv[])
{
	char *s = "I don't know what this sentence is supposed to be, but it's used for testing KMP algorithm";
	char *w = "know what this";

	int i = kmp_search(s,w);

	cout << "Found at " << i << endl;

	system("pause");
	return 0;
}

int kmp_search(char *s, char *w)
{
	//the beginning of the current match in S
	int m = 0;

	//the position of the current character in W
	int i = 0;

	int lengthW = strlen(w);

	//the table holding search informaiton
	int *T = new int[lengthW];

	kmp_table(w,T);

	while (m + i < strlen(s))
	{
		if (w[i] == s[m + i]) //match
		{
			if (i == strlen(w) - 1)
				return m;
			else
				i++;
		}
		else //no match
		{
			if (T[i] > - 1)
			{
				m = m + i - T[i];
				i = T[i];
			}
			else
			{
				i = 0;
				m++;
			}
		
		}
	}

	delete [] T;

	return strlen(s);
}

void kmp_table(char *w, int T[])
{
	//current potisition we are computing in T
	int pos = 2;
	//the zero-based index in W of the next character of the current candidate substring
	int cnd = 0;

	T[0] = -1;
	T[1] = 0;

	while (pos < strlen(w))
	{
		//first case: the substring continues
		if (w[pos - 1] == w[cnd])
		{
			cnd++;
			T[pos] = cnd;
			pos++;
		}
		else if (cnd > 0)//second case: it doesn't, but we can fall back
		{
			cnd = T[cnd];
		}
		else //third case: we have run out of candidates. Note cnd = 0
		{
			T[pos] = 0;
			pos++;
		}
	}
}

