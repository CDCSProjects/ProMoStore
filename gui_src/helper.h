#ifndef HELPER_H
#define HELPER_H

//!We need this constructor to conveniently load images directly from main memory. Unfortunately it is protected in gtkmm, so we use this inherited class to be able to call it.
class MyImageLoader : public Gdk::PixbufLoader{
    public:
    MyImageLoader(){};
    MyImageLoader(const Glib::ustring &image_type, bool mime_type = false):Gdk::PixbufLoader(image_type, mime_type){};
};

#endif
