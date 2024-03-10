#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int fibonacci_search(int arr[], int n, int key) {
    int fib2 = 0;
    int fib1 = 1;
    int fib = fib2 + fib1;

    // Tìm số Fibonacci nhỏ hơn hoặc bằng n
    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }

    int offset = -1; // Lưu vị trí của mảng
    while (fib > 1) {
        int i = (offset + fib2 < n - 1) ? offset + fib2 : n - 1;

        if (arr[i] == key)
            return i; // Trả về vị trí nếu key được tìm thấy

        // Di chuyển về phía trái trong dãy Fibonacci
        if (arr[i] < key) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        }

        // Di chuyển về phía phải trong dãy Fibonacci
        else {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }
    }

    // Kiểm tra phần tử cuối cùng
    if (fib1 && arr[offset + 1] == key)
        return offset + 1;

    return -1; // Key không được tìm thấy
}

int interpolation_search(int arr[], int n, int key) {
    int left = 0;
    int right = n - 1;

    while (left <= right && key >= arr[left] && key <= arr[right]) {
        // Calculate the position using interpolation formula
        int pos = left + ((double)(right - left) / (arr[right] - arr[left])) * (key - arr[left]);

        // If key is found at calculated position
        if (arr[pos] == key)
            return pos;

        // If key is larger, ignore the left half
        if (arr[pos] < key)
            left = pos + 1;

        // If key is smaller, ignore the right half
        else
            right = pos - 1;
    }

    return -1; // Key not found
}
int ternary_search(int arr[], int left, int right, int key) {
    if (right >= left) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        // Kiểm tra xem key có nằm ở các vị trí mid1, mid2 không
        if (arr[mid1] == key)
            return mid1;
        if (arr[mid2] == key)
            return mid2;

        // Nếu key nhỏ hơn phần tử ở vị trí mid1, tiếp tục tìm kiếm trong phần đầu tiên
        if (key < arr[mid1])
            return ternary_search(arr, left, mid1 - 1, key);

        // Nếu key lớn hơn phần tử ở vị trí mid2, tiếp tục tìm kiếm trong phần cuối cùng
        else if (key > arr[mid2])
            return ternary_search(arr, mid2 + 1, right, key);

        // Nếu key nằm giữa mid1 và mid2, tiếp tục tìm kiếm trong phần giữa
        else
            return ternary_search(arr, mid1 + 1, mid2 - 1, key);
    }
    // Nếu không tìm thấy key trong mảng, trả về -1
    return -1;
}

int binary_search(int arr[], int left, int right, int key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Kiểm tra xem key có nằm ở giữa mảng không
        if (arr[mid] == key)
            return mid;

        // Nếu key lớn hơn phần tử ở vị trí mid, bỏ qua nửa trái của mảng
        if (arr[mid] < key)
            left = mid + 1;

        // Ngược lại, bỏ qua nửa phải của mảng
        else
            right = mid - 1;
    }

    // Nếu không tìm thấy key trong mảng, trả về -1
    return -1;
}

int linear_search(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i; // return index if key is found
        }
    }
    return -1; // return -1 if key is not found
}

void bbs(int a[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(a[j]>a[j+1])
            {
                int temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    int a[n];
    int b[n];
    srand(time(0));
    for(int i=0;i<n;i++)
    {
        a[i]=rand()%n;
    }
    // for(int i=0;i<n;i++)
    // {
    //     printf("%d ",a[i]);
    // }
    //printf("\n");
    for(int i=0;i<n;i++)
    {
        b[i]=a[i];
    }
    bbs(b,n);
    // for(int i=0;i<n;i++)
    // {
    //     printf("%d ",b[i]);
    // }
    //printf("\n");

    clock_t begin1 = clock(); //ghi lại thời gian đầu
    linear_search(a,n,500);
    //printf("%d ",linear_search(a,n,5));
    clock_t end1 = clock(); //ghi lại thời gian lúc sau
    printf("Time run linear_search : %f s\n",(end1 - begin1) / CLOCKS_PER_SEC);

    clock_t begin2 = clock(); //ghi lại thời gian đầu
    binary_search(b,0,n/2,5);
    //printf("%d ",binary_search(b,0,n/2,5));
    clock_t end2 = clock(); //ghi lại thời gian lúc sau
    printf("Time run binary_search : %f s\n",(end2 - begin2) / CLOCKS_PER_SEC);

    clock_t begin3 = clock(); //ghi lại thời gian đầu
    interpolation_search(b,n,5);
    //printf("%d ",interpolation_search(b,n,5));
    clock_t end3 = clock(); //ghi lại thời gian lúc sau
    printf("Time run interpolation_search : %f s\n",(end3 - begin3) / CLOCKS_PER_SEC);

    clock_t begin4 = clock(); //ghi lại thời gian đầu
    ternary_search(b,0,n/2,5);
    //printf("%d ",ternary_search(b,0,n/2,5));
    clock_t end4 = clock(); //ghi lại thời gian lúc sau
    printf("Time run ternary_search : %f s\n",(end4 - begin4) / CLOCKS_PER_SEC);

    clock_t begin5 = clock(); //ghi lại thời gian đầu
    fibonacci_search(b,n,5);
    //printf("%d ",fibonacci_search(b,n,5));
    clock_t end5 = clock(); //ghi lại thời gian lúc sau
    printf("Time run fibonacci_search : %f s\n",(end5 - begin5) / CLOCKS_PER_SEC);
}
