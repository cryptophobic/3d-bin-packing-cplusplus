#include "../Data.h"

using namespace DataTypes;

namespace SinglePack
{
	struct ExtremePoint 
	{
	public:
		int box;
		Axis* dot;
	};

	struct Relation
	{
	public:
		bool front;
		bool right;
		bool top;
	};
}