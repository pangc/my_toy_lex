#include <iostream>
#include "lex.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;
enum StateType{
    STATE_START,
    STATE_NUM,
    STATE_ID,
    STATE_NE,
    STATE_GE,
    STATE_LE,
    STATE_EQ,
    STATE_GT,
    STATE_LT,
    STATE_STR,
    STATE_OP,
    STATE_DONE,
    STATE_ERROR
};
enum TokenType{
    TOKEN_NUM,
    TOKEN_ID,
    TOKEN_NE,
    TOKEN_GE,
    TOKEN_LE,
    TOKEN_EQ,
    TOKEN_GT,
    TOKEN_LT,
    TOKEN_STR,
    TOKEN_OP
};
typedef struct Token{
    string data;
    TokenType type;
}Token;
vector<Token> vecToken;

void getToken(string str,vector<Token> &vecToken){
    string str_tmp;
    StateType currState = STATE_START;
    TokenType tokenType;
    Token t;
    int pos = 0;
    int size = str.length();
    char c;
    while(pos++<size){
        c=str.at(pos-1);
        switch(currState){
            case STATE_START:
                if(ISDIGIT(c))
                    currState = STATE_NUM;
                else if(ISLETTER(c))
                    currState = STATE_ID;
                else if(ISOP(c))
                    currState = STATE_OP;
                else if(ISEQ(c))
                    currState = STATE_EQ;
                else if(ISGT(c))
                    currState = STATE_GT;
                else if(ISLT(c))
                    currState = STATE_LT;
                else if(ISDQ(c))
                    currState = STATE_STR;
                else if(ISNE(c))
                    currState = STATE_NE;
                else if(c==' '||c=='\t')
                    ;
                else
                    currState = STATE_DONE;
                break;
            case STATE_NUM:
                if(ISDIGIT(c))
                    currState = STATE_NUM;
                else{
                    currState = STATE_DONE;
                    tokenType = TOKEN_NUM;
                }
                break;
            case STATE_ID:
                if(ISLETTER(c)||ISDIGIT(c))
                    currState = STATE_ID;
                else{
                    currState = STATE_DONE;
                    tokenType = TOKEN_ID;
                }
                break;
            case STATE_EQ:
                currState = STATE_DONE;
                tokenType = TOKEN_EQ;
            case STATE_OP:
                currState = STATE_DONE;
                tokenType = TOKEN_OP;
                break;
            case STATE_NE:
                if(ISEQ(c)){
                    currState = STATE_DONE;
                    tokenType = TOKEN_EQ;
                }
                else
                    currState = STATE_ERROR;
                break;
            case STATE_GT:
                if(ISEQ(c))
                    currState = STATE_GE;
                else{
                    currState = STATE_DONE;
                    tokenType = TOKEN_GT;
                }
                break;
            case STATE_GE:
                currState = STATE_DONE;
                tokenType = TOKEN_GE;
                break;
            case STATE_LT:
                if(ISEQ(c))
                    currState = STATE_LE;
                else{
                    currState = STATE_DONE;
                    tokenType = TOKEN_LT;
                }
                break;
            case STATE_STR:
                if(ISDQ(c)){
                    currState = STATE_DONE;
                    tokenType = TOKEN_STR;
                }
                else
                    currState = STATE_STR;
                break;
        }
        if(currState  == STATE_DONE){
            t.data = str_tmp;
            cout << str_tmp << "\n";
            t.type = tokenType;
            cout << tokenType << "\n";
            vecToken.push_back(t);
            pos = pos -1;
            currState = STATE_START;
            str_tmp="";
        }
        else
            str_tmp += c;
    }

}


int main(){
    int line=0;
    string str;
    ifstream FileName("test.lex",ios::in);
    while(getline(FileName,str)){
        cout << str <<"\n";
        ++line;
        getToken(str,vecToken);
//        vector <Token> ::iterator   iter=vecToken.begin();
//        for(;iter!=vecToken.end();iter++)
//            cout << iter->data  << iter ->type;
    }
    return 0;
}
