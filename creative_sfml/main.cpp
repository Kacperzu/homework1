#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // create some shapes
    sf::CircleShape circle(50.0);
    circle.setPosition(100.0, 300.0);
    circle.setFillColor(sf::Color(100, 250, 50));

    sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
    rectangle.setPosition(500.0, 400.0);
    rectangle.setFillColor(sf::Color(100, 50, 250));

    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0.0, 0.0));
    triangle.setPoint(1, sf::Vector2f(0.0, 100.0));
    triangle.setPoint(2, sf::Vector2f(140.0, 40.0));
    triangle.setOutlineColor(sf::Color::Red);
    triangle.setOutlineThickness(2);
    triangle.setPosition(600.0, 100.0);
    sf::Clock clock;

    int rectangle_velocity_x = 50;
    int rectangle_velocity_y = 200;
    int rectangle_angular_velocity = 20;

    int triangle_velocity_x = 50;
    int triangle_velocity_y = 200;
    int triangle_angular_velocity = 20;
    int circle_velocity_x = 50;
    int circle_velocity_y = 200;
    int circle_angular_velocity = 20;



    bool flag_y = false;
    bool flag_x = false;


    // run the program as long as the window is open
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();


        sf::FloatRect rectangle_bounds = rectangle.getGlobalBounds();

       if(rectangle_bounds.top <= 0){
           rectangle_velocity_y = abs(rectangle_velocity_y);
           rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
       }

       if(rectangle_bounds.top + rectangle_bounds.height >= window.getSize().y){
           rectangle_velocity_y = abs(rectangle_velocity_y) * -1;
           rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
       }

       if(rectangle_bounds.left <= 0 ){
          rectangle_velocity_x = abs(rectangle_velocity_x);
          rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
       }

       if(rectangle_bounds.left + rectangle_bounds.width >= window.getSize().x){
           rectangle_velocity_x = abs(rectangle_velocity_x) * -1;
           rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
       }

        rectangle.move(rectangle_velocity_x*dt,rectangle_velocity_y*dt);


        //triangle
       sf::FloatRect triangle_bounds = triangle.getGlobalBounds();

       if(triangle_bounds.top <= 0)
       {
           triangle_velocity_y = abs(triangle_velocity_y);
           triangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
           triangle.setOutlineThickness(rand()% 10);
       }

       if(triangle_bounds.top + triangle_bounds.height >= window.getSize().y)
       {
           triangle_velocity_y = abs(triangle_velocity_y) * -1;
           triangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
           triangle.setOutlineThickness(rand()% 10);
       }

       if(triangle_bounds.left + triangle_bounds.width >= window.getSize().x){
           triangle_velocity_x = abs(triangle_velocity_x) * -1;
           triangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
           triangle.setOutlineThickness(rand()% 10);
       }

       if(triangle_bounds.left <= 0 )
       {
           triangle_velocity_x = abs(triangle_velocity_x);
           triangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
           triangle.setOutlineThickness(rand()% 10);
       }
        triangle.move(triangle_velocity_x*dt,triangle_velocity_y*dt);




       // kolo
        sf::FloatRect circle_bounds = circle.getGlobalBounds();


        if(circle_bounds.top <= 0)
        {
            circle_velocity_y = abs(circle_velocity_y);
            circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            circle.setOutlineThickness(rand()% 10);
        }

        if(circle_bounds.top + circle_bounds.height >= window.getSize().y)
        {
            circle_velocity_y = abs(circle_velocity_y) * -1;
            circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            circle.setOutlineThickness(rand()% 10);
        }

        if(circle_bounds.left + circle_bounds.width >= window.getSize().x){
            circle_velocity_x = abs(circle_velocity_x) * -1;
            circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            circle.setOutlineThickness(rand()% 10);
        }

        if(circle_bounds.left <= 0 )
        {
            circle_velocity_x = abs(circle_velocity_x);
            circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            circle.setOutlineThickness(rand()% 10);
        }
         circle.move(circle_velocity_x*dt,circle_velocity_y*dt);





        if (rectangle_bounds.intersects(triangle_bounds))
        {
        // Collision detected!
            rectangle.rotate(0);
            triangle.rotate(0);

            triangle.setPosition(rand ()%800 - triangle_bounds.width, rand()%600 - triangle_bounds.height);
            rectangle.setPosition(rand ()%800 - rectangle_bounds.width, rand()%600 - rectangle_bounds.height);

            rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            rectangle.setOutlineThickness(rand()% 10);

            triangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            triangle.setOutlineThickness(rand()% 10);
            float random_size = rand() / (RAND_MAX / (1.5 - 0.1)) + 0.1;
            float random_size2 = rand() / (RAND_MAX / (1.5 - 0.5)) + 0.5;
            rectangle.setScale(sf::Vector2f(random_size,random_size2));
            triangle.setScale(sf::Vector2f(random_size,random_size2));
          }


        if (rectangle_bounds.intersects(circle_bounds))
        {
        // Collision detected!
            rectangle.rotate(0);
            circle.rotate(0);

            circle.setPosition(rand ()%800 - circle_bounds.width, rand()%600 - circle_bounds.height);
            rectangle.setPosition(rand ()%800 - rectangle_bounds.width, rand()%600 - rectangle_bounds.height);

            circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            rectangle.setOutlineThickness(rand()% 10);

            circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            circle.setOutlineThickness(rand()% 10);
            float random_size = rand() / (RAND_MAX / (1.5 - 0.1)) + 0.1;
            float random_size2 = rand() / (RAND_MAX / (1.5 - 0.5)) + 0.5;
            rectangle.setScale(sf::Vector2f(random_size,random_size2));
            circle.setScale(sf::Vector2f(random_size,random_size2));
          }



        if (triangle_bounds.intersects(circle_bounds))
        {
        // Collision detected!
            triangle.rotate(0);
            circle.rotate(0);

            circle.setPosition(rand ()%800 - circle_bounds.width, rand()%600 - circle_bounds.height);
            triangle.setPosition(rand ()%800 - triangle_bounds.width, rand()%600 - triangle_bounds.height);

            circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            triangle.setOutlineThickness(rand()% 10);

            circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            circle.setOutlineThickness(rand()% 10);
            float random_size = rand() / (RAND_MAX / (1.5 - 0.1)) + 0.1;
            float random_size2 = rand() / (RAND_MAX / (1.5 - 0.5)) + 0.5;
            triangle.setScale(sf::Vector2f(random_size,random_size2));
            circle.setScale(sf::Vector2f(random_size,random_size2));
          }




            triangle.rotate(triangle_angular_velocity*dt);
            rectangle.rotate(rectangle_angular_velocity*dt);
            circle.rotate(circle_angular_velocity*dt);




        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(circle);
        window.draw(rectangle);
        window.draw(triangle);

        // end the current frame
        window.display();
    }

    return 0;
}
