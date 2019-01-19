#include <iostream>
#include <stack>
#include <vector>

using namespace std; 

struct Point2D
{
    int x;
    int y;
};

Point2D point0;
constexpr int pointsCount = 3;

Point2D topNext(stack<Point2D> &pointsStack)
{
    const Point2D point = pointsStack.top();
    pointsStack.pop();
    const Point2D res = pointsStack.top();
    pointsStack.push(point);

    return res;
}

int squareOfDistance(const Point2D &point1, const Point2D &point2)
{
    return (point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y);
}

int orientation(const Point2D &point1, const Point2D &point2, const Point2D &point3)
{
   const int value = (point2.y - point1.y) * (point3.x - point2.x) - (point2.x - point1.x) * (point3.y - point2.y);

    if (value == 0)
        return 0;

    return (value > 0) ? 1 : 2;
}

int comparePoints(const void *point1, const void *point2)
{
    const Point2D *point1Cast = static_cast<const Point2D*> (point1);
    const Point2D *point2Cast = static_cast<const Point2D*> (point2);
    const int orientationValue = orientation(point0, *point1Cast, *point2Cast);

    if (orientationValue == 0)
        return (squareOfDistance(point0, *point2Cast) >= squareOfDistance(point0, *point1Cast)) ? -1 : 1;

    return (orientationValue == 2) ? -1 : 1;
}

int solution(vector<Point2D> &A)
{
    int yMinimum = A[0].y;
    int minimum = 0;
    const int size = A.size();

    for (int i = 1; i < size; ++i)
    {
        const int y = A[i].y;

        if ((y < yMinimum) || (yMinimum == y && A[i].x < A[minimum].x))
            yMinimum = A[i].y, minimum = i;
    }

    swap(A[0], A[minimum]);
    point0 = A[0];
    qsort(&A[1], size - 1, sizeof(Point2D), comparePoints);

    stack<Point2D> pointsStack;

    pointsStack.push(A[0]);
    pointsStack.push(A[1]);
    pointsStack.push(A[2]);

    for (int i = pointsCount; i < size; ++i)
    {
        while (orientation(topNext(pointsStack), pointsStack.top(), A[i]) != 2)
            pointsStack.pop();

        pointsStack.push(A[i]);
    }

    return pointsStack.size();
}

int main()

{
    vector<Point2D> v = { {3, 2}, {6, 3}, {2, 5}, {5, 2}, {1, 1}, {4, 4} };

    cout << "The points in the convex hull are: \n";
    cout << solution(v) << endl;

    return 0;

}
