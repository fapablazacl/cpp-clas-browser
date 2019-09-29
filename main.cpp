
#define BOOST_DI_CFG_DIAGNOSTICS_LEVEL 2
#include "boost/di.hpp"

#include <iostream>

namespace di = boost::di;

struct renderer {
  int device;
};

class iview {
public:
    iview() {
        std::cout << "IView::IView()" << std::endl;
    }

  virtual ~iview() noexcept = default;
  virtual void update() =0;
};

class gui_view: public iview {
public:
  gui_view(std::string title, const renderer&) {
      std::cout << "    GuiView::GuiView()" << std::endl;
  }
  void update() override {}
};

class text_view: public iview {
public:
    text_view() {
        std::cout << "    TextView::TextView()" << std::endl;
    }

  void update() override {}
};


class model {};

class controller {
 public:
  controller(model&, iview&) {
      std::cout << "Controller::Controller()" << std::endl;
  }
};

class user {};

class app {
 public:
  app(controller&, user&) {
      std::cout << "Application::Application()" << std::endl;
  }
};

int main() {
  /**
   * renderer renderer_;
   * view view_{"", renderer_};
   * model model_;
   * controller controller_{model_, view_};
   * user user_;
   * app app_{controller_, user_};
   */


  auto useGuiView = false;


  auto injector = di::make_injector(
      di::bind<iview>.to([useGuiView](const auto &injector) -> iview& {
          if (useGuiView) {
              return injector.template create<gui_view&>();
          }
          
          return injector.template create<text_view&>();
      })
      ,di::bind<int>.to(42)
  );

  injector.create<app>();
}
