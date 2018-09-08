#include "graphicsEngine.h"

   /*
    *   Author: Carlos Hernandez
    *   Version: 1.0
    *   date: 2-9-2018
    *
    */

//constructor

graphicsEngine::graphicsEngine(std::string title, GLint majorVer, GLint minorVer, int width, int height) :
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
//    delete verts;
}

float graphicsEngine::Xfunc(int i, int numVerts){
    int mult, constant;
    float cCosT = (2 * PI)/ numVerts;//top
    float cCosM = ((2 * PI)/ numVerts) /2;//center
    float answer;


    if(numVerts % 2 != 0){
    if(i == numVerticies/2 || i == 0){
        if(numVerts % 2 == 0){
            counterX = (numVerts/2) + 1;
        }
        else{
            counterX = (numVerts / 2);
        }
        counter1X = 0;
    }
    if(i % 3 == 0 && i < numVerticies/2){// for center
        counterX++;
        mult = counterX;
        constant = cCosT;
        answer = cos( ((PI)/2) -  (mult*cCosT/*constant*/) );
    }
    else if(i % 3 == 1 && i<numVerticies/2){
        counter1X++;
        mult = counter1X;
        constant = cCosM;
        answer = cos( ((3* PI / 2)) -  (mult*cCosT/*constant*/) );
    }
    else if(i % 3 == 0 && i >= numVerticies/2){
        counterX++;
        mult = counterX;
        constant = cCosM;
        answer = cos( ((PI / 2)) +  (mult*cCosT/*constant*/) );
    }
    else{
        counter1X++;
        mult = counter1X;
        constant = cCosT;
        answer = cos( ((3 * PI)/2) + (mult*cCosT/*constant*/) );
    }
    }
    else{
    if(i == numVerticies/2 || i == 0){
        /*if(numVerts % 2 == 0){
            counterX = (numVerts/2) + 1;
        }
        else{
            counterX = (numVerts / 2);
        }*/
        counter1X = -2;
        counterX = 0;
    }

        if(i % 3 == 0 && i < numVerticies/2){// for center
        counterX++;
        mult = counterX;
        constant = cCosT;
        answer = cos( ((PI)/2) -  (mult*cCosT/*constant*/) );
    }
    else if(i % 3 == 1 && i<numVerticies/2){
        counter1X++;
        mult = counter1X;
        constant = cCosM;
        answer = cos( -(mult*cCosT/*constant*/) );
    }
    else if(i % 3 == 0 && i >= numVerticies/2){
        counterX++;
        mult = counterX;
        constant = cCosM;
        answer = cos( ((PI / 2)) +  (mult*cCosT/*constant*/) );
    }
    else{
        counter1X++;
        mult = counter1X;
        constant = cCosT;
        answer = cos(PI + (mult*cCosT/*constant*/) );
    }
    }
    return answer;
}

float graphicsEngine::Yfunc(int i, int numVerts){
    int mult, constant;
    float cSinT = (2 * PI)/ numVerts;//tips
    float cSinM = ((PI)/ numVerts) /2;//center
    float answer;

    //std::cout<<cSin << "\n";
    if(numVerts % 2 != 0){

    if(i == numVerticies/2 || i == 0){
        counter1Y = 0;
        if(numVerts %2 == 0){
            counterY = (numVerts/2) + 1;
        }
        else{
            counterY = (numVerts /2);
        }
    }

    if(i % 3 == 0 && i < numVerticies/2){// for center
        counterY++;
        mult = counterY;
        //constant = cCosT;
        answer = sin( ((PI)/2) -  (mult*cSinT/*constant*/) );
    }
    else if(i % 3 == 1 && i<numVerticies/2){
        counter1Y++;
        mult = counter1Y;
        //constant = cM;
        answer = sin( ((3* PI / 2)) -  (mult*cSinT/*constant*/) );
    }
    else if(i % 3 == 0 && i >= numVerticies/2){
        counterY++;
        mult = counterY;
        //constant = cCosM;
        answer = sin( (( PI / 2)) +  (mult*cSinT/*constant*/) );
    }
    else{
        counter1Y++;
        mult = counter1Y;
        //constant = cCosT;
        answer = sin( ((3 *PI)/2) + (mult*cSinT/*constant*/) );
    }
    }
    else{

    if(i == numVerticies/2 || i == 0){
        counterY = 0;
        counter1Y = -2;
        /*if(numVerts %2 == 0){
            counterY = (numVerts/2) + 1;
        }
        else{
            counterY = 3;
        }*/
    }
        if(i % 3 == 0 && i < numVerticies/2){// for center
        counterY++;
        mult = counterY;
        //constant = cCosT;
        answer = sin( ((PI)/2) -  (mult*cSinT/*constant*/) );
    }
    else if(i % 3 == 1 && i<numVerticies/2){
        counter1Y++;
        mult = counter1Y;
        //constant = cM;
        answer = sin( -(mult*cSinT/*constant*/) );
    }
    else if(i % 3 == 0 && i >= numVerticies/2){
        counterY++;
        mult = counterY;
        //constant = cCosM;
        answer = sin( (( PI / 2)) +  (mult*cSinT/*constant*/) );
    }
    else{
        counter1Y++;
        mult = counter1Y;
        //constant = cCosT;
        answer = sin( PI + (mult*cSinT/*constant*/) );
    }
    }
    return answer;
}

//initialization of the GE, loads vertex and color data to the Graphics Card.
//Loads shader programs from the disk to the GC,
//links data stream to the vertex/color data

void graphicsEngine::init(){
    //std::cin >> numVerticies;// = 6;
    numVerticies = 30;
    mode = GL_FILL;
    vPos = 0;
    vColor = 1;
    /*
    outerTipX = -0.90;
    outerTipY = -0.90;
    middleTipX = 0.90;
    middleTipY = -0.90;
    innerTipX = -0.90;
    innerTipY = 0.90;
    */
    //background color
    glClearColor(0, 0, 0, 1);

    //vertex and color information of the polygons
    vertexInfo verts[numVerticies];/* = {
        {{1.00, 0.00, 0.00}, {outerTipX, outerTipY}},  // Triangle 1 bottom left
        {{0.00, 1.00, 0.00}, {middleTipX, middleTipY}},    //bottom right
        {{0.00, 0.00, 1.00}, {innerTipX, innerTipY}},    //top left

        {{0.5, 0.00, 0.00}, {0.90, -0.90}},   // Triangle 2 bottom right
        {{0.00, 0.50, 0.00}, {0.90, 0.90}},     //top right
        {{0.00, 0.00, 0.50}, {-0.90, 0.90}}     //top left
    };*/
    //vertexInfo* verts = new vertexInfo[numVerticies];


    /*
        Okay we are going to calulate the X and Y coordinate and also give static colors for the moment
        Then put those colors and (x,y) coordinates into the verts array accordingly then bam!!
        also do the attrbpointer stuff to notify that they need to move more fo rthe information

    */
   for(int i = 0; i < numVerticies ; i++){
        int mod = i %3;
        if(mod == 0){ //this will handle the tips
            verts[i] = {{1.00, 0.00, 0.00}, {Xfunc((i), numVerticies/6), Yfunc((i), numVerticies/6)}};
        }
        else if(mod == 2){ // this will handle the center
            verts[i] = {{1.00, 1.00, 1.00}, {0 /* Xfunc(i -3, numVerticies/2)*/, 0 /* Yfunc(i-3, numVerticies/2)*/}};
        }
        else{ //midle vert
            verts[i] = {{ 1.00 , 1.00, 1.00}, {0.40 * Xfunc(i, numVerticies/6), 0.40 * Yfunc(i, numVerticies/6)}};
        }
        //std::cout<< i<< ": " "vert x: "<< verts[i].position[0] << ", vert y: "<< verts[i].position[1] << "\n";
    }

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
