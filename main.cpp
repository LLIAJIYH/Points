#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int search (int **a, int m, int n, double what, 
 bool match, unsigned int &uI, unsigned int &uJ, unsigned int starti, unsigned int startj) {
 // Поиск в матрице a[m][n] элемента с указанным значением what
 // Возвращаеются его номер строки и столбца uI, uJ, если элемент найден.
 // match - искать равный элемент или отличный от указанного.
 // Вернёт 0 - не найдено, не 0 - найдено
 if ((!m) || (!n)) return 0;
 if ((starti >= n) || (startj >= m)) return 0;
 for (unsigned int i = starti; i < n; i++)
 for (unsigned int j = startj; j < m; j++) {
  if (match == true) {
   if (a[i][i] == what) {
    uI = i; uJ = j; return 1;
   }
  }
  else if (a[i][j] != what) {
   uI = i; uJ = j; return 1;
  }
 }
 return 0;
}

void swaprows (int **a, int n, int m, unsigned int x1, unsigned int x2) {
 //Меняет в матрице a[n][m] строки с номерами x1 и x2 местами
 if ((!n) || (!m)) return; 
 if ((x1 >= n) || (x2 >= n) || (x1 == x2)) return;
  double tmp;
  for (unsigned int x = 0; x < m; x++) {
    tmp = a[x1][x];
    a[x1][x] = a[x2][x];
    a[x2][x] = tmp;
  }
  return;
};

void swapcolumns (int **a, int n, int m, unsigned int x1, unsigned int x2) {
 //Меняет в матрице a[n][m] столбцы с номерами x1 и x2 местами
 if ((!n) || (!m)) return; 
 if ((x1 >= m) || (x2 >= m) || (x1 == x2)) return;
  double tmp;
  for (unsigned int x = 0; x < n; x++) {
    tmp = a[x][x1];
    a[x][x1] = a[x][x2];
    a[x][x2] = tmp;
  }
  return;
};

double determinant (int **a, unsigned int n) {
 //Вычисление определителя квадратной матрицы a[n][n]
 unsigned int m = n;
 if (m == 0) return 0;
 if (m == 1) return a[0][0];
 if (m == 2) return (a[0][0] * a[1][1] - a[1][0] * a[0][1]);
 bool sign = false; // смена знака определителя. по умолчанию - нет
 double det = 1; // определитель
 double tmp;
 unsigned int x, y;
 for (unsigned int i = 0; i < n; i++) { // цикл по всей главной диагонали
  if (a[i][i] == 0) { // если элемент на диагонали равен 0, то ищем ненулевой элемент в матрице
   if (!search(a,m,n,0, false, y, x, i, i)) return 0; // если все элементы нулевые, то опр. = 0
   if (i != y) { // меняем i-ую строку с y-ой
    swaprows(a,m,n,i, y);
    sign = !sign;
   }
   if (i != x) { // меняем i-ый столбец с x-ым
    swapcolumns(a,m,n,i, x);
    sign = !sign;
   }
   // таким образом, в a[i][i], теперь ненулевой элемент.
  }
  // выносим элемент a[i][i] за определитель
  det *= a[i][i];
  tmp = a[i][i];
  for (x = i; x < m; x++) {
   a[i][x] = a[i][x] / tmp;
  }
  // таким образом a[i][i] теперь равен 1
  // зануляем все элементы стоящие под (i, i)-ым,
  // при помощи вычитания с опр. коеффициентом
  for (y = i + 1; y < n; y++) {
   tmp = a[y][i];
   for (x = i; x < m; x++)
    a[y][x] -= (a[i][x]*tmp);
   }
  }
  if (sign) return det*(-1);
  return det;
};


class Point
{
    public:
        Point() {}
        virtual int getX() = 0;
        virtual int getY() = 0;
        virtual int getZ() = 0;
        virtual void setX(int x_) =0;
        virtual void setY(int y_) =0;
        virtual void setZ(int z_) =0;
        virtual void print() {}
    protected:
        int x, y;
        virtual ~Point() {}
};

class Point2D: public virtual Point
{
    public:
        int getX(){ return x; }
        int getY(){ return y; }
        void setX(int x_){ x = x_; }
        void setY(int y_){ y = y_; } 
        void print() { cout<<x<<" "<<y<<endl; }
        Point2D(){ x = 0; y = 0; }
        Point2D(int x_, int y_){ x = x_; y = y_; }
        Point2D(const Point2D &other){ this->x = other.x; this->y = other.y; }
        ~Point2D(){ /* delete x; delete y; */}
};

class Point3D: public virtual Point
{
    public:
        int getX(){ return x; }
        int getY(){ return y; }
        int getZ(){ return z; }
        void setX(int x_){ x = x_; }
        void setY(int y_){ y = y_; }
        void setZ(int z_){ z = z_; } 
        void print() { cout<<x<<" "<<y<<" "<<z<<endl; }
        Point3D(){ x = 0; y = 0; z=0; }
        Point3D(int x_, int y_, int z_){ x = x_; y = y_; z = z_; }
        Point3D(const Point3D &other){ this->x = other.x; this->y = other.y; this->z = other.z; }
        ~Point3D(){}
    protected:
        int z;
};

class Figure
{
    public:
        virtual int perimeter(){}
        virtual double area(){}
        virtual double volume(){}
        virtual void print(){}
        void setX(int x, int pos){ Point3D point = points[pos]; point.setX(x); }
        void setY(int y, int pos){ Point3D point = points[pos]; point.setY(y); }
        void setZ(int z, int pos){ Point3D point = points[pos]; point.setZ(z); }
        int getX(int pos){ Point3D point = points[pos]; return points[pos].getX(); }
        int getY(int pos){ Point3D point = points[pos]; return points[pos].getY(); }
        int getZ(int pos){ Point3D point = points[pos]; return points[pos].getZ(); }
        Figure(){ cout<<"Figure constructor"<<endl; }
        ~Figure(){ cout<<"Figure destructor"<<endl; /*delete name; delete points;*/ }
    protected:
    //BUG: Добавить точки сюда и добавить методы работы с ними
        string name;
        vector<Point3D> points;
};

//TODO: РЕАЛИЗОВАТЬ КОНСТРУКТОРЫ, ДЕСТРУКТОРЫ И КОНСТРУКТОРЫ КОПИРОВАНИЯ ДЛЯ ВСЕХ ФИГУР и для класса фигуры

class Triangle: public virtual Figure
{
    public:
        int perimeter(){
                int sum = 0;
            //Очень глупый способ, но все же что-то
                sum+=sqrt(pow((this->getX(1)-this->getX(0)), 2) + pow((this->getY(1)-this->getY(0)), 2));
                sum+=sqrt(pow((this->getX(2)-this->getX(1)), 2) + pow((this->getY(2)-this->getY(1)), 2));
                sum+=sqrt(pow((this->getX(0)-this->getX(2)), 2) + pow((this->getY(0)-this->getY(2)), 2));
                return sum;
            }
        double area(){
        //отвратительная часть кода
            double half_perimeter = perimeter()/2;
            double ar = sqrt(half_perimeter*(half_perimeter - sqrt(pow((this->getX(1)-this->getX(0)), 2) - pow((this->getY(1)-this->getY(0)), 2)))*(half_perimeter - sqrt(pow((this->getX(2)-this->getX(1)), 2) - pow((this->getY(2)-this->getY(1)), 2)))*(half_perimeter - sqrt(pow((this->getX(0)-this->getX(2)), 2) - pow((this->getY(2)-this->getY(0)), 2))));
            return ar;
        }
        void print(){
            cout<<"[ Triangle ]\npoints are in: "<<endl;
            for(int i = 0; i<3;i++){
                cout<<this->getX(i)<<" "<<this->getY(i)<<endl;
            }
        }
        Triangle(){
            cout<<"Triangle constructor"<<endl;
            for(int i; i<3;i++){
                int x, y;
                cout<<"Enter "<<i<<" point"<<endl;
                cout<<"x = ";
                cin>>x;
                cout<<"y = ";
                cin>>y;
                setX(x, i);
                setY(y, i);
            }
        }
        ~Triangle(){cout<<"Triangle destructor"<<endl;}

};

// class Circle: public virtual Figure
// {
//     public:
//         int perimeter(){
//             return 2*M_PI*r;
//         }
//         double area(){
//             return M_PI*r*r;
//         }
//         void print(){
//             cout<<"[ Circle ]\nCenter at "<<points.getX(0)<<" "<<points.getY(0)<<endl;
//             cout<<"And radius is "<<r<<endl;
//         }
//         Circle(){cout<<"Circle constructor"<<endl;}
//         ~Circle(){cout<<"Circle destructor"<<endl; delete r;}
//     protected:
//         int *r;
// };

// class Rectangle: public virtual Figure
// {
//     public:
//         int perimeter(){
//             int sum = 0;
//             sum+=sqrt(pow((points.getX(1)-points.getX(0)), 2) + pow((points.getY(1)-points.getY(0)), 2));
//             sum+=sqrt(pow((points.getX(2)-points.getX(1)), 2) + pow((points.getY(2)-points.getY(1)), 2));
//             return sum*2;
//         }
//         double area(){
//             double sum = 1;
//             sum*=sqrt(pow((points.getX(1)-points.getX(0)), 2) + pow((points.getY(1)-points.getY(0)), 2));
//             sum*=sqrt(pow((points.getX(2)-points.getX(1)), 2) + pow((points.getY(2)-points.getY(1)), 2));
//             return sum;
//         }
//         void print(){
//             cout<<"[ Rectangle ]\npoints are in: "<<endl;
//             for(int i = 0; i<3;i++){
//                 cout<<points.getX(i)<<" "<<points.getY(i)<<endl;
//             }
//         }
//         Rectangle(){cout<<"Rectangle constructor"<<endl;}
//         ~Rectangle(){cout<<"Rectangle destructor"<<endl;}
// };

// class Sphere: public virtual Figure
// {
//     public:
//         double area(){
//             return 4*M_PI*r*r;
//         }
//         double volume(){
//             return (4/3)*M_PI*r*r*r;
//         }
//         void print(){
//             cout<<"[ Sphere ]\nCenter at "<<points.getX(0)<<" "<<points.getY(0)<<" "<<points.getZ(0)<<endl;
//             cout<<"And radius is "<<r<<endl;
//         }
//         Sphere(){cout<<"Sphere constructor"<<endl;}
//         ~Sphere(){cout<<"Sphere destructor"<<endl; delete r;}
//     protected:
//         int *r;
// };

// class Tetrahedron: public virtual Figure
// {
//     //РЕМАРКА
//     // первые три координаты это координаты основания, последняя вершина
//     public:
//         double volume(){
//             int **matrix;
//             matrix = new int*[4];
//             for (int i = 0; i<4; i++) {
//                 matrix[i] = new int[4];
//                 for (int j = 0; j<4; j++) { 
//                     if(i == 0){
//                         matrix[i][j] = 1;
//                     }
//                     if(i == 1){
//                         matrix[i][j] = points.getX(i);
//                     }
//                     if(i == 2){
//                         matrix[i][j] = points.getY(i);
//                     }
//                     if(i == 3){
//                         matrix[i][j] = points.getZ(i);
//                     }
//                 }
//             }
//             double det = determinant(matrix, 4);
//             return det/6;
//         }
//         int perimeter(){
//             int sum = 0;
//             sum+=sqrt(pow((points.getX(1)-points.getX(0)), 2) + pow((points.getY(1)-points.getY(0)), 2));
//             sum+=sqrt(pow((points.getX(2)-points.getX(1)), 2) + pow((points.getY(2)-points.getY(1)), 2));
//             sum+=sqrt(pow((points.getX(0)-points.getX(2)), 2) + pow((points.getY(0)-points.getY(2)), 2));
//             sum+=sqrt(pow((points.getX(3)-points.getX(0)), 2) + pow((points.getY(3)-points.getY(0)), 2));
//             sum+=sqrt(pow((points.getX(3)-points.getX(1)), 2) + pow((points.getY(3)-points.getY(1)), 2));
//             sum+=sqrt(pow((points.getX(3)-points.getX(2)), 2) + pow((points.getY(3)-points.getY(2)), 2));
//             return sum;
//         }
//         void print(){
//             cout<<"[ Tetrahedron ]\npoints are in: "<<endl;
//             for(int i = 0; i<4;i++){
//                 cout<<points.getX(i)<<" "<<points.getY(i)<<" "<<points.getZ(i)<<endl;
//             }
//         }
//         Tetrahedron(){cout<<"Tetrahedron constructor"<<endl;}
//         ~Tetrahedron(){cout<<"Tetrahedron destructor"<<endl;}
// };

// class RectangularParallelepiped: public virtual Figure
// {

//     public:
//         double volume(){
//             double sum = 1;
//             sum*=sqrt(pow((points.getX(1)-points.getX(0)), 2) + pow((points.getY(1)-points.getY(0)), 2));
//             sum*=sqrt(pow((points.getX(3)-points.getX(0)), 2) + pow((points.getY(3)-points.getY(0)), 2));
//             sum*=sqrt(pow((points.getX(4)-points.getX(0)), 2) + pow((points.getY(4)-points.getY(0)), 2));
//             return sum;
//         }
//         double area(){
//             double a, b, c;
//             a = sqrt(pow((points.getX(1)-points.getX(0)), 2) + pow((points.getY(1)-points.getY(0)), 2))*sqrt(pow((points.getX(3)-points.getX(0)), 2) + pow((points.getY(3)-points.getY(0)), 2));
//             b = sqrt(pow((points.getX(3)-points.getX(0)), 2) + pow((points.getY(3)-points.getY(0)), 2))*sqrt(pow((points.getX(4)-points.getX(0)), 2) + pow((points.getY(4)-points.getY(0)), 2));
//             c = sqrt(pow((points.getX(1)-points.getX(0)), 2) + pow((points.getY(1)-points.getY(0)), 2))*sqrt(pow((points.getX(3)-points.getX(0)), 2) + pow((points.getY(3)-points.getY(0)), 2));
//             return 2*(a+b+c);
//         }
//         void print(){
//             cout<<"[ RectangularParallelepiped ]\npoints are in: "<<endl;
//             for(int i = 0; i<7;i++){
//                 cout<<points.getX(i)<<" "<<points.getY(i)<<" "<<points.getZ(i)<<endl;
//             }
//         }
//         RectangularParallelepiped(){cout<<"RectangularParallelepiped constructor"<<endl;}
//         ~RectangularParallelepiped(){cout<<"RectangularParallelepiped destructor"<<endl;}
// };

//TODO: добавить следющие классы
// «Параллелепипед»


int main()
{
    Triangle tri;
    tri.perimeter();
    tri.area();
    return 0;
}