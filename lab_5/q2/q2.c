#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
int partition(int* arr,int left,int right){
    int pivot=arr[right];
    int i=left;
    for(int j=left;j<right;j++){
        if(arr[j]<pivot){
            swap(&arr[i],&arr[j]);
            i++;
        }
    }
    swap(&arr[i],&arr[right]);
    return i;
}
int quickSelect(int* arr,int left,int right,int k){
    if(left==right)return arr[left];

    int part=partition(arr,left,right);
    if(part==k){
        return arr[part];
    }else if(k<part) return quickSelect(arr,left,part-1,k);
    else return quickSelect(arr,part+1,right,k);
}

int main(){
    int n;
    printf("Enter the value of n: ");
    scanf("%d",&n);
    int* arr=(int*)malloc(n*sizeof(int));
    
    for(int i=0;i<n;i++){
        printf("Enter the element: ");
        scanf("%d",&arr[i]);
    }
    int k;
    printf("Enter the value of k: ");
    scanf("%d",&k);
    while(k<0 || k>n){
        printf("Invalid k, enter again: ");
        scanf("%d",&k);
    }


    int min=quickSelect(arr,0,n-1,k-1);
    printf("Element: %d",min);
    return 0;

}