//created by Wang Jianwei on 01 Dec 2012
#ifndef ABSTRACTINTERPOLATOR_H
#define ABSTRACTINTERPOLATOR_H
#include <vector>

namespace utilities{
	class AbstractInterpolator{

		enum interpolAlgo{LINEAR,LOGLINEAR};

	public:

		AbstractInterpolator();

		template <class T>
		std::vector<T> interpolate(T startPoint, T endPoint, std::vector<long> JDNs, interpolAlgo algo);
		
	};
}
#endif