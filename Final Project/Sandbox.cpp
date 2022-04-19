#include "Sandbox.h"

int MyShape::count = 0;

Sandbox::Sandbox()
    : m_IsRunning(true)
{
    m_Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "ImGui");
    m_Window->setFramerateLimit(60);
    ImGui::SFML::Init(*m_Window);
    LoadTexture();
}

Sandbox::~Sandbox()
{
    ImGui::SFML::Shutdown();
}

void Sandbox::Update()
{
    HandleInput();
    ImGui::SFML::Update(*m_Window, m_DeltaClock.restart());
    //HandleUserInput();

    MouseClicking();
    Draw();
}

void Sandbox::HandleInput()
{
    while (m_Window->pollEvent(m_Event)) {
        ImGui::SFML::ProcessEvent(m_Event);

        if (m_Event.type == sf::Event::Closed) {
            m_IsRunning = false;
            m_Window->close();
        }
    }
}

void Sandbox::Draw()
{
    m_Window->clear();
    ImGui::Begin("Convex Hull");


    for (auto& shape : m_Shapes)
        m_Window->draw(*shape.shape);

    
    ShapesGUI();
    ImGui::End();

    ImGui::SFML::Render(*m_Window);
    m_Window->display();
}


void Sandbox::ShapesGUI()
{
    //Bools for the radio buttons
    static bool animation = false;
    static bool instant = false;
    static bool load = false;
    static bool useri = false;
    //Gets the style from ImGui
    ImGui::GetStyle();

    //Gets the ImGui color
    ImVec4* colors = ImGui::GetStyle().Colors;

    //sets window color black
    colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.00f, 0.00f, 1.0f);

    //sets the Text color to white
    colors[ImGuiCol_Text] = ImVec4(1.0f, 1.00f, 1.00f, 1.0f);

    //Aligns the title of the window
    ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5, 0.5);

    //matches seperator to background color to appear as blank spaces
    colors[ImGuiCol_Separator] = ImVec4(0.0f, 0.00f, 0.00f, 1.0f);

    //Sets the radio buttons to blue
    colors[ImGuiCol_Button] = ImVec4(0.0f, 0.81f, 0.96f, 1.0f);

    //Title of the ImGui
    ImGui::Text("Choose your desired boxes",100);
    //for loop to create separators
    for (int i = 0; i < 10; i++) {
        ImGui::Separator();
    }
  
    //Creates the Radio button
    ImGui::RadioButton("Animated Convex Hull", &animation);
    for (int i = 0; i < 5; i++) {
        ImGui::Separator();
    }  
    
    ImGui::RadioButton("Instant Convex Hull", &instant);
    for(int i = 0; i < 5; i++) {
        ImGui::Separator();
    }
    
    ImGui::RadioButton("Load file", &load);
    for (int i = 0; i < 5; i++) {
        ImGui::Separator();
    }
   
    ImGui::RadioButton("User input circles", &useri);
    for (int i = 0; i < 20; i++) {
        ImGui::Separator();
    }
    //sets the Button color to grey
    colors[ImGuiCol_Button] = ImVec4(0.10f, 0.10f, 0.10f, 1.0f);
    ImVec2 buttonSize(80, 30); //button size
    ImGui::Button("Start", buttonSize);
    
}



void Sandbox::DrawTexture()
{
    m_Window->draw(m_Sprite);
}

void Sandbox::LoadTexture()
{
    std::string path = std::filesystem::current_path().u8string();
    spdlog::info("path: {}", path);
    if (!m_Texture.loadFromFile("space.jpg"))
    {
        // error...
        spdlog::error("failed to load texture");
    }

    m_Sprite.setTexture(m_Texture);
    m_Sprite.setScale(sf::Vector2f(0.1f, 0.1f));
}

void Sandbox::MouseClicking()
{
    auto mousePos = sf::Mouse::getPosition(*m_Window);

    for (auto& shape : m_Shapes)
        if (m_Event.type == sf::Event::MouseButtonPressed) // && myMouseBool == false
        {
            // check mouse pos vs global bounds of your object
            if (shape.shape->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                spdlog::info("shape {} pressed!", shape.id);
            }
            // mymousebool =true
        }
    // if event is mouserelease - set mymousebool false
    //if (event.type == sf::Event::MouseButtonReleased)
}


