#include "RombergIntegration.h"
#include "RecursiveIntegration.h"
#include "QueueLinked.h"
#include "Double.h"
using CSC2110::Double;

#include <math.h>

//a is the lower limit and b is the upper limit
double RombergIntegration::accurateRomberg(MultiVarFunction* f, double a, double b, int level)
{
   Double* db;  //use this variable to place and retrieve values on the queue
   Doulbe* dbjr;
	
   QueueLinked<Double>* q1 = new QueueLinked<Double>(); //creating queues of type double
   QueueLinked<Double>* q2 = new QueueLinked<Double>();
	
   Double* iL;
   Double* iM;


   int counter = 0;
   int n = 1;  //current number of intervals
   while (counter <= level)
   {
      //DO THIS
      //obtain the required number of trapezoid evaluations depending on the number of levels requested
      //put all of the level 0 results on the q1
	double answer = RecursiveIntegration::romberg(f, level, a, b);  //trap was not recognized
      	db = new Double(answer);
	q1->enqueue(db);
    n = 2*n;  //double the number of intervals
    counter++;
   }

   //q1 now has all of the level 0 integration results

   double factor;  //use this to compute the current Romberg Factor (4^k stuff)
   int power = 1;  //k, used to compute the Romberg Factor

   //if level 0 has been requested, the loop will not execute
   //the total number of executions of the loop is ??
   
   double results;
   //DO THIS
   int iterations = (level * (level+1))/ 2 //can be precomputed
   while (iterations > 0)
   {
      //DO THIS
      //use the algorithm described in the lab to improve the accuracy of your level 0 results
	   while(q1->size() != 1)
	   {
		factor = pow(4, power);
		   
		iL = q1->dequeue();
		iM = q1->peek();
		   
		results = ((factor * iM->getValue()) - iL-getValue())/(factor - 1);
		dbjr = new Double(results);
		q2->enqueue(dbjr);
	   }
	  
   int q2sz = q2->size();
   q1->dequeueAll();
   for(int i = 0; i < q2sz; i++)
   {
	   dbjr = q2->dequeue();
	   q1->enqueue(dbjr);
   }

      power++;
      iterations--;
   }

   //obtain the final answer
   db = q1->dequeue();
   double result = db->getValue();  
   delete db;
   delete dbjr;

   delete q1;
   delete q2;

   return result;
}
