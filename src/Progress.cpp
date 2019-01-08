#include <mutex>

#include <crombie2/Progress.h>


using namespace crombie2;


Progress::Progress (Gtk::Box& page) {

  page.pack_start (bar, Gtk::PACK_SHRINK);
  bar.show();

  emitter.connect(sigc::mem_fun(*this, &Progress::on_update_progress));

}


namespace {

  std::mutex progress_lock {};

}


void Progress::set_progress (const std::string& text, double frac) {

  std::lock_guard<std::mutex> lock {progress_lock};
  newtext = text;
  newfrac = frac;

  emitter.emit();

}


void Progress::on_update_progress () {

  bar.set_text(newtext);
  bar.set_fraction(newfrac);

}
