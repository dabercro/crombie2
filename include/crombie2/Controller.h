#ifndef CROMBIE2_CONTROLLER_H
#define CROMBIE2_CONTROLLER_H

#include <list>

#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>

#include <crombie2/ConfigModel.h>
#include <crombie2/ConfigPage.h>
#include <crombie2/GuiConfigurable.h>
#include <crombie2/UpdateBox.h>

namespace crombie2 {
  class Controller {
  public:

    class ConfigRef {
    public:
      ConfigRef (GuiConfigurable& config, const std::string& label);
      GuiConfigurable& config;
      Gtk::Label label;
      Gtk::Entry entry {};
      Gtk::HBox box {};
      void show ();
    };

    /// Hold a reference to the page to draw on
    Controller (ConfigPage& page, ConfigModel& model);
    virtual ~Controller () {}


    /// Get a reference back to the page for something else to draw on
    ConfigPage& get_page ();

    /// Add the update button
    void add_update ();

    /// Register a configurable to be updated with the update button
    ConfigRef& register_configurable (GuiConfigurable& config);

    /// Register a configurable to be updated with the update button
    void register_configurable (GuiConfigurable& config, Gtk::Box& box);

    /// Take configurable out
    void unregister_configurable (GuiConfigurable& config);

    static const std::string last_tag;

  private:

    void on_update ();

    UpdateBox updatebox {};

    ConfigPage& page;
    ConfigModel& model;

    std::list<ConfigRef> configurables {};

  };
}

#endif
