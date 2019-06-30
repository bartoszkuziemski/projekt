#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <cstdlib>

class Czlowiek
{
public:
    Czlowiek()
    {
       czlowiek_.setSize(sf::Vector2f(50,100));
       czlowiek_.setFillColor(sf::Color::Cyan);

       lufa_.setSize(sf::Vector2f(70,20));
       lufa_.setFillColor(sf::Color::Blue);
       lufa_.setOrigin(70,10);
    }
    sf::RectangleShape czlowiek()
    {
        return czlowiek_;
    }
    sf::RectangleShape lufa()
    {
        return lufa_;
    }
    void draw(sf::RenderWindow &w)
    {
        w.draw(czlowiek_);
        w.draw(lufa_);
    }
    void set_position(float x, float y)
    {
        czlowiek_.setPosition(x,y);
        lufa_.setPosition(x+20,y+50);
    }

/*
    void step(float time)
    {
        sf::FloatRect bounds = czlowiek_.getGlobalBounds();
        float rotation = lufa_.getRotation();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rotation>0.5)
        {
            lufa_.rotate(-velocity_obr_*time);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rotation<180)
        {
            lufa_.rotate(velocity_obr_*time);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && bounds.left>0)
        {
            czlowiek_.move(-velocity_x_*time,0);
            lufa_.move(-velocity_x_*time,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && bounds.left+bounds.width<1400)
        {
            czlowiek_.move(velocity_x_*time,0);
            lufa_.move(velocity_x_*time,0);
        }
    }
*/

    void step(float time, sf::Vector2i mouse_position)
    {
        sf::FloatRect bounds = czlowiek_.getGlobalBounds();
        float rotation = lufa_.getRotation();
        sf::Vector2f lufa_position = lufa().getPosition();
        float x=lufa_position.x-mouse_position.x;
        float y=lufa_position.y-mouse_position.y;
        float angle;
        if(x>0)
        {
            angle=180/3.14*atan(y/x);
        }
        if(x<0)
        {
            angle=(180/3.14*atan(y/x))+180;
        }
        //std::cout << angle << std::endl;



        lufa_.setRotation(angle);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && bounds.left>0)
        {
            czlowiek_.move(-velocity_x_*time,0);
            lufa_.move(-velocity_x_*time,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && bounds.left+bounds.width<1400)
        {
            czlowiek_.move(velocity_x_*time,0);
            lufa_.move(velocity_x_*time,0);
        }

    }    


private:
    sf::RectangleShape czlowiek_;
    sf::RectangleShape lufa_;
    float velocity_x_=200;
    float velocity_obr_=100;
    int pkt_=0;
};

class Pocisk
{
public:
    Pocisk()
    {
        pocisk_.setRadius(10);
        pocisk_.setFillColor(sf::Color::Yellow);
    }
    void draw(sf::RenderWindow &w)
    {
        w.draw(pocisk_);
    }
    void set_position(sf::Vector2f s)
    {
        s.y+=30;
        pocisk_.setPosition(s);
    }
    sf::CircleShape pocisk()
    {
        return pocisk_;
    }
    void set_velocity(float velocity_p)
    {
        velocity_pocisk_=velocity_p;
    }
    void set_angle_value_x(float angle_v_x)
    {
        angle_value_x_=angle_v_x;
    }
    void set_angle_value_y(float angle_v_y)
    {
        angle_value_y_=angle_v_y;
    }
    void set_velocity_y(float v)
    {
        velocity_y_=v;
    }
    void step(float time,float time_sin)
    {
        velocity_y_+=gravity_*time;
        velocity_x_=angle_value_x_*velocity_pocisk_;

        pocisk_.move(velocity_x_*time,velocity_y_*time);

        //std::cout << velocity_x_ << "    " << velocity_y_ << std::endl;
        //std::cout << time << std::endl;
        //std::cout << pocisk_.getPosition().y << std::endl;
        //std::cout << angle_value_x_ << "        " << angle_value_y_ << std::endl;
    }


private:
    sf::CircleShape pocisk_;
    float velocity_pocisk_=0;
    float gravity_=600;
    float angle_value_x_=0;
    float angle_value_y_=0;
    float velocity_x_=0;
    float velocity_y_=0;
};


class Ptak
{
public:
    Ptak(float velocity_x=300)
    {
        velocity_x_=velocity_x;
        ptak_.setRadius(20);
        ptak_.setFillColor(sf::Color::Magenta);
        float y=rand()%400+50;
        ptak_.setPosition(sf::Vector2f(20,y));
    }
    void draw(sf::RenderWindow &w)
    {
        w.draw(ptak_);
    }
    void set_position(sf::Vector2f s)
    {
        ptak_.setPosition(s);
    }
    sf::CircleShape ptak()
    {
        return ptak_;
    }
    void set_velocity_x(float velocity_x)
    {
        velocity_x_=velocity_x;
    }
    void set_velocity_y(float velocity_y)
    {
        velocity_y_=velocity_y;
    }
    void step(float time)
    {
        float change_velocity=rand() % 10000;      //prawdopodobienstwo ze predkosc sie zmieni
        if(change_velocity>9998)
        {
            velocity_y_=rand()%300-150;
        }
        ptak_.move(velocity_x_*time,velocity_y_*time);
    }
    bool hit(Pocisk p)
    {
        if(ptak_.getGlobalBounds().intersects(p.pocisk().getGlobalBounds()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
private:
    sf::CircleShape ptak_;
    float velocity_x_=0;
    float velocity_y_=0;
};

class Drzewo
{
public:
    Drzewo()
    {
        drzewo_.setSize(sf::Vector2f(400,500));
        drzewo_.setFillColor(sf::Color::Green);
    }
    void draw(sf::RenderWindow &w)
    {
        w.draw(drzewo_);
    }
    sf::RectangleShape drzewo()
    {
        return drzewo_;
    }
    void set_drzewo_position(float x,float y)
    {
        drzewo_.setPosition(sf::Vector2f(x,y));
    }
    bool owoc_znika(Ptak ptak)
    {
        if(drzewo_.getGlobalBounds().intersects(ptak.ptak().getGlobalBounds()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
private:
    sf::RectangleShape drzewo_;
};

class Owoc
{
public:
    Owoc()
    {
        owoc_.setRadius(20);
        owoc_.setFillColor(sf::Color::Red);
        float x=rand()%350+980;
        float y=rand()%450+30;
        owoc_.setPosition(sf::Vector2f(x,y));
    }
    void draw(sf::RenderWindow &w)
    {
        w.draw(owoc_);
    }    
    sf::CircleShape owoc()
    {
        return owoc_;
    }

private:

    sf::CircleShape owoc_;
};



Pocisk rob_pocisk(Czlowiek cz)
{
        Pocisk p;
        p.set_position(cz.czlowiek().getPosition());
        p.set_velocity(-1000);
        float angle=cz.lufa().getRotation();
        p.set_velocity_y(-1000*sin(angle*3.14/180));

        //std::cout << angle << std::endl;

        p.set_angle_value_x(cos(angle*3.14/180));
        p.set_angle_value_y(sin(angle*3.14/180));

        return p;
}
/*
Ptak rob_ptaka()
{
    Ptak ptak;
    ptak.set_velocity_x(300);
    float y=rand()%400+50;
    ptak.set_position(sf::Vector2f(20,y));
    return ptak;
}*/
/*
Owoc rob_owoce()
{
    Owoc owoc;
    owoc.set_owoc_position();
    return owoc;
}*/

int main() {
    srand (time(NULL));

    sf::RenderWindow window(sf::VideoMode(1400, 900), "My window");

    std::vector<Pocisk> pociski;
    std::vector<Ptak> ptaki;
    std::vector<Owoc> owoce;

    float time_sum=0;
    float time_sum_ptak=0;
    float time_sin=0;

    int pkt=0;
    //ustawienie czlowieka
    Czlowiek cz;
    cz.set_position(1000,700);
    //ustawienie drzewa
    Drzewo drzewo;
    drzewo.set_drzewo_position(980,30);

    for(int n=0;n<7;n++)        //ilosc owocow na drzewie
    {
        Owoc owoc;
        owoce.push_back(owoc);
    }

    sf::Clock clock;

    while (window.isOpen()) {

        float time = float(clock.getElapsedTime().asMicroseconds()/1000000.0);
        clock.restart();

        time_sum+=time;
        time_sum_ptak+=time;
        time_sin+=time;

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        cz.draw(window);
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
        cz.step(time, mouse_position);
        drzewo.draw(window);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && time_sum>0.5)     //time_sum - co jaki czas mozna oddac strzal
        {
            time_sum=0;
            pociski.push_back(rob_pocisk(cz));
        }


        if(time_sum_ptak>2)     //co jaki czas pojawia sie nowy ptak
        {
            time_sum_ptak=0;
            Ptak ptak;
            ptaki.push_back(ptak);
        }
        //rysowanie pociskow
        for(int i=0;i<pociski.size();i++)
        {
            pociski[i].draw(window);
            pociski[i].step(time,time_sin);
        }
        //rysowanie ptakow
        for(int j=0;j<ptaki.size();j++)
        {
            ptaki[j].draw(window);
            ptaki[j].step(time);
            if(drzewo.owoc_znika(ptaki[j]))     //usuwanie owocow gdy ptak wleci w drzewo
            {
                owoce.erase(owoce.begin());
                ptaki.erase(ptaki.begin()+j);
            }
        }
        //usuwanie pocisku i ptaka gdy sie zderza
        for(int k=0;k<pociski.size();k++)
        {
            for(int l=0;l<ptaki.size();l++)
            {
                if(ptaki[l].hit(pociski[k]))
                {
                    pkt++;
                    std::cout << pkt << std::endl;
                    ptaki.erase(ptaki.begin()+l);
                    pociski.erase(pociski.begin()+k);
                }
            }
        }
        //rysowanie owocow
        for(int m=0;m<owoce.size();m++)
        {
            owoce[m].draw(window);
        }



        window.display();
    }

    return 0;
}
