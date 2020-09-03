#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters = 4;
int const NA = -1;

//Node of Trie
struct Node
{
	//A G T C are the allowed characters
	int next[Letters];
	bool patternEnd;

	Node()
	{
		fill(next, next + Letters, NA);
		patternEnd = false;
	}
};

int letterToIndex(char letter)
{
	//Matching Letters to positions in the "next" array
	switch (letter)
	{
	case 'A':
		return 0;
		break;
	case 'C':
		return 1;
		break;
	case 'G':
		return 2;
		break;
	case 'T':
		return 3;
		break;
	default:
		assert(false);
		return -1;
	}
}

vector<int> solve(string text, vector<string> &patterns)
{
	vector<int> result;
	vector<Node> trie;
	//init root node
	trie.push_back(Node());

	//construct trie from all patterns
	for (auto p = patterns.begin(); p != patterns.end(); p++)
	{
		//pos traverses the trie
		int pos = 0;
		for (int i = 0; i < (*p).size(); i++)
		{
			//extract character
			char ch = (*p)[i];
			if (trie[pos].next[letterToIndex(ch)] == NA)
			{
				//node with edge of "ch" doesnt exist, add a new node
				trie.push_back(Node());
				//move over to that and also add the req edge
				pos = trie[pos].next[letterToIndex(ch)] = trie.size() - 1;
			}
			else
			{
				//path already exists just move over to that node
				pos = trie[pos].next[letterToIndex(ch)];
			}
		}
		//mark that last node as pattern end
		trie[pos].patternEnd = true;
	}

	for (int i = 0; i < text.size(); i++)
	{
		//pos will be used to traverse tree
		int pos = 0;
		for (int j = i; j < text.size(); j++)
		{
			if (trie[pos].next[letterToIndex(text[j])] == NA)
				//no further matching possible, edge doesnt exist
				break;
			else
			{
				//move over to next node
				pos = trie[pos].next[letterToIndex(text[j])];
				if (trie[pos].patternEnd)
				{
					//if a pattern gets over here, then add to results
					result.push_back(i);
					break;
				}
			}
		}
	}
	return result;
}

int main(void)
{
	string text;
	cin >> text;

	int n;
	cin >> n;

	vector<string> patterns(n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector<int> ans;
	ans = solve(text, patterns);

	for (int i = 0; i < (int)ans.size(); i++)
	{
		cout << ans[i];
		if (i + 1 < (int)ans.size())
			cout << " ";
		else
			cout << endl;
	}

	return 0;
}
