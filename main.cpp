#include <GL/glut.h>
#include"Voronoi.h"

void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(5.0);
    glLineWidth(1.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Render the vertices
     glBegin(GL_POINTS);
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan color
    for (const Vertex& site : sites) {
        glVertex2d(site.x, site.y);
    }
    glEnd();

    glFlush();
}

void reshape(GLsizei width, GLsizei height)
{
   if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height)
        
        gluOrtho2D(-3.0 * aspect, 3.0 * aspect, -3.0, 3.0);
    else
        gluOrtho2D(-3.0, 3.0, -3.0 / aspect, 3.0 / aspect);
}
Vertex normalizeVertex(const Vertex& v, double maxVal) {
    return Vertex(v.x / maxVal, v.y / maxVal);
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

        // Convert pixel coordinates to normalized OpenGL coordinates
        double normalizedX = (2.0 * x / windowWidth) - 1.0;
        double normalizedY = 1.0 - (2.0 * y / windowHeight);

        Vertex mouse(normalizedX, normalizedY);
        std::cout << "Mouse click at: (" << normalizedX << ", " << normalizedY << ")" << std::endl;

        Vertex closestSite = vd->findClosestSite(mouse);

        std::cout << "The closest site to point (" << normalizedX << ", " << normalizedY
                  << ") is at (" << closestSite.x << ", " << closestSite.y << ")." << std::endl;
    }
}
int main(int argc, char** argv) {
    sites.push_back(Vertex(-0.1, -0.1));
    sites.push_back(Vertex(0.1, 0.1));
    sites.push_back(Vertex(-0.5, 1));
    sites.push_back(Vertex(-0.5, -1));
    sites.push_back(Vertex(1, -0.5));
    sites.push_back(Vertex(-1, -0.5));
    sites.push_back(Vertex(0, 1));
    sites.push_back(Vertex(0, -1));
    sites.push_back(Vertex(1, 0));
    sites.push_back(Vertex(-1, 0));
    sites.push_back(Vertex(0.5, 1));
    sites.push_back(Vertex(0.5, -1));
    sites.push_back(Vertex(1, 0.5));
    sites.push_back(Vertex(-1, 0.5));
    sites.push_back(Vertex(-1, 1));
    sites.push_back(Vertex(-1, -1));
    sites.push_back(Vertex(1, 1));
    sites.push_back(Vertex(1, -1));

    

     vd=new VoronoiDiagram(sites);

              
    glutInit(&argc, argv);
    glutInitWindowSize(840, 768);   // Set the window's initial width & height - non-square
    glutInitWindowPosition(100, 100); // Position the window's initial top-left corner
    glutCreateWindow("Voronoi Diagram");  // Create window with the given title
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();                       // Our own OpenGL initialization
    glutMouseFunc(mouseClick);
    glutMainLoop();                 // Enter the infinite event-processing loop
    delete vd;

    return 0;
}
 
