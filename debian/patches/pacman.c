Description: fix some problems and add features.
               - Problems fixed:
                   * Changed screen/window resolution error message.
                   * Bugfix for possible buffer overflow when choosing a
                     level. (Closes #641652)
                   * Bugfix for possible index out of bound when going through
                     a border while playing. (Closes #641657)
               - Feature to allow create a menu icon for X (Closes: #737997):
                   * Game Over screen which allows to exit or to restart.
               - Another features:
                   * Added a help option (documents before undocumented level
                     choosing option).
                   * Changed option syntax for level choosing.
Author: Yannic Scheper <ys42@cd42.de>
Last-Update: 2014-02-10
--- a/pacman.c
+++ b/pacman.c
@@ -16,19 +16,21 @@
 #include "pacman.h"
 
 void IntroScreen();                                     //Show introduction screen and menu
-void CheckCollision();                                  //See if Pacman and Ghosts collided
+int CheckCollision();                                   //See if Pacman and Ghosts collided
 void CheckScreenSize();                                 //Make sure resolution is at least 32x29
 void CreateWindows(int y, int x, int y0, int x0);       //Make ncurses windows
 void Delay();                                           //Slow down game for better control
 void DrawWindow();                                      //Refresh display
 void ExitProgram(char message[255]);                    //Exit and display something
 void GetInput();                                        //Get user input
+int GameOverScreen();                                   //Show 'Game Over' screen
 void InitCurses();                                      //Start up ncurses
 void LoadLevel(char levelfile[100]);                    //Load level into memory
-void MainLoop();                                        //Main program function
+int MainLoop();                                         //Main program function
 void MoveGhosts();                                      //Update Ghosts' location
 void MovePacman();                                      //Update Pacman's location
 void PauseGame();                                       //Pause
+void PrintHelp(char* name);                             //Print help and exit
 
 //For ncurses
 WINDOW * win;
@@ -50,45 +52,76 @@
 
 int main(int argc, char *argv[100]) {
 
-	int j = 0;
+	int loop = 1;       //loop program? 0 = no, 1 = yes
+	char* level = NULL; //level to load
+	int j = 1;
+	int i;
+	for(i = 1; i < argc; ++i) {
+		if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
+			PrintHelp(argv[0]);
+			return 0;
+		}
+		else if(strncmp(argv[i], "--level=", 8) == 0) {
+			level = argv[i];
+			level += 8;
+			int len = strlen(level);
+			if(len == 0) {
+				level = NULL;
+			}
+			else if(len == 1) {
+				for(LevelNumber = '1'; LevelNumber <= '9'; LevelNumber++) {
+					if(LevelNumber == level[0]) {
+						j = LevelNumber - '0';
+						level = NULL;
+						break;
+					}
+				}
+			}
+		}
+		else {
+			PrintHelp(argv[0]);
+			return 0;
+		}
+	}
+
 	srand( (unsigned)time( NULL ) );
 
 	InitCurses();
 	CheckScreenSize();
 	CreateWindows(29, 28, 1, 1);
 
-	//If they specified a level to load
-	if((argc > 1) && (strlen(argv[1]) > 1)) {
-		LoadLevel(argv[1]);
-		MainLoop();
-	}
-        
-	//If not, display intro screen then use default levels
-	else {
-		//Show intro "movie"
-		IntroScreen();
+	//Show intro "movie"
+	IntroScreen();
 
-		j = 1;
-		//They want to start at a level 1-9
-		if(argc > 1)
-			for(LevelNumber = '1'; LevelNumber <= '9'; LevelNumber++)
-				if(LevelNumber == argv[1][0]) j = LevelNumber - '0';
-
-		//Load 9 levels, 1 by 1, if you can beat all 9 levels in a row, you're awesome
-		for(LevelNumber = j; LevelNumber < 10; LevelNumber++) {
-                        LevelFile[strlen(LevelFile) - 6] = '0';
-			LevelFile[strlen(LevelFile) - 5] = LevelNumber + '0';
-			LoadLevel(LevelFile);
+	int start_lives = Lives;
+	int start_points = Points;
+	do {
+		Lives = start_lives;
+		Points = start_points;
+		if(level == NULL) {
+			//j = 1;
+			//Load levels, 1 by 1, if you can beat all 9 levels in a row, you're awesome
+			for(LevelNumber = j; LevelNumber < 10; LevelNumber++) {
+                            LevelFile[strlen(LevelFile) - 6] = '0';
+				LevelFile[strlen(LevelFile) - 5] = LevelNumber + '0';
+				LoadLevel(LevelFile);
+				Invincible = 0;			//Reset invincibility
+				if(MainLoop() == 1) break;
+			}
+		}
+		else {
+			//Load special non-standard level
+			LoadLevel(level);
 			Invincible = 0;			//Reset invincibility
 			MainLoop();
 		}
-
-	}
+		if(GameOverScreen() == 1) loop = 0;
+	} while(loop == 1);
 
 	ExitProgram("Good bye!");
 }
 
-void CheckCollision() {
+int CheckCollision() {
 	int a = 0;
 	for(a = 0; a < 4; a++) {
 		//Collision
@@ -116,7 +149,7 @@
 				Lives--;
 				usleep(1000000);
 
-				if(Lives == -1) ExitProgram("Game Over");
+				if(Lives == -1) return 1;
 
 				//Reset level
 				for(a = 0; a < 5; a++) {
@@ -135,6 +168,7 @@
 			}
 		}
 	}
+	return 0;
 }
 
 void CheckScreenSize() {
@@ -143,7 +177,7 @@
         if((h < 32) || (w < 29)) {
                 endwin();
                 fprintf(stderr, "\nSorry.\n");
-                fprintf(stderr, "To play Pacman for Console, your console window must be at least 32x29\n");
+                fprintf(stderr, "To play Pacman for Console, your console window must be at least 29x32\n");
                 fprintf(stderr, "Please resize your window/resolution and re-run the game.\n\n");
                 exit(0);
         }
@@ -223,6 +257,34 @@
 	exit(0);
 }
 
+int GameOverScreen() {
+	char chr = ' ';
+	int a, b;
+	for(a = 0; a < 29; a++) for(b = 0; b < 28; b++) {
+		mvwaddch(win, a, b, chr);
+	}
+
+	wattron(win, COLOR_PAIR(Pacman));
+	mvwprintw(win, 8, 11, "Game Over");
+
+	wattron(win, COLOR_PAIR(Normal));
+	mvwprintw(win, 14, 2, "Press q to quit ...");
+	mvwprintw(win, 16, 2, "... or any other key");
+	mvwprintw(win, 17, 6, "to play again");
+
+	wrefresh(win);
+
+	//And wait
+	int chtmp;
+	do {
+		chtmp = getch();
+	} while (chtmp == ERR);
+
+	if(chtmp == 'q' || chtmp == 'Q')
+		return 1;
+	return 0;
+}
+
 void GetInput() {
 	int ch;
 	static int chtmp;
@@ -233,28 +295,37 @@
 	if(ch == ERR) ch = chtmp;
 	chtmp = ch;
 
+	int tmp;
 	switch (ch) {
 		case KEY_UP:    case 'w': case 'W':
-			if((Level[Loc[4][0] - 1][Loc[4][1]] != 1)
-			&& (Level[Loc[4][0] - 1][Loc[4][1]] != 4))
+			if(Loc[4][0] == 0) tmp = 28;
+			else tmp = Loc[4][0] - 1;
+			if((Level[tmp][Loc[4][1]] != 1)
+			&& (Level[tmp][Loc[4][1]] != 4))
 				{ Dir[4][0] = -1; Dir[4][1] =  0; }
 			break;
 
 		case KEY_DOWN:  case 's': case 'S':
-			if((Level[Loc[4][0] + 1][Loc[4][1]] != 1)
-			&& (Level[Loc[4][0] + 1][Loc[4][1]] != 4))
+			if(Loc[4][0] == 28) tmp = 0;
+			else tmp = Loc[4][0] + 1;
+			if((Level[tmp][Loc[4][1]] != 1)
+			&& (Level[tmp][Loc[4][1]] != 4))
 				{ Dir[4][0] =  1; Dir[4][1] =  0; }
 			break;
 
 		case KEY_LEFT:  case 'a': case 'A':
-			if((Level[Loc[4][0]][Loc[4][1] - 1] != 1)
-			&& (Level[Loc[4][0]][Loc[4][1] - 1] != 4))
+			if(Loc[4][1] == 0) tmp = 27;
+			else tmp = Loc[4][1] - 1;
+			if((Level[Loc[4][0]][tmp] != 1)
+			&& (Level[Loc[4][0]][tmp] != 4))
 				{ Dir[4][0] =  0; Dir[4][1] = -1; }
 			break;
 
 		case KEY_RIGHT: case 'd': case 'D':
-			if((Level[Loc[4][0]][Loc[4][1] + 1] != 1)
-			&& (Level[Loc[4][0]][Loc[4][1] + 1] != 4))
+			if(Loc[4][1] == 27) tmp = 0;
+			else tmp = Loc[4][1] + 1;
+			if((Level[Loc[4][0]][tmp] != 1)
+			&& (Level[Loc[4][0]][tmp] != 4))
 				{ Dir[4][0] =  0; Dir[4][1] =  1; }
 			break;
 
@@ -355,7 +426,7 @@
 
 }
 
-void LoadLevel(char levelfile[100]) {
+void LoadLevel(char* levelfile) {
 
 	int a = 0; int b = 0;
 	char error[255] = "Cannot find level file: ";
@@ -373,7 +444,7 @@
         fin = fopen(levelfile, "r");
 
         //Make sure it didn't fail
-        if(!(fin)) { strcat(error, levelfile); ExitProgram(error); }
+        if(!(fin)) { strncat(error, levelfile, 230); ExitProgram(error); }
 
         //Open file and load the level into the array
         for(a = 0; a < 29; a++) {
@@ -398,7 +469,7 @@
 
 }
 
-void MainLoop() {
+int MainLoop() {
 
 	DrawWindow();
 	wrefresh(win);
@@ -406,8 +477,8 @@
 	usleep(1000000);
 
 	do {
-		MovePacman();	DrawWindow();	CheckCollision();
-		MoveGhosts();	DrawWindow();	CheckCollision();
+		MovePacman();	DrawWindow();	if(CheckCollision() == 1) return 1;
+		MoveGhosts();	DrawWindow();	if(CheckCollision() == 1) return 1;
 		if(Points > FreeLife) { Lives++; FreeLife *= 2;}
 		Delay();
 
@@ -416,6 +487,7 @@
 	DrawWindow();
 	usleep(1000000);
 
+	return 0;
 }
 
 void MoveGhosts() {
@@ -424,6 +496,7 @@
 	int tmpdx = 0; int tmpdy = 0;
 	int checksides[] = { 0, 0, 0, 0, 0, 0 };
 	static int SlowerGhosts = 0;
+	int tmp;
 
 	if(Invincible == 1) {
 		SlowerGhosts++;
@@ -445,10 +518,18 @@
 
 		//Determine which directions we can go
 		for(b = 0; b < 4; b++) checksides[b] = 0;
-		if(Level[Loc[a][0] + 1][Loc[a][1]] != 1) checksides[0] = 1;
-		if(Level[Loc[a][0] - 1][Loc[a][1]] != 1) checksides[1] = 1;
-		if(Level[Loc[a][0]][Loc[a][1] + 1] != 1) checksides[2] = 1;
-		if(Level[Loc[a][0]][Loc[a][1] - 1] != 1) checksides[3] = 1;
+		if(Loc[a][0] == 28) tmp = 0;
+		else tmp = Loc[a][0] + 1;
+		if(Level[tmp][Loc[a][1]] != 1) checksides[0] = 1;
+		if(Loc[a][0] == 0) tmp = 28;
+		else tmp = Loc[a][0] - 1;
+		if(Level[tmp][Loc[a][1]] != 1) checksides[1] = 1;
+		if(Loc[a][1] == 27) tmp = 0;
+		else tmp = Loc[a][1] + 1;
+		if(Level[Loc[a][0]][tmp] != 1) checksides[2] = 1;
+		if(Loc[a][1] == 0) tmp = 27;
+		else tmp = Loc[a][1] - 1;
+		if(Level[Loc[a][0]][tmp] != 1) checksides[3] = 1;
 
 		//Don't do 180 unless we have to
 		c = 0; for(b = 0; b < 4; b++) if(checksides[b] == 1) c++;
@@ -559,3 +640,11 @@
 	} while (chtmp == ERR);
 
 }
+
+void PrintHelp(char* name) {
+	printf("Usage: %s [OPTION]\n\n", name);
+	printf("Options:\n");
+	printf("  -h, --help        print help\n");
+	printf("  --level=[1..9]    start at specified standard level\n");
+	printf("  --level=LEVEL     play specified non-standard LEVEL\n");
+}
