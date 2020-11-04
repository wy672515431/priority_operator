#include<iostream>
#include<cstring>
#include<stdio.h>
#include<ctype.h>
#include<algorithm>
#include<string>
#include<cmath>
#include<fstream>
#include<stack>
using namespace std;
const int maxn = 1024;
int top = 0;
string s;
char stack_t[maxn];
/* + * ( ) i #
+
*
(    
)
i 
#
1代表优先级大于,-1代表优先级小于,0代表优先级等于,2代表不能比较.*/
int priority_matrix[6][6] = {{1,-1,-1,1,-1,1},
                             {1,1,-1,1,-1,1},
                             {-1,-1,-1,0,-1,2},
                             {1,1,2,1,2,1},
                             {1,1,2,1,2,1},
                             {-1,-1,-1,2,-1,2}};
char terminal_operators[6]={'+','*','(',')','i','#'};
char non_terminal_operators[3]={'E','T','F'};
/*返回终结符的位置，以便获得终结符之间的优先关系，若不是终结符则返回-1 */
int check(char t){
    for(int i=0;i<6;i++){
        if( t == terminal_operators[i])
            return i;
    }
    return -1;
}
int check1(char t){
    for(int i=0;i<3;i++){
        if( t == non_terminal_operators[i])
            return i;
    }
    return -1;
}
void push(char t){
    stack_t[top++]=t;
}
char pop(){
    char tem =stack_t[top];
    top--;
    return tem;
}
int main(int argc,char **argv)
{
    /*读取一行字符串*/
    char c;
    FILE*fp;
    fp =fopen(argv[1],"r");
    //标记读入符号的位置
    int flag=0;
    while(true){
        c = fgetc(fp);
        if(c == '\r'|| c=='\n')
            break;
        s+=c;
    }
    s+='#';
    push('#');
    c = s[flag];
    //最终停止的条件，栈里面只有#和开始符,待读符号串读到右#号.
    while(!(top==2&&c=='#'&&stack_t[top-1]=='E')){
        //读入的符号无法识别.
        if(check(c)==-1&&check1(c)==-1){
            cout<<"E"<<endl;
            return 0;
        }
        //读入符号为非终结符,直接入栈,读入符号的位置+1
        if(check(c)==-1){
            if(check(stack_t[top-1])==-1){
                cout<<"E"<<endl;
                return 0;
            }
            cout<<"I"<<c<<endl;
            push(c);
            flag++;
            c=s[flag];
        }
        //读入的符号为终结符
        else{
            int right_terminal_operators = check(c);
            int left_terminal_operators;
            int flag1;
            //判断栈顶是不是终结符，如果不是,那么栈顶减1的元素一定是终结符。
            if(check(stack_t[top-1])!=-1){
                left_terminal_operators = check(stack_t[top-1]);
                flag1 = top-1;
            }
            else if (check(stack_t[top-1])==-1){
                if(check(stack_t[top-2])==-1){
                    /*error */
                    return 0;
                }
                else {
                    left_terminal_operators = check(stack_t[top-2]);
                    flag1 = top-2;
                }
            }
            // 判断栈顶终结符或者靠近栈顶的终结符与要读入的终结符的优先级,如果小于直接递进
            if(priority_matrix[left_terminal_operators][right_terminal_operators]==-1
                ||priority_matrix[left_terminal_operators][right_terminal_operators]==0){
                    cout<<"I"<<c<<endl;
                    push(c);
                    flag++;
                    c=s[flag];
            }
            //大于进行规约
            else if (priority_matrix[left_terminal_operators][right_terminal_operators]==1){
                if(stack_t[flag1]=='i'){
                    pop();
                    push('E');
                    cout<<"R"<<endl;
                }
                else if(stack_t[flag1]=='+'){
                    if(flag1-1<0||flag1+1>=top){
                        cout<<"RE"<<endl;
                        return 0;
                    }
                    else{
                        pop();
                        pop();
                        pop();
                        push('E');
                        cout<<"R"<<endl;
                    }
                }
                else if(stack_t[flag1]=='*'){
                    if(flag1-1<0 || flag1+1>=top){
                        cout<<"RE"<<endl;
                        return 0;
                    }
                    else{
                        pop();
                        pop();
                        pop();
                        push('E');
                        cout<<"R"<<endl;
                    }
                }
                else if(stack_t[flag1]==')'){
                    if(flag1-1<0||flag1+1>=top){
                        cout<<"RE"<<endl;
                        return 0;
                    }
                    else{
                        pop();
                        pop();
                        pop();
                        push('E');
                        cout<<"R"<<endl;
                    }
                }
            }
            //无法比较优先级
            else if(priority_matrix[left_terminal_operators][right_terminal_operators]==2){
                cout<<"E"<<endl;
                return 0;
            }
        }
    }
    fclose(fp);
}