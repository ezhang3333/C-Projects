// Preprocessor directives to prevent multiple inclusions of header file
#ifndef SHAPE_H_
#define SHAPE_H_

// Including necessary libraries
#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>

using namespace std;

// Code written by Ethan Zhang(ethanjz2), Akhil Morissetty(akhilm6), and Aashay Soni(asoni29)
/* With the help of this application, many forms may be made. Four classes are derived from a basic class called "shape": "rectangle,"

"circle," "sphere," and "rectangular prism." There are values associated with each of these four classes, such as width, height, length,

and/or radius. With these parameters, the application has the ability to calculate and provide back the area, volume, and whether or not

a form is added to or deleted from another shape in the same class. This course incorporates many of the same methods for every class,

like getVolume and getArea(), but each has its unique individual expression.*/

// Shape is the base class for all shapes
class Shape
{
public:
    // Constructor that initializes the name of the shape
    Shape(string name)
    {
        name_ = name;
    }
   
    // Returns the name of the shape
    string getName()
    {
        return name_;
    }
   
    // Pure virtual function for getting area, to be implemented in derived classes
    virtual double getArea() const = 0;
    // Pure virtual function for getting volume, to be implemented in derived classes
    virtual double getVolume() const = 0;
   
private:
  string name_; // Name of the shape

};

// Rectangle is a derived class of Shape
template <class T>
class Rectangle : public Shape
{
public:
    // Constructor that initializes the width and length of the rectangle
    Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle")
    {
        width_ = width;
        length_ = length;
    }
   
    // Returns the area of the rectangle
    double getArea() const 
    {
        return (double)(width_ * length_);
    }
   
    // Returns the volume of the rectangle
    double getVolume() const 
    {
        return 0;
    }
   
    // Overloading + operator for adding two rectangles
    Rectangle<T> operator + (const Rectangle<T>& rec)
    {
            return Rectangle((width_ + rec.width_), (length_ + rec.length_));
    }
   
    // Overloading - operator for subtracting two rectangles
    Rectangle<T> operator - (const Rectangle<T>& rec)
    {
        T num1 = 0;

        return Rectangle(max(num1, (T)(width_ - rec.width_)), max(num1, (T)(length_ - rec.length_)));
    }
   
    // Returns the width of the rectangle
    T getWidth() const 
    {
        return width_;
    }
   
    // Returns the length of the rectangle
    T getLength() const 
    {
        return length_;
    }
private:
    T width_; // Width of the rectangle
    T length_; // Length of the rectangle

};

// Circle is a derived class of Shape
class Circle : public Shape
{
public:
    // Constructor that initializes the radius of the circle
    Circle(double radius):Shape("Circle")
    {
        radius_ = radius;
    }
   
    // Returns the area of the circle
    double getArea() const
    {
        return (M_PI * pow(radius_, 2));
    }
   
    // Returns the volume of the circle
    double getVolume() const
    {
        return 0;
    }
   
    // Overloading + operator for adding two circles
    Circle operator + (const Circle& cir)
    {
        return Circle(radius_ + cir.radius_);
    }
   
    // Overloading - operator for subtracting two circles
    Circle operator - (const Circle& cir)
    {
        return Circle(max(0.0, radius_ - cir.radius_));
    }

    // Returns the radius of the circle
    double getRadius() const 
    {
        return radius_;
    }
   
private:
    double radius_; // Radius of the circle

};

// Sphere is a derived class of Shape
class Sphere : public Shape
{
public:
    // Constructor that initializes the radius of the sphere
    Sphere(double radius):Shape("Sphere")
    {
        radius_ = radius;
    }

    // Returns the volume of the sphere
    double getVolume() const 
    {
        return((4.0 / 3.0) * M_PI * pow(radius_, 3));
    }  
   
    // Returns the area of the sphere
    double getArea() const 
    {
        return (4.0 * M_PI * pow(radius_, 2));
    }

    // Overloading + operator for adding two spheres
    Sphere operator + (const Sphere& sph)
    {
        return Sphere(radius_ + sph.radius_);
    }

    // Overloading - operator for subtracting two spheres
    Sphere operator - (const Sphere& sph)
    {
        return Sphere(max(0.0, radius_ - sph.radius_));
    }
   
    // Returns the radius of the sphere
    double getRadius() const 
{
    return radius_;
}

// Private member variable for storing the radius of the shape
private:
    double radius_;
};

// RectPrism class is derived from the Shape base class
class RectPrism : public Shape
{
public:
    // Constructor for the RectPrism class which initializes the width, length, and height
    RectPrism(double width, double length, double height):Shape("RectPrism")
    {
        length_ = length;
        width_ = width;
        height_ = height;
    }
   
    // Function to calculate the volume of the rectangular prism
    double getVolume() const 
    {
        return(length_ * width_ * height_);
    }
   
    // Function to calculate the surface area of the rectangular prism
    double getArea() const 
    {
        return(2 * ((width_ * length_) + (height_ * length_) + (height_ * width_)));
    }
   
    // Overloading + operator for adding two rectangular prisms
    RectPrism operator + (const RectPrism& rectp)
    {
        return RectPrism(width_ + rectp.width_, length_ + rectp.length_, height_ + rectp.height_);
    }
   
    // Overloading - operator for subtracting two rectangular prisms
    RectPrism operator - (const RectPrism& rectp)
    {
        return RectPrism(max(0.0, width_ - rectp.width_), max(0.0, length_ -rectp.length_), max(0.0, height_ - rectp.height_));
    }  
   
    // Function to return the width of the rectangular prism
    double getWidth() const 
    {
        return width_;
    }
   
    // Function to return the length of the rectangular prism
    double getLength() const 
    {
        return length_;
    }
   
    // Function to return the height of the rectangular prism
    double getHeight() const 
    {
        return height_;
    }
 
private:
    // Private member variables for storing the length, width, and height of the rectangular prism
    double length_;
    double width_;
    double height_;
};


// Read shapes from the specified file and initialize corresponding objects
// Return a vector of pointers that point to the created objects
static list<Shape*> CreateShapes(char* file_name)
{
    // Declare variables for reading shape information from the file
    string shapeName;
    double numberOfShapes, radius, length, width, height;
   
    // Create a list to store pointers to Shape objects
    list<Shape*> inputShapes;
   
    // Open the file for reading
    ifstream shapesFile(file_name);

    // Read the total number of shapes from the file
    shapesFile >> numberOfShapes;

    // Loop through each shape entry in the file
    for(double n = numberOfShapes; n > 0; n--)
    {
        // Declare a pointer to a Shape object
        Shape* shape_ptr;

        // Read the shape name from the file
        shapesFile >> shapeName;

        // Check the shape type and create the corresponding object
        if(shapeName == "Rectangle")
        {
            shapesFile >> width;
            shapesFile >> length;

            // Create a Rectangle object and assign its pointer to shape_ptr
            shape_ptr = new Rectangle<double>(width, length);
        }
        else if(shapeName == "Circle")
        {
            shapesFile >> radius;

            // Create a Circle object and assign its pointer to shape_ptr
            shape_ptr = new Circle(radius);
        }
        else if(shapeName == "Sphere")
        {
            shapesFile >> radius;

            // Create a Sphere object and assign its pointer to shape_ptr
            shape_ptr = new Sphere(radius);
        }
        else if(shapeName == "RectPrism")
        {
            shapesFile >> width;
            shapesFile >> length;
            shapesFile >> height;

            // Create a RectPrism object and assign its pointer to shape_ptr
            shape_ptr = new RectPrism(width, length, height);
        }

        // Add the created object's pointer to the list
        inputShapes.push_back(shape_ptr);
    }

    // Close the file
    shapesFile.close();

    // Return the list of shape pointers
    return inputShapes;
}

// Calculate the maximum area among the shapes
static double MaxArea(list<Shape*> shapes)
{
    // Initialize the maximum area to zero
    double max_area = 0;

    // Iterate through each shape in the list
    for(list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++)
    {
        // Check if the current shape's area is greater than the current max_area
        if((*it)->getArea() > max_area)
        {
            // Update max_area with the current shape's area
            max_area = (*it)->getArea();
        }
    }  
   
    // Return the maximum area
    return max_area;
}

// Calculate the maximum volume among the shapes
static double MaxVolume(list<Shape*> shapes)
{
    // Initialize the maximum volume to zero
    double max_volume = 0;

    // Iterate through each shape in the list
    for(list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++)
    {
        // Check if the current shape's volume is greater than the current max_volume
        if((*it)->getVolume() > max_volume)
        {
            // Update max_volume with the current shape's volume
            max_volume = (*it)->getVolume();
        }
    }
   
    // Return the maximum volume
    return max_volume;
}

#endif

