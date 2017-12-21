#include "fun_head.h"

MODELBEGIN


EQUATION("Statistics")

WRITE("AvAvQuality", V("AvAvQuality")+V("AvQuality")/(double)max_step);
WRITE("AvAvx", V("AvAvx")+V("Avx")/(double)max_step);
WRITE("AvAvQVI", V("AvAvQVI")+V("AvQVI")/(double)max_step);
//WRITE("AvAvQuality", V("AvAvQuality")+V("AvQuality")/(double)max_step);
//WRITE("AvAvQuality", V("AvAvQuality")+V("AvQuality")/(double)max_step);
//WRITE("AvAvQuality", V("AvAvQuality")+V("AvQuality")/(double)max_step);

RESULT(1)

EQUATION("AvQuality")
/*
Average true unobservable quality, computing also the av. observable indicator
*/
v[0]=v[1]=v[2]=v[3]=0;

CYCLE(cur, "Prof")
 {
  v[0]+=VS(cur,"Quality");
  v[1]+=VS(cur,"x");
  v[3]+=VS(cur,"QVI");
  v[2]++;
 }

WRITE("Avx",v[1]/v[2]);
WRITE("AvQVI",v[3]/v[2]);
RESULT(v[0]/v[2] )

EQUATION("Hiring")
/*
Perform the selection of new prof  to hire

*/

CYCLE(cur, "Candidate")
 {
  v[0]=V("QualityGenerator");
  WRITES(cur,"CQuality",v[0]);
  V_CHEAT("XGenerator", cur);
  V_CHEAT("QVIGenerator",cur);  
  V_CHEAT("ProbGenerator",cur);  
 }

v[1]=V("Retiring");

for(v[2]=0; v[2]<v[1]; v[2]++)
 {
  cur=RNDDRAW("Candidate","Prob");
  cur1=ADDOBJ("Prof");
  WRITELS(cur1,"Age",0, t);
  WRITES(cur1,"Quality",VS(cur, "CQuality"));
  WRITES(cur1,"x",VS(cur, "Cx"));  
  WRITES(cur1,"QVI",VS(cur, "CQVI"));     
 }

RESULT(1 )


EQUATION("Retiring")
/*
Remove professors
*/

v[0]=0;
v[1]=V("RetiringAge");
CYCLE_SAFE(cur, "Prof")
 {
  if(v[1]<=VS(cur,"Age"))
   {v[0]++;
    DELETE(cur);
   }
 }

RESULT(v[0] )

EQUATION("Age")
/*
Increase age by 1
*/

RESULT(CURRENT+1 )


EQUATION("QualityGenerator")
/*
Produce the quality of potential hires, distributed as a power law random variable.

Power law distribution:
x = [(x1^(n+1) - x0^(n+1))*y + x0^(n+1)]^(1/(n+1))
where y is a uniform variate, n is the distribution power, x0 and x1 define the range of the distribution, and x is your power-law distributed variate.

*/

v[4]=V("ExpPowerLaw")+1;
v[0]=1;
v[1]=0;
v[2]=(pow(v[1],v[4])-pow(v[0],v[4]))*RND+pow(v[0],v[4]);

v[5]=pow(v[2], 1/v[4]);

RESULT(1-v[5] )

EQUATION("XGenerator")
/*
Generate the indicator value, as a random draw in a range around the true quality
*/

v[3]=VS(c,"CQuality");
v[0]=V("ErrorRange");
if(v[3]-v[0]/2<0)
 {v[1]=0;
  v[2]=v[0]/2;
 }
else
 {
  if(v[3]+v[0]/2>1)
   {
    v[1]=1-v[0]/2;
    v[2]=1;
   }
  else
   {
    v[1]=v[3]-v[0]/2;
    v[2]=v[3]+v[0]/2;
   } 
 
 }  
 
/*
v[1]=max(0, v[3]-v[0]/2);
v[2]=min(1, v[3]+v[0]/2);
*/
v[3]=UNIFORM(v[1],v[2]);

WRITES(c,"Cx",v[3]);
RESULT(v[3] )

EQUATION("ProbGenerator")
/*
Probability of being hired generator, representing the selection process.

Since it depends on the indicator, not on the true quality.
*/

v[0]=V("ExpSelection");
v[1]=VS(c,"Cx");
v[2]=pow(v[1],v[0]);
WRITES(c,"Prob",v[2]);
RESULT(v[2] )

EQUATION("QVIGenerator")
/*
Preferences of Quality vs Indicator activity. QVI closer to 1 improve the hidden quality of the professor, while closer to 0 the indicators are boosted.
*/

v[0]=V("QVIstock");
v[1]=UNIFORM(1,-1);
WRITES(c,"CQVI",v[1]);
v[2]=VS(c,"Cx");
v[3]=VS(c,"CQuality");
v[4]=max(0,min(1,v[3] +v[1]*v[0]));
WRITES(c,"CQuality",v[4]);
v[5]=max(0,min(1,v[2] -v[1]*v[0]));
WRITES(c,"Cx",v[5]);

RESULT(v[1] )

MODELEND




void close_sim(void)
{

}

