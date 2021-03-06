#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Constants.h"
#include "Entity.h"
#include "Bloc.h"
#include "BlocGroup.h"
#include "main.h"
#include "Grid.h"

char form1[4][4] = {
    {'-','-','-','-'},
    {'-','#','-','-'},
    {'#','#','#','-'},
    {'-','-','-','-'}
};

char form2[4][4] = {
    {'-','#','-','-'},
    {'-','#','-','-'},
    {'-','#','-','-'},
    {'-','#','-','-'}
};

char form3[4][4] = {
    {'-','-','-','-'},
    {'-','#','#','-'},
    {'-','#','#','-'},
    {'-','-','-','-'}
};

char form4[4][4] = {
    {'-','-','-','-'},
    {'#','-','-','-'},
    {'#','#','#','-'},
    {'-','-','-','-'}
};

char form5[4][4] = {
    {'-','-','-','-'},
    {'-','-','#','-'},
    {'#','#','#','-'},
    {'-','-','-','-'}
};

char form6[4][4] = {
    {'-','-','-','-'},
    {'-','#','#','-'},
    {'#','#','-','-'},
    {'-','-','-','-'}
};

char form7[4][4] = {
    {'-','-','-','-'},
    {'#','#','-','-'},
    {'-','#','#','-'},
    {'-','-','-','-'}

};

// Entities
std::vector<Entity*> entities;
std::vector<Bloc*> blocs;
std::vector<sf::Text> ui;

// Textures
sf::Texture bgTxt;
sf::Texture blockTxt[7];
sf::Font font;

// Controllers
Grid plateau;
BlocGroup* currentBlock;
BlocGroup* nextBlock;
bool locked = false;
bool _pressed = false;

int Load() 
{
    
    if (!font.loadFromFile("Textures/FreePixel.ttf"))
    {
        return 0;
    }
    if (!bgTxt.loadFromFile("Textures/background.png", sf::IntRect(0, 0, 80, 160)))
    {
        return 0;
    }
    if (!blockTxt[0].loadFromFile("Textures/square_blue.png", sf::IntRect(0, 0, 8, 8)))
    {
        return 0;
    }
    if (!blockTxt[1].loadFromFile("Textures/square_darkblue.png", sf::IntRect(0, 0, 8, 8)))
    {
        return 0;
    }
    if (!blockTxt[2].loadFromFile("Textures/square_green.png", sf::IntRect(0, 0, 8, 8)))
    {
        return 0;
    }
    if (!blockTxt[3].loadFromFile("Textures/square_purpple.png", sf::IntRect(0, 0, 8, 8)))
    {
        return 0;
    }
    if (!blockTxt[4].loadFromFile("Textures/square_yellow.png", sf::IntRect(0, 0, 8, 8)))
    {
        return 0;
    }
    if (!blockTxt[5].loadFromFile("Textures/square_red.png", sf::IntRect(0, 0, 8, 8)))
    {
        return 0;
    }
    if (!blockTxt[6].loadFromFile("Textures/square_orange.png", sf::IntRect(0, 0, 8, 8)))
    {
        return 0;
    }
    return 1;
}

void eventUpdate(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (locked) return;

        if (event.type == sf::Event::KeyPressed)
        {
            //std::cout << "Click\n";
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (!_pressed && currentBlock->CanMove(plateau, sf::Vector2f(-1, 0)) ) {
                currentBlock->Move(sf::Vector2f(-1, 0));
                _pressed = true;
            }

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (!_pressed && currentBlock->CanMove(plateau, sf::Vector2f(1, 0))) {
                currentBlock->Move(sf::Vector2f(1, 0));
                _pressed = true;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if ( currentBlock->CanMove(plateau, sf::Vector2f(0, 1))) {
                currentBlock->Move(sf::Vector2f(0, 1));
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (!_pressed && currentBlock->Rorate(plateau) ) {
                _pressed = true;
            }
        }
        else
        {
            _pressed = false;
        }
    }
}

bool removeAllFromY(int y)
{
    for (int i = 0; i < blocs.size(); i++) {
        if (blocs[i]->GridY() == y && blocs[i]->GridX() < GRID_WIDTH) {
            blocs.erase(blocs.begin()+i);
            return true;
        }
    }
    return false;
}

void downAllUpperThanY(int y)
{
    for (int i = 0; i < blocs.size(); i++) {
        if (blocs[i]->GridY() < y && blocs[i]->GridX() < GRID_WIDTH) {
            blocs[i]->Move(sf::Vector2f(0,1));
        }
    }
}

BlocGroup* initNewBloc(int formIdx)
{
    BlocGroup* forme = new BlocGroup();
    std::vector<Bloc*> blocsTmp;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if ((formIdx == 0 && form2[j][i] == '#') || // bar en / bleu clair
                (formIdx == 1 && form4[j][i] == '#') || 
                (formIdx == 2 && form5[j][i] == '#') ||
                (formIdx == 3 && form1[j][i] == '#') || // haut du T / en violet
                (formIdx == 4 && form3[j][i] == '#') || // bloc / en jaune
                (formIdx == 5 && form6[j][i] == '#') ||
                (formIdx == 6 && form7[j][i] == '#') 
                )
            {
                blocs.push_back(new Bloc());
                blocs[blocs.size() - 1]->worldX = (GRID_WIDTH/2)-1;
                blocs[blocs.size() - 1]->worldY = -4;

                blocs[blocs.size() - 1]->localX = i;
                blocs[blocs.size() - 1]->localY = j;

                //std::cout << "LocalX : " + std::to_string(i) << "\n";
                //std::cout << "LocalY : " + std::to_string(j) << "\n\n";

                blocsTmp.push_back(blocs[blocs.size() - 1]);
            }
        }
    }

    forme->Initialize(blockTxt[formIdx], blocsTmp);
    forme->worldX = (GRID_WIDTH / 2)-1;
    forme->worldY = -4;

    forme->size = 3;
    if (formIdx == 4) forme->size = 2;
    if (formIdx == 0) forme->size = 4;

    return forme;
}

void NextGroupShow()
{
    nextBlock = initNewBloc(rand() % 7);
    nextBlock->Move(sf::Vector2f(8.5, 7));
}

void SwitchNext()
{
    currentBlock = nextBlock;
    currentBlock->Move(sf::Vector2f(-8.5, -7));
    NextGroupShow();
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(80*6+120, 160*5), "Tetris");

    if (!Load()) return 1;

    srand(time(NULL));

    bool finished = false;
    int score = 0;

    sf::Text text1;
    text1.setFont(font);
    text1.setString("Score : ");
    text1.setCharacterSize(24);
    text1.setPosition(80 * 4 + 70, 160*3);
    ui.push_back(text1);

    sf::Text text2;
    text2.setFont(font);
    text2.setString(std::to_string(score));
    text2.setCharacterSize(24);
    text2.setPosition(80 * 4 + 70, 160 * 3 + 24);
    
    sf::Text text3;
    text3.setFont(font);
    text3.setString("Prochaine piece :");
    text3.setCharacterSize(24);
    text3.setPosition(80 * 4 + 70, 32);
    ui.push_back(text3);
    
    /*
    sf::Text text4;
    text4.setFont(font);
    text4.setString("Piece stockee :");
    text4.setCharacterSize(24);
    text4.setPosition(80 * 4 + 70, 260);
    ui.push_back(text4);
    */

    ui.push_back(text2);

    // Background -----------------------
    Entity background;
    background.Initialize(bgTxt);

    background.scale = sf::Vector2f(4.8f, 5);
    background.position = sf::Vector2f(0, 0);

    entities.push_back(&background);
    
    NextGroupShow();
    SwitchNext();

    // Game Loop
    sf::Clock clock;
    float timeSum = 0;
    float speed = 0.3f;
    while (window.isOpen())
    {
        eventUpdate(window);

        if (finished)
        {
            
            if (entities.size() > 0) entities.clear();
            if (blocs.size() > 0) blocs.clear();

            // Black Screen ---------------------
            sf::RectangleShape rectangle(sf::Vector2f(0, 0));
            rectangle.setSize(sf::Vector2f(80 * 6 + 120, 160 * 5));
            rectangle.setFillColor(sf::Color(255, 255, 255));
            ui[2].setString(std::to_string(score));

            sf::Text text;
            text.setFont(font);
            text.setString("GAME OVER");
            text.setCharacterSize(54);
            text.setPosition(20, 60);
            ui[1] = text;
            
        }
        else
        {
            timeSum += clock.restart().asSeconds();
            if (timeSum >= speed) {
                timeSum -= speed;
                if (!currentBlock->UpdateStep(plateau))
                {
                    //std::cout << "FIXED\n\n";
                    if (plateau.isEnd(currentBlock->GetBlocs()))
                    {
                        finished = true;
                    }
                    else
                    {
                        locked = true;
                        plateau.Fix(currentBlock->GetBlocs());

                        // Controle des lignes
                        int lineY = plateau.HasLine();
                        while (lineY != -1)
                        {
                            // Suppresion de la ligne lignes
                            while (removeAllFromY(lineY))
                            {
                                score += 10;
                            }
                            // Decentes des blocs
                            downAllUpperThanY(lineY);

                            // Update grille
                            plateau.UpdateGrid(blocs);

                            // Reverification des lignes
                            lineY = plateau.HasLine();

                        }
                        SwitchNext();
                        locked = false;
                    }

                }


            }
        }
        

            window.clear();

                // Entities
                for (int i = 0; i < entities.size(); i++) {
                    entities[i]->Draw(window);
                }

                // Blocs
                for (int i = 0; i < blocs.size(); i++) {
                    blocs[i]->GetEntity().Draw(window);
                }
            

                // UI
                ui[2].setString(std::to_string(score));
                for (int i = 0; i < ui.size(); i++) {
                    window.draw(ui[i]);
                }

            window.display();

        
    }

    return 0;
}
    