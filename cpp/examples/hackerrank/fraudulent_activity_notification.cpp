#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);


double median(std::map<int, std::size_t> & subset, int d)
{
	static const std::size_t i0 = std::floor((d-1)/2);
	static const std::size_t i1 = std::floor(d/2);

	std::size_t acc = 0;
	int m1 = 0;
	int m2 = 0;

	bool found0 = false;
	for (auto & item : subset)
	{
		acc += item.second;
		if (acc >= i0 + 1 && !found0)
		{
			m1 = item.first;
			found0 = true;
		}

		if (acc >= i1 + 1)
		{
			m2 = item.first;
			break;
		}
	}
	return ((double)m1 + (double)m2) / 2.0;
}


int activityNotifications(vector<int> expenditure, int d) {
	int notif = 0;
	std::map<int, std::size_t> subset;

	for (int i = 0; i < expenditure.size(); ++i)
	{
		if (i < d)
		{
			subset.emplace(expenditure[i], 0).first->second++;
			continue;
		}

		double m = median(subset, d);
		if (expenditure[i] >= 2 * m)
		{
			notif++;
		}

		subset.emplace(expenditure[i], 0).first->second++;
		subset[expenditure[i-d]]--;
	}

	return notif;
}


int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	string first_multiple_input_temp;
	getline(cin, first_multiple_input_temp);

	vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

	int n = stoi(first_multiple_input[0]);

	int d = stoi(first_multiple_input[1]);

	string expenditure_temp_temp;
	getline(cin, expenditure_temp_temp);

	vector<string> expenditure_temp = split(rtrim(expenditure_temp_temp));

	vector<int> expenditure(n);

	for (int i = 0; i < n; i++) {
		int expenditure_item = stoi(expenditure_temp[i]);

		expenditure[i] = expenditure_item;
	}

	int result = activityNotifications(expenditure, d);

	fout << result << "\n";

	fout.close();

	return 0;
}

string ltrim(const string &str) {
	string s(str);

	s.erase(
			s.begin(),
			find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
		   );

	return s;
}

string rtrim(const string &str) {
	string s(str);

	s.erase(
			find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
			s.end()
		   );

	return s;
}

vector<string> split(const string &str) {
	vector<string> tokens;

	string::size_type start = 0;
	string::size_type end = 0;

	while ((end = str.find(" ", start)) != string::npos) {
		tokens.push_back(str.substr(start, end - start));

		start = end + 1;
	}

	tokens.push_back(str.substr(start));

	return tokens;
}


