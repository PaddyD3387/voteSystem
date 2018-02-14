//Student Name: Patrick Delaney
//Student ID: C00207931
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <time.h>
using namespace std;
ifstream file("candidates.txt");
//====================================================================================================================
// BallotPaper Class
//====================================================================================================================
class BallotPaper{
	public:
		BallotPaper(int candCount, string line);

		void setPreference(int pref, int cand);
		int getPreference(int pref);
		int getSize();
		vector<int> getBallot();

	private:
		vector<int> prefs;
		int size;
};
BallotPaper::BallotPaper(int candCount, string line)
{
	int votePref, split, size = candCount;
	prefs.resize(size);
	for(int i=0; i<size; i++)
	{
		stringstream(line)>> votePref;
		split = line.find(",");
		prefs[votePref-1] = i;
		line = line.substr(split+1);
	}
}
void BallotPaper::setPreference(int votePref, int cand)
{
	prefs[votePref-1] = cand;
}
int BallotPaper::getPreference(int votePref)
{
	return prefs[votePref];
}
vector<int> BallotPaper::getBallot()
{
	return prefs;
};
//====================================================================================================================
// Candidate Class
//====================================================================================================================
class Candidate{
	public:
		void setName(string name);
		string getName(void);

		void setParty(string party);
		string getParty(void);

		Candidate(string name, string party); //constructor


	private:
		string candName;
		string candParty;
};
Candidate::Candidate(string name, string party)
{
	candName = name;
	candParty = party;
	cout<< "Candidate " << name<< " is running in the election." << endl;
}
void Candidate::setName(string name)
{
	cout<< candName;
	candName = name;
	cout<< " updated to "<< candName;
}
string Candidate::getName()
{
	return candName;
}
void Candidate::setParty(string party)
{
	cout<< candParty;
	candParty = party;
	cout<< " updated to "<< candParty;
}
string Candidate::getParty()
{
	return candParty;
};
//====================================================================================================================
//VoteCounter Method
//====================================================================================================================
int voteCounter(vector<BallotPaper> votes, int size, vector<Candidate> candidates)
{
	int high, elim;
	int stage = 1;
	bool check;
	int* count = new int[size];
	int* valid = new int[size];
	vector<int> low;
	srand(time(NULL));
	for(int i=0; i<size; i++)
	{
		valid[i] = true;
	}
	while(true)
	{
		for(int i=0; i<size; i++)
		{
			count[i] = 0;
		}
		for(int i=0; i<(int)votes.size(); i++)
		{
			for(int j=0; j<size; j++)
			{
				if(valid[votes[i].getPreference(j)])
				{
					count[votes[i].getPreference(j)]++;
					break;
				}
			}
		}
		for(int i=0; i<size; i++)
		{
			cout << count[i]<< "|";
		}
		cout<< endl;
		check = true;
		for(int i=0; i<size; i++)
		{
			if(check && valid[i])
			{
				check = false;
				low.push_back(i);
				high = i;
			}
			else if(valid[i])
			{
				if(count[low[0]] > count[i])
				{
					low.clear();
					low.push_back(i);
				}
				else if(count[low[0]] == count[i])
				{
					low.push_back(i);
				}
				if(count[high] < count[i])
				{
					high = i;
				}
			}
		}
		if(count[high]*2 > (int)votes.size())
			break;
		elim = low[rand()%low.size()];
		low.clear();
		valid[elim] = false;
        cout << "================== STAGE " << stage++ << " ======================" << endl;
		cout<< "candidate "<< candidates[elim].getName() << " eliminated\n";
		cout << "=================================================" << endl;
	}
	return high;
}
//====================================================================================================================
// Main
//====================================================================================================================
int main()
{
	string line, name, party;
	int split;
	vector<Candidate> candidates;
	vector<BallotPaper> votes;
/*Reads in the candidate's Names and Party and stores them into candidates vector*/
	while(getline(file, line))
	{
		if(line == "")
			break;
		split = line.find(";");
		name = line.substr(0, split);
		split++;
		party = line.substr(split);
		Candidate temp(name, party);
		candidates.push_back(temp);
	}
/*Reads in the votes for each BallotPaper stores them into votes vector*/
	while(getline(file, line))
	{
		BallotPaper tempo(candidates.size(), line);
		votes.push_back(tempo);
	}
/*finds the winner using the vote counter method*/
	Candidate winner = candidates[voteCounter(votes, (int)candidates.size(), candidates)];
	cout << "*************** WINNER ******************" << endl;
	cout<< winner.getName() << " of the " << winner.getParty() << " Party." << std::endl;
	system("pause");
}
