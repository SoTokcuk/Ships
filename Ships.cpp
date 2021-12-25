#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;
int main()
{
    fstream file("SHIPS.OUT");
    fstream file1("SHIPS.IN");
    ofstream fout("SHIPS.OUT");
    ifstream fin("SHIPS.IN");
    int N;
    vector <string> shipName;
    fin >> N;
    fin.ignore();
    map <int, string> mp;

    for (int i = 1; i < N + 1; i++)
    {
        mp[i] = "free";
    }
    map <int, string>::iterator iterMap;
    iterMap = mp.begin();
    try
    {
        if (!file)
        {
            throw "File <SHIPS.OUT> isn't open";
        }
        else if (!file1)
        {
            throw "File <SHIPS.IN> iisn't open";
        }
        else if (file1.peek() == EOF)
        {
            throw "<SHIPS.IN> is empty";
        }
        else
        {
            while (!fin.eof())
            {
                string str;
                getline(fin, str);
                int x;
                auto pos = str.find(" ");
                string str0 = str.substr(0, pos + 1);
                if (isdigit(str[0]) && str.size() == 1)
                {
                    x = stoi(str);
                }
                else
                {
                    str0.erase(1, 1);
                    str.erase(0, pos + 1);
                    x = stoi(str0);
                }
                switch (x)
                {
                case 1:
                {
                    shipName.push_back(str);
                    for (iterMap = mp.begin(); iterMap != mp.end(); iterMap++)
                    {
                        if (shipName.size() == 0)
                        {
                            break;
                        }
                        if (iterMap->second == "free")
                        {
                            iterMap->second = *shipName.begin();
                            shipName.erase(shipName.begin());
                        }
                    }
                    break;
                }
                case 2:
                {
                    int numOfFreePiers = stoi(str);
                    try
                    {
                        if (numOfFreePiers > N || numOfFreePiers <= 0)
                        {
                            throw "Wrong number of pier";
                        }
                    }
                    catch (const char* exception)
                    {
                        cout << "Error" << exception;
                    }
                    mp[numOfFreePiers] = "free";
                    if (shipName.size() != 0)
                    {
                        mp[numOfFreePiers] = shipName.front();
                        shipName.erase(shipName.begin());
                    }
                    break;
                }
                case 3:
                {
                    fout << "Maximum number of ports: " << N << endl;
                    if (shipName.size())
                    {
                        fout << "Number of ships in queue: " << shipName.size() << endl;
                        fout << "Ships in queue: ";
                        if (shipName.size() != 0)
                        {
                            for (int i = 0; i < shipName.size(); i++)
                            {
                                fout << shipName[i] << ";";
                            }
                            fout << endl;
                        }
                    }
                    else
                    {
                        fout << "No ships in the queue" << endl;
                    }
                    break;
                }
                case 4:
                {
                    fout << "Port busy information:" << endl;
                    for (iterMap = mp.begin(); iterMap != mp.end(); iterMap++)
                    {
                        fout << iterMap->first << ":" << iterMap->second << endl;
                    }
                    break;
                }
                default:
                    try
                    {
                        if (x > 4 || x < 1)
                        {
                            throw "No information about this inquiry";
                        }
                    }
                    catch (const char* exception)
                    {
                        cerr << "Error" << exception;
                    }
                }
            }
        }
    }
    catch (const char* exception)
    {
        fout << "Error:" << exception;
    }
    return 0;
}