#include "../../include/Menus/HighscoreScreen.h"

void HighscoreScreen::setup() {
  // Retry
  buttons.push_back(new Button);
  buttons[0]->setup(SPACE_X_RESOLUTION/4*3, SPACE_Y_RESOLUTION/10, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/GameMenus/Retry.png");
  // Quit
  buttons.push_back(new Button);
  buttons[1]->setup(SPACE_X_RESOLUTION/4 +width/2, SPACE_Y_RESOLUTION/10, BUTTONWIDTH, BUTTONHEIGHT,  (char*)"Textures/Menu/Misc/Quit.png");
  
/*  // Title
  lb.push_back(new Label);
  lb[0]->setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/5*4, 0.4);
  // Score
  lb.push_back(new Label);
  lb[1]->setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/5*4 + BUTTONHEIGHT, 0.4);
  
  for(int i = 0; i < 10; ++i) {
    // Highscores
    lb.push_back(new Label);
    lb[i+2]->setup(SPACE_X_RESOLUTION/4*3-BUTTONWIDTH, SPACE_Y_RESOLUTION/10 * ((7-(i*0.5)) + 0.5) - height/2, 0.3);    
  }
  for(int i = 0; i < 10; ++i) {
    // Highscores names
    lb.push_back(new Label);
    lb[i+12]->setup(SPACE_X_RESOLUTION/4 + BUTTONWIDTH, SPACE_Y_RESOLUTION/10 * ((7-(i*0.5)) + 0.5) - height/2, 0.3);
  }

  std::string str = "Highscores";
  lb[0]->setText(str.c_str(), str.length());
  str = "Your Score: ";
  lb[1]->setText(str.c_str(), str.length());
  // #f08600 R 240 G 134 B 0
  float R = 0.941176471;
  float G = 0.525490246;
  float B = 0;

  lb[0]->setColour(R, G, B);
  lb[1]->setColour(R, G, B);
  R = 0;
  G = 1;
  B = 0;
  for(int i = 0; i < 10; ++i) {
    lb[i+2]->setColour(R, G, B);
    lb[i+12]->setColour(R, G, B);
  }*/
} 

void HighscoreScreen::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  ended = false;
  for(unsigned int i = 0; i < buttons.size(); ++i)
    buttons[i]->update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);

  if(buttons[0]->Clicked()) {
    type = GAME;
    ended = true;
  }
  if(buttons[1]->Clicked()) {
    type = MAINMENU;
    ended = true;
  }
}

void HighscoreScreen::setScore(int score) {
  std::stringstream ss;
  ss << score;
  std::string strScore = "Your score: " + ss.str();
  //lb[1]->setText(strScore.c_str(), strScore.length());
  //LoadHighscores(score);
}
/*
void HighscoreScreen::LoadHighscores(int score) {
  if (!File::check_if_file_exists("data/highscore.bin")) {
    printf("\nCreating new highscore file\n");
    saveDefaults();
  }
  for(int i = 0; i < 10; ++i) {
    names[i] = "";
  }
  printf("\nLoading highscore\n");
  std::ifstream ifs("./data/highscore.bin", std::ios::binary);
  bool isHighscore = false;
  bool done = false;
  for(int i = 0; i < 10; ++i) {  
    std::stringstream ss;
    ss << i+1;
    std::string tempname = ss.str() + ". ";   

    for(int j = 0; j < 6; ++j) 
      names[i] += File::LoadChar(ifs);  
       
    highscores[i] = File::LoadInt(ifs);
     
    if(!isHighscore && score > highscores[i]) {
      isHighscore = true;
      if(i+1 < 10) {
        names[i+1] = names[i];
        highscores[i+1] = highscores[i];
      }
      highscores[i] = score; 
      names[i] = "You   ";
    }
    tempname += names[i]; 
    lb[i+12]->setText(tempname.c_str(), tempname.length()); 
    std::stringstream ss1;
    ss1 << highscores[i];
    std::string tempscore = ss1.str();
    lb[i+2]->setText(tempscore.c_str(), tempscore.length());
    
    if(!done && isHighscore) {
      if(i+1 < 10) {
        tempname = "";
        std::stringstream ss3;
        ss3 << i+2;
        tempname += ss3.str() +". " + names[i+1]; 
        lb[i+12+1]->setText(tempname.c_str(), tempname.length()); 
        std::stringstream ss2;
        ss2 << highscores[i+1];
        std::string tempscore = ss2.str();
        lb[i+2+1]->setText(tempscore.c_str(), tempscore.length());
        i++;
        done = true;
      }      
    }
  }
    
  if(isHighscore) {
    std::ofstream ofs("./data/highscore.bin", std::ios::binary);
    for(int i = 0; i < 10; ++i) {
      for(int j = 0; j < 6; ++j) {
        File::SaveChar(ofs, names[i].at(j));
      }
      File::SaveInt(ofs, highscores[i]);
    }
  }
} 
*/
void HighscoreScreen::restart() {}
