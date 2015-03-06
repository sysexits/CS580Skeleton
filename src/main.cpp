#include "Angel.h"
#include "sphere.h"
#include "LoadBMP.h"

#include <stdio.h>
#include <vector>
#include <time.h>

#define GLFW_INCLUDE_GL_3

GLuint program;

GLuint g_vertexShaderID; // vertex shader ID
GLuint g_fragmentShaderID; // fragment shader ID

GLfloat g_FPS;

GLuint VBID_sphere2;
GLuint VAID_sphere2;

GLuint VAID_triangle;
GLuint VBID_triangle;

const int tNumVertices = 6;
int timePreviousFrame = 0;
int frameCount = 0;

vec4 tpoints[tNumVertices];
vec2 ttexture[tNumVertices];

std::vector<vec4> sph_points;
std::vector<vec4> sph_normals;
std::vector<vec2> sph_coord;

vec4 tvertices[4] = {
    vec4(-1.0, -0.5, 0.0, 1.0),
    vec4(1.0, -0.5, 0.0, 1.0),
    vec4(-1.0, 0.5, 0.0, 1.0),
    vec4(1.0, 0.5, 0.0, 1.0)
};

vec2 ttexcoord[4] = {
    vec2(0.0, 0.0),
    vec2(1.0, 0.0),
    vec2(0.0, 1.0),
    vec2(1.0, 1.0)
};

mat4 identityM(1.0,0.0,0.0,0.0,
                0.0,1.0,0.0,0.0,
                0.0,0.0,1.0,0.0,
                0.0,0.0,0.0,1.0);

typedef vec4 color4;
typedef vec4 point4;

GLuint view;
GLuint projection;
GLuint operation;

mat4 mProjection;

GLfloat ly = 0.0;
int Index = 0;
int pIndex = 0;
int tIndex = 0;
int programStat = 0;

GLuint texture;

bool gluInvertMatrix(double m[16], double invOut[16]);

void init_sphere2(void){
    glGenVertexArrays(1,&VAID_sphere2);
    glBindVertexArray(VAID_sphere2);

    glGenBuffers(1,&VBID_sphere2);
    glBindBuffer(GL_ARRAY_BUFFER,VBID_sphere2);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vec4)*sph_points.size()*2+sizeof(vec2)*sph_coord.size(),0,GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER,0,sph_points.size()*sizeof(vec4),sph_points.data());
    glBufferSubData(GL_ARRAY_BUFFER,sph_points.size()*sizeof(vec4),sph_normals.size()*sizeof(vec4),sph_normals.data());
    glBufferSubData(GL_ARRAY_BUFFER,sph_points.size()*sizeof(vec4)+sph_normals.size()*sizeof(vec4),sph_coord.size()*sizeof(vec2),sph_coord.data());
    
    GLuint vPosition = glGetAttribLocation(program,"vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition,4,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(0));

    GLuint vNormal = glGetAttribLocation(program,"vNormal");
    glEnableVertexAttribArray(vNormal);
    glVertexAttribPointer(vNormal,4,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(sph_points.size()*sizeof(vec4)));
        
    GLuint vTexture = glGetAttribLocation(program,"vTexCoord");
    glEnableVertexAttribArray(vTexture);
    glVertexAttribPointer(vTexture,2,GL_FLOAT,GL_FALSE,0,BUFFER_OFFSET(sph_points.size()*sizeof(vec4)*2));
}

void triangle_quad(void){
    //Step0
    //Step5
    tpoints[tIndex] = tvertices[0]; ttexture[tIndex] = ttexcoord[0]; tIndex++;
    tpoints[tIndex] = tvertices[1]; ttexture[tIndex] = ttexcoord[1]; tIndex++;
    tpoints[tIndex] = tvertices[2]; ttexture[tIndex] = ttexcoord[2]; tIndex++;
    tpoints[tIndex] = tvertices[2]; ttexture[tIndex] = ttexcoord[2]; tIndex++;
    tpoints[tIndex] = tvertices[1]; ttexture[tIndex] = ttexcoord[1]; tIndex++;
    tpoints[tIndex] = tvertices[3]; ttexture[tIndex] = ttexcoord[3]; tIndex++;
}

void drawSphere(){
    switch(programStat){
    case 0:
        glBindVertexArray(VAID_sphere2);
        glBindBuffer(GL_ARRAY_BUFFER,VBID_sphere2);
        glDrawArrays(GL_TRIANGLES,0,sph_points.size());
        break;
    }
}

void init_triangle(void){
    //Step2: vertex generation
    //Step5: texture buffer generation
}

void drawTriangle(){
    //Step3: draw 
}

void init(void){        
    //vertex information//
    //Step0

    //Initialize your shader here/////////////////
    //Step1: shader initialization

    //Initialize your vertices here////////////////
    //Step2: vertex initialization

    //Initialize your texture here////////////////
    //Step5: texture initialization
    
    //////////////////////////////////////////////
    view = glGetUniformLocation(program,"view");
    projection = glGetUniformLocation(program,"projection");
    operation = glGetUniformLocation(program,"op");
    glUniform1i(operation,0);
        
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    
    glShadeModel(GL_SMOOTH);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glClearColor(0.0,0.0,0.0,1.0);
}

void destroyShaders()
{   
    GLenum ErrorCheckValue = glGetError();

    glUseProgram( 0 );

    glDetachShader( program, g_vertexShaderID );
    glDetachShader( program, g_fragmentShaderID );

    glDeleteShader( g_vertexShaderID );
    glDeleteShader( g_fragmentShaderID );

    glDeleteProgram( program );
}

void destroyVBO()
{
    GLenum ErrorCheckValue = glGetError();

    glBindBuffer( GL_ARRAY_BUFFER,VBID_sphere2);
    glDeleteBuffers( 1, &VBID_sphere2 );    

    glBindVertexArray(VAID_sphere2);
    glDeleteVertexArrays( 1, &VAID_sphere2 );   
}

void cleanup(GLFWwindow* window)
{
    destroyShaders();
    destroyVBO();
}

void display(void){
    
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    vec3 viewer_pos(0.0,0.0,2.0);
    mat4 mv = (Translate(-viewer_pos)*RotateY(ly));     
    
    //We select which shader program to use
    glUseProgram(program);
    
    glUniformMatrix4fv(view,1,GL_TRUE,mv);
    glUniformMatrix4fv(projection,1,GL_TRUE,mProjection);
    
    //Step3: draw
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    /* 
        Reference of Keyboard Keys : http://opengl-tutorial-org.googlecode.com/hg-history/b95661a0bb7d7d19d9b78ed58b967f387d1c4f66/external/glfw-3.0.3/docs/html/group__keys.html
    */
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        exit(EXIT_SUCCESS);
    } else if(key == GLFW_KEY_F && action != GLFW_RELEASE) {
        ly += 1.0;
    } else if(key == GLFW_KEY_L && action != GLFW_RELEASE) {
        glUniform1i(operation, 1);
    } else if(key == GLFW_KEY_S && action != GLFW_RELEASE) {
        glUniform1i(operation, 0);
    }
}

void reshape(GLFWwindow* window, int width, int height) {
    glViewport(0,0,width,height);
    GLfloat aspect = GLfloat(width)/height;
    mat4 m_projection = Perspective(45.0,aspect,0.5,3.0);
    mProjection = m_projection;
}

void calculateFPS()
{
    int timeCurrentFrame;

    frameCount++;
    timeCurrentFrame = glfwGetTime();
    
    int timeElapsed = timeCurrentFrame - timePreviousFrame;
    if( timeElapsed > 1.0 )
    {
        g_FPS = 1000.0 / double(frameCount);
        timePreviousFrame += 1.0;
        frameCount = 0; 

        printf( "%.2lf ms/frame\n", g_FPS );
    }
}

int main(void) {
    GLFWwindow* window;

    /* Initialize the GLFW library */
    if(!glfwInit()) return -1;

    /* 
        Create a windowed mode window and its OpenGL context 
        Related reference : http://opengl-tutorial-org.googlecode.com/hg-history/b95661a0bb7d7d19d9b78ed58b967f387d1c4f66/external/glfw-3.0.3/docs/html/window.html#window_hints
    */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 1); // desired numbers of samples to use for multisampling
    glfwWindowHint(GLFW_DEPTH_BITS, 32); // set depth buffer bits, default is 24
    /* 
       We don't need to set Double buffer hint for this window, because GLFW windows are always double buffered.
       Sometimes it can be useful to select when the buffer swap will occur. 
       With the function glfwSwapInterval it is possible to select the minimum number of monitor
       refreshes the driver should wait before swapping the buffers:
       ** glfwSwapInterval(1); 
    */
    window = glfwCreateWindow(512, 512, "Mac OS X OpenGL Skeleton Code", NULL, NULL);

    if(!window) {
        glfwTerminate();
        return -1;
    }
    glfwSetWindowCloseCallback(window, cleanup);
    glfwMakeContextCurrent(window);
    glEnable(GL_MULTISAMPLE);

    // Start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();
    timePreviousFrame = glfwGetTime();

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);

    printf("Renderer: %s\n", renderer);
    printf("OpenGL version support %s\n", version);

    init();
    reshape(window, 512, 512);

    /* Make the window's context current */
    while(!glfwWindowShouldClose(window)) {
        /* Render here */
        display();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        glfwSetKeyCallback(window, keyboard);
        glfwSetWindowSizeCallback(window, reshape);

        calculateFPS();

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
