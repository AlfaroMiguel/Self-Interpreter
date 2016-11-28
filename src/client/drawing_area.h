#ifndef DRAWING_AREA_H
#define DRAWING_AREA_H

#include <gtkmm/drawingarea.h>
#include <gtkmm.h>
#include <goocanvasmm.h>

class LineDrawingArea: public Gtk::DrawingArea{
 public:
  LineDrawingArea(Goocanvas::Canvas* canvas);
  ~LineDrawingArea();
 private:
  Goocanvas::Canvas* canvas;
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};
#endif