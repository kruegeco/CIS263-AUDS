///Number of allowed character for dev reference (line below)
//1234567890123456789012345678901234567890123456789012345678901234567890
/***********************************************************************
* HOMEWORK 2-1; CIS263-AUDS "Almost Useless Data Structure"
* CIS 263 MWF 1200-1250, Winter 2017
* Professor Woodring, Ira
* Partners: NONE
* @author Krueger, Cody
* @version v1.0 03FEB2017 19:45
*
* Description: This is the full class for a generic data structure.  It
*  functions as a dynamic array that handles its own memory allocation.
*  It is fully defined in the header file because it uses generics.
*
* References: 
*  note - my previous cpp class text was learncpp.com
*  http://www.learncpp.com/cpp-tutorial/133-template-classes/
*  http://www.learncpp.com/cpp-tutorial/1-10a-header-guards/
*  http://www.cplusplus.com/reference/cstdlib/rand/
*
*  for generic reference
*  for header guards reference
*  for random use
* TODO check on conventions for constructors from eclipse
***********************************************************************/

// Header Guards FIXME: is this an issue?  having comments outside header guards?
#ifndef __AUDS__
#define __AUDS__

// Includes
#include <iostream>
#include <stdio.h>  //Used for rand 
#include <stdlib.h> //Used for rand, srand
#include <time.h>   //Used for rand seed 
#include <string>

// Generic
template <typename T>

// Class begins (full definition)
class AUDS {
    
    // Private Section
    private:

        // Instance Variables
        /** TODO add m_ prefix for member variables */
        /** max number of elements currently allowed in AUDS  */ 
        int maxE; 
        /** number of elements in AUDS  */ 
        int numE;
        /** current position of last element in AUDS (1 element less than
         * the number of elements) */ 
        int curLoc;
        /** pointer representing the array that points to the data */
        T* data;

        /****************************************************************
         * This helper method is used to automatically expand and handle 
         *  memory management of the AUDS after a new max has been given 
         *  to the data structure.  
         *  TODO May want to make this method private. 
         *  TODO-refactor could make this use copy constructor
         ***************************************************************/
        void setSize(){
            T* reSized = new T[maxE];
            
            //Copy elements into new empty array
            for(int i=0; i<curLoc; i++) {
                reSized[i] = data[i];
            }

            delete[] data;

            data = reSized;
        }

    // Public Section
    public:
       
        /****************************************************************
         * This is the std, dev defined constructor for AUDS.  
         *  It takes no parameters.
         ***************************************************************/
        AUDS() {
            maxE = 100;
            numE = 0; 
            curLoc = 0;
            //Declare array at beginning size
            data = new T[maxE];
            //Initialize random seed
            srand (time(NULL));
        }

        /****************************************************************
         * This is the std, dev defined copy constructor for AUDS.  
         * 
         * @param: const AUDS& other - reference to another AUDS object. 
         *  note: as a const, other is not intended to be altered
         ***************************************************************/
        AUDS(const AUDS& other) {
            //Copy the values of the array that can be duplicated by value
            maxE = other.maxE;
            numE = other.numE;
            curLoc = other.curLoc;
            //Declare a new array space
            data = new T[maxE];
            //Copy elements into new empty array
            for(int i=0; i<curLoc; i++) {
                data[i] = other.data[i];
            }
        }

        /****************************************************************
         * This is the std, dev defined copy operator for AUDS.  
         * 
         * @param: const AUDS& other - reference to another AUDS object.
         *  note: as a const, other is not intended to be altered
         * @return: &AUDS - reference to AUDS object.
         ***************************************************************/
        AUDS& operator=(AUDS other) {
            //Swap variables in the object copied (via the parameter call)
            // to object operated on (in a=b, b).
            std::swap(maxE, other.maxE);
            std::swap(numE, other.numE);
            std::swap(curLoc, other.curLoc);
            std::swap(data, other.data);

            return *this;
        }

        /****************************************************************
         * This is the std, dev-defined destructor for AUDS.  
         ***************************************************************/
        ~AUDS() {
            delete[] data;
        }

        /****************************************************************
         * This method returns the current number of objects we are
         *  holding. 
         * @return: int - number of elements held.
         ***************************************************************/
        int size(){
            return this->numE;
        }

        /****************************************************************
         * This method returns the current maximum of objects the AUDS 
         *  can hold. TODO May want to make this method private. 
         * @return: int - current max number of elements.
         ***************************************************************/
        int max(){
            return this->maxE;
        }


        /****************************************************************
         * This method adds a passed data element to an AUDS.  It
         *  automatically handles resizing of the data structure. 
         *   
         * @param: T x - data element to add to the AUDS.
         *
         * TODO-refactor: possible error from wrong type pushed, but type
         *  not sure how to do type checking in cpp yet.
         ***************************************************************/
        void push(T x){
            //Check if maximum size will be reached
            if ((size()+1) >= max()) {
                //Increase maximum
                maxE *= 1.5;
                //Expand array and copy over elements
                setSize();
            }
            
            //Add the data
            data[curLoc++] = x;
            //Increment our count
            numE++;
        }

        /****************************************************************
         * This method removes a random data element from the AUDS.  
         *  It then moves the last item in the AUDS to the spot that was
         *  occupied by the element we removed.  It automatically handles
         *  resizing of the data structure. 
         *   
         * @return: T - data element to return from the AUDS.
         *
         * @error checking - prints a basic message and ignores request
         *  when AUDS is empty and pop is called.
         ***************************************************************/
        T pop(){
            //Catch when AUDS is empty
            if (size() == 0){
                //Print error message
                std::cout << "Cannot pop when AUDS is empty!" << std::endl;
                //Exit pop function
                return nullptr;
            }

            //Spawn random int in bounds
            int rE = rand() % size();
            //Copy data from selected random array address
            T temp = data[rE];
            //Replace copied element with last element
            data[rE] = data[curLoc];
            //Decrement counters
            numE--;
            curLoc--;
            //now data will be overwritten or ignored, effectively deleting it

            //Check if the current number of elements is now below 2/3s of
            //the original size, as well as not below 100.
            if ((size() > 100) && (size() < ((max() * (.66))-1))) {
                //Decrease maximum
                maxE *= .66;
                //Resize array and copy over elements
                setSize();
            }

            //Return the data we copied from the random location
            return temp;
        }

        //This is for testing purposes only
        void printAUDS() {
            for(int i=0; i<curLoc; i++) {
                //FINISH
                std::cout << data[i] << std::endl;
            }
        }
};

#endif
