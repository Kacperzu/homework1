#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class CustomRectangleShape : public sf::RectangleShape {
public:
    CustomRectangleShape(const sf::Vector2f &size, const sf::Vector2f &position) : sf::RectangleShape(size)
    {
        setPosition(position);
    }

    void setSpeed(const int& x_speed, const int& y_speed, const int & ro_speed) {
        x_speed_ = x_speed;
        y_speed_ = y_speed;
        ro_speed_ = ro_speed;
    }

    void animate(const sf::Time &elapsed){
        bouncce();
        float dt = elapsed.asSeconds();
        move(x_speed_*dt,y_speed_*dt);
        rotate(ro_speed_*dt);
    }

    void setBounds(const float& l_bound, const float& r_bound,const float& u_bound,const float& d_bound){
        l_bound_  = l_bound  ;
        r_bound_  = r_bound  ;
        u_bound_  = u_bound  ;
        d_bound_  = d_bound  ;
    }

private:
    int x_speed_ = 0 ;
    int y_speed_ = 0 ;
    int ro_speed_ = 0 ;
    float l_bound_ = 0;
    float r_bound_ = 0;
    float u_bound_ = 0;
    float d_bound_ = 0;


    void bouncce(){
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(rectangle_bounds.top <= u_bound_){
            y_speed_ = abs(y_speed_);
        }

        if(rectangle_bounds.top + rectangle_bounds.height >= d_bound_){
            y_speed_ = abs(y_speed_) * -1;
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds.left <= l_bound_ ){
           x_speed_ = abs(x_speed_);
           setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds.left + rectangle_bounds.width >= r_bound_){
            x_speed_ = abs(x_speed_) * -1;
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }
    }


};





int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");



    sf::Vector2f size(120.0, 60.0);
    sf::Vector2f position(120.0, 60.0);
    CustomRectangleShape rectangle_inh(size, position);
    rectangle_inh.setFillColor(sf::Color(150, 100, 50));
    rectangle_inh.setSpeed(100, 150, 10);


    // create some shapes
    sf::CircleShape circle(50.0);
    circle.setPosition(100.0, 300.0);
    circle.setFillColor(sf::Color(100, 250, 50));
    bool is_circle_clicked = false;

    sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
    rectangle.setPosition(500.0, 400.0);
    rectangle.setFillColor(sf::Color(100, 50, 250));
    bool is_triangle_clicked = false;

    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0.0, 0.0));
    triangle.setPoint(1, sf::Vector2f(0.0, 100.0));
    triangle.setPoint(2, sf::Vector2f(140.0, 40.0));
    triangle.setOutlineColor(sf::Color::Red);
    triangle.setOutlineThickness(2);
    triangle.setPosition(600.0, 100.0);
    sf::Clock clock;

    int rectangle_velocity_x = 5;
    int rectangle_velocity_y = 15;
    int rectangle_angular_velocity = 10;

    bool flag_y = false;
    bool flag_x = false;


    // run the program as long as the window is open
    while (window.isOpen()) {



        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        rectangle.move(rectangle_velocity_x*dt,rectangle_velocity_y*dt);
        rectangle.rotate(rectangle_angular_velocity*dt);

//        rectangle_inh.animate(elapsed);



        rectangle_inh.setBounds(0, window.getSize().x, 0, window.getSize().y);

        sf::FloatRect rectangle_bounds = rectangle.getGlobalBounds();
//        std::cout << rectangle_bounds.top << " " << rectangle_bounds.left << " " ;
//        std::cout << rectangle_bounds.width << " " << rectangle_bounds.height << std::endl;









        if(rectangle_bounds.top<=0 || rectangle_bounds.top+rectangle_bounds.height>=window.getSize().y)
            {
                if(flag_y != true)
                {
                    rectangle_velocity_y *= -1;
                    rectangle.setFillColor(sf::Color(rand() % 256,
                                                     rand() % 256,
                                                     rand() % 256));
                }
                flag_y = true;
            }
            else
                flag_y = false;



            if(rectangle_bounds.left<=0 || rectangle_bounds.left+rectangle_bounds.width>=window.getSize().x)
            {
                if(flag_x!=true)
                {
                    rectangle_velocity_x *= -1;
                    rectangle.setFillColor(sf::Color(rand() % 256,
                                                     rand() % 256,
                                                     rand() % 256));
                }
                flag_x = true;
            }
            else
                flag_x = false;


            sf::FloatRect circle_bounds = circle.getGlobalBounds();

            if(circle_bounds.left<=0 || circle_bounds.left+circle_bounds.width>=window.getSize().x)
            {
                circle.setPosition(100.0, 300.0);
            }
            if(circle_bounds.top<=0 || circle_bounds.top+circle_bounds.height>=window.getSize().y)
            {
                circle.setPosition(100.0, 300.0);
            }



            sf::FloatRect triangle_bounded = triangle.getGlobalBounds();
            if(triangle_bounded.left<=0 || triangle_bounded.left+triangle_bounded.width>=window.getSize().x)
            {
                triangle.setPosition(600.0, 100.0);
            }
            if(triangle_bounded.top<=0 || triangle_bounded.top+triangle_bounded.height>=window.getSize().y)
            {
                triangle.setPosition(600.0, 100.0);
            }









        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::Space)
                {


                    std::cout << "Space released" << std::endl;
                }
            }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    rectangle_inh.animate(elapsed);
                }


        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && circle.getGlobalBounds().contains(worldPosition))
        {
             is_circle_clicked = true;
        }
        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !circle.getGlobalBounds().contains(worldPosition))
        {
            is_circle_clicked = false;
        }

        if (is_circle_clicked)
       {
            int circle_speed_key_x = 1000 ;
            int circle_speed_key_y = 1000 ;
           if (event.key.code == sf::Keyboard::Left)
           {
               circle.move(-1*(circle_speed_key_x)*dt, 0);
           }
           else if (event.key.code == sf::Keyboard::Right)
           {
               circle.move(circle_speed_key_x*dt, 0);
           }
           else if (event.key.code == sf::Keyboard::Up)
           {
               circle.move(0, -1*circle_speed_key_y*dt);
           }
           else if (event.key.code == sf::Keyboard::Down)
           {
               circle.move(0, (circle_speed_key_y)*dt);
           }
        }

        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && triangle.getGlobalBounds().contains(worldPosition))
        {
             is_triangle_clicked = true;
        }
        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !triangle.getGlobalBounds().contains(worldPosition))
        {
            is_triangle_clicked = false;
        }

        if (is_triangle_clicked)
       {
            int triangle_speed_key_x = 1000 ;
            int triangle_speed_key_y = 1000 ;
           if (event.key.code == sf::Keyboard::Left)
           {
               triangle.move(-1*(triangle_speed_key_x)*dt, 0);
           }
           else if (event.key.code == sf::Keyboard::Right)
           {
               triangle.move(triangle_speed_key_x*dt, 0);
           }
           else if (event.key.code == sf::Keyboard::Up)
           {
               triangle.move(0, -1*triangle_speed_key_y*dt);
           }
           else if (event.key.code == sf::Keyboard::Down)
           {
               triangle.move(0, (triangle_speed_key_y)*dt);
           }
        }























        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(circle);
        window.draw(rectangle);
        window.draw(triangle);
        window.draw(rectangle_inh);

        // end the current frame
        window.display();
    }

    return 0;
}
