#include <stdio.h>

int fibTab(int n){  //using memorization
    int mem[1000]={0};
    if(n<=1)return n;

    if(mem[n]!=0)return mem[n];
    return mem[n]=fibTab(n-1)+fibTab(n-2);
}

int fibo(int n){
    if(n<=1)return n;
    int prev2=0,prev1=1,curr;
    for(int i=2;i<=n;i++){
        curr=prev2+prev1;
        prev2=prev1;
        prev1=curr;
    }
    return curr;
}
int main(){
    
    int n;
    printf("Enter the value of n: ");
    scanf("%d",&n);
    printf("Fibo: %d",fibo(n));
    return 0;

}