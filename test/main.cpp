#ifdef __APPLE__

#include <mach-o/dyld.h>
#include <sys/proc_info.h>
#include <libproc.h>
#include <zconf.h>

#endif

#include <iostream>
#include <Window.h>

int main() {
    graphics::Window* window = new graphics::Window("Hi", 1280, 720);
	
	return 0;
}