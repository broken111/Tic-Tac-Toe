#include <windows.h>  // For MS Windows
#include <iostream>
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <string>
#include <math.h>
#include <ctime>
#include <time.h>


using std::cerr;
using std::endl;
using namespace std;
float x,y;
bool check=true;
bool drawIt=false;
void drawX(int, int);
void drawCircle(int, int);
int findRowOnClick(int);
int findColOnClick(int);
int screenW = 300;
int screenH = 300;
int rowClick = -1;
int colClick = -1;
int turn=1; //1 means 'O'  -1 means 'X'
bool isThereAWin = false;
int winDirection; //1 is horizontal 2 is vertical 3 diagonalleft  4 diagonalright
int winStartRow;
int winStartCol;
int moveCount;
// these are variables from version 1 (no graphics)
bool Xmove = true;
bool Omove = false;
int numPlayers;
bool computerIsPlaying = false;
int computerIs;  //1 means 'O'  -1 means 'X'


char board[3][3];

void fillBoardWithNull();
void checkForGameOver2();
void makeRandomMove();
bool tryForWinOrBlock();


// This is the function for generating a computer move.....

void doComputerMove(){
    cout << "The COMP will move..." << endl << endl;
    cout << "And the computer turn is "  << turn << endl;
    //srand(time(NULL));   // this seeds the random num generator....
    //int select = (rand() % 9) + 1;

   if(tryForWinOrBlock() == false ) {


	   if(board[1][1] != 'x' && board[1][1] != 'o') {

		   if(computerIs == 1)
		   {
			   board[1][1] = 'o';
		   } else {

			   board[1][1] = 'x';
		   }
		   checkForGameOver2();
			turn *= -1;
			moveCount += 1;
			std::cout << "There have been " << moveCount << " moves" << endl;

	   } else {


		   if(board[1][1] == 'x' && computerIs == 1){
			   if(board[0][0] != 'x' && board[0][0] != 'o') {
				   if(computerIs == 1)
					   {
						   board[0][0] = 'o';
					   } else {

						   board[0][0] = 'x';
					   }
				   checkForGameOver2();
					turn *= -1;
					moveCount += 1;
					 std::cout << "There have been " << moveCount << " moves" << endl;
			   } else if(board[0][2] != 'x' && board[0][2] != 'o') {
					   if(computerIs == 1)
					   {
						   board[0][2] = 'o';
					   } else {

						   board[0][2] = 'x';
					   }
						checkForGameOver2();
						turn *= -1;
						moveCount += 1;
						std::cout << "There have been " << moveCount << " moves" << endl;
				  } else if(board[2][0] != 'x' && board[2][0] != 'o') {
					  if(computerIs == 1)
						   {
							   board[2][0] = 'o';
						   } else {

							   board[2][0] = 'x';
						   }
						checkForGameOver2();
						turn *= -1;
						moveCount += 1;
						std::cout << "There have been " << moveCount << " moves" << endl;
			   } else if(board[2][2] != 'x' && board[2][2] != 'o') {
				   if(computerIs == 1)
					   {
						   board[2][2] = 'o';
					   } else {

						   board[2][2] = 'x';
					   }
					checkForGameOver2();
					turn *= -1;
					moveCount += 1;
					std::cout << "There have been " << moveCount << " moves" << endl;
			   } else {

				   std::cout << "Oh CRUD   WE NEED TO MAKE A MOVE  AND WE ARE NOT DOING THAT!!!!! " << moveCount << " moves" << endl;
				   makeRandomMove();
			   }




		   } else {

			   makeRandomMove();

		   }

	   }
	  } else {
		  checkForGameOver2();
			   turn *= -1;
			   moveCount += 1;
			   std::cout << "There have been " << moveCount << " moves" << endl;



	  }

}

bool tryForWinOrBlock()
{

	// Part I try for a win...
	bool isThereWinOrBlock = false;
	char lookingFor;
//	int winOrBlockStartRow = 0;
//	int winOrBlockStartCol = 0;

	int emptyRow;
	int emptyCol;

	if(turn == 1){
		 lookingFor = 'o';
	} else {
		 lookingFor = 'x';
	}

	//Horizontal check
	for( int r = 0; r < 3; r++){
		int found = 0;
		int empties = 0;
		 for(int c = 0; c < 3 ; c++){
			 if(board[c][r] == lookingFor){
				 found++;
			  }

			 if(board[c][r] != 'x' && board[c][r] != 'o'){
				   empties++;
				   emptyRow = r;
				   emptyCol = c;
			    }
		   }
		   cout << found << endl;
		   if(found ==  2 && empties == 1){
			   /// here we draw the line through all the x's or o's

			   cout << "we are going for win or block in a horizontal way!" << endl;
			   isThereWinOrBlock = true;

			   if(turn == 1){
				   board[emptyCol][emptyRow] = 'o';
			   } else {
				   board[emptyCol][emptyRow] = 'x';
			   }

			   return true;

		   }
	   }



	   //Vertical check
	     for( int c = 0; c < 3; c++){
	  	   int found = 0;
	  	   int empties = 0;
	  	   for(int r = 0; r < 3 ; r++){
	  		   if(board[c][r] == lookingFor){
	  			   found++;
	  		   }
	  		 if(board[c][r] != 'x' && board[c][r] != 'o'){
	  		 				   empties++;
	  		 				   emptyRow = r;
	  		 				   emptyCol = c;
	  		 }
	  	   }
	  	   cout << found << endl;
	  	   if(found ==  2 && empties == 1){
	  	 			   /// here we draw the line through all the x's or o's

	  	 			   cout << "we are going for win or block in a vertical (win) way!" << endl;
	  	 			   isThereWinOrBlock = true;

	  	 			   if(turn == 1){
	  	 				   board[emptyCol][emptyRow] = 'o';
	  	 			   } else {
	  	 				   board[emptyCol][emptyRow] = 'x';
	  	 			   }

	  	 			   return true;

	  	 		   }
	     }

	     //Diag 1 check (right or left?)

	     int found = 0;
	     int empties =0;
	     for( int i=0; i < 3; i++){
	    	 if(board[i][i] == lookingFor){
	    	 	  found++;
	    	 }
	    	 if(board[i][i] != 'x' && board[i][i] != 'o'){
	    	 	  	empties++;
	    	 	  	emptyRow = i;
	    	 	  	emptyCol = i;
	    	 }
	     }

	  	   if(found ==  2 && empties == 1){
	  	 			   /// here we draw the line through all the x's or o's

	  	 		cout << "we are going for win or block in a diag (win) way!" << endl;
	  	 		isThereWinOrBlock = true;

	  	 		if(turn == 1){
	  	 			board[emptyCol][emptyRow] = 'o';
	  	 		} else {
	  	 			board[emptyCol][emptyRow] = 'x';
	  	 		}

	  	 		return true;

	  	 }
	     //Diag 2 check (right or left?)

	 	 found = 0;
	 	 empties = 0;
	     for( int i=0; i < 3; i++){

	    	 cout << "checking row: " << 3-i-1 << " and col " << i << endl;
	    	 if(board[i][3-i-1] == lookingFor){
	    	 	   found++;
	    	 }
	    	 if(board[i][3-i-1] != 'x' && board[i][3-i-1] != 'o'){
	    	 	   empties++;
	    	 	   emptyRow = 3-i-1;
	    	 	   emptyCol = i;
	    	  }
	     }

	  	   if(found ==  2 && empties == 1){
	  	 			   /// here we draw the line through all the x's or o's

	  	 		cout << "we are going for win or block in a diag2 (win) way!" << endl;
	  	 		isThereWinOrBlock = true;

	  	 		if(turn == 1){
	  	 			board[emptyCol][emptyRow] = 'o';
	  	 		} else {
	  	 			board[emptyCol][emptyRow] = 'x';
	  	 		}

	  	 		return true;

	  	 }



// Part II Looking for a block....


	  	 if(turn == 1){
	  	 		 lookingFor = 'x';
	  	 	  cout << "for a computer block we are looking for 'x' " << endl;

	  	 	} else {
	  	 		 lookingFor = 'o';
	  	 	  cout << "for a computer block we are looking for 'o' " << endl;

	  	 	}

	 	//Horizontal check
	 	for( int r = 0; r < 3; r++){
	 		int found = 0;
	 		int empties = 0;
	 		 for(int c = 0; c < 3 ; c++){
	 			 if(board[c][r] == lookingFor){
	 				 found++;
	 			  }

	 			 if(board[c][r] != 'x' && board[c][r] != 'o'){
	 				   empties++;
	 				   emptyRow = r;
	 				   emptyCol = c;
	 			    }
	 		   }
	 		   cout << found << endl;
	 		   if(found ==  2 && empties == 1){
	 			   /// here we draw the line through all the x's or o's

	 			   cout << "we are going for win or block in a horizontal (block) way!" << endl;
	 			   isThereWinOrBlock = true;

	 			   if(turn == 1){
	 				   board[emptyCol][emptyRow] = 'o';
	 			   } else {
	 				   board[emptyCol][emptyRow] = 'x';
	 			   }

	 			   return true;

	 		   }
	 	   }



	 	   //Vertical check
	 	     for( int c = 0; c < 3; c++){
	 	  	   int found = 0;
	 	  	   int empties = 0;
	 	  	   for(int r = 0; r < 3 ; r++){
	 	  		   if(board[c][r] == lookingFor){
	 	  			   found++;
	 	  		   }
	 	  		 if(board[c][r] != 'x' && board[c][r] != 'o'){
	 	  		 				   empties++;
	 	  		 				   emptyRow = r;
	 	  		 				   emptyCol = c;
	 	  		 }
	 	  	   }
	 	  	   cout << found << endl;
	 	  	   if(found ==  2 && empties == 1){
	 	  	 			   /// here we draw the line through all the x's or o's

	 	  	 			   cout << "we are going for win or block in a vertical (block) way!" << endl;
	 	  	 			   isThereWinOrBlock = true;

	 	  	 			   if(turn == 1){
	 	  	 				   board[emptyCol][emptyRow] = 'o';
	 	  	 			   } else {
	 	  	 				   board[emptyCol][emptyRow] = 'x';
	 	  	 			   }

	 	  	 			   return true;

	 	  	 		   }
	 	     }

	 	     //Diag 1 check (right or left?)

	 	     found = 0;
	 	     empties = 0;
	 	     for( int i=0; i < 3; i++){
	 	    	 if(board[i][i] == lookingFor){
	 	    	 	  found++;
	 	    	 }
	 	    	 if(board[i][i] != 'x' && board[i][i] != 'o'){
	 	    	 	  	empties++;
	 	    	 	  	emptyRow = i;
	 	    	 	  	emptyCol = i;
	 	    	 }
	 	     }

	 	  	   if(found ==  2 && empties == 1){
	 	  	 			   /// here we draw the line through all the x's or o's

	 	  	 		cout << "we are going for win or block in a diag 1 (block) way!" << endl;
	 	  	 		isThereWinOrBlock = true;

	 	  	 		if(turn == 1){
	 	  	 			board[emptyCol][emptyRow] = 'o';
	 	  	 		} else {
	 	  	 			board[emptyCol][emptyRow] = 'x';
	 	  	 		}

	 	  	 		return true;

	 	  	 }
	 	     //Diag 2 check (right or left?)

		 	 found = 0;
		 	 empties = 0;
	 	     for( int i=0; i < 3; i++){

	 	    	cout << "checking col: " << 3-i-1 << " and row " << i << endl;
	 	    	 if(board[i][3-i-1] == lookingFor){
	 	    	 	   found++;
	 	    	 }
	 	    	 if(board[i][3-i-1] != 'x' && board[i][3-i-1] != 'o'){
	 	    	 	   empties++;
	 	    	 	   emptyRow = 3-i-1;
	 	    	 	   emptyCol = i;
	 	    	  }
	 	     }

	 	  	   if(found ==  2 && empties == 1){
	 	  	 			   /// here we draw the line through all the x's or o's

	 	  	 		cout << "we are going for win or block in a diag2 (block) way!" << endl;
	 	  	 		isThereWinOrBlock = true;

	 	  	 		if(turn == 1){
	 	  	 			board[emptyCol][emptyRow] = 'o';
	 	  	 		} else {
	 	  	 			board[emptyCol][emptyRow] = 'x';
	 	  	 		}

	 	  	 		return true;

	 	  	 }







  cout << "***** We did not find a win or block....." << endl;


	return isThereWinOrBlock;

}


void makeRandomMove(){
		if(moveCount >= 9){
			cout << "Game Over!" << endl;
		} else {
		bool selectboard = false;
		while(selectboard == false)
		{
			 //srand(time(NULL));
				int selectRow = (rand() % 3);
				int selectCol = (rand() % 3);
				cout << "In Computer move select is " << selectRow << ", " << selectCol << endl;

				if(board[selectRow][selectCol] != 'x' && board[selectRow][selectCol] != 'o') {
						  if(turn == 1){
									board[selectRow][selectCol] = 'o';
						  } else {
									board[selectRow][selectCol] = 'x';
						  }
				selectboard = true;
				checkForGameOver2();
				turn *= -1;
				moveCount += 1;
				std::cout << "There have been " << moveCount << " moves" << endl;
							 //glutPostRedisplay();

			}
		}
		}
}




void checkForGameOver2(){

   char lookingFor;
   winDirection = 0;
   winStartRow = 0;
   winStartCol = 0;
   if(turn == 1){
	   lookingFor = 'o';
   } else {
	   lookingFor = 'x';
   }

   //Horizontal check
   for( int r = 0; r < 3; r++){
	   int found = 0;
	   //int empties = 0;
	   for(int c = 0; c < 3 ; c++){
		   if(board[c][r] == lookingFor){
			   found++;
		   }

//		   if(board[c][r] != 'x' && board[c][r] != 'o'){
//			   empties++;
//		    }
	   }
	   cout << found << endl;
	   if(found >= 3){
		   /// here we draw the line through all the x's or o's

		   cout << "You won in a horizontal way!" << endl;
		   isThereAWin = true;
		   winDirection = 1;
		   winStartRow = r;
		   //winStartCol = 0;

	   }
   }



   //Vertical check
     for( int c = 0; c < 3; c++){
  	   int found = 0;
  	   for(int r = 0; r < 3 ; r++){
  		   if(board[c][r] == lookingFor){
  			   found++;
  		   }
  	   }
  	   cout << found << endl;
  	   if(found >= 3){
  		   /// here we draw the line through all the x's or o's

  		   cout << "YOU WIN!!! in a vertical way" << "really" << endl;
  		   isThereAWin = true;
  		   winDirection = 2;
  		   //winStartRow = 0;
  		   winStartCol = c;

  	   }
     }

     //Diag 1 check (right or left?)
     bool foundIt = true;
     for( int i=0; i < 3; i++){
    	 if(board[i][i] != lookingFor){
    		 foundIt = false;
    		 break;
    	 }
     }

     if(foundIt){
       		   /// here we draw the line through all the x's or o's

       		   cout << "YOU WIN!!! in a diag 1 way" << "really" << endl;
       		   isThereAWin = true;
       		   winDirection = 3;
       		   winStartRow = 0;
       		   winStartCol = 0;

       	   }
     //Diag 2 check (right or left?)
     foundIt = true;
     for( int i=0; i < 3; i++){
    	 if(board[i][3 - (i+1)] != lookingFor){
    		 foundIt = false;
    		 break;
    	 }
     }

     if(foundIt){
       		   /// here we draw the line through all the x's or o's

       		   cout << "YOU WIN!!! in a diag 2 way" << "really" << endl;
       		   isThereAWin = true;
       		   winDirection = 4;
       		   winStartRow = 0;
       		   winStartCol = 2;

       	   }

  }

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
   if(check)
   {
	   glBegin(GL_POINTS);
	   glVertex2i(x,y);

	   glEnd();
   }
   glFlush();
   // Draw a Red 1x1 Square centered at origin
   glLineWidth(2.5);
   glColor3f(1, 0, 0);
   glBegin(GL_LINES);
   glVertex3f(.33, 1, 0);
   glVertex3f(.33, -1, 0);
   glVertex3f(-.33, 1, 0);
   glVertex3f(-.33, -1, 0);
   glVertex3f(-1, .33, 0);
   glVertex3f(1, .33, 0);
   glVertex3f(-1, -.33, 0);
   glVertex3f(1, -.33, 0);
   glEnd();




   for( int r = 0; r < 3; r++){
	   for( int c = 0; c < 3; c++){
	   	   if(board[r][c] == 'x'){
	   		 //glColor3f(0, 1, 0);
	   		 drawX(r, c);
	   	   }
	   	   if(board[r][c] == 'o'){
	   		  //glColor3f(0, 1, 0);
	   		  drawCircle(r, c);
	   	   }
	      }
   }
					  // if(drawIt == true){
						  // drawCircle(0, 0);
						   //drawCircle(1, 1);
						  // drawCircle(2, 2);
					//	   if(turn > 0){
					//		   drawCircle(rowClick, colClick);
					//	   } else {
					//		   drawX(rowClick, colClick);
					//	   }






   // Each set of 4 vertices form a quad
     // glColor3f(1.0f, 0.0f, 0.0f); // Red
      //glVertex2f(-0.5f, -0.5f);    // x, y
      //glVertex2f( 0.5f, -0.5f);
      //glVertex2f( 0.5f,  0.5f);
      //glVertex2f(-0.5f,  0.5f);

   // if there is a win then draw the big line

   if(isThereAWin == true){
	   //this is for horizontal

	   if(winDirection == 1){
		   glColor3f(0,0,1);
		   glBegin(GL_LINES);
		   //Pick it up here ****
		   //if(winStartRow == 0){
		    glVertex3f(-1, 1-.330 - (winStartRow * .660) , 0);
		    glVertex3f(1, 1 -.330 - (winStartRow * .660) , 0);

		  // }
		   glEnd();

	   }

	   if(winDirection == 2){
		   //this is for vertical
		   glColor3f(0,0,1);
		   glBegin(GL_LINES);
		   glVertex3f(.330 - 1 + (winStartCol * .660), -1 , 0);
		   glVertex3f(.330 - 1 + (winStartCol * .660), 1 , 0);
		   glEnd();

	   	   }

	   if(winDirection == 3){
		   glColor3f(0,0,1);
		   glBegin(GL_LINES);
		   glVertex3f(-1,1,0);
		   glVertex3f(1,-1,0);
		   glEnd();

	   	   }

	   if(winDirection == 4){
		   glColor3f(0,0,1);
		   glBegin(GL_LINES);
		   glVertex3f(1,1,0);
		   glVertex3f(-1,-1,0);
		   glEnd();

	   	   }
   }




   glFlush();  // Render now
}


void fillBoardWithNull(){

	for(int r = 0; r < 3; r++){
		for(int c = 0; c < 3; c++){
			board[r][c] = ' ';
		}
	}

	moveCount = 0;
}

void drawX(int row, int col)
{
	glBegin(GL_LINES);
	   	   glColor3f(0,1,0);
	   	   glVertex2f(-1        + (row * 0.66),   (1-.66)  -  (col * 0.66));
	   	   glVertex2f(-1  +.66  + (row * 0.66), 1  -  (col * 0.66));
	   	   glVertex2f(-1        + (row * 0.66), 1  -  (col * 0.66));
	   	   glVertex2f(-1  +.66  + (row * 0.66), 1-.66  -  (col * 0.66));
	glEnd();
}

void drawCircle(int row, int col)
{
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * 3.141592;

	glBegin(GL_LINE_LOOP);
	    glColor3f(0,1,0);
		for(i = 0; i <= lineAmount;i++) {
			glVertex2f(
				x + (.33 * cos(i *  twicePi / lineAmount)) - .66 + (.66 * row),
				y + (.33 * sin(i * twicePi / lineAmount)) + .66 - (.66 * col)
			);
		}
	glEnd();
}




void mouse(int button, int state, int mousex, int mousey)
{
	if(button==GLUT_LEFT_BUTTON && state ==GLUT_DOWN)
	{
		check=true;

		x = mousex;
		y = 480-mousey;
		cout << "Hi" << endl;
	}
	glutPostRedisplay();
}


int onMouse;
void mouseClicks(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        onMouse = 1;

        //drawCircle();
        drawIt = true;



        rowClick = findRowOnClick(x);
        colClick = findColOnClick(y);

        cout << "You clicked in this square: " << rowClick << ", " << colClick << endl;
        if(board[rowClick][colClick] == 'x' || board[rowClick][colClick] == 'o'){
        	std::cout << "Error: stop cheating!" << std::endl;
        } else {
        if(moveCount >= 9 || isThereAWin == true ){
        	cout << "Game Over! Press R to Restart!" << endl;
        } else {




        if(turn == 1){
        	board[rowClick][colClick] = 'o';
        } else {
        	board[rowClick][colClick] = 'x';
        }
        checkForGameOver2();
        turn *= -1;
        moveCount += 1;
        std::cout << "There have been " << moveCount << " moves" << endl;
        glutPostRedisplay();
        display();

        if(computerIsPlaying && isThereAWin == false && turn == computerIs){
        	  //glutPostRedisplay();

        	clock_t start_time= clock();
        	clock_t end_time = 2.0 * 1000 + start_time;
        	//Maybe this isn't the greatest coding example, but we found this on the net.
        	while(clock() != end_time)
        	{

        	}
        	doComputerMove();
        	cout << "Hi back from doComputerMove"  << endl;
            glutPostRedisplay();
            display();
        }

        glutPostRedisplay();
        display();
    }
    }
    }
}

int findRowOnClick(int mouseX){

	cout << "Hi from findRowOnClick, mouse X is " << mouseX << endl;
	cout << "Hi from findRowOnClick, screenW is " << screenW << endl;
	double swd3 = screenW/3.0;
	cout << "Hi from findRowOnClick, swd3 is " << swd3 << endl;

	if(  (double)(mouseX) < (double)(screenW/3)  ){
		return 0;
	} else if((double) mouseX < (double) (screenW/3) * 2) {
		return 1;
	} else {
		return 2;
	}
}

int findColOnClick(int mouseY){

	if(mouseY < screenW/3){
		return 0;
	} else if(mouseY < (screenW/3) * 2) {
		return 1;
	} else {
		return 2;
	}
}



/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

	//trying random again...
	srand(time(NULL));


	 cout << "welcome to tic-tac-toe" << endl << endl;
	     cout << "How many players?" << endl;
	     cin >> numPlayers;
	     while (numPlayers > 2 || numPlayers < 1) {
	       cout << "invalid number of players, please re-enter value." << endl;
	       cin >> numPlayers;
	     }

	     cout << "Get ready to play "  << endl;
	     if(numPlayers == 2){
	         cout << "x moves first " << endl << endl;
	         turn = -1;  // THis will start with x

	     }

	     if(numPlayers == 1){
	    	 int whoFirst = rand() % 100 + 1;
	    	 cout << whoFirst << endl;
	    	 if(whoFirst > 50){
	    		 cout << "x moves first  and computer will be o" << endl << endl;
	    		 turn = -1;  // THis will start with x
	    		 computerIsPlaying = true;
	    		 computerIs = 1;
	    	 } else {


	     	      cout << "x moves first  and computer will be x" << endl << endl;
	     	      turn = -1;  // THis will start with x
	     	      computerIsPlaying = true;
	     	      computerIs = -1;

	     	     doComputerMove();
	     	     cout << "Hi back from doComputerMove"  << endl;

	    	 }

	     }



   glutInit(&argc, argv);                 // Initialize GLUT
   glutCreateWindow("Tic Tac Toe"); // Create a window with the given title
   glutInitWindowSize(screenW, screenH);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutMouseFunc(mouseClicks);
   glutMainLoop();  // Enter the infinitely event-processing loop







   return 0;
}








