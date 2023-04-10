





// ----------------------
void pollForHalfSec(int rinput);
void addToHits();
void subLives();
int[] getXY(int rinput); 
int getHoleNum(int input);




void gameplayScreen(int mode, int modeData)
{
    drawImage(0,0, 240, 320, gameplayBackImg);
//param updating , these param determine the while loop arg, after param==0 we exit gameplay
    while(param)
    {
        int rinput =rand()%13; //0-12, //0-7 are holes, //8-12 
        int misses=0;
        int hits=0;
        int input=-1;

       if(rinput<8) 
       {
        int molePos[2] =getXY(rinput);
        drawImage(molePos[1],molePos[0],///////////,moleIMG);
        pollForHalfSec(rinput,mode);
       }
       else // not drawing anything
       {
        //poll for .5 sec, if input recieved its a miss
        pollForHalfSec(-1,mode);
       }


    }

//todo
//add location to xy coverstion, 
//is array syntax for getXY correct?
//does rand nu,mber need a headfile, also does it produce exp0ected output?
//make moleImg array
//phtoshop and madke the hammer img
//insert delay in polling



}



void pollForHalfSec(int rinput, int mode) //shoudl fix to have timer integrated 
{   int input;
        int counter =50000;//should be 25million for board 
        while(counter) //counting down till 0, polling at each step
        {
            counter--;
            KbdData =*kbdPtr; //retrieving input and identifying if its valid button press
            RVALID= (KbdData & 0x8000);    
            if (RVALID != 0) 
            {
                input = KbdData & 0xFF;
                if (getHoleNum(input) == rint) //means they missed it
                {
                    addToHits();  
                }
                else
                {
                    if(mode==2)
                    { subLives();}
                }
                int input[2] =getXY(input);
                drawImage(input[1],input[0],//sizeee of hitt, hitImg);
                //insertDelay for like very short time
                drawImage(0,0, 240, 320, gameplayBackImg);
                int molePos[2] =getXY(rinput);
                drawImage(molePos[1],molePos[0],///////////,moleIMG);

            }
        }
    
}

void addToHits()
{
    //basically just ad 1  to the number on the hex
}
void subLives()
{
   //decrements the lifecount ont he leds
}

//need to add xylocations to draw images at, add proper syntax for the pair variable 
int[2] getXY(int rinput)
{
    int input[2];
    
     if(rinput==0) //corr to hole A
          { input[0]=;
          input[1]=;}
          else if (rinput==1) //corr to hole S
         { input[0]=;
          input[1]=;}
          else if (rinput==2) //corr to hole D
         { input[0]=;
          input[1]=;}
          else if (rinput==3) //corr to hole F
         { input[0]=;
          input[1]=;}
          else if (rinput==4) //corr to hole H
         { input[0]=;
          input[1]=;}
          else if (rinput==5) //corr to hole J
         { input[0]=;
          input[1]=;}
          else if (rinput==6) //corr to hole K
         { input[0]=;
          input[1]=;}
          else //if (rinput==7) //corr to hole L
         { input[0]=;
          input[1]=;}

    return input;

}

int getHoleNum(int input) //gives us back the hole number from keyboard input,, holes range 0-7
{
    int holeNum;
    if(rinput==28) //corr to hole A
          { holeNum=0;}
          else if (rinput==27) //corr to hole S
          { holeNum=1;}
          else if (rinput==35) //corr to hole D
         { holeNum=2;}
          else if (rinput==43) //corr to hole F
         { holeNum=3;}
          else if (rinput==51) //corr to hole H
         { holeNum=4;}
          else if (rinput==59) //corr to hole J
         { holeNum=5;}
          else if (rinput==66) //corr to hole K
         { holeNum=6;}
          else if (rinput==75) //corr to hole L
         { holeNum=7;} 
         else
         {holeNum=-1;}

         return holeNum;
}