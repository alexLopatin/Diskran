#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
    int indices[] = {0, 0, 0, 0};
    cin >> indices[3];
    int* arr = new int[indices[3]];
    for( int i = 0; i < indices[3]; i++) {
    	cin >> arr[i];
    	indices[arr[i]-1]++;
    }
    indices[2] = indices[1] + indices[0];
    indices[1] = indices[0];
    indices[0] = 0;
    int res = 0;
    for( int i = 0; i < indices[3]; i++) {
    	if(i < indices[arr[i]-1] || i >= indices[arr[i]]) {
    		int lastNotSorted = -1;
    		for ( int j = indices[arr[i]-1]; j < indices[arr[i]]; j++ ) {
    			if(j < indices[arr[j]-1] || j >= indices[arr[j]]) {
    				lastNotSorted = j;
    			}
    			if(i >= indices[arr[j]-1] && i < indices[arr[j]]) {
    				int tmp = arr[i];
    				arr[i] = arr[j];
    				arr[j] = tmp;
    				res++;
    				break;
    			}
    		}
    		if(i < indices[arr[i]-1] || i >= indices[arr[i]]) {
    			int tmp = arr[i];
	    		arr[i] = arr[lastNotSorted];
	    		arr[lastNotSorted] = tmp;
	    		res++;
    		}
    	}
    }
    cout << res << endl;
    delete[] arr;
}