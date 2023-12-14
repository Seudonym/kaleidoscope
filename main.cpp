#include <stdio.h>
#include <mpfr.h>
#include <iostream>
#include <thread>

#include <SFML/Graphics.hpp>

#include <Globals.hpp>
#include <Mandelbrot.hpp>

int main(int argc, char **argv) {
    Mandelbrot mandelbrot;

    sf::RenderWindow window(sf::VideoMode(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT), "Mandelbrot");
    sf::Sprite sprite;
    sf::Texture texture;
    texture.create(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT);

    mpfr_inits(Globals::x, Globals::y, Globals::zoom, Globals::stride, (mpfr_ptr)0);
    mpfr_set_flt(Globals::x, 0.0, MPFR_RNDN);
    mpfr_set_flt(Globals::y, 0.0, MPFR_RNDN);
    mpfr_set_flt(Globals::zoom, 1.0, MPFR_RNDN);
    mpfr_set_flt(Globals::stride, 0.01, MPFR_RNDN);

    // Get max num of threads
    Globals::NUM_THREADS = std::thread::hardware_concurrency();
    DEBUG_LOG("Max num of threads: " << Globals::NUM_THREADS)

    // Measure frames
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q) {
                    mpfr_div_d(Globals::zoom, Globals::zoom, 1.01, MPFR_RNDN);
                    mpfr_d_div(Globals::stride, 0.01, Globals::zoom, MPFR_RNDN);
                }
                if (event.key.code == sf::Keyboard::E) {
                    mpfr_mul_d(Globals::zoom, Globals::zoom, 1.01, MPFR_RNDN);
                    mpfr_d_div(Globals::stride, 0.01, Globals::zoom, MPFR_RNDN);
                }
                if (event.key.code == sf::Keyboard::W) {
                    mpfr_sub(Globals::y, Globals::y, Globals::stride, MPFR_RNDN);
                }
                if (event.key.code == sf::Keyboard::S) {
                    mpfr_add(Globals::y, Globals::y, Globals::stride, MPFR_RNDN);
                }
                if (event.key.code == sf::Keyboard::A) {
                    mpfr_sub(Globals::x, Globals::x, Globals::stride, MPFR_RNDN);
                }
                if (event.key.code == sf::Keyboard::D) {
                    mpfr_add(Globals::x, Globals::x, Globals::stride, MPFR_RNDN);
                }
                if (event.key.code == sf::Keyboard::P) {
                    // Print globals
                    mpfr_printf("x: %.128Rf\n", Globals::x);
                    mpfr_printf("y: %.128Rf\n", Globals::y);
                    mpfr_printf("zoom: %.128Rf\n", Globals::zoom);
                }
            }
        }

        float time = clock.getElapsedTime().asMilliseconds();
        clock.restart();
        DEBUG_LOG("Frame time: " << time << "ms");
        DEBUG_LOG("\rFPS: " << 1000.0 / time);

        mandelbrot.render();
        texture.update(mandelbrot.getPixels(), Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, 0, 0);
        sprite.setTexture(texture);
        window.draw(sprite);
        window.display();
    }
}
