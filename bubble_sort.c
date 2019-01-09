#include<stdio.h>
void sort(int *a){
    int i, j, temp;
    for(i = 0; i < 5; i++){
        for(j = 0;j < 5 - i - 1; j++){
            if(a[j]>a[j+1]){
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
    for(i = 0; i < 5; i++)
        printf("%d ",a[i]);
    putchar('\n');
}

int main(){
    int a[5] = {0}, i;
    for(i = 0; i < 5; i++){
        scanf("%d",&a[i]);
    }
    sort(a);
    return 0;
}
