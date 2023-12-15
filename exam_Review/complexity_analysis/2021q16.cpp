using namespace std;

//From Salma's learningcpp.org

// For each code snippet, specify the worst case complexity using the Big-O notation.



int main() {

    int n; 

    //Question 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    for (int i = 0; i < n; i++) {
        for (int j = 0; j * j < n; j++) {
            // some code with o(1)
        }
    }

    /*
    
        Outer loop: O(n)
        Inner loop: O(j^2 < n)

        Total: (j^2 < n) --> (j < sqrt(n)). Inner loop is bounded by sqrt(n).
        So in total, the worst case time complexity should be n times * sqrt(n) times,
        yielding pow(n, 3/2).

        $$$$$$$$$ CORRECT! $$$$$$$$$$
    
    */

   //Question 2

   for (int i = 0; i < n; i++) {
        for (int j = 0; j * j < 1000000; j++) {
            // some code with O(1)
        }  
    }

    /*
    
        Outer loop: O(n)
        Inner loop: I believe it's bounded by the square root of a constant, so O(1)

        Total: O(n) times

        $$$ CORRECT $$$
    
    */

   //Question 3

   for(int i = 1; i < n ; i = i*2){

        for(int j = 0; j < n; j++)  {
            // some code with O(1)
        }
    }

    /*
    
        Outer loop: Not quite O(n), i is growing non-linearly. We'll say log(n).
        Inner loop: O(n)
        Total: nlog(n)

        $$$ CORRECT $$$
    
    */
   

}