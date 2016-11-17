#ifndef POSICION_H
#define POSICION_H

class Posicion{
 private:
  double x;
  double y;
 public:
  Posicion(double x, double y);
  ~Posicion();

  double get_x();
  double get_y();
  void add_x(double x);
  void add_y(double y);
};
#endif