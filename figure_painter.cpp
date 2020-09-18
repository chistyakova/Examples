#include <iostream>
#include <vector>
#include <cmath>

// базовый класс фигуры---------------------------------------------
class Figure {
public:
    Figure(unsigned canvasSize){
        m_pixels = std::vector<std::vector<bool>>(canvasSize, std::vector<bool>(canvasSize, false));
    }
    virtual ~Figure(){}

    const std::vector<std::vector<bool>>& getPixels() const {
        return m_pixels;
    }
protected:
    std::vector<std::vector<bool>> m_pixels;
};

// производные классы круга, прямоугольника и треугольника-------------------------
class Circle : public Figure {
public:
    Circle(int canvasSize) : Figure(canvasSize) {
        const int R = canvasSize / 2;
        for (int i = 0; i <= R; ++i) {
            const int j = sqrt(pow(R, 2) - pow(i, 2))+0.5;
            m_pixels.at(R - i).at(R - j) = true;
            m_pixels.at(R + i - 1).at(R + j - 1) = true;
            m_pixels.at(R - i).at(R + j - 1) = true;
            m_pixels.at(R + i - 1).at(R - j) = true;
        }
    }
    ~Circle(){}
};


class Rectangle : public Figure {
public:
    Rectangle(unsigned canvasSize) : Figure(canvasSize){
        for(unsigned i=0; i<canvasSize; ++i) {
            for(unsigned j=0; j<canvasSize; ++j) {
                if(i==0 || j==0 || i==canvasSize-1 || j==canvasSize-1)
                    m_pixels.at(i).at(j) = true;
            }
        }
    }
    ~Rectangle(){}
};

class Triangle : public Figure {
public:
    Triangle(unsigned canvasSize) : Figure(canvasSize){
        for(unsigned i=0; i<canvasSize; ++i) {
            const unsigned j = i*0.5;
            m_pixels.at(i).at(canvasSize/2+j) = true;
            m_pixels.at(i).at(canvasSize/2-j-1-canvasSize%2) = true;
        }
        for(unsigned i=1; i<canvasSize-1; ++i){
            m_pixels.at(canvasSize-1).at(i) = true;
        }
    }
    ~Triangle(){}
};

// базовый класс отрисовщика-----------------------------------------------------------
class Painter {
public:
    virtual void paint(const Figure&) = 0;
    virtual ~Painter(){}
};

// производный класс отрисовщика в ASCII-стиле-----------------------------------------------------
class ASCIIPainter : public Painter {
public:
    void paint(const Figure& figure) override {
        auto pixels = figure.getPixels();

        for(unsigned i=0; i<pixels.size(); ++i) {
            for(unsigned j=0; j<pixels.size(); ++j) {
                std::cout << (pixels.at(i).at(j) ? '*' : '.');
            }
            std::cout << std::endl;
        }
    }
    ~ASCIIPainter(){}
};

// тело программы-----------------------------------------------------------------
int main(int argc, char** argv)
{
    int defaultSize = 10;
    if (argc == 2) {
        defaultSize = atoi(argv[1]);
    }
    std::vector<Figure> figureContainer;
    figureContainer.push_back(Rectangle(defaultSize));
    figureContainer.push_back(Circle(defaultSize));
    figureContainer.push_back(Triangle(defaultSize));

    ASCIIPainter asciiPainter;
    Painter &painter = asciiPainter;

    for(auto figure : figureContainer) {
        painter.paint(figure);
    }
}
