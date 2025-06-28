#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
using namespace sf;

struct point
{
    int x;
    int y;
};


int main()
{
    srand(time(0));

    RenderWindow app(sf::VideoMode({540, 540}), "Goblin Game!");
    app.setFramerateLimit(60);

    Texture tx_player, tx_bg, tx_plat;

    if (!tx_player.loadFromFile("assets/goblin.png")) {
        return -1;
    }
    if (!tx_bg.loadFromFile("assets/background_1.png")) {
        return -1;
    }
    if (!tx_plat.loadFromFile("assets/platform_1.png")) {
        printf("deu ruim");
        return -1;
    }

    Sprite sBackground(tx_bg), sPlatform(tx_plat), sPlayer(tx_player);
    
    sBackground.setScale(Vector2f(3.0 , 3.0));

    // Platform Creator
    point plat[20];
    for (int i = 0; i < 10; i++) {
        plat[i].x = rand()%540;
        plat[i].y = rand()%540;
    }

    // Player Coords and Direction Vector
    int x = 100, y = 540, h = 200;
    float dir_x = 0, dir_y = 0;

    // Game Loop: Renderize sprites,
    while (app.isOpen()) {
        while (const std::optional event = app.pollEvent())
        {
            if (event->is<Event::Closed>())
                app.close();
        }

        // Keyboard Capture: Move to right n left
        if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
            x+=3;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
            x-=3;
        }

        // CAMERA
        if (y < h) {
            for (int i = 0; i < 10; i++) {
                y = h;
                plat[i].y = plat[i].y - dir_y;
                if (plat[i].y > 540) {
                    plat[i].y = 0;
                    plat[i].x = rand()%540;
                }
            }
        }

        // JUMP: Automatically
        dir_y += 0.2f;
        y += dir_y;
        if (y > 500) {
            dir_y = -10;
        }

        // COLLISION - Player 48x48, Plataforma 69x22
        for (int i = 0; i < 10; i++) {
            if ((x + 48 > plat[i].x) &&           // Borda direita do player > borda esquerda da plataforma
                (x < plat[i].x + 69) &&           // Borda esquerda do player < borda direita da plataforma
                (y + 48 >= plat[i].y) &&          // Base do player chegou ao topo da plataforma
                (y + 48 <= plat[i].y + 5) &&      // Base do player próxima ao topo (margem de tolerância)
                (dir_y > 0)                       // Player está caindo
            ) {
                dir_y = -10;                      // Pular
                y = plat[i].y - 48;               // Posicionar player exatamente em cima da plataforma
            }
        }

        sPlayer.setPosition(Vector2f(x, y));

        app.draw(sBackground);
        app.draw(sPlayer);

        for (int i = 0; i < 10; i++) {
            sPlatform.setPosition(Vector2f(static_cast<float>(plat[i].x), static_cast<float>(plat[i].y)));
            app.draw(sPlatform);
        }

        app.display();
    }
    
    return 0;
}