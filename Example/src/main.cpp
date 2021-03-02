#include <Nyx/Nyx.hpp>

int main() {
	auto renderer = Nyx::init();

	auto window = std::make_shared<Nyx::Window>("Nyx Demo", 640, 480);
	window->makeCurrentContext();

	while (true) {
		window->update();
	}
}