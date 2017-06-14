#include<bits/stdc++.h>

using namespace std;

vector<string> readPage(int pgno){
	vector<string> lines;	
	string filename;
	char linesin[1000][1000];
	if(pgno<=9){
	filename = "page_1.txt";
	filename[5]='0'+pgno;}
	else{
	filename = "page_10.txt";
	filename[5]='0'+ pgno/10;
	filename[6]='0'+ pgno%10;}
	int k=0;
	ifstream ifile;
	ifile.open(filename.c_str(), ios::in);
	if(!ifile){
		cout<<"File "<<filename<<" not opened properly!";
		return lines;
	}
	
	while(ifile.getline(linesin[k], 1000)){
		lines.push_back(linesin[k]);
		k++;
	}
	ifile.close();
	return lines;
}
void LPS(string word, int M, int lps[]){
	// len is the length of the previous lps
    int len = 0;

    lps[0] = 0; // lps[0] is always 0
 
    //Calculating:
    int i = 1;
    while (i < M)
    {
        if (word[i] == word[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else 
        {
            if (len != 0)
            {
                len = lps[len-1];
            }
            else 
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

	
 
void StringSearch(string word, string line, int lineno, int pgno, int &flag)
{
    int M = word.size();
    int N = line.size();
    int lps[M];
    LPS(word,M,lps);
 	int i = 0;  
    int j  = 0; 
    while (i < N)
    {
        if (word[j] == line[i])
        {
            i++;
            j++;
            
        }
        if ((j == M)&&((line[i]==' '||line[i]=='\n')&&line[i - M - 1] ==' '))
        {
            cout<<"Page "<<pgno<<" Line "<<lineno<<endl;
            j = lps[j-1];
            flag=1;
        }
 
        else if (i < N && word[j] != line[i])
        {
            
            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }
    
}


int main(){
	ifstream queries;
	int pgno=1,lineno;
	vector <string> lines;
	queries.open("queries.txt");
	while(!queries.eof()){
		string word;
		queries>>word;
		cout<<"Word: "<<word<<endl;
		cout<<"Occurrences:"<<endl;
		int flag=0;
		pgno=1;
		for(int i=1;i<=25;i++){
			lines=readPage(pgno);
			lineno=1;
			for(int j=0;j<lines.size();j++){
				
				StringSearch(word,lines[j],lineno,pgno,flag);
			lineno++;
			}
			pgno++;
		}
		if(flag==0)
		cout<<"None"<<endl;
		}
		queries.close();
		
	return 0;
}
