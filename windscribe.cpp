#include <bits/stdc++.h>
using namespace std;

vector<string> tokenize(string str)
{
    vector<string> tokens;
    string element;
    for (int i = 0; i < str.length(); i++)
    {
        if ((str[i] == ' ' || str[i] == '\t') && element.length() != 0)
        {
            tokens.push_back(element);
            element.clear();
        }
        else if (!(str[i] == ' ' || str[i] == '\t'))
        {
            element += string(1, str[i]);
        }
    }
    if (element.length() != 0)
    {
        tokens.push_back(element);
    }
    return tokens;
}

bool comparator(pair<string, float> &a, pair<string, float> &b)
{
    return a.second > b.second;
}

int main()
{
    ifstream locations("locations.txt");

    vector<string> locationVec;
    vector<pair<string, float>> speeds;
    string location, line;
    int countLine = 0;
    float per;

    while (getline(locations, location))
    {
        locationVec.push_back(location);
        cout<<location<<endl;
    }
    locations.close();
    cout<<"[          ]  " << 0 << "% completed" << endl;
    for (int i = 0; i < locationVec.size(); i++)
    {
        string query = "windscribe connect " + locationVec[i] + " >> ignore.txt";
        system(query.c_str());
        query = "speedtest --simple --no-upload >> output.txt";
        system(query.c_str());
        per = (i + 1) * 1.0 / locationVec.size();
        cout << "[";
        for (int i = 1; i <= 10; i++)
        {
            if (i <= 10 * per)
                cout << "*";
            else
                cout << " ";
        }
        cout << "]  " << per * 100 << "% completed" << endl;
    }

    ifstream outputs("output.txt");

    while (getline(outputs, line))
    {
        countLine++;
        if (countLine % 3 == 2)
        {
            vector<string> tokens = tokenize(line);
            speeds.push_back(make_pair(locationVec[countLine / 3], stof(tokens[1])));
        }
    }

    outputs.close();
    sort(speeds.begin(), speeds.end(), comparator);
    cout << "\n\nLocation\tSpeed" << endl
         << endl;
    for (auto i : speeds)
    {
        cout << i.first << "         " << i.second << endl;
    }
    system("rm output.txt ignore.txt");
}