#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source(filename.c_str());
    string textline;
    int count = 0;
    while(getline(source,textline)){
    	
    	float a,b,c,sum;
    	char format[] = "%[^:]: %f %f %f";
    	char t_name[100];
    	
		sscanf(textline.c_str(), format, t_name, &a, &b, &c);
		
		sum = a+b+c;
        char t_grade = score2grade(sum);
        
		names.push_back(t_name);
		scores.push_back(sum);
		grades.push_back(t_grade);
		
		count++;
	}
    
}


void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    cin >> command;
    string x;
    x = toUpperStr(command);
    if((x == "GRADE") || (x == "NAME")) {
        cin.ignore();
    getline(cin,key);
    }
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int test = 0;
    int x = names.size();
    for(int i = 0; i < x; i++) {
        if(toUpperStr(names[i]) == key) {
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            test++;
        }
    }

    if(test == 0) {
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    } 
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int test = 0;
    int x = grades.size();
    cout << "---------------------------------\n";
    
    for(int i = 0; i < x; i++) {
        grades[i] = toupper(grades[i]);
        if(grades[i] == key[0]) {
            cout << names[i] << " (" << scores[i] << ")\n";
            test++;
        }
    }

    if(test == 0) {
        cout << "Cannot found.\n";
    }

    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}