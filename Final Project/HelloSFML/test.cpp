#include <SFML/Graphics.hpp>
#include <iostream>

class Field
{
public:
    // fill 'm_points'
    void fill(const std::size_t number_of_points)
    {
        m_sorted = false;
        //Creating the points
        for(std::size_t i = 0; i < number_of_points; ++i)
        {
            m_points.push_back(i);
        }
        //Shuffling it
        std::random_shuffle(m_points.begin(), m_points.end());
    }

    //bubble sort
    bool sort()
    {
        bool exit = false;
        for(std::size_t o = this->m_points.size()-1;o > 0; --o)
        {
            for(std::size_t pos = 0; pos < o; ++pos)
            {
                if(this->m_points[pos] < this->m_points[pos+1])
                {
                    int tmp_pos = this->m_points[pos];
                    this->m_points[pos] = this->m_points[pos+1];
                    this->m_points[pos+1] = tmp_pos;
                    exit = true;
                }
            }
            if (exit)
            {
                return m_sorted;
            }
        }
        m_sorted = true;
        return m_sorted;
    }

    //bubble sort
    void show_points(sf::RenderWindow& App)
    {
        sf::Shape point(sf::Shape::Circle(0.0, 0.0, 2, sf::Color::Red));
        for(std::size_t i = 0; i < this->m_points.size(); i++)
        {
            point.SetPosition(i, m_points[i]);
            App.Draw(point);
        }
    }

private:
            std::vector<int> m_points;
    bool m_sorted;
};

int main()
{
    sf::RenderWindow App;
    sf::Event Event;
    Field fieldContext;
    bool sorting = false;

    App.Create(sf::VideoMode(600, 600), "Bubble sort");

    //Filling the field
    std::cout << "Filling..." << std::endl;
    fieldContext.fill(600);

    //Let's start the app
    while (App.IsOpened())
    {
        //Verifying events
        while (App.GetEvent(Event))
        {
            // Window closed
            if (Event.Type == sf::Event::Closed)
            {
                App.Close();
            }
            //Key pressed
            if (Event.Type == sf::Event::KeyPressed)
            {
                switch (Event.Key.Code)
                {
                    case sf::Key::Escape :
                        App.Close();
                        break;
                    case sf::Key::S :
                        if (!sorting)
                        {
                            std::cout << "Sorting..." << std::endl;
                            sorting = true;
                        }
                        break;
                    default :
                        break;
                }
            }
        }

        //Update objects
        if (sorting)
        {
            sorting = !fieldContext.sort();
            if (sorting == false)
            {
                std::cout << "Sorted !" << std::endl;
            }
        }

        //Clearing screen
        App.Clear();

        //Dessin du test
        fieldContext.show_points(App);

        //Displaying result
        App.Display();
    }

    return EXIT_SUCCESS;
}