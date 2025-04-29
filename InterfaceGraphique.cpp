#include "InterfaceGraphique.h"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include "logger.h"

void SFMLSimulation(void) {
    unsigned int width = 1600;
    unsigned int height = 900;
    sf::RenderWindow window(sf::VideoMode({ width, height }), "Ascenseur SFML");
    window.setFramerateLimit(60);

    sf::Font font;
    std::string fontPath = "../dependances_exterieurs/fonts/Roboto-BlackItalic.ttf";


    if (!std::filesystem::exists(fontPath)) {
        std::cerr << "Le fichier " << fontPath << " nexiste pas!" << std::endl;
    }
    else {
        std::cout << "Le fichier " << fontPath << " existe!" << std::endl;
        if (!font.openFromFile(fontPath)) {
            std::cerr << "Erreur lors du chargement de la police!" << std::endl;
        }
        else {
            std::cout << "Police chargee avec succes!" << std::endl;
        }
    }

    //fenetre help
    sf::RectangleShape helpBox(sf::Vector2f(400, 200));
    helpBox.setFillColor(sf::Color(0, 0, 0, 150)); // Noir transparent
    helpBox.setPosition({ 50.f, 20.f });

    sf::Text helpText(font);
    helpText.setCharacterSize(18);
    helpText.setFillColor(sf::Color::White);
    helpText.setString("Touches :\n[H] - Aide\n[Up] - Monter\n[Down] - Descendre\n[Esc] - Quitter");
    helpText.setPosition({ 70.f, 40.f });

    bool showHelp = false; // Variable pour gérer l'affichage de l'aide

    // Moteur (Poulie)
    sf::CircleShape moteur(120.f);
    moteur.setOrigin({ 120.f, 120.f });
    moteur.setPosition({ 800.f, 200.f });
    moteur.setFillColor(sf::Color::White);
    moteur.setOutlineThickness(3);
    moteur.setOutlineColor(sf::Color::Black);

    // Cabine
    sf::RectangleShape cabine({ 120.f,160.f });
    cabine.setOrigin({ 60.f, 80.f });
    cabine.setPosition({ 920.f, 800.f }); // Position initiale
    cabine.setFillColor(sf::Color::White);
    cabine.setOutlineThickness(3);
    cabine.setOutlineColor(sf::Color::Black);

    // Contrepoids
    sf::RectangleShape contrepoids({ 80.f, 140.f });
    contrepoids.setOrigin({ 40.f, 70.f });
    contrepoids.setPosition({ 680.f, 400.f }); // Position initiale
    contrepoids.setFillColor(sf::Color::White);
    contrepoids.setOutlineThickness(3);
    contrepoids.setOutlineColor(sf::Color::Black);

    // Câbles
    sf::RectangleShape cable1({ 3.f, 520.f }); // Câble cabine ? Poulie
    cable1.setOrigin({ 1.5f, 0.f });
    cable1.setPosition({ 921.f, 200.f });
    cable1.setFillColor(sf::Color::Black);

    sf::RectangleShape cable2({ 3.f, 150.f }); // Câble contrepoids ? Poulie
    cable2.setOrigin({ 1.5f, 0.f });
    cable2.setPosition({ 680.f, 200.f });
    cable2.setFillColor(sf::Color::Black);

    // Limites
    const float LIMITE_HAUT = 400.f;  // Ne pas dépasser la poulie
    const float LIMITE_BAS = 800.f;   // Niveau du sol
    float vitesse = 5.0f; // Vitesse de déplacement

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return;
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                    return;
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::H) {
                    showHelp = !showHelp; // Toggle affichage aide
                }
            }
        }

        // Mouvement de la cabine et du contrepoids
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) { // Monte
            if (cabine.getPosition().y > LIMITE_HAUT) {
                cabine.move({ 0.f, -vitesse });
                contrepoids.move({ 0.f, vitesse });
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) { // Descend
            if (cabine.getPosition().y < LIMITE_BAS) { // Vérification de la limite basse
                cabine.move({ 0.f, vitesse });
                contrepoids.move({ 0.f, -vitesse });
            }
        }

        // Mise à jour des câbles pour suivre les mouvements
        cable1.setSize({ 3.f, cabine.getPosition().y - 200.f });
        cable1.setPosition({ 921.f, 200.f });

        cable2.setSize({ 3.f, contrepoids.getPosition().y - 200.f });
        cable2.setPosition({ 680.f, 200.f });

        // Affichage
        window.clear(sf::Color::White);
        window.draw(moteur);
        window.draw(cable1);
        window.draw(cable2);
        window.draw(cabine);
        window.draw(contrepoids);


        if (showHelp) {
            window.draw(helpBox);
            window.draw(helpText);
        }
        window.display();
    }
}
