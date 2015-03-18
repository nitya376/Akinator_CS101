#include <iostream>
#include <sstream>
using namespace std;
class Akinator
{
public:
    string characters[7][5]={{"SI No", "Name", "Department", "Gender", "State"}, {"1.", "Illa", "Aero", "Female", "Delhi"}, {"2.", "Vidit", "Meta", "Male", "UP"}, {"3.", "DK", "Aero", "Male", "UP"}, {"4.", "Nitya", "Aero", "Female", "Haryana"}, {"5.", "Bablu", "Aero", "Male", "Haryana"}, {"6.", "Shinjan", "Meta", "Male", "Delhi"}};
    string questions[4][3]={{"SI. No.", "Question", "YESCODE"}, {"1.", "Is the department of your character ", ""}, {"2.", "Is your character ", ""}, {"3.", "Is your character from ", "2"}};
    string code[4]={"", "", "2 1 ", "3 "};//notice the spaces given at the end of 3. first entry will be blank. in test code no children for department question
    int n;
    int index;//index is a variable which will point to the parent question. the parent question points to the children from code array
    Akinator()
    {
        n=7;
        index=3;
    }
    void responseYes(int i, int &n , string characters[][5], int blots[], string quality[])
    {
            for(int j=1;j<n;j++)
                {
                    if(characters[j][blots[i]+1]!=quality[i])
                    {
                        for(int k=j;k<n-1;k++)
                        {
                            for(int l=0;l<5;l++)
                                characters[k][l]=characters[k+1][l];
                        }
                        j--;
                        n--;
                    }
                }
    }
    void responseNo(int i, int n, string characters[][5], int blots[], string quality[])
    {
        for(int j=1;j<n;j++)
                {
                    if(characters[j][blots[i]+1]==quality[i])
                    {
                        for(int k=j;k<n-1;k++)
                        {
                            for(int l=0;l<5;l++)
                                characters[k][l]=characters[k+1][l];
                        }
                        j--;
                        n--;
                    }
                }
    }
    int getArray(string quality[], int frequency[], int blots[], int index, int n)
    {
        string sequence=code[index];//the sequence is in string. now we will extract each number from string and store it in pointer
        string pointer="";
        int l=0;//at the end of the function this will give the actual size of the three arrays
        for(int i=0;i<sequence.length();i++)//.length() function gives length of string analogous to size of array
        {
            if(sequence[i]==' ')//extracting number not digit
            {
                int num;
                istringstream(pointer) >> num;//converts valid string to integer. now num stores the position of attribute for which we will store different variations in quality along with the frequency
                for(int j=1;j<n;j++)
                {
                    int flag=0;//flag checks whether it has been repeated before
                    for(int k=0;k<l;k++)
                    {
                        if(quality[k]==characters[j][num+1])
                        {
                            flag=1;
                            break;
                        }
                    }
                    if(flag==0)//if not repeated
                    {
                        int c=0;//stores frequency
                        for(int a=j;a<n;a++)
                        {
                            if(characters[j][num+1]==characters[a][num+1])
                                c++;
                        }
                        quality[l]=characters[j][num+1];
                        frequency[l]=c;
                        blots[l]=num;//stores question tag
                        l++;//increase actual size of arrays
                        c=0;
                    }
                }
                pointer="";//reset
            }
            else
                pointer=pointer+sequence[i];//IF NOT A SPACE THEN ADD DIGIT TO MAKE NUMBER
        }
        return l;
    }
    void sortArray(string quality[], int frequency[], int blots[], int sizeArray)
    {
        for(int i=0;i<sizeArray-1;i++)
        {
            for(int j=i+1;j<sizeArray;j++)
            {
                if(frequency[i]>frequency[j])
                {
                    int temp1=frequency[i];
                    frequency[i]=frequency[j];
                    frequency[j]=temp1;
                    string temp2=quality[i];
                    quality[i]=quality[j];
                    quality[j]=temp2;
                    int temp3=blots[i];
                    blots[i]=blots[j];
                    blots[j]=temp3;
                }
            }
        }
    }
    string mainAkinator()
    {
        string quality[20];//a big drawback here. we do not know the size. it can be overcome with a function(i. e getting to know the exact size) but it will take up memory. do not think it is worth it. will discuss with maloo
        int frequency[20];//QUALITY stores the variations of an attribute and frequency stores the corresponding frequency of the variation and blots stores the question number to which variation of attribute is related
        int blots[20];
        int sizeArray=getArray(quality, frequency, blots, index, n);//sizeArray will get actual size
        sortArray(quality, frequency, blots, sizeArray);//sorts in descending
        for(int i=0;i<sizeArray;i++)
        {
            cout << questions[blots[i]][1]+quality[i]+"?" << endl;
            string response;
            cin >> response;
            if(response=="YES")
            {
                responseYes(i, n, characters, blots, quality);
                if(n==1)
                    return "No character";
                if(n==2)
                    return characters[1][1];
                istringstream(questions[blots[i]][2]) >> index;// c will store the new index from YESCODE
                return mainAkinator();
                }
            else
            {
                responseNo(i, n, characters, blots, quality);
                if(n==1)
                    return "No character";
                if(n==2)
                    return characters[1][1];
            }
        }
        return "No character";
    }
}obj;
int main()
{
    cout << "Akinator begins!!!" << endl;
    cout << obj.mainAkinator();
}
//commments
//1. A big challenge will be to transfer it from double dimension structure to text file structure. Even though double dimension code is working, the text version will look sophisticated and will be flexible
//2. Using tree search algorithm, very intricate designing will be required i.e. determining parents in the same hierarchy and their children. It has to be done carefully.
//3. simpleCpp should be more than enough.
//4. Everybody keep a copy of this. If anyone wants to write a comment and update it, do it in their version and upload it on the fb group.
