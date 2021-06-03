#include <stdio.h>
#include <string.h>
typedef char *string;

string letters[8] = {"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

int getInputSize(int input){
    int counter = 0;
    while(input>1){
        input/=10;
        counter++;
    }
    return counter;
}

string* n2c(int number) {
    switch (number) {
    case 2: return "abc";
    case 3: return "def";
    
    default: return "";
        break;
    }
}

string* predict(int input){
    int size = getInputSize(input);
    string* ans = malloc(size*size*size*sizeof(string));
    int aux[size];
    for(int i=size-1; i>=0; i--){
        aux[i] = input%10;
        input/=10;
    }
    // for(int i = 0; i<size; i++)
    //     printf("%s ",letters[aux[i]-2]);
    // puts("");



    return ans;
}