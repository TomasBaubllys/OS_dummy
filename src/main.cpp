/* Virtual - Dummy OS (OS4)
 * Authors: Tomas Baublys and Goda Gutparakyte
 * */

//#include "../include/virtual_machine.h"
//#include "../include/menu.h"
#include "../include/io.h"
#include <assert.h>
#include "../include/real_machine.h"
#include "../include/kernel.h"

int main(int argc, char* argv[]) {
	srand(time(nullptr));
	// init start stop
	Real_Machine real_machine;
	Kernel kernel(&real_machine);
	kernel.run();

	/*Real_Machine real_machine;
    assert(init_real_machine(&real_machine) == 0);
	menu(&real_machine);
    destroy_real_machine(&real_machine);*/
	return 0;
}
