#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "EasyBMP.h"
#include "BinaryHeap.h"

char name[100];
int outNum = 1;

using namespace std;



void drawGraph (BMP & img, vector<int> & list)
{
    int count = 0;
    for (auto l : list) {
        double left = (count * (img.TellWidth() / list.size())) + 2.5;
        double right = left + 5;

        for (int j = 0; j < img.TellHeight(); ++j) {
            for (int i = 0; i < img.TellWidth(); ++i) {
                if ((j > img.TellHeight() - l) && (i >= left && i <= right)) {
                    img(i, j)->Red = 0;
                    img(i, j)->Green = 0;
                    img(i, j)->Blue = 0;
                }
            }
        }
        count++;
    }
}

void reDraw(BMP & img, int Red, int Green, int Blue, double left, int bound)
{
    double right = left + 5;

    for (int j = 0; j < img.TellHeight(); ++j) {
        for (int i = 0; i < img.TellWidth(); ++i) {
            if ((j > bound) && (i >= left && i <= right)) {

                img(i, j)->Red = Red;
                img(i, j)->Green = Green;
                img(i, j)->Blue = Blue;

            }
        }
    }
}

void update(BMP & img, int counter, int val, int val2, vector<int> & array, int bound, int color)
{

    int size = array.size();
    double left = (counter * (img.TellWidth() / size)) + 2.5;

    int idx1 = 0;
    int num = 0;

    for (vector<int>::iterator it = array.begin(); it != array.end(); ++it) {
        if (val == *it) {
            idx1 = num;
        }
        num++;
    }

    char buffer [50];

    if (outNum < 9)
        sprintf (buffer, "00");
    else if (outNum > 8 && outNum < 99)
        sprintf (buffer, "0");
    else if (outNum > 98)
        sprintf (buffer, "");

    double left2 = (idx1 * (img.TellWidth() / size)) + 2.5;

    //Set the column white
    reDraw(img, 255, 255, 255, left, 0); // height all

    //Set the first column red
    reDraw(img, color, 0, 0, left, img.TellHeight() - val2);


    if (outNum < 9)
        sprintf (buffer, "00");
    else if (outNum > 8 && outNum < 99)
        sprintf (buffer, "0");
    else if (outNum > 98)
        sprintf (buffer, "");
    sprintf(name, "C:\\Users\\Will\\Documents\\CS315\\Lab 11_2\\output_bmp\\board%s%d.bmp", buffer, outNum++);
    img.WriteToFile(name);

    reDraw(img, 255, 255, 255, left2, 0); // height all

    //Set the second column red
    reDraw(img, color, 0, 0, left2, img.TellHeight() - val);



    if (outNum < 9)
        sprintf (buffer, "00");
    else if (outNum > 8 && outNum < 99)
        sprintf (buffer, "0");
    else if (outNum > 98)
        sprintf (buffer, "");
    sprintf(name, "C:\\Users\\Will\\Documents\\CS315\\Lab 11_2\\output_bmp\\board%s%d.bmp", buffer, outNum++);
    img.WriteToFile(name);


    // SWAPPING

    //Set the column white
    reDraw(img, 255, 255, 255, left, 0); // height all

    //Set the first column red
    if (color != -1)
        reDraw(img, color, 0, 0, left, img.TellHeight() - val);

    reDraw(img, 255, 255, 255, left2, 0); // height all

    //Set the second column red
    if (color == -1)
        reDraw(img, 0, color, 0, left2, img.TellHeight() - val2);
    else
        reDraw(img, color, 0, 0, left2, img.TellHeight() - val2);


    if (outNum < 9)
        sprintf (buffer, "00");
    else if (outNum > 8 && outNum < 99)
        sprintf (buffer, "0");
    else if (outNum > 98)
        sprintf (buffer, "");
    sprintf(name, "C:\\Users\\Will\\Documents\\CS315\\Lab 11_2\\output_bmp\\board%s%d.bmp", buffer, outNum++);
    img.WriteToFile(name);

    //reDraw(img, 0, 255, 48, left, img.TellHeight() - val);
    array.at(counter) = val;
    array.at(idx1) = val2;

}


/* A utility function to print array of size n */
void printArray(int arr[], int n)
{
    for (int i=0; i<n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}


// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(int arr[], int n, int i, BMP & img, vector<int> & list, int & depth)
{
    int color = 255;
    int largest = i;  // Initialize largest as root
    int l = 2 * i + 1;  // left = 2*i + 1
    int r = 2 * i + 2;  // right = 2*i + 2

    //cout << "\nD: " << depth << endl;

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        depth++;

        color = color/((depth+1)) * 2;
        update(img, i, arr[i], arr[largest], list, n, color);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest, img, list, depth);

    }
}


// main function to do heap sort
void heapSort(int arr[], int n, BMP & img, vector<int> & list) {

    int deptth = 0;
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, img, list, deptth);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        deptth = 0;
        // Move current root to end
        //update(img, i, arr[i], arr[0], list, n, -1);
        swap(arr[0], arr[i]);

        update(img, i, arr[0], arr[i], list, n, -1);

        // call max heapify on the reduced heap
        heapify(arr, i, 0, img, list, deptth);

    }


}


void startRandImage(BMP & img, int k, int n) {

    vector<int> list;

    for (int i = k; i <= n; ++i)
        list.push_back(i * 3);

    random_device rd;
    mt19937 g(rd());

    shuffle(list.begin(), list.end(), g);

    drawGraph(img, list);

    sprintf(name, "C:\\Users\\Will\\Documents\\CS315\\Lab 11_2\\output_bmp\\board000.bmp");
    img.WriteToFile(name);

    int muah = 0;
    int arr[list.size()];
    for (vector<int>::iterator it = list.begin(); it != list.end(); ++it)
    {
        arr[muah] = *it;
        muah++;
    }

    int n2 = sizeof(arr)/ sizeof(arr[0]);

    heapSort(arr, n2, img, list);
}


int main() {

    int num = -1, min = -1;

    cout << "Enter positive integer number of values to sort: ";
    cin >> num;

    cout << "\nEnter lowest positive integer value";
    cin >> min;

    BMP in;
    int width = ((num) * 10 + ((num) * 5));
    int height = num * 3;
    in.SetSize(width, height);
    in.SetBitDepth(8);


    startRandImage(in, min, num);

    return 0;
}