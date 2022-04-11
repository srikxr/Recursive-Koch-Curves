#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

//struct for handling x and y points
struct Point {
    double x, y;
};

//helper method to use for calculations
void calculate(vector<Point> &points, int Left, int Right)
{
    Point p1 = points[Left];
    Point p2 = points[Right]; //placing the initial points at the indexes of the Left and Right iterators.

    double x1 = p1.x, x2 = p2.x, y1 = p1.y, y2 = p2.y; 
    double x3, x4, x5, x6;
    double y3, y4, y5, y6;
    double theta1, theta2;
    double base_triangle, height_triangle;
    double PI = 3.1415926535;

    //distance formula of the overall line
    double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    //find the points for the first third of the line
    x3 = x1 + ((x2-x1)/3);
    y3 = y1 + ((y2-y1)/3);

    //find the points for the second third of the line
    x4 = x1 + (2*((x2-x1)/3));
    y4 = y1 + (2*((y2-y1)/3));

    //finding the points for the middle of the line
    x5 = (x1 + x2)/2;
    y5 = (y1 + y2)/2;

    //finding the angle of the whole line compared to the x-axis
    theta1 = atan2(y2-y1, x2-x1);

    //finding the angle to put the top of the triangle point at
    theta2 = theta1 + (PI/2);

    //finding the value of the base of the 30-60-90 triangle
    base_triangle = (distance / 6);

    //finding the height of the 30-60-90 triangle
    height_triangle = base_triangle * sqrt(3);

    //finding the points for the top of the bump
    x6 = x5 + (height_triangle * cos(theta2));
    y6 = y5 + (height_triangle * sin(theta2));

    Point p3 = {x3, y3}, p4 = {x6, y6}, p5 = {x4,y4}; //pushed the newly found points of the bump into a points vector
    
    points.insert(points.begin()+(Left+1), p3); 
    points.insert(points.begin()+(Left+2), p4); //pushing newly calculated points
    points.insert(points.begin()+(Left+3), p5); 

    
}

void koch(vector<Point> points, int level) //method to recursively iterate and calculate the vector elements
{
    if ( level == 0 ) //base case of the recursive call, outputs straight line
    {
        cout << points[0].x << " " << points[0].y << " moveto" << endl; //starting point command

        for (int i=1; i < points.size(); i++ ) {    //iterates through the final vector and outputs every line in a Postscript command using "lineto"
            double x = points[i].x;
            double y = points[i].y; 
            cout << x << " " << y << " lineto" << endl;
        }
        cout << "stroke" << endl; //ending commands to draw and show output
        cout << "showpage" << endl;

        return;
    } 

    //if the levels is not equal to 0:
    int Left = 0, Right = 1; //setting iterators one apart as they traverse the vector
    while (Left < points.size() - 1) 
    {
        calculate(points, Left, Right); //calculates each point
        Left += 4;  //program places three points in between Left and right, so they would have to move 4 spots until they get to a new segment
        Right += 4;
    }
    koch(points, level-1); // recursive call with level value going down to eventually reach the base case
}

int main(int argc, char* argv[])
{
    double x1 = atof(argv[1]), y1 = atof(argv[2]); //setting the command line inputs to variables
    double x2 = atof(argv[3]) , y2 = atof(argv[4]);
    int level = (atoi(argv[5]));

    double x_snowflake, y_snowflake; //defining seperate initial snowflake values
    double PI = 3.1415926535;


    double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); //distance formula
    double base_snow = (distance / 2); //calculating the base of the 30-60-90 triangle
    double height_snow = base_snow * (sqrt(3)); //calculating the height of the triangle
    double theta1 = atan2(y2-y1, x2-x1); // calculating the angle of the initial line
    double theta2 = theta1 + (PI/2); // calculating the angle of which the new point needs to be at

    double x_midpoint = (x1 + x2)/2; // finding the midpoint coordinate of line
    double y_midpoint = (y1 + y2)/2;

    x_snowflake = x_midpoint - (height_snow * cos(theta2)); // finally finding the new point's coordinate, which will be placed below the line to make a triangle
    y_snowflake = y_midpoint - (height_snow * sin(theta2));

    
    Point p1 = { x1, y1}, p2 = { x2, y2}, pSnow = {x_snowflake, y_snowflake}; // making new point types with given start, ending and new snowflake points

    vector<Point> points; // pushing these points to the points vector
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(pSnow);
    points.push_back(p1); // connecting one more line from the new snow point back to the starting point


    koch(points, level); // calling the recursive function

}