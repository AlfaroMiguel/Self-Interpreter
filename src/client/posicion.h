#ifndef POSICION_H
#define POSICION_H

class Posicion{
 private:
  double x;
  double y;

  Posicion(const Posicion& otra) = delete;
  Posicion& operator=(const Posicion& otra) = delete;
 public:
  Posicion(double x, double y);
  ~Posicion();

  Posicion(const Posicion&& otra);
  Posicion& operator=(const Posicion&& otra);

  bool operator==(const Posicion& otra) const;
  bool operator>(const Posicion& otra) const;
  bool operator<(const Posicion& otra) const;
  Posicion& operator+=(const Posicion& otra);
  double get_x() const;
  double get_y() const;
  void add_x(double x);
  void add_y(double y);
  void set_x(double x);
  void set_y(double y);
};
#endif