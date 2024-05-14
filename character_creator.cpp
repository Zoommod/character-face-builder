#include <GL/glut.h>
#include <cmath>

const float PI = 3.1416f;

int eyes = 0;
int hats = 0;
int body = 0;

void drawEquilateralTriangle(float centerX, float centerY, float size, bool inverted)
{
    float height = size * sqrt(3) / 2; // Height of the equilateral triangle
    // Set the color of the star (RGB)
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glBegin(GL_TRIANGLES);
    if (!inverted)
    {
        glVertex2f(centerX - size / 2, centerY - height / 3);
        glVertex2f(centerX + size / 2, centerY - height / 3);
        glVertex2f(centerX, centerY + height * 2 / 3);
    }
    else
    {
        glVertex2f(centerX - size / 2, centerY + height / 3);
        glVertex2f(centerX + size / 2, centerY + height / 3);
        glVertex2f(centerX, centerY - height * 2 / 3);
    }
    glEnd();
}

void drawStarOfDavid(float centerX, float centerY, float size)
{
    // Adjust the value of 'size' to change the size of the star
    size = size / 7; // Reduce the size by half

    // Adjust the value of 'centerY' to shift the star downwards
    centerY -= size; // Shifts the star down by the value of 'size'

    // Draw the triangle with the tip upwards
    drawEquilateralTriangle(centerX, centerY, size, false);

    // Draw the triangle with the tip downwards
    drawEquilateralTriangle(centerX, centerY, size, true);

    // Draw the sphere in the center of the star
    glPushMatrix();                    // Save the current transformation matrix
    glTranslatef(centerX, centerY, 0); // Move the center of the sphere to the center of the star
    // Set the color of the sphere (RGB)
    glColor3f(1.0, 0.0, 0.0);          // Red
    glutSolidSphere(size / 3, 20, 20); // Draw the sphere with a third of the size of the star
    glPopMatrix();                     // Restore the previous transformation matrix
}

void drawSantaHat()
{
    // Draw Santa's hat
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, -1.2f);  // Lower vertex
    glVertex2f(-0.2f, -0.6f); // Upper left vertex
    glVertex2f(0.2f, -0.6f);  // Upper right vertex
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    glBegin(GL_QUADS);
    glVertex2f(0.2f, -0.6f);  // Lower left vertex
    glVertex2f(0.2f, -0.5f);  // Upper left vertex
    glVertex2f(-0.2f, -0.5f); // Upper right vertex
    glVertex2f(-0.2f, -0.6f); // Lower right vertex
    glEnd();
    glTranslatef(0.0f, -1.3f, -0.1f); // Move up to draw the pom-pom
    glColor3f(1.0f, 1.0f, 1.0f);      // White
    glutSolidSphere(0.05, 100, 100);  // Draw the pom-pom of the hat
}

void drawCowboyHat(GLUquadricObj *quad)
{
    // Draw the cowboy hat
    glColor3f(0.5f, 0.35f, 0.05f); // Brown color for the hat

    glPushMatrix();
    glTranslatef(0.0f, -0.75f, 0.0f);    // Move the hat to the correct position above the head
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotate the hat so it is oriented correctly

    // Draw the top part of the hat as a cylinder
    gluCylinder(quad, 0.4f, 0.4f, 0.2f, 30, 30); // Draw the cylinder

    // Draw the brim of the hat as a toroid
    glutSolidTorus(0.04f, 0.5f, 20, 20); // Draw the brim
    glPopMatrix();

    glColor3f(0.99f, 0.99f, 0.99f); // Color of R2-D2's head (Light gray)

    gluDeleteQuadric(quad);
}

void drawHalo()
{
    // Set the color of the halo to gold
    glColor3f(1.0f, 0.843f, 0.0f);

    glPushMatrix();
    // Position of the halo
    glTranslatef(0.0f, -0.7f, 0.0f);

    // Rotation so that the halo is parallel to the ground
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    // Use the function glutSolidTorus to draw the halo
    glutSolidTorus(0.02f, 0.3f, 20, 20);
    glPopMatrix();
}
void drawHead()
{
    GLdouble eqn[4];
    // Create a new quadric
    GLUquadricObj *quad = gluNewQuadric();
    glColor3f(0.99f, 0.99f, 0.99f); // Color of R2-D2's head (Light gray)
    // Enable clipping plane to cut the sphere in half
    eqn[0] = 0.0;
    eqn[1] = -1.0;
    eqn[2] = 0.0;
    eqn[3] = 0.0; // Plane equation to clip the lower half
    glClipPlane(GL_CLIP_PLANE0, eqn);
    glEnable(GL_CLIP_PLANE0);
    glutSolidSphere(0.5, 100, 100); // Draw half sphere
    glDisable(GL_CLIP_PLANE0);      // Disable clipping plane

    switch (hats)
    {
    case 0:
        // No hat is drawn
        break;
    case 1:
        // Draw the first style of hat
        drawSantaHat();
        break;
    case 2:
        // Draw the second style of hat
        drawCowboyHat(quad);
        break;
    case 3:
        // Draw the third style of hat
        drawHalo();
        break;
    }
}


void drawEyeStyleOne()
{
    glColor3f(0.0f, 0.0f, 0.0f); // Color of R2-D2's eye (Black)
    glPushMatrix();
    glTranslatef(0.0f, 0.75f, 0.4f); // Eye position in relation to the head
    glutSolidSphere(0.08, 50, 50);   // Draw the eye sphere
    glPopMatrix();
}

void drawEyeStyleTwo()
{
    glColor3f(0.0f, 0.0f, 0.0f); // Eye color (Black)
    glPushMatrix();
    glTranslatef(-0.05f, 0.78f, 0.4f); // Left eye position in relation to the head
    glutSolidSphere(0.04, 50, 50);     // Draw the left eye sphere
    glTranslatef(0.1f, 0.0f, 0.0f);    // Move to the right eye position
    glutSolidSphere(0.04, 50, 50);     // Draw the right eye sphere
    glPopMatrix();
    // Draw the eyebrows
    glColor3f(1.0f, 0.5f, 0.0f); // Eyebrow color (Orange)
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex3f(-0.1f, 0.82f, 0.41f); // Left eyebrow
    glVertex3f(-0.0f, 0.84f, 0.41f);
    glVertex3f(0.1f, 0.82f, 0.41f); // Right eyebrow
    glVertex3f(0.0f, 0.84f, 0.41f);
    glEnd();
}

void drawEyeStyleThree()
{
    glColor3f(0.0f, 0.0f, 0.0f); // Eye color (Black)
    glPushMatrix();
    glTranslatef(0.0f, 0.75f, 0.4f); // Eye position in relation to the head
    glutSolidSphere(0.08, 50, 50);   // Draw the eye sphere
    glColor3f(1.0f, 1.0f, 1.0f);     // Pupil color (White)
    glutSolidSphere(0.04, 50, 50);   // Draw the pupil
    // Draw the eyelashes above the eye
    glColor3f(0.0f, 0.0f, 0.9f); // Eyelash color (Black)
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex3f(-0.1f, -0.03f, 0.41f); // Left eyelash
    glVertex3f(-0.16f, 0.05f, 0.41f);
    glVertex3f(0.0f, 0.016f, 0.41f); // Middle eyelash
    glVertex3f(0.0f, 0.088f, 0.41f);
    glVertex3f(0.1f, -0.03f, 0.41f); // Right eyelash
    glVertex3f(0.16f, 0.05f, 0.41f);
    glEnd();
    glPopMatrix();
}

void drawEyeStyleFour()
{
    glColor3f(0.0f, 0.0f, 0.0f); // Eye color (Black)
    glPushMatrix();
    glTranslatef(-0.05f, 0.78f, 0.4f); // Left eye position in relation to the head
    glutSolidSphere(0.04, 50, 50);     // Draw the left eye sphere
    glTranslatef(0.1f, 0.0f, 0.0f);    // Move to the right eye position
    glutSolidSphere(0.04, 50, 50);     // Draw the right eye sphere
    glPopMatrix();
    // Draw the angry eyebrows
    glColor3f(1.0f, 0.5f, 0.0f); // Eyebrow color (Orange)
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex3f(-0.1f, 0.9f, 0.41f);   // Left eyebrow (start)
    glVertex3f(-0.02f, 0.83f, 0.41f); // Left eyebrow (end)
    glVertex3f(0.02f, 0.83f, 0.41f);  // Right eyebrow (start)
    glVertex3f(0.1f, 0.9f, 0.41f);    // Right eyebrow (end)
    glEnd();
}

void drawEye()
{
    switch (eyes)
    {
    case 0:
        drawEyeStyleOne();
        break;
    case 1:
        drawEyeStyleTwo();
        break;
    case 2:
        drawEyeStyleThree();
        break;
    case 3:
        drawEyeStyleFour();
        break;
    }
}

void drawBodyStyleOne(GLUquadric *quad)
{
    // Draw a rectangular panel
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glBegin(GL_QUADS);
    glVertex3f(-0.2f, 0.2f, 0.01f);  // Top left corner
    glVertex3f(0.2f, 0.2f, 0.01f);   // Top right corner
    glVertex3f(0.2f, -0.2f, 0.01f);  // Bottom right corner
    glVertex3f(-0.2f, -0.2f, 0.01f); // Bottom left corner
    glEnd();
    glPopMatrix();

    // Draw the larger rectangle on X and smaller on Y
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for rectangle
    glBegin(GL_QUADS);
    glVertex3f(-0.2f, 0.46f, 0.0f); // Bottom left corner
    glVertex3f(0.2f, 0.46f, 0.0f);  // Bottom right corner
    glVertex3f(0.2f, 0.5f, 0.0f);   // Top right corner
    glVertex3f(-0.2f, 0.5f, 0.0f);  // Top left corner
    glEnd();

    // Draw the diamond at the left tip of the rectangle
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for diamond
    glBegin(GL_POLYGON);
    glVertex3f(-0.2f, 0.485f, 0.0f);  // Right center of diamond (connected to rectangle)
    glVertex3f(-0.22f, 0.44f, 0.0f);  // Bottom of diamond
    glVertex3f(-0.24f, 0.485f, 0.0f); // Left center of diamond
    glVertex3f(-0.22f, 0.52f, 0.0f);  // Top of diamond
    glEnd();
    glPopMatrix();

    // Draw the rectangle below the previous one
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for rectangle
    glBegin(GL_QUADS);
    glVertex3f(-0.2f, 0.4f, 0.0f);  // Bottom left corner (adjusted downwards)
    glVertex3f(0.2f, 0.4f, 0.0f);   // Bottom right corner (adjusted downwards)
    glVertex3f(0.2f, 0.44f, 0.0f);  // Top right corner (adjusted downwards)
    glVertex3f(-0.2f, 0.44f, 0.0f); // Top left corner (adjusted downwards)
    glEnd();

    // Draw the diamond at the right tip of the rectangle
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for diamond
    glBegin(GL_POLYGON);
    glVertex3f(0.2f, 0.423f, 0.0f);  // Left center of diamond (connected to rectangle)
    glVertex3f(0.22f, 0.38f, 0.0f);  // Bottom of diamond
    glVertex3f(0.24f, 0.423f, 0.0f); // Right center of diamond
    glVertex3f(0.22f, 0.46f, 0.0f);  // Top of diamond
    glEnd();
    glPopMatrix();

    // Draw a new rectangle below with adjusted space and dimensions
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for rectangle
    glBegin(GL_QUADS);
    glVertex3f(-0.15f, -0.3f, 0.0f); // Bottom left corner (more upwards and inwards)
    glVertex3f(0.15f, -0.3f, 0.0f);  // Bottom right corner (more upwards and inwards)
    glVertex3f(0.15f, 0.34f, 0.0f);  // Top right corner (more upwards and inwards)
    glVertex3f(-0.15f, 0.34f, 0.0f); // Top left corner (more upwards and inwards)
    glEnd();
    glPopMatrix();

    glPushMatrix();
    // Draw the lower circle and tic-tac-toe lines
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);      // Gray color for circles
    glTranslatef(0.0f, -0.1f, 0.0f);  // Position the lower circle
    gluDisk(quad, 0.0f, 0.1f, 30, 1); // Draw the lower circle

    // Tic-tac-toe lines centered for the lower circle
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for lines
    glBegin(GL_LINES);
    glVertex3f(-0.05f, 0.0f, 0.01f); // Bottom horizontal line
    glVertex3f(0.05f, 0.0f, 0.01f);
    glVertex3f(-0.05f, 0.05f, 0.01f); // Top horizontal line
    glVertex3f(0.05f, 0.05f, 0.01f);

    glVertex3f(0.0f, -0.05f, 0.01f); // Left vertical line
    glVertex3f(0.0f, 0.05f, 0.01f);
    glVertex3f(0.05f, -0.05f, 0.01f); // Right vertical line
    glVertex3f(0.05f, 0.05f, 0.01f);
    glEnd();

    glPopMatrix();
    // Draw the upper circle and tic-tac-toe lines
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);      // Gray color for circles
    glTranslatef(0.0f, 0.15f, 0.0f);  // Position the upper circle
    gluDisk(quad, 0.0f, 0.1f, 30, 1); // Draw the upper circle

    // Tic-tac-toe lines centered for the upper circle
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for lines
    glBegin(GL_LINES);
    glVertex3f(-0.05f, 0.0f, 0.01f); // Bottom horizontal line
    glVertex3f(0.05f, 0.0f, 0.01f);
    glVertex3f(-0.05f, 0.05f, 0.01f); // Top horizontal line
    glVertex3f(0.05f, 0.05f, 0.01f);

    glVertex3f(0.0f, -0.05f, 0.01f); // Left vertical line
    glVertex3f(0.0f, 0.05f, 0.01f);
    glVertex3f(0.05f, -0.05f, 0.01f); // Right vertical line
    glVertex3f(0.05f, 0.05f, 0.01f);
    glEnd();
    glPopMatrix();
    glPopMatrix();

    // Draw detail of the left rectangle
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);     // Set color to gray
    glBegin(GL_LINE_LOOP);           // Start drawing lines
    glVertex3f(-0.44f, -0.2f, 0.0f); // Mirrored bottom right corner
    glVertex3f(-0.25f, -0.2f, 0.0f); // Mirrored bottom left corner
    glVertex3f(-0.25f, 0.5f, 0.0f);  // Mirrored top left corner
    glVertex3f(-0.44f, 0.5f, 0.0f);  // Mirrored top right corner
    glEnd();                         // End drawing lines
    glPopMatrix();

    // Draw detail of the left inner rectangle
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.5f);       // Set color to blue
    glBegin(GL_QUADS);                 // Start drawing rectangle
    glVertex3f(-0.42f, -0.18f, 0.01f); // Inner bottom right corner
    glVertex3f(-0.27f, -0.18f, 0.01f); // Inner bottom left corner
    glVertex3f(-0.27f, 0.48f, 0.01f);  // Inner top left corner
    glVertex3f(-0.42f, 0.48f, 0.01f);  // Inner top right corner
    glEnd();                           // End drawing rectangle
    glPopMatrix();

    // Draw detail of the right rectangle
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);    // Set color to gray
    glBegin(GL_LINE_LOOP);          // Start drawing lines
    glVertex3f(0.25f, -0.2f, 0.0f); // Bottom left corner
    glVertex3f(0.44f, -0.2f, 0.0f); // Bottom right corner
    glVertex3f(0.44f, 0.5f, 0.0f);  // Top right corner
    glVertex3f(0.25f, 0.5f, 0.0f);  // Top left corner
    glEnd();                        // End drawing lines
    glPopMatrix();

    // Draw detail of the right inner rectangle
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.5f);      // Set color to blue
    glBegin(GL_QUADS);                // Start drawing rectangle
    glVertex3f(0.27f, -0.18f, 0.01f); // Inner bottom left corner
    glVertex3f(0.42f, -0.18f, 0.01f); // Inner bottom right corner
    glVertex3f(0.42f, 0.48f, 0.01f);  // Inner top right corner
    glVertex3f(0.27f, 0.48f, 0.01f);  // Inner top left corner
    glEnd();                          // End drawing rectangle
    glPopMatrix();

    gluDeleteQuadric(quad);
}

void drawBodyStyleTwo()
{
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glVertex2f(0.1f, -0.1f);     // Top
    glVertex2f(0.1f, -0.05f);    // Right
    glVertex2f(0.51f, -0.44f);   // Right tip
    glVertex2f(-0.5f, 0.57f);    // Left tip
    glEnd();

    // Draw the second diamond, shifted downwards
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.77f, 0.0f); // Yellow
    glVertex2f(0.1f, -0.1f);      //
    glVertex2f(0.5f, -0.44f);     // Right tip
    glVertex2f(-0.05f, -0.04f);   //
    glVertex2f(-0.5f, 0.55f);     // Left tip
    glEnd();

    // Draw the third diamond, shifted further downwards
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glVertex2f(0.14f, -0.19f);   // Top
    glVertex2f(0.5f, -0.45f);    // Right tip
    glVertex2f(0.05f, -0.19f);   // Base
    glVertex2f(-0.5f, 0.54f);    // Left tip
    glEnd();
}

void drawBodyStyleThree(GLUquadric *quad)
{
    glColor3f(0.0f, 0.0f, 0.0f); // Black color for the R2-D2 body

    glPushMatrix();
    glTranslatef(0.0f, 0.55f, 0.0f);             // Position the cylinder at the bottom of the head
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);          // Rotate the cylinder around the X-axis
    gluCylinder(quad, 0.5f, 0.5f, 1.0f, 50, 50); // Draw the cylinder
    glPopMatrix();

    // Draw the tie as an upside-down red triangle
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the tie
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.0f); // Position the tie in the center of the body
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, -0.1f, 0.0f);   // Top of the upside-down triangle
    glVertex3f(-0.05f, 0.35f, 0.0f); // Left base of the upside-down triangle
    glVertex3f(0.05f, 0.35f, 0.0f);  // Right base of the upside-down triangle
    glEnd();
    glPopMatrix();
}

void drawBody()
{
    GLUquadric *quad = gluNewQuadric();
    // Set the color to gray for the rectangle
    glColor3f(0.5f, 0.5f, 0.5f); // Gray color

    // Draw the rectangle that connects the arms to the body
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 0.0f);    // Adjust the position as necessary
    glScalef(1.2f, 0.3f, 1.0f);        // Adjust the scale to be larger in X and smaller in Y
    glRectf(-0.5f, -0.1f, 0.5f, 0.1f); // Coordinates for a centered rectangle
    glPopMatrix();
    glColor3f(0.8f, 0.8f, 0.8f); // Light gray color for the R2-D2 body
    glPushMatrix();
    glTranslatef(0.0f, 0.55f, 0.0f);             // Position the cylinder at the bottom of the head
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);          // Rotate the cylinder around the X-axis
    gluCylinder(quad, 0.5f, 0.5f, 1.0f, 50, 50); // Draw the cylinder
    glPopMatrix();
    switch (body)
    {
    case 0:
        drawBodyStyleOne(quad);
        break;
    case 1:
        drawBodyStyleTwo();
        drawStarOfDavid(-0.02f, 0.15f, 1.0f);
        break;
    case 2:
        drawBodyStyleThree(quad);
        break;
    }
}

void drawArm()
{
    GLUquadric *quad = gluNewQuadric();
    glColor3f(0.5f, 0.5f, 0.5f); // Gray

    // Draw the arm
    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, 0.13f, 0.13f, 1.21f, 20, 20);
    glPopMatrix();

    // Draw the adjusted inverted trapezoid
    glPushMatrix();
    glTranslatef(0.01f, -1.46f, 0.6f); // Adjust the position to align with the end of the arm
    glBegin(GL_QUADS);
    // Adjusted coordinates of the trapezoid
    glVertex3f(-0.19f, 0.3f, -0.1f); // Stretched to the left
    glVertex3f(0.19f, 0.3f, -0.1f);  // Stretched to the right
    glVertex3f(0.4f, 0.1f, 0.0f);
    glVertex3f(-0.4f, 0.1f, 0.0f);
    glEnd();
    glPopMatrix();

    gluDeleteQuadric(quad);
}

// Função callback de teclado
void keyboard(unsigned char key, int x, int y)
{
    char keys[] = {'1', '2', '3', '4', 'a', 's', 'd'};
    int *indices[] = {&eyes, &eyes, &eyes, &eyes,
                      &body, &body, &body};

    for (int i = 0; i < sizeof(keys) / sizeof(char); i++)
    {
        if (key == keys[i])
        {
            if (i < 4)
            { // If it's 1, 2, 3, or 4, update 'eyes'
                *indices[i] = i % 4;
            }
            else
            { // If it's 'a', 's', 'd', update 'body'
                // Here you can set a specific value for each key
                // that corresponds to one of the 'body' cases
                *indices[i] = (i - 4) % 3; // This will give values from 0 to 2
            }
            break;
        }
    }

    if (key == 27)
    { // ESC key to exit
        exit(0);
    }

    glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_F1:
    case GLUT_KEY_F2:
    case GLUT_KEY_F3:
    case GLUT_KEY_F4: // Hats: F1...F4
        hats = key - GLUT_KEY_F1;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void displayString(float x, float y, void *font, const char *string)
{
    glColor3f(1.0f, 1.0f, 1.0f); // Set text color to white
    glRasterPos2f(x, y);         // Position the text on the screen
    while (*string)
    {
        glutBitmapCharacter(font, *string++);
    }
}

void displayControls()
{
    // Write the instructions on the screen
    displayString(-1.99f, 1.9f, GLUT_BITMAP_HELVETICA_18, "Body: A, S, D");
    displayString(-1.99f, 1.8f, GLUT_BITMAP_HELVETICA_18, "Eyes: 1, 2, 3, 4");
    displayString(-1.99f, 1.7f, GLUT_BITMAP_HELVETICA_18, "Hat: F1, F2, F3, F4");
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0.0, 0.0, 5.0,  // camera position
              0.0, 0.0, 0.0,  // where the camera is looking
              0.0, 1.0, 0.0); // up direction of the camera

    // Draw R2-D2's head
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glScalef(1.0f, -1.0f, 1.0f);
    drawHead();
    glPopMatrix();

    // Draw R2-D2's body
    drawBody();
    drawEye();

    // Draw left arm
    glPushMatrix();
    glTranslatef(-0.8f, 0.6f, -0.9f); // Left arm position
    drawArm();                        // Specify that it's the left arm
    glPopMatrix();

    // Draw right arm
    glPushMatrix();
    glTranslatef(0.8f, 0.6f, -0.9f); // Right arm position
    drawArm();                       // Specify that it's the right arm
    glPopMatrix();

    displayControls();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutCreateWindow("R2-D2");
    glClearColor(1.0f, 0.7f, 0.7f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutMainLoop();
    return 0;
}