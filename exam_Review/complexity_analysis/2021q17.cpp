using namespace std;

// Two students were asked to write a recursive 
// function that given a positive integer n, computes 2^n.

    // Amy wrote the following function:
    int Amy (int n) {

        if (n == 0) {
            return 1;
        } else {
            return Amy(n - 1) + Amy(n - 1);
        }
    }

    //John wrote the following fn:

    int John(int n) {

        if (n == 0) {
            return 1;
        } else {
            return (2 * John(n - 1));
        }
    }

    //Q1: Is Amy's function correct? (Correct time complexity?)

    /*

       Q1&Q2 computed on paper. Yes & Yes.
       Recurrance Expansion works pretty well for  Q3&Q4.
       O(2^n) and O(n) for Q3&Q4 
    
    */

