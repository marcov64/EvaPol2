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
  v[4] = VS(cur, "CQuality");
  v[5] = VS(cur, "Cx");

  v[10]=INCR("PSumQ",v[4]);
  v[12]=INCR("PSumQ2",v[4]*v[4]);
  v[13]=INCR("PSumX",v[5]);
  v[14]=INCR("PSumX2",v[5]*v[5]);
  v[15]=INCR("PSteps",1);
  v[16]=INCR("PSumQX",v[4]*v[5]);


  v[34] = VS(cur, "CQualityT");
  v[35] = VS(cur, "CxT");

  v[40]=INCR("SumQ",v[34]);
  v[42]=INCR("SumQ2",v[34]*v[34]);
  v[43]=INCR("SumX",v[35]);
  v[44]=INCR("SumX2",v[35]*v[35]);
  v[46]=INCR("SumQX",v[34]*v[35]);

 }

  v[17]=v[10]/v[15];
  v[18]=v[12]/v[15];
  v[19]=v[13]/v[15];
  v[20]=v[14]/v[15];
  v[21]=v[16]/v[15];
  
  v[22]=v[18]-v[17]*v[17];
  v[23]=v[20]-v[19]*v[19];
  v[24]=v[21]-v[17]*v[19];
  
  v[25]=v[24]/sqrt(v[22]*v[23]);
  
  WRITE("PCorrQX",v[25]);

  v[57]=v[40]/v[15];
  v[58]=v[42]/v[15];
  v[59]=v[43]/v[15];
  v[50]=v[44]/v[15];
  v[51]=v[46]/v[15];

  v[62]=v[58]-v[57]*v[57];
  v[63]=v[50]-v[59]*v[59];
  v[64]=v[51]-v[57]*v[59];
  
  v[65]=v[64]/sqrt(v[62]*v[63]);
  
  WRITE("CorrQX",v[65]);

v[1]=V("Retiring");

for(v[2]=0; v[2]<v[1]; v[2]++)
 {
  cur=RNDDRAW("Candidate","Prob");
  cur1=ADDOBJ("Prof");
  WRITELS(cur1,"Age",0, t);
  WRITES(cur1,"Quality",v[4]=VS(cur, "CQualityT"));
  WRITES(cur1,"x",v[5]=VS(cur, "CxT"));  
  WRITES(cur1,"QVI",VS(cur, "CQVI"));
   
 /*
  v[10]=INCR("PSumQ",v[4]);
  v[12]=INCR("PSumQ2",v[4]*v[4]);
  v[13]=INCR("PSumX",v[5]);
  v[14]=INCR("PSumX2",v[5]*v[5]);
  v[15]=INCR("PSteps",1);
  v[16]=INCR("PSumQX",v[4]*v[5]);
  
  v[17]=0;
  v[18]=(v[15]*v[16]-v[10]*v[13]);
  v[19]=(v[15]*v[12]-v[10]*v[10]);
  v[20]=(v[15]*v[14]-v[13]*v[13]);
  if(v[15]>1)
   {
    if(v[20]*v[19]<=0)
      INTERACT("merda 1", v[20]*v[19]);  
    else  
      v[17]=v[18]/sqrt(v[19]*v[20]);
   } 
  WRITE("PCorrQX",v[17]);
  */
      
 }

RESULT(1 )


EQUATION("Retiring")
/*
Remove professors
*/

v[0]=0;
v[1]=V("RetiringAge");
v[2]=1;
v[3]=v[4]=0;
CYCLE_SAFE(cur, "Prof")
 {
  v[5] = VS(cur, "Quality");
  if(v[5]<v[2])
   v[2]=v[5]; //this is the min

  if(v[1]<=VS(cur,"Age"))
   {v[0]++;
    DELETE(cur);
   }
 }

WRITE("Threshold", v[2]);

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

//v[12]=(pow(v[1],v[4])-pow(v[0],v[4]))*RND+pow(v[0],v[4]);
//v[15]=pow(v[12], 1/v[4]);

//WRITE("cazzo", v[15]);

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

v[5]=VS(c, "CQuality");
v[6] = V("Threshold");
if(v[5]<v[6])
 {
  WRITES(c, "Prob", 0);
  END_EQUATION(0)
 }

v[0]=V("ExpSelection");
v[1]=VS(c,"CxT");
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

v[30]=min(v[2], min(1-v[2],v[0]));
v[31]=min(v[3], min(1-v[3],v[30]));
v[4]=v[3] +v[1]*v[31];
WRITES(c,"CQualityT",v[4]);
v[5]=v[2] -v[1]*v[31];
WRITES(c,"CxT",v[5]);

/*
v[4]=max(0,min(1,v[3] +v[1]*v[0]));
WRITES(c,"CQuality",v[4]);
v[5]=max(0,min(1,v[2] -v[1]*v[0]));
WRITES(c,"Cx",v[5]);
*/

/*
v[10]=INCR("SumQ",v[4]);
v[12]=INCR("SumQ2",v[4]*v[4]);
v[13]=INCR("SumX",v[5]);
v[14]=INCR("SumX2",v[5]*v[5]);
v[15]=INCR("Steps",1);
v[16]=INCR("SumQX",v[4]*v[5]);


v[17]=0;
v[18]=(v[15]*v[16]-v[10]*v[13]);
v[19]=(v[15]*v[12]-v[10]*v[10]);
v[20]=(v[15]*v[14]-v[13]*v[13]);
if(v[15]>1)
 {
  if(v[20]*v[19]<=0)
    INTERACT("merda", v[20]*v[19]);  
  else  
    v[17]=v[18]/sqrt(v[19]*v[20]);
 } 
WRITE("CorrQX",v[17]);
*/
RESULT(v[1] )

MODELEND




void close_sim(void)
{

}


