#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <cstdlib>
#include <memory>

class Czlowiek
{
public:
    Czlowiek()
    {
       //czlowiek_.setSize(sf::Vector2f(50,100));
       //czlowiek_.setFillColor(sf::Color::Cyan);

       czlowiek_texture_.loadFromFile("czlowiek.png");
       czlowiek_.setTexture(czlowiek_texture_);

       //karabin_.setSize(sf::Vector2f(70,20));
       //karabin_.setFillColor(sf::Color::Blue);
       //karabin_.setOrigin(70,10);

       karabin_texture_.loadFromFile("karabin.png");
       karabin_.setTexture(karabin_texture_);       
       karabin_.setOrigin(70,42);
    }
    void set_texture(sf::Texture texture)
    {
        czlowiek_.setTexture(texture);
    }
    sf::Sprite czlowiek()
    {
        return czlowiek_;
    }
    sf::Sprite karabin()
    {
        return karabin_;
    }
    void draw(sf::RenderWindow &w)
    {
        w.draw(czlowiek_);
        w.draw(karabin_);
    }
    void set_position(float x, float y)
    {
        czlowiek_.setPosition(x,y);
        karabin_.setPosition(x+40,y+150);
    }

/*
    void step(float time)
    {
        sf::FloatRect bounds = czlowiek_.getGlobalBounds();
        float rotation = karabin_.getRotation();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rotation>0.5)
        {
            karabin_.rotate(-velocity_obr_*time);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rotation<180)
        {
            karabin_.rotate(velocity_obr_*time);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && bounds.left>0)
        {
            czlowiek_.move(-velocity_x_*time,0);
            karabin_.move(-velocity_x_*time,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && bounds.left+bounds.width<1400)
        {
            czlowiek_.move(velocity_x_*time,0);
            karabin_.move(velocity_x_*time,0);
        }
    }
*/

    void step(float time, sf::Vector2i mouse_position)
    {
        sf::FloatRect bounds = czlowiek_.getGlobalBounds();
        float rotation = karabin_.getRotation();
        sf::Vector2f karabin_position = karabin().getPosition();
        float x=karabin_position.x-mouse_position.x;
        float y=karabin_position.y-mouse_position.y;
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



        karabin_.setRotation(angle);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && bounds.left>0)
        {
            czlowiek_.move(-velocity_x_*time,0);
            karabin_.move(-velocity_x_*time,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && bounds.left+bounds.width<1400)
        {
            czlowiek_.move(velocity_x_*time,0);
            karabin_.move(velocity_x_*time,0);
        }

    }    


private:
    sf::Sprite czlowiek_;
    sf::Texture czlowiek_texture_;
    sf::Sprite karabin_;
    sf::Texture karabin_texture_;
    float velocity_x_=200;
    float velocity_obr_=100;
    int pkt_=0;
};

class Pocisk
{
public:
    Pocisk()
    {
        pocisk_.setRadius(5);
        pocisk_.setFillColor(sf::Color::Red);
    }
    void draw(sf::RenderWindow &w)
    {
        w.draw(pocisk_);
    }
    void set_position(sf::Vector2f s)
    {
        //ustawienie skad wylatuje pocisk
        s.y+=120;
        s.x+=20;
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
    void step(float time)
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
        //ptak_.setRadius(20);
        //ptak_.setFillColor(sf::Color::Magenta);
        float y=rand()%400+50;
        ptak_.setPosition(sf::Vector2f(20,y));

        ptak_texture_.loadFromFile("ptak.png");
        ptak_.setTexture(ptak_texture_);
        ptak_.setTextureRect({0,0,62,73});

        fly_frames_.push_back({0,0,62,73});
        fly_frames_.push_back({62,0,63,73});
        fly_frames_.push_back({125,0,62,73});
        fly_frames_.push_back({187,0,63,73});
    }
    void draw(sf::RenderWindow &w)
    {
        w.draw(ptak_);
    }
    void set_position(sf::Vector2f s)
    {
        ptak_.setPosition(s);
    }
    sf::Sprite ptak()
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
    float velocity_x()
    {
        return velocity_x_;
    }
    void step(float time)
    {
        current_frame_time+=time;
        while (current_frame_time >= (1.0/fps_))
        {
             current_frame_time-=(1.0/fps_);
             current_frame_index_ = (current_frame_index_ +1) % fly_frames_.size();
             ptak_.setTextureRect(fly_frames_[current_frame_index_]);
        }

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
    sf::Sprite ptak_;
    sf::Texture ptak_texture_;
    float velocity_x_=0;
    float velocity_y_=0;
    std::vector<sf::IntRect> fly_frames_;
    float fps_ = 4.0;
    float current_frame_time = 0.0;
    int current_frame_index_ = 0;
};

class Drzewo
{
public:
    Drzewo()
    {        
        drzewo_texture_.loadFromFile("drzewo.png");
        drzewo_.setTexture(drzewo_texture_);
        drzewo_.setScale(1.1,1.1);
    }
    void draw(sf::RenderWindow &w)
    {
        w.draw(drzewo_);
    }
    void set_texture(sf::Texture drzewo_texture)
    {
        drzewo_.setTexture(drzewo_texture);
    }
    sf::Sprite drzewo()
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
    sf::Sprite drzewo_;
    sf::Texture drzewo_texture_;
};

class Owoc
{
public:
    //virtual ~Owoc() = default;
    Owoc()
    {
        //owoc_.setRadius(20);
        //owoc_.setFillColor(sf::Color::Red);

        owoc_texture_.loadFromFile("owoc.png");
        owoc_.setTexture(owoc_texture_);
        owoc_.setScale(0.1,0.1);

        float x=rand()%360+940;     //losowo od 940-1300
        float y=rand()%240+100;      //losowo od 100-340
        owoc_.setPosition(sf::Vector2f(x,y));
    }
    void set_texture(sf::Texture owoc_texture)
    {
        owoc_.setTexture(owoc_texture);
    }
    void draw(sf::RenderWindow &w)
    {
        w.draw(owoc_);
    }    
    sf::Sprite owoc()
    {
        return owoc_;
    }

private:
    sf::Texture owoc_texture_;
    sf::Sprite owoc_;
};

Pocisk rob_pocisk(Czlowiek cz)
{
        Pocisk p;
        p.set_position(cz.czlowiek().getPosition());
        p.set_velocity(-1000);
        float angle=cz.karabin().getRotation();
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
    //std::vector<Ptak> ptaki;
    //std::vector<Owoc> owoce;
    std::vector<std::unique_ptr<Owoc>> owoce;
    std::vector<std::unique_ptr<Ptak>> ptaki;

    float time_sum=0;
    float time_sum_ptak=0;
    float czas_ptaka=2;      //co jaki czas pojawia sie nowy ptak

    int pkt=0;
    int pkt_temp=0;
    int ammo=20;
    float velocity_x=300;

    //ustawienie czlowieka
    Czlowiek cz;
    cz.set_position(1000,600);
    //ustawienie drzewa
    Drzewo drzewo;
    drzewo.set_drzewo_position(900,30);

    sf::Texture tlo_texture;
    if (!tlo_texture.loadFromFile("tlo.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    sf::Sprite tlo;
    tlo.setTexture(tlo_texture);
    tlo.setTextureRect(sf::IntRect(150,300,1400,900));


    for(int n=0;n<5;n++)        //ilosc owocow na drzewie
    {        
        //sf::Texture owoc_texture;
        //owoc_texture.loadFromFile("owoc.png");
        //owoc.setTexture(owoc_texture);
        owoce.push_back(std::make_unique<Owoc>());
    }

    sf::Clock clock;

    while (window.isOpen()) {

        float time = float(clock.getElapsedTime().asMicroseconds()/1000000.0);
        clock.restart();

        time_sum+=time;
        time_sum_ptak+=time;        

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        window.draw(tlo);

        cz.draw(window);
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
        //std::cout << mouse_position.x << "      " << mouse_position.y << std::endl;
        cz.step(time, mouse_position);
        drzewo.draw(window);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && time_sum>0.5)     //time_sum - co jaki czas mozna oddac strzal
        {
            time_sum=0;
            pociski.push_back(rob_pocisk(cz));
            ammo--;
            //std::cout << ammo << std::endl;
        }

        //zmiana co jaki czas pojawia sie nowy ptak - co 5 punktow ptaki pojawiaja sie coraz szybciej az do granicy 1.2s
        if(time_sum_ptak>czas_ptaka)
        {
            time_sum_ptak=0;
            std::unique_ptr<Ptak> p=std::make_unique<Ptak>();
            if(pkt_temp>=5  && czas_ptaka>1.3)
            {
                pkt_temp=0;
                czas_ptaka-=0.2;
            }
            if(pkt_temp>=6)
            {
                pkt_temp=0;
                velocity_x+=100;
            }
            p->set_velocity_x(velocity_x);
            ptaki.push_back(move(p));

        }
        /*
        if(pkt_temp>=6)
        {
            pkt_temp=0;
            for (int a=0;a<ptaki.size();a++)
            {
               ptaki[a]->set_velocity_x(ptaki[0]->velocity_x()+100);
            }
        }
        */
        //rysowanie pociskow
        for(int i=0;i<pociski.size();i++)
        {
            pociski[i].draw(window);
            pociski[i].step(time);
        }
        //rysowanie ptakow
        for(int j=0;j<ptaki.size();j++)
        {
            ptaki[j]->draw(window);
            ptaki[j]->step(time);
            if(drzewo.owoc_znika(*ptaki[j]))     //usuwanie owocow gdy ptak wleci w drzewo
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
                if(ptaki[l]->hit(pociski[k]))
                {
                    pkt++;
                    pkt_temp++;
                    ammo++;
                    //std::cout << pkt << std::endl;
                    //std::cout << ammo << std::endl;
                    ptaki.erase(ptaki.begin()+l);
                    pociski.erase(pociski.begin()+k);
                }
            }
        }
        //rysowanie owocow
        for(int m=0;m<owoce.size();m++)
        {
            owoce[m]->draw(window);
            //window.draw(owoce[m]);
        }

        std::cout << "pkt: " << pkt << "     amunicja: " << ammo << std::endl;

        if(owoce.empty() || ammo<=0)
        {
            std::cout << "koniec gry, twoj wynik to : " << pkt << std::endl;
            return 1;
        }

        //window.draw(owoc);
        window.display();
    }

    return 0;
}


