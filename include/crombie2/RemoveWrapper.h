#ifndef CROMBIE2_REMOVEWRAPPER_H
#define CROMBIE2_REMOVEWRAPPER_H


#include <functional>
#include <list>

#include <gtkmm/box.h>
#include <gtkmm/button.h>


namespace crombie2 {
  /**
     @brief A wrapper for removing objects from a list

     We want the wrapper to act just like the class inside of the wrapper.
     This means this can only wrap classes with a virtual destructor.
  */

  template<class T>
    class RemoveWrapper : public T {

  public:
    /**
       @param list A reference to the list containing this object
       @param args The arguments to pass to the parent class contructor
    */
    template<typename ... Args>
      RemoveWrapper (std::list<RemoveWrapper<T>>& list, Args ... args) :
    T {args ...}, list {list} {
      remove.signal_clicked().
        connect(sigc::mem_fun(*this, &RemoveWrapper<T>::on_remove));
      copy.signal_clicked().
        connect(sigc::mem_fun(*this, &RemoveWrapper<T>::on_copy));

    }

    /// Destructor must override to ensure that parent class has virtual destructor
    ~RemoveWrapper () override = default;

    /// Add a function to call on removal
    void also_remove (std::function<void()> function) {
      functions.push_back(function);
    };

    void draw_removable (Gtk::Box& page) {
      T::draw(page);

      page.pack_start(button_box, Gtk::PACK_SHRINK);
      button_box.show();

      if (not buttoned) {
        button_box.pack_start(remove, Gtk::PACK_SHRINK);
        button_box.pack_start(copy, Gtk::PACK_SHRINK);
        buttoned = true;
      }

      remove.show();
      copy.show();
    }

    /// Need to pack and show button
    Gtk::Button remove {"Remove"};

  private:
    /// Copy an element to the end of the list
    Gtk::Button copy {"Copy"};

    Gtk::VBox button_box {};

    bool buttoned {false};

    std::list<RemoveWrapper<T>>& list;

    std::list<std::function<void()>> functions {};

    /// Removes this element from the list holding it
    void on_remove () {
      for (auto& function : functions)
        function();
      list.remove_if([this] (auto& element) { return &element == this; });
    }

    void on_copy () {
      if (functions.size()) {
        throw;
      }

      list.emplace_back(list, T(*this));
    }


  };
}


#endif
