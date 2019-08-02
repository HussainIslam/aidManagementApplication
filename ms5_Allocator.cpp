#include "Good.h"
#include "Perishable.h"

namespace aid {

	// creates an empty good
	//
	iGood* CreateGood() {
		return new Good();
	}

	// creates an empty perishable good
	//
	iGood* CreatePerishable() {
		return new Perishable();
	}
}
