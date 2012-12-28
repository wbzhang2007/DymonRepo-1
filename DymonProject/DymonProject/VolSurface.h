//created by Hu Kun on 30 Nov 2012

#ifndef VOLSURFACE_H
#define VOLSURFACE_H
#include "currency.h"
#include "date.h"
#include "AbstractInstrument.h"
#include <vector>
#include "zero.h"
#include <tuple>
#include <iterator>
#include "RecordHelper.h"
#include "DiscountCurve.h"
#include "AbstractInstrument.h"

using namespace utilities;
using namespace std;
using namespace enums;
using namespace instruments;

namespace instruments {

	class VolSurface {
		
	public:

		VolSurface();
		~VolSurface();

	};

}
#endif