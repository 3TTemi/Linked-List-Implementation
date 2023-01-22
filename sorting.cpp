#include "listnode.h"
#include "vector.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
This function is given a list of element and divides the elemnts into three sublists
The three sublists are less, greater than, and equal and are decided by a pivot number which is chosen to be the first elemt nfo the lsit
Iterates while the valeu is not null pointer and checks if the if data is less, equal to, or more than pivot
From there it saves the original lsit, Adds current next value to be less,more,or equal, Puts less,more,or equal at the start of the lsit by equlizing it to crurent and resets the list back to the original
This effectively saves the current list while incrementing to either the less,equal to, or greater
 */

void partition(ListNode*& front, ListNode*& less, ListNode*& equal,ListNode*& greater, int& pivot)
{

   ListNode* current = front;
   ListNode* temp;
   less = nullptr;
   equal = nullptr;
   greater = nullptr;

   if (front != nullptr)
   {
       pivot = front->data;
   }

   while (current != nullptr)
   {
        if(current->data < pivot)
        {
            // save rest of the original list
            temp = current->next;
            //add current less to to currents next
            current->next = less;
            // put less back at the start of t
            less = current;
            // reset list back to rest of original
            current = temp;

        }
        else if(current->data > pivot)
        {
            temp = current->next;
            current->next = greater;
            greater = current;
            current = temp;
        }
        else if(current->data == pivot)
        {
            temp = current->next;
            current->next = equal;
            equal = current;
            current = temp;
        }

   }

}


/*
This function puts together three lists into one list in order of less -> equal -> greater
Checks if less list is empty, if it is then it sets the front to equal instead, or if not empty then it iterates and sets less last node to point to equal
Checks if equal list is empty, if it is and front is nullptr then front is set to greaater, if front is not null pointer then the next value of less is set to greater,
if the list is not empty then it repeats iterating and sets the  last pointer of equal to greater

*/
void concatenate(ListNode*& front, ListNode*& less, ListNode*& equal,ListNode*& greater)
{

    if (less != nullptr)
    {
        front = less;
        while(less->next != nullptr)
        {
            less = less->next;
        }
        less->next = equal;
    }
    else
    {
        front = equal;
    }


    if(equal != nullptr)
    {
        while(equal->next != nullptr)
        {
            equal = equal->next;
        }

        equal->next = greater;
    }
    else if(front == nullptr)
    {
        front = greater;
    }
    else
    {
        less->next = greater;

    }

}

/*
 * QuickSort function sorts all the elemtn of the provided list in a recursive manner
  The base case is a list with 0 or 1 elements becasue it is already sorted, in which case it just returns to stop the function from conitnuing
  A call is made to parition the list into three less, equal, and greater categories by the pivot
  The recursive case sorts the two unsorted components of less, and greater
  Concatenate is called at the end to put the sorted results of less, equal, and greater to, together into the final front list
 */
void quickSort(ListNode*& front) {
    ListNode* less;
    ListNode* equal;
    ListNode* greater;
    int pivot;


    if(front == nullptr || front->next == nullptr)
    {
        return;
    }

    partition(front, less, equal,greater, pivot);

    quickSort(less);
    quickSort(greater);

    concatenate(front, less, equal, greater);

}


void printList(ListNode* front) {
   cout << "{";
   for (ListNode *cur = front; cur != nullptr; cur = cur->next) {
       cout << cur->data;
       if (cur->next != nullptr){
           cout << ", ";
       }
   }
   cout << "}" << endl;
}


void deallocateList(ListNode* front) {
    while(front != nullptr)
    {
        ListNode* next = front-> next;
        delete front;
        front = next;
    }
}


ListNode* createList(Vector<int> values){
    if(values.size() == 0)
    {
        return nullptr;
    }

    ListNode* front = new ListNode(values[0],nullptr);
    ListNode* current = front;

    for(int i = 1; i < values.size(); i++)
    {
        current->next = new ListNode;
        current->next->data = values[i];
        current = current->next;
    }
    current->next = nullptr;


    return front;
}


bool areEquivalent(ListNode* front, Vector<int> v){
    ListNode* current = front;
    for(int i = 0; i < v.size(); i++)
    {
        if (current == nullptr)
        {
            return false;
        }
        if(current->data != v[i])
        {
            return false;
        }
        current = current->next;
    }
    if (current != nullptr)
    {
        return false;
    }
    return true;
}


TEST("Testing partition helper function")
{
      Vector<int> values = {4, 6, 2,4,4,5,8,1,3,5,};
      ListNode* list = createList(values);
      ListNode* left;
      ListNode* right;
      ListNode* equal;
      int pivot;
      partition(list, left, equal, right, pivot);

      EXPECT(areEquivalent(left, {3,1,2}));
      EXPECT(areEquivalent(right, {5,8,5,6}));
      EXPECT(areEquivalent(equal, {4,4,4}));

      deallocateList(left);
      deallocateList(right);
      deallocateList(equal);

      values = {9,9,9};
      list = createList(values);
      partition(list, left, equal, right, pivot);

      EXPECT(areEquivalent(left, {}));
      EXPECT(areEquivalent(right, {}));
      EXPECT(areEquivalent(equal, {9,9,9}));

      deallocateList(left);
      deallocateList(right);
      deallocateList(equal);

}

TEST("Testing the concatenate helper function")
{
    ListNode* front;
    ListNode* less = createList({3,1,2});
    ListNode* more = createList({5,8,5,6});
    ListNode* equal = createList({4,4,4});
    concatenate(front, less, equal, more);
    EXPECT(areEquivalent(front, {3,1,2,4,4,4,5,8,5,6}));
    deallocateList(front);

    less = createList({});
    more = createList({10,20,30,40});
    equal = createList({8,8});
    concatenate(front, less, equal, more);
        EXPECT(areEquivalent(front, {8,8,10,20,30,40}));
    deallocateList(front);

    less = createList({});
    more = createList({});
    equal = createList({});
    concatenate(front, less, equal, more);
    EXPECT(areEquivalent(front, {}));
    deallocateList(front);

    less = createList({});
    more = createList({5,9,7,8});
    equal = createList({});
    concatenate(front, less, equal, more);
    EXPECT(areEquivalent(front, {5,9,7,8}));
    deallocateList(front);

    less = createList({});
    more = createList({});
    equal = createList({7,7,7});
    concatenate(front, less, equal, more);
    EXPECT(areEquivalent(front, {7,7,7}));
    deallocateList(front);

    less = createList({1,2,3});
    more = createList({});
    equal = createList({9});
    concatenate(front, less, equal, more);
    EXPECT(areEquivalent(front, {1,2,3,9}));
    deallocateList(front);

    less = createList({1,2,3});
    more = createList({5,6,7});
    equal = createList({});
    concatenate(front, less, equal, more);
    EXPECT(areEquivalent(front, {1,2,3,5,6,7}));
    deallocateList(front);

}


TEST("Testing the quickSort function overall")
{
    ListNode* testList = createList({14,12,16,13,11,15});
    quickSort(testList);
    EXPECT(areEquivalent(testList, {11,12,13,14,15,16}));
    deallocateList(testList);

    testList = createList({});
    quickSort(testList);
    EXPECT(areEquivalent(testList, {}));
    deallocateList(testList);

    testList = createList({20,22,26,31,35,39});
    quickSort(testList);
    EXPECT(areEquivalent(testList, {20,22,26,31,35,39}));
    deallocateList(testList);

    testList = createList({100,90,80,70,60,50,40,30,20,10});
    quickSort(testList);
    EXPECT(areEquivalent(testList, {10,20,30,40,50,60,70,80,90,100}));
    deallocateList(testList);

    testList = createList({-8,22,31,14,-11,-22,9});
    quickSort(testList);
    EXPECT(areEquivalent(testList, {-22,-11,-8,9,14,22,31}));
    deallocateList(testList);

    testList = createList({70,10,31,34,30,51,85,42,83,4,71,73,41,95,16,49,57,14,69,6,52,82,84,65,40,3,74,29,17,75,1,35,28,98,38,68,100,18,44,50,78,27,67,2,33,81,13,94,36,26});
    quickSort(testList);
    EXPECT(areEquivalent(testList, {1,2,3,4,6,10,13,14,16,17,18,26,27,28,29,30,31,33,34,35,36,38,40,41,42,44,49,50,51,52,57,65,67,68,69,70,71,73,74,75,78,81,82,83,84,85,94,95,98,100}));
    deallocateList(testList);

}

TEST("Time trials for QuickSort")
{
    int startSize = 600;
    int n = startSize;

    for(int c = 0; c < 4 ;  c++) {
        ListNode* list = nullptr;

        for (int i = n-1; i >= 0; i--) {
            list = new ListNode(randomInteger(-10000, 10000), list);
        }

        TIME_OPERATION(n, quickSort(list));
        deallocateList(list);

        n*= 2;
    }

    for(int c = 0; c < 4 ;  c++) {
        ListNode* list = nullptr;

        for (int i = n-1; i >= 0; i--) {
            list = new ListNode(i, list);
        }

        TIME_OPERATION(n, quickSort(list));
        deallocateList(list);

        n*= 2;
    }


}

TEST("This is a skeleton to demonstrate an end-to-end student test."){
    Vector<int> values = {1, 2, 3, 4};
    ListNode* list = createList(values);

    quickSort(list);

    values.sort();

    EXPECT(areEquivalent(list, values));

    deallocateList(list);
}

TEST("This tests some of the testing helper functions you are recommended to implement."){
    ListNode* testList = nullptr;
    testList = new ListNode(3, testList);
    testList = new ListNode(2, testList);
    testList = new ListNode(1, testList);

    EXPECT(areEquivalent(testList, {1, 2, 3}));
    EXPECT(!areEquivalent(testList, {1, 2}));
    EXPECT(!areEquivalent(testList, {1, 2, 3, 4}));
    EXPECT(!areEquivalent(testList, {1, 3, 2}));

    ListNode* studentList = createList({1, 2, 3, 4});
    printList(studentList);
    ListNode* cur = studentList;
    for (int i = 1; i <= 4; i++){
        EXPECT(cur != nullptr);
        EXPECT_EQUAL(cur->data, i);
        cur = cur->next;
    }

    deallocateList(studentList);
    deallocateList(testList);
}


TEST("Time linked list quicksort vs vector quicksort") {
    int startSize = 50000;

    for(int n = startSize; n < 10*startSize; n *= 2) {
        Vector<int> v(n);
        ListNode* list = nullptr;

        for (int i = n-1; i >= 0; i--) {
            v[i] = randomInteger(-10000, 10000);
            list = new ListNode(v[i], list);
        }

     
        TIME_OPERATION(n, quickSort(list));
        TIME_OPERATION(n, v.sort());        

        deallocateList(list);
    }
}

