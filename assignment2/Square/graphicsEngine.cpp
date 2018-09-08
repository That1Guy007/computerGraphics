#include "graphicsEngine.h"

   /*
    *   Author: Carlos Hernandez
    *   Version: 1.0
    *   date: 2-9-2018
    *
    */

//constructor

graphicsEngine::graphicsEngine(std::string title, GLuint majorVer, GLuint minorVer, int width, int height) :
    sf::RenderWindow( sf::VideoMode( width, height), title, sf::Style::Default,
     sf::ContextSettings(24, 8, 4, majorVer, minorVer, sf::ContextSettings::Core)){

    setVerticalSyncEnabled(true);
    ssCount = 1;

    //set as active window for openGL calls
    setActive();

    //init program data and load shader programs
    init();
}

//detructor
graphicsEngine::~graphicsEngine(){

}

//initialization of the GE, loads vertex and color data to the Graphics Card.
//Loads shader programs from the disk to the GC,
//links data stream to the vertex/color data

void graphicsEngine::init(){
    numVerticies = 6;
    mode = GL_FILL;
    vPos = 0;
    vColor = 1;

    //background color
    glClearColor(0, 0, 0, 1);

    //vertex and color information of the polygons
    vertexInfo verts[6] = {
        {{1.00, 0.00, 0.00}, {-0.90, -0.90}},  // Triangle 1 bottom left
        {{0.00, 1.00, 0.00}, {0.90, -0.90}},    //bottom right
        {{0.00, 0.00, 1.00}, {-0.90, 0.90}},    //top left

        {{0.5, 0.00, 0.00}, {0.90, -0.90}},   // Triangle 2 bottom right
        {{0.00, 0.50, 0.00}, {0.90, 0.90}},     //top right
        {{0.00, 0.00, 0.50}, {-0.90, 0.90}}     //top left
    };

    //Create and enable a vertex array
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Generate and turn on buffer
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    //transfer vertex info to the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts),
                    verts, GL_STATIC_DRAW);

    //set up vertexdata position info
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_TRUE,
                                sizeof(vertexInfo), BUFFER_OFFSET(0));
    glVertexAttribPointer(vPos, 2, GL_FLOAT,GL_FALSE, sizeof(vertexInfo),
                                BUFFER_OFFSET(sizeof(verts[0].color)));

    //set position index for shader streams
    glEnableVertexAttribArray(vPos);
    glEnableVertexAttribArray(vColor);

    //load frag and vertex shaders
    GLuint program = loadShaderFromFile("passThroughVerts.glsl", "passThroughFrags.glsl");

    //check program..if load shaders fails -> exit
    if(!program){
        std::cerr<< "\nError loading shader programs...exiting\n";

        exit(1);
    }

    //use the shaders
    glUseProgram(program);
}

//display() draws the openGL frame buffer
void graphicsEngine::display(){
    //clear screen or clear fram buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //Draw the polygons..prob triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0 , numVerticies);

    sf::RenderWindow::display();
}

void graphicsEngine::changeMode(){
    //Changes the mod from fill to line and vise versa
    if(mode == GL_FILL){
        mode = GL_LINE;
    }
    else{
        mode = GL_FILL;
    }
    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void graphicsEngine::screenshot(){
    char ssFilename[100];
    std::sprintf(ssFilename, "screenshot%d.png", ssCount);
    sf::Vector2u windowSize = getSize();
    sf::Texture texture;
    texture.create(windowSize.x, windowSize.y);
    texture.update(*this);
    sf::Image img = texture.copyToImage();
    img.saveToFile(ssFilename);
    ssCount++;
}

void graphicsEngine::resize(){
    glViewport(0, 0, getSize().x, getSize().y);
}

void graphicsEngine::setSize(unsigned int width, unsigned int height){
    sf::RenderWindow::setSize(sf::Vector2u(width, height));
    resize();
}
