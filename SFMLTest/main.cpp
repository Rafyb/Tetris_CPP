#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
#include "Entity.h"
#include "Bloc.h"
#include "main.h"
#include "Grid.h"

// Entities
std::vector<Entity*> entities;
std::vector<Bloc*> blocs;
std::vector<sf::Text> ui;

// Textures
sf::Texture bgTxt;
sf::Texture blockTxt[6];
sf::Font font;

// Controllers
Grid plateau;
Bloc* currentBlock;
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
    return 1;
}

void eventUpdate(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
            std::cout << "Click\n";

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (!_pressed && plateau.CanMove(currentBlock->gridX - 1, currentBlock->gridY)) {
                currentBlock->Move(sf::Vector2f(-1, 0));
                _pressed = true;
            }

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (!_pressed && plateau.CanMove(currentBlock->gridX + 1, currentBlock->gridY)) {
                currentBlock->Move(sf::Vector2f(1, 0));
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
        if (blocs[i]->gridY == y) {
            blocs.erase(blocs.begin()+i);
            return true;
        }
    }
    return false;
}

void downAllUpperThanY(int y)
{
    for (int i = 0; i < blocs.size(); i++) {
        if (blocs[i]->gridY > y) {
            blocs[i]->Move(sf::Vector2f(0,1));
        }
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(80*6+120, 160*5), "Tetris");

    if (!Load()) return 1;

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
    ui.push_back(text2);
    sf::Text text3;
    text3.setFont(font);
    text3.setString("Prochaine piece :");
    text3.setCharacterSize(24);
    text3.setPosition(80 * 4 + 70, 32);
    ui.push_back(text3);
    sf::Text text4;
    text4.setFont(font);
    text4.setString("Piece stockee :");
    text4.setCharacterSize(24);
    text4.setPosition(80 * 4 + 70, 260);
    ui.push_back(text4);
    //text.setColor(sf::Color::White);
   // text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // Background -----------------------
    Entity background;
    background.Initialize(bgTxt);

    background.scale = sf::Vector2f(4.8f, 5);
    background.position = sf::Vector2f(0, 0);

    entities.push_back(&background);
    
    // Plateau de jeu -------------------
    plateau.Initialize(blockTxt);
    
    blocs.push_back(plateau.InstantiateBloc());
    currentBlock = blocs[blocs.size()-1];
    //entities.push_back(&(currentBlock->GetEntity()));
    

    // Game Loop
    sf::Clock clock;
    float timeSum = 0;
    float speed = 0.3f;
    while (window.isOpen())
    {
        eventUpdate(window);

        timeSum += clock.restart().asSeconds();
        if (timeSum >= speed) {
            timeSum -= speed;
            if(plateau.CanMove(currentBlock->gridX, currentBlock->gridY+1)) currentBlock->UpdateStep();
            else {
                plateau.Fix(*currentBlock);

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

                blocs.push_back(plateau.InstantiateBloc());
                currentBlock = blocs[blocs.size()-1];
                //entities.push_back(&(currentBlock->GetEntity()));


            }
        }

        window.clear();

        // Entities
        for (int i = 0; i < entities.size(); i++) {
            entities[i]->Draw(window);
        }
        // Entities
        for (int i = 0; i < blocs.size(); i++) {
            blocs[i]->GetEntity().Draw(window);
        }
        // UI
        ui[1].setString(std::to_string(score));
        for (int i = 0; i < ui.size(); i++) {
            window.draw(ui[i]);
        }
        
        window.display();
    }

    return 0;
}
    